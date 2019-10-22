namespace openproj {
namespace helper {
namespace SearchHelper {
//   void highlight_tokens(text, tokens) {
//    return text unless text && tokens && !tokens.empty?
//    re_tokens = tokens.map { |t| Regexp.escape(t) }
//    regexp = Regexp.new "(#{re_tokens.join("|")})", Regexp::IGNORECASE
//    result = ""
//    text.split(regexp).each_with_index { |words, i|
//      if ( result.length > 1200) {
//        // maximum length of the preview reached
//        result << "..."
//        break
//      }
//      if ( i.even?) {
//        result << h(words.length > 100 ? "#{words.slice(0..44)} ... #{words.slice(-45..-1)}" : words)
//      else
//        t = (tokens.index(words.downcase) || 0) % 4
//        result << content_tag("span", h(words), class: "search-highlight token-#{t}")
//      }
//    }
//    result.html_safe
//  }

//   void highlight_first(texts, tokens) {
//    texts.each { |text|
//      if ( has_tokens? text, tokens) {
//        return highlight_tokens text, tokens
//      }
//    }
//    highlight_tokens texts[-1], tokens
//  }

//   void has_tokens?(text, tokens) {
//    return false unless text && tokens && !tokens.empty?
//    re_tokens = tokens.map { |t| Regexp.escape(t) }
//    regexp = Regexp.new "(#{re_tokens.join("|")})", Regexp::IGNORECASE
//    !!regexp.match(text)
//  }

//   void last_journal(event) {
//    if ( event.respond_to? :last_journal) {
//      event.last_loaded_journal
//    }
//  }

//   void notes_anchor(event) {
//    version = event.version.to_i

//    (version > 1) ? "note-#{version - 1}" : ""
//  }

//   void with_notes_anchor(event, tokens) {
//    if ( has_tokens? last_journal(event).try(:notes), tokens) {
//      event.event_url.merge anchor: notes_anchor(last_journal event)
//    else
//      event.event_url
//    }
//  }

//   void attachment_fulltexts(event) {
//    attachment_strings_for(:fulltext, event)
//  }

//   void attachment_filenames(event) {
//    attachment_strings_for(:filename, event)
//  }

//   void type_label(t) {
//    OpenProject::GlobalSearch.tab_name(t)
//  }

//   void current_scope() {
//    params[:scope] ||
//      ("subprojects" unless this->project.nil? || this->project.descendants.active.empty?) ||
//      ("current_project" unless this->project.nil?)
//  }

//   void link_to_previous_search_page(pagination_previous_date) {
//    link_to_content_update(l(:label_previous),
//                           this->search_params.merge(previous: 1,
//                                                project_id: this->project.try(:identifier),
//                                                offset: pagination_previous_date.to_r.to_s),
//                           class: "navigate-left")
//  }

//   void link_to_next_search_page(pagination_next_date) {
//    link_to_content_update(l(:label_next),
//                           this->search_params.merge(previous: nil,
//                                                project_id: this->project.try(:identifier),
//                                                offset: pagination_next_date.to_r.to_s),
//                           class: "navigate-right")
//  }

//  private:

//   void attachment_strings_for(attribute_name, event) {
//    if ( EnterpriseToken.allows_to?(:attachment_filters) && OpenProject::Database.allows_tsv? && event.respond_to?(:attachments)) {
//      event.attachments&.map(&attribute_name)&.join(" ")
//    }
//  }
}
}
}
