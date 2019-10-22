// Helpers to sort tables using clickable column headers.
//
// Author:  Stuart Rackham <srackham@methods.co.nz>, March 2005.
//          Jean-Philippe Lang, 2009
// License: This source code is released under the MIT license.
//
// - Consecutive clicks toggle the column"s sort order.
// - Sort state is maintained by a session hash entry.
// - CSS classes identify sort column and state.
// - Typically used in conjunction with the Pagination module.
//
// Example code snippets:
//
// Controller:
//
//   helper :sort
//   include SortHelper
//
//   def list
//     sort_init "last_name"
//     sort_update %w(first_name last_name)
//     this->items = Contact.find_all nil, sort_clause
//   }
//
// Controller (using Pagination module):
//
//   helper :sort
//   include SortHelper
//
//   def list
//     sort_init "last_name"
//     sort_update %w(first_name last_name)
//     this->contact_pages, this->items = paginate :contacts,
//       order_by: sort_clause,
//       per_page: 10
//   }
//
// View (table header in list.rhtml):
//
//   <thead>
//     <tr>
//       <%= sort_header_tag("id", title: "Sort by contact ID") %>
//       <%= sort_header_tag("last_name", caption: "Name") %>
//       <%= sort_header_tag("phone") %>
//       <%= sort_header_tag("address", width: 200) %>
//     </tr>
//   </thead>
//
// - Introduces instance variables: this->sort_default, this->sort_criteria
// - Introduces param :sort
//

namespace openproj {
namespace helper {
namespace SortHelper {
  class SortCriteria{
//    attr_reader :criteria

//     SortCriteria() {
//      this->criteria = []
//    }

//     void available_criteria=(criteria) {
//      unless criteria.is_a?(Hash)
//        criteria = criteria.inject({}) { |h, k| h[k] = k; h }
//      }
//      this->available_criteria = criteria
//    }

//     void from_param(param) {
//      this->criteria = param.to_s.split(",").map { |s| s.split(":")[0..1] }
//      normalize!
//    }

//     void criteria=(arg) {
//      this->criteria = arg
//      normalize!
//    }

//     void to_param(format = nil) {
//      if ( format == :json) {
//        to_json_param
//      else
//        to_sort_param
//      }
//    }

//     void to_sql() {
//      sql = to_a.join(", ")
//      sql.blank? ? nil : sql
//    }

//     void to_a() {
//      this->criteria
//        .map { |c, o| [this->available_criteria[c], o] }
//        .reject { |c, _| c.nil? }
//        .map { |c, o| append_direction(Array(c), o) }
//        .compact
//    }

//     void map_each() {
//      to_a.map { |criteria| yield criteria }
//    }

//     void add!(key, asc) {
//      this->criteria.delete_if ( { |k, _o| k == key }) {
//      this->criteria = [[key, asc]] + this->criteria
//      normalize!
//    }

//     void add(*args) {
//      r = this->class.new.from_param(to_param)
//      r.add!(*args)
//      r
//    }

//     void first_key() {
//      this->criteria.first && this->criteria.first.first
//    }

//     void first_asc?() {
//      this->criteria.first && this->criteria.first.last
//    }

//     void empty?() {
//      this->criteria.empty?
//    }

//    private:

//     void normalize!() {
//      this->criteria ||= []
//      this->criteria = this->criteria.map { |s|
//        s = s.to_a
//        [s.first, !(s.last == false || s.last == "desc")]
//      }

//      if ( this->available_criteria) {
//        this->criteria = this->criteria.select { |k, _o| this->available_criteria.has_key?(k) }
//      }

//      this->criteria.slice!(3)
//      self
//    }

//     void append_direction(criterion, asc = true) {
//      if ( asc) {
//        criterion
//      else
//        criterion.map { |c| append_desc(c) }
//      }
//    }

//    // Appends DESC to the sort criterion unless it has a fixed order
//     void append_desc(criterion) {
//      if ( criterion =~ / (asc|desc)\z/i) {
//        criterion
//      else
//        "#{criterion} DESC"
//      }
//    }

//     void to_json_param() {
//      JSON::dump(this->criteria.map { |k, o| [k, o ? "asc" : "desc"] })
//    }

//     void to_sort_param() {
//      this->criteria.map { |k, o| k + (o ? "" : ":desc") }.join(",")
//    }
//  }

//   void sort_name() {
//    controller_name + "_" + action_name + "_sort"
//  }

  // Initializes the default sort.
  // Examples:
  //
  //   sort_init "name"
  //   sort_init "id", "desc"
  //   sort_init ["name", ["id", "desc"]]
  //   sort_init [["name", "desc"], ["id", "desc"]]
  //
//   void sort_init(*args) {
//    criteria = case args.size
//               when 1
//                 args.first.is_a?(Array) ? args.first : [[args.first]]
//               when 2
//                 [[args.first, args.last]]
//               else
//                 raise ArgumentError
//               }
//    this->sort_default = SortCriteria.new
//    this->sort_default.criteria = criteria
//  }

