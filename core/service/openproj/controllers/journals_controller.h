#include "diff"

#include "application_controller.h"
class JournalsController : public ApplicationController {
  // before_action :find_journal, except: [:index]
  // before_action :find_optional_project, only: [:index]
  // before_action :authorize, only: [:diff]
  // accept_key_auth :index
  // menu_item :issues

  // include QueriesHelper
  // include SortHelper

   void index() {
    retrieve_query
    sort_init 'id', 'desc'
    sort_update(@query.sortable_key_by_column_name)

    if ( @query.valid?) {
      @journals = @query.work_package_journals(order: "#{Journal.table_name}.created_at DESC",
                                               limit: 25)
    }

    title = (@project ? @project.name : Setting.app_title) + ': ' + (@query.new_record? ? l(:label_changes_details) : @query.name)

    respond_to { |format|
      format.atom {
        render layout: false,
               content_type: 'application/atom+xml',
               locals: { title: title,
                         journals: @journals }
      }
    }
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void diff() {
    journal = Journal::AggregatedJournal.for_journal(@journal)
    field = params[:field].parameterize.underscore.to_sym

    unless valid_diff?
      return render_404
    }

    unless journal.details[field].is_a?(Array)
      return render_400 message: I18n.t(:error_journal_attribute_not_present, attribute: field)
    }

    from = journal.details[field][0]
    to = journal.details[field][1]

    @diff = Redmine::Helpers::Diff.new(to, from)
    @journable = journal.journable
    respond_to { |format|
      format.html
      format.js {
        render partial: 'diff', locals: { diff: @diff }
      }
    }
  }

  private:

   void find_journal() {
    @journal = Journal.find(params[:id])
    @project = @journal.journable.project
  rescue ActiveRecord::RecordNotFound
    render_404
  }

  // Is this a valid field for diff'ing?
   void valid_field?(field) {
    field.to_s.strip == 'description'
  }

   void valid_diff?() {
    return false unless valid_field?(params[:field])
    @journal.journable.class == WorkPackage
  }
}
