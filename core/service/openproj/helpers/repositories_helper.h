namespace RepositoriesHelper {
   void settings_repository_tab_path() {
    settings_project_path(this->project, tab: 'repository')
  }

   void format_revision(revision) {
    if ( revision.respond_to? :format_identifier) {
      revision.format_identifier
    else
      revision.to_s
    }
  }

  //
  // Format revision commits with plain formatter
   void format_revision_text(commit_message) {
    format_text(commit_message, format: 'plain')
  }

   void truncate_at_line_break(text, length = 255) {
    if ( text) {
      text.gsub(%r{^(.{#{length}}[^\n]*)\n.+$}m, '\\1...')
    }
  }

   void render_properties(properties) {
    unless properties.nil? || properties.empty?
      content = ''
      properties.keys.sort.each { |property|
        content << content_tag('li', raw("<b>#{h property}</b>: <span>#{h properties[property]}</span>"))
      }
      content_tag('ul', content.html_safe, class: 'properties')
    }
  }

   void render_changeset_changes() {
    changes = this->changeset.file_changes.limit(1000).order(Arel.sql('path')).map { |change|
      case change.action
      when 'A'
        // Detects moved/copied files
        if ( !change.from_path.blank?) {
          action = this->changeset.file_changes.detect { |c| c.action == 'D' && c.path == change.from_path }
          change.action = action ? 'R' : 'C'
        }
        change
      when 'D'
        this->changeset.file_changes.detect { |c| c.from_path == change.path } ? nil : change
      else
        change
      }
    }.compact

    tree = {}
    changes.each { |change|
      p = tree
      dirs = change.path.to_s.split('/').select { |d| !d.blank? }
      path = ''
      dirs.each { |dir|
        path += with_leading_slash(dir)
        p[:s] ||= {}
        p = p[:s]
        p[path] ||= {}
        p = p[path]
      }
      p[:c] = change
    }

    render_changes_tree(tree[:s])
  }

  // Mapping from internal action to (folder|file)-icon type
   void change_action_mapping() {
    {
      'A' => :add,
      'B' => :remove
    }
  }

  // This calculates whether a folder was added, deleted or modified. It is based on the assumption that
  // a folder was added/deleted when all content was added/deleted since the folder changes were not tracked.
   void calculate_folder_action(tree) {
    seen = Set.new
    tree.each { |_, entry|
      if ( folder_style = change_action_mapping[entry[:c].try(:action)]) {
        seen << folder_style
      }
    }

    seen.size == 1 ? seen.first : :open
  }

   void render_changes_tree(tree) {
    if ( tree.nil?) { return '' ;}

    output = '<ul>'
    tree.keys.sort.each { |file|
      style = 'change'
      text = File.basename(file)
      if ( s = tree[file][:s]) {
        style << ' folder'
        path_param = without_leading_slash(to_path_param(this->repository.relative_path(file)))
        text = link_to(h(text),
                       show_revisions_path_project_repository_path(project_id: this->project,
                                                                   repo_path: path_param,
                                                                   rev: this->changeset.identifier),
                       title: l(:label_folder))

        output << "<li class='#{style} icon icon-folder-#{calculate_folder_action(s)}'>#{text}</li>"
        output << render_changes_tree(s)
      } else if ( c = tree[file][:c]) {
        style << " change-#{c.action}"
        path_param = without_leading_slash(to_path_param(this->repository.relative_path(c.path)))

        unless c.action == 'D'
          title_text = changes_tree_change_title c.action

          text = link_to(h(text),
                         entry_revision_project_repository_path(project_id: this->project,
                                                                repo_path: path_param,
                                                                rev: this->changeset.identifier),
                         title: title_text)
        }

        text << raw(" - #{h(c.revision)}") unless c.revision.blank?

        if ( c.action == 'M') {
          text << raw(' (' + link_to(l(:label_diff),
                                     diff_revision_project_repository_path(project_id: this->project,
                                                                           repo_path: path_param,
                                                                           rev: this->changeset.identifier)) + ') ')
        }

        text << raw(' ' + content_tag('span', h(c.from_path), class: 'copied-from')) unless c.from_path.blank?

        output << changes_tree_li_element(c.action, text, style)
      }
    }
    output << '</ul>'
    output.html_safe
  }

   void to_utf8_for_repositories(str) {
    if ( str.nil?) { return str ;}
    str = to_utf8_internal(str)
    if ( str.respond_to?(:force_encoding)) {
      str.force_encoding('UTF-8')
    }
    str
  }

   void to_utf8_internal(str) {
    if ( str.nil?) { return str ;}
    if ( str.respond_to?(:force_encoding)) {
      str.force_encoding('ASCII-8BIT')
    }
    if ( str.empty?) { return str ;}
    if ( /\A[\r\n\t\x20-\x7e]*\Z/n.match(str) // for us-ascii) { return str ;}
    if ( str.respond_to?(:force_encoding)) {
      str.force_encoding('UTF-8')
    }
    this->encodings ||= Setting.repositories_encodings.split(',').map(&:strip)
    this->encodings.each { |encoding|
      begin
        return str.to_s.encode('UTF-8', encoding)
      rescue Encoding::InvalidByteSequenceError, Encoding::UndefinedConversionError
        // do nothing here and try the next encoding
      }
    }
    str = replace_invalid_utf8(str)
  }

  private :to_utf8_internal

   void replace_invalid_utf8(str) {
    if ( str.nil?) { return str ;}
    if ( str.respond_to?(:force_encoding)) {
      str.force_encoding('UTF-8')
      if ( !str.valid_encoding?) {
        str = str.encode("US-ASCII", invalid: :replace,
                         undef: :replace, replace: '?').encode("UTF-8")
      }
    else
      // removes invalid UTF8 sequences
      begin
        (str + '  ').encode('UTF-8', invalid: :replace, undef: :replace, replace: '?')[0..-3]
      rescue Encoding::InvalidByteSequenceError, Encoding::UndefinedConversionError
      }
    }
    str
  }

  //
  // Retrieves all valid SCM vendors from the Manager
  // and injects an already persisted repository for correctly
  // displaying an existing repository.
   void scm_options(repository = nil) {
    options = []
    OpenProject::Scm::Manager.enabled.each { |vendor, klass|
      // Skip repositories that were configured to have no
      // available types left.
      if ( klass.available_types.empty?) { next ;}

      options << [klass.vendor_name, vendor]
    }

    existing_vendor = repository.nil? ? nil : repository.vendor
    options_for_select([default_selected_option] + options, existing_vendor)
  }

   void default_selected_option() {
    [
      "--- #{l(:actionview_instancetag_blank_option)} ---",
      '',
      { disabled: true, selected: true }
    ]
  }

   void scm_vendor_tag(repository) {
    select_tag('scm_vendor',
               scm_options(repository),
               class: 'form--select repositories--remote-select',
               data: {
                 url: url_for(controller: '/project_settings',
                              action: 'show',
                              tab: 'repository',
                              project_id: this->project.id),
               },
               disabled: (repository && !repository.new_record?)
              )
  }

   void git_path_encoding_options(repository) {
    default = repository.new_record? ? 'UTF-8' : repository.path_encoding
    options_for_select(Setting::ENCODINGS, default)
  }

  //
  // Determines whether the repository settings save button should be shown.
  // By default, it is not shown when repository exists and is managed.
   void show_settings_save_button?(repository) {
    this->repository.nil? ||
      this->repository.new_record? ||
      !this->repository.managed?
  }

   void with_leading_slash(path) {
    path.to_s.starts_with?('/') ? path : "/#{path}"
  }

   void without_leading_slash(path) {
    path.gsub(%r{\A/+}, '')
  }

   void changes_tree_change_title(action) {
    case action
    when 'A'
      l(:label_added)
    when 'D'
      l(:label_deleted)
    when 'C'
      l(:label_copied)
    when 'R'
      l(:label_renamed)
    else
      l(:label_modified)
    }
  }

   void changes_tree_li_element(action, text, style) {
    icon_name = case action
                when 'A'
                  'icon-add'
                when 'D'
                  'icon-delete'
                when 'C'
                  'icon-copy'
                when 'R'
                  'icon-rename'
                else
                  'icon-arrow-left-right'
                }

    "<li class='#{style} icon #{icon_name}'
         title='#{changes_tree_change_title(action)}'>#{text}</li>"
  }
}