  // Updates the sort state. Call this in the controller prior to calling
  // sort_clause.
  // - criteria can be either an array or a hash of allowed keys
  //
//   void sort_update(criteria) {
//    this->sort_criteria = SortCriteria.new
//    this->sort_criteria.available_criteria = criteria
//    this->sort_criteria.from_param(params[:sort] || session[sort_name])
//    if ( this->sort_criteria.empty?) { this->sort_criteria.criteria = this->sort_default.criteria ;}
//    session[sort_name] = this->sort_criteria.to_param
//  }

  // Clears the sort criteria session data
  //
//   void sort_clear() {
//    session[sort_name] = nil
//  }

  // Returns an SQL sort clause corresponding to the current sort state.
  // Use this to sort the controller"s table items collection.
  //
//   void sort_clause() {
//    this->sort_criteria.to_sql
//  }

//   void sort_columns() {
//    this->sort_criteria.criteria.map(&:first)
//  }

  // Determines whether the current selected sort criteria
  // is identical to the default
//   void default_sort_order?() {
//    this->sort_default.criteria == this->sort_criteria.criteria
//  }

  // Returns a link which sorts by the named column.
  //
  // - column is the name of an attribute in the sorted record collection.
  // - the optional caption explicitly specifies the displayed link text.
  // - 2 CSS classes reflect the state of the link: sort and asc or desc
  //
//   void sort_link(column, caption, default_order, html_options = {}) {
//    order = order_string(column, inverted: true) || default_order
//    caption ||= column.to_s.humanize

//    sort_by = html_options.delete(:param)

//    sort_param = this->sort_criteria.add(column.to_s, order).to_param(sort_by)
//    sort_key = sort_by == :json ? :sortBy : :sort

//    sort_options = { sort_key => sort_param }

//    // Don"t lose other params.
//    link_to_content_update(h(caption), safe_query_params(%w{filters page per_page expand}).merge(sort_options), html_options)
//  }

  // Returns a table header <th> tag with a sort link for the named column
  // attribute.
  //
  // Options:
  //   :caption     The displayed link name (defaults to titleized column name).
  //   :title       The tag"s "title" attribute (defaults to "Sort by :caption").
  //
  // Other options hash entries generate additional table header tag attributes.
  //
  // Example:
  //
  //   <%= sort_header_tag("id", title: "Sort by contact ID") %>
  //
  //   Generates (for the users controller and if ( the table is sorted by the column)) {
  //     <th>
  //       <div class="generic-table--sort-header-outer">
  //         <div class="generic-table--sort-header">
  //           <span class="sort asc">
  //             <a href="/users?sort=id:desc%3Adesc">Id</a>
  //           </span>
  //         </div>
  //       </div>
  //     </th>
  //
//   void sort_header_tag(column, options = {}) {
//    caption = get_caption(column, options)

//    default_order = options.delete(:default_order) || "asc"
//    lang = options.delete(:lang) || nil
//    param = options.delete(:param) || :sort

//    options[:title] = sort_header_title(column, caption, options)

//    within_sort_header_tag_hierarchy(options, sort_class(column)) {
//      sort_link(column, caption, default_order, param: param, lang: lang, title: options[:title])
//    }
//  }

//   void sort_class(column) {
//    order = order_string(column)

//    order.nil? ? nil : "sort #{order}"
//  }

//   void order_string(column, inverted: false) {
//    if ( column.to_s == this->sort_criteria.first_key) {
//      if ( this->sort_criteria.first_asc?) {
//        inverted ? "desc" : "asc"
//      else
//        inverted ? "asc" : "desc"
//      }
//    }
//  }

//   void within_sort_header_tag_hierarchy(options, classes) {
//    content_tag "th", options {
//      content_tag "div", class: "generic-table--sort-header-outer" {
//        content_tag "div", class: "generic-table--sort-header" {
//          content_tag "span", class: classes {
//            yield
//          }
//        }
//      }
//    }
//  }

//   void sort_header_title(column, caption, options) {
//    if ( column.to_s == this->sort_criteria.first_key) {
//      order = this->sort_criteria.first_asc? ? t(:label_ascending) : t(:label_descending)
//      order + " #{t(:label_sorted_by, value: "\"#{caption}\"")}"
//    else
//      t(:label_sort_by, value: "\"#{caption}\"") unless options[:title]
//    }
//  }

//   void get_caption(column, options) {
//    caption = options.delete(:caption)

//    if ( caption.blank?) {
//      caption = defined?(model) ? model.human_attribute_name(column.to_s) : column.humanize
//    }

//    caption
//  }
};
}
}
}
