#pragma once
//#include "diff"

#include "application_controller.h"
namespace openproj {
namespace controller {
class JournalsController : public ApplicationController {
public:
  // before_action :find_journal, except: [:index]
  // before_action :find_optional_project, only: [:index]
  // before_action :authorize, only: [:diff]
  // accept_key_auth :index
  // menu_item :issues

  // include QueriesHelper
  // include SortHelper

   void index() {
//    retrieve_query
//    sort_init 'id', 'desc'
//    sort_update(this->query.sortable_key_by_column_name)

//    if ( this->query.valid?) {
//      this->journals = this->query.work_package_journals(order: "#{Journal.table_name}.created_at DESC",
//                                               limit: 25)
//    }

//    title = (this->project ? this->project.name : Setting.app_title) + ': ' + (this->query.new_record? ? l(:label_changes_details) : this->query.name)

//    respond_to { |format|
//      format.atom {
//        render layout: false,
//               content_type: 'application/atom+xml',
//               locals: { title: title,
//                         journals: this->journals }
//      }
//    }
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void diff() {
//    journal = JournalN::AggregatedJournal.for_journal(this->journal)
//    field = params[:field].parameterize.underscore.to_sym

//    unless valid_diff?
//      return render_404
//    }

//    unless journal.details[field].is_a?(Array)
//      return render_400 message: I18n.t(:error_journal_attribute_not_present, attribute: field)
//    }

//    from = journal.details[field][0]
//    to = journal.details[field][1]

//    this->diff = Redmine::Helpers::Diff.new(to, from)
//    this->journable = journal.journable
//    respond_to { |format|
//      format.html
//      format.js {
//        render partial: 'diff', locals: { diff: this->diff }
//      }
//    }
  }

  private:

   void find_journal() {
//    this->journal = Journal.find(params[:id])
//    this->project = this->journal.journable.project
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

  // Is this a valid field for diff'ing?
//   void valid_field?(field) {
//    field.to_s.strip == 'description'
//  }

   bool valid_diff() {
//    return false unless valid_field?(params[:field])
//    this->journal.journable.class == WorkPackage
  }
};
}
}
