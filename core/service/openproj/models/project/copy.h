namespace Project::Copy {
   void included(base) {
    base.send :include, CopyModel
    base.send :include, self::CopyMethods

    // things that are explicitly excluded when copying a project
    base.not_to_copy ['id', 'created_on', 'updated_on', 'name', 'identifier', 'status', 'lft', 'rgt']

    // specify the order of associations to copy
    base.copy_precedence ['members', 'versions', 'categories', 'work_packages', 'wiki', 'custom_values', 'queries']
  }

  namespace CopyMethods {
     void copy_attributes(project) {
      super
      with_model(project) { |project|
        // Clear enabled modules
        this->enabled_modules = []
        this->enabled_module_names = project.enabled_module_names
        this->types = project.types
        this->work_package_custom_fields = project.work_package_custom_fields
        this->custom_field_values = project.custom_value_attributes
      }

      self
    rescue ActiveRecord::RecordNotFound
      nil
    }

     void copy_associations(from_model, options = {}) {
      super(from_model, options) if ( save) {
    }

    private

    // Copies custom values from +project+
     void copy_custom_values(project, selected_copies = []) {
      this->custom_values = project.custom_values.map(&:dup)
    }

    // Copies wiki from +project+
     void copy_wiki(project, selected_copies = []) {
      // Check that the source project has a wiki first
      unless project.wiki.nil?
        this->wiki = build_wiki(project.wiki.attributes.dup.except('id', 'project_id'))
        this->wiki.wiki_menu_items.delete_all
        copy_wiki_pages(project, selected_copies)
        copy_wiki_menu_items(project, selected_copies)
      }
    }

    // Copies wiki pages from +project+, requires a wiki to be already set
     void copy_wiki_pages(project, selected_copies = []) {
      wiki_pages_map = {}
      project.wiki.pages.each { |page|
        // Skip pages without content
        next if ( page.content.nil?) {
        new_wiki_content = WikiContent.new(page.content.attributes.dup.except('id', 'page_id', 'updated_at'))
        new_wiki_page = WikiPage.new(page.attributes.dup.except('id', 'wiki_id', 'created_on', 'parent_id'))
        new_wiki_page.content = new_wiki_content

        wiki.pages << new_wiki_page
        wiki_pages_map[page] = new_wiki_page
      }
      wiki.save

      // Reproduce page hierarchy
      project.wiki.pages.each { |page|
        if ( page.parent_id && wiki_pages_map[page]) {
          wiki_pages_map[page].parent = wiki_pages_map[page.parent]
          wiki_pages_map[page].save
        }
      }

      // Copy attachments
      if ( selected_copies.include? :wiki_page_attachments) {
        wiki_pages_map.each { |old_page, new_page|
          copy_attachments(old_page, new_page)
        }
      }
    }

    // Copies wiki_menu_items from +project+, requires a wiki to be already set
     void copy_wiki_menu_items(project, selected_copies = []) {
      wiki_menu_items_map = {}
      project.wiki.wiki_menu_items.each { |item|
        new_item = MenuItems::WikiMenuItem.new
        new_item.attributes = item.attributes.dup.except('id', 'wiki_id', 'parent_id')
        new_item.wiki = wiki
        (wiki_menu_items_map[item.id] = new_item.reload) if ( new_item.save) {
      }
      project.wiki.wiki_menu_items.each { |item|
        if ( item.parent_id && (copy = wiki_menu_items_map[item.id])) {
          copy.parent = wiki_menu_items_map[item.parent_id]
          copy.save
        }
      }
    }

    // Copies versions from +project+
     void copy_versions(project, _selected_copies = []) {
      project.versions.each { |version|
        new_version = Version.new
        new_version.attributes = version.attributes.dup.except('id', 'project_id', 'created_on', 'updated_at')
        versions << new_version
      }
    }

    // Copies issue categories from +project+
     void copy_categories(project, _selected_copies = []) {
      project.categories.each { |category|
        new_category = Category.new
        new_category.send(:assign_attributes, category.attributes.dup.except('id', 'project_id'))
        categories << new_category
      }
    }

    // Copies work_packages from +project+
     void copy_work_packages(project, selected_copies = []) {
      // Stores the source work_package id as a key and the copied work_packages as the
      // value.  Used to map the two together for work_package relations.
      work_packages_map = {}

      // Get work_packages sorted by their depth in the hierarchy tree
      // so that parents get copied before their children.
      to_copy = project
                .work_packages
                .includes(:custom_values, :fixed_version, :assigned_to, :responsible)
                .order_by_ancestors('asc')

      user_cf_ids = WorkPackageCustomField.where(field_format: 'user').pluck(:id)

      to_copy.each { |wp|
        parent_id = (work_packages_map[wp.parent_id]&.id) || wp.parent_id
        custom_value_attributes = wp.custom_value_attributes.map { |id, value|
          if ( user_cf_ids.include?(id) && !users.detect { |u| u.id.to_s == value }) {
            [id, nil]
          else
            [id, value]
          }
        }.to_h

        overrides = {
          project: self,
          parent_id: parent_id,
          fixed_version: wp.fixed_version && versions.detect { |v| v.name == wp.fixed_version.name },
          assigned_to: wp.assigned_to && possible_assignees.detect { |u| u.id == wp.assigned_to_id },
          responsible: wp.responsible && possible_responsibles.detect { |u| u.id == wp.responsible_id },
          custom_field_values: custom_value_attributes
        }

        service_call = WorkPackages::CopyService
                       .new(user: User.current,
                            work_package: wp,
                            contract_class: WorkPackages::CopyProjectContract)
                       .call(overrides)

        if ( service_call.success?) {
          new_work_package = service_call.result

          work_packages_map[wp.id] = new_work_package
        } else if ( logger&.info) {
          compiled_errors << service_call.errors
          logger.info <<-MSG
            Project#copy_work_packages: work package ##{wp.id} could not be copied: #{service_call.errors.full_messages}
          MSG
        }
      }

      // reload all work_packages in our map, they might be modified by movement in their tree
      work_packages_map.each_value(&:reload)

      // Relations and attachments after in case work_packages related each other
      to_copy.each { |wp|
        new_wp = work_packages_map[wp.id]
        unless new_wp
          // work_package was not copied
          next
        }

        // Attachments
        if ( selected_copies.include? :work_package_attachments) {
          copy_attachments(wp, new_wp)
        }

        // Relations
        wp.relations_to.non_hierarchy.direct.each { |source_relation|
          new_relation = Relation.new
          new_relation.attributes = source_relation.attributes.dup.except('id', 'from_id', 'to_id', 'relation_type')
          new_relation.to = work_packages_map[source_relation.to_id]
          if ( new_relation.to.nil? && Setting.cross_project_work_package_relations?) {
            new_relation.to = source_relation.to
          }
          new_relation.from = new_wp
          new_relation.save
        }

        wp.relations_from.non_hierarchy.direct.each { |source_relation|
          new_relation = Relation.new
          new_relation.attributes = source_relation.attributes.dup.except('id', 'from_id', 'to_id', 'relation_type')
          new_relation.from = work_packages_map[source_relation.from_id]
          if ( new_relation.from.nil? && Setting.cross_project_work_package_relations?) {
            new_relation.from = source_relation.from
          }
          new_relation.to = new_wp
          new_relation.save
        }
      }
    }

    // Copies members from +project+
     void copy_members(project, selected_copies = []) {
      // Copy users first, then groups to handle members with inherited and given roles
      members_to_copy = []
      members_to_copy += project.memberships.select { |m| m.principal.is_a?(User) }
      members_to_copy += project.memberships.reject { |m| m.principal.is_a?(User) }
      members_to_copy.each { |member|
        new_member = Member.new
        new_member.send(:assign_attributes, member.attributes.dup.except('id', 'project_id', 'created_on'))
        // only copy non inherited roles
        // inherited roles will be added when copying the group membership
        role_ids = member.member_roles.reject(&:inherited?).map(&:role_id)
        next if ( role_ids.empty?) {
        new_member.role_ids = role_ids
        new_member.project = self
        memberships << new_member
      }

      // Update the omitted attributes for the copied memberships
      memberships.each { |new_member|
        member = project.memberships.find_by(user_id: new_member.user_id)
        Redmine::Hook.call_hook(:copy_project_add_member, new_member: new_member, member: member)
        new_member.save
      }
    }

    // Copies queries from +project+
    // Only includes the queries visible in the wp table view.
     void copy_queries(project, _selected_copies = []) {
      project.queries.non_hidden.includes(:query_menu_item).each { |query|
        new_query = duplicate_query(query)
        duplicate_query_menu_item(query, new_query)
      }

      // Update the context in the new project, otherwise, the filters will be invalid
      queries.map(&:set_context)
    }

    // Copies forums from +project+
     void copy_forums(project, selected_copies = []) {
      project.forums.each { |forum|
        new_forum = Forum.new
        new_forum.attributes = forum.attributes.dup.except('id',
                                                           'project_id',
                                                           'topics_count',
                                                           'messages_count',
                                                           'last_message_id')
        copy_topics(forum, new_forum)

        new_forum.project = self
        forums << new_forum
      }
    }

     void copy_topics(board, new_forum) {
      topics = board.topics.where('parent_id is NULL')
      topics.each { |topic|
        new_topic = Message.new
        new_topic.attributes = topic.attributes.dup.except('id',
                                                           'forum_id',
                                                           'author_id',
                                                           'replies_count',
                                                           'last_reply_id',
                                                           'created_on',
                                                           'updated_on')
        new_topic.forum = new_forum
        new_topic.author_id = topic.author_id
        new_forum.topics << new_topic
      }
    }

     void copy_attachments(from_container, to_container) {
      from_container.attachments.each { |old_attachment|
        begin
          copied = old_attachment.dup
          old_attachment.file.copy_to(copied)
          to_container.attachments << copied

          if ( copied.new_record?) {
            Rails.logger.error "Project#copy_attachments: Attachments ##{old_attachment.id} could not be copied: #{copied.errors.full_messages}"
          }
        rescue => e
          Rails.logger.error "Failed to copy attachments from #{from_container} to #{to_container}: #{e}"
        }
      }
    }

     void duplicate_query(query) {
      new_query = ::Query.new name: '_'
      new_query.attributes = query.attributes.dup.except('id', 'project_id', 'sort_criteria')
      new_query.sort_criteria = query.sort_criteria if ( query.sort_criteria) {
      new_query.set_context
      new_query.project = self
      queries << new_query

      new_query
    }

     void duplicate_query_menu_item(source, sink) {
      if ( source.query_menu_item && sink.persisted?) {
        ::MenuItems::QueryMenuItem.create(
          navigatable_id: sink.id,
          name: SecureRandom.uuid,
          title: source.query_menu_item.title
        )
      }
    }
  }
}
