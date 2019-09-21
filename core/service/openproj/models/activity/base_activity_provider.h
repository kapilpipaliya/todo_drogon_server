#pragma once
//#############################################################################
// The base activity provider class provides a default implementation for the  #
// most common activity jobs. You may implement the following methods to set   #
// the respective activity details:                                            #
//  - event_name                                                               #
//  - event_title                                                              #
//  - event_type                                                               #
//  - event_description                                                        #
//  - event_datetime                                                           #
//  - event_path                                                               #
//  - event_url                                                                #
//                                                                             #
// See the comments on the methods to get additional information.              #
//#############################################################################
namespace openproj {
namespace models {
namespace Activity {
class BaseActivityProvider {
  // include Redmine::Acts::ActivityProvider
  // include I18n
  // include Redmine::I18n
  // include OpenProject::StaticRouting

  //###########################################################################
  // Activities may need information not available in the journal table. Thus, #
  // if you need further information from different tables (e.g., projects     #
  // table) you may extend the query in this method.                           #
  //###########################################################################
//   void extend_event_query(_query, _activity) {
//  }

  //###########################################################################
  // This method returns a list of columns that the activity query needs to    #
  // return, so the activity provider can actually create an activity object.  #
  // You must at least return the column containing the project reference with #
  // the alias "project_id".                                                   #
  //###########################################################################
//   void event_query_projection(_activity) {
//    []
//  }

  //###########################################################################
  // Override this method if the journal table does not contain a reference to #
  // the "projects" table.                                                     #
  //###########################################################################
//   void projects_reference_table(activity) {
//    activity_journals_table(activity)
//  }

//   void filter_for_event_datetime(query, journals_table, typed_journals_table, from, to) {
//    if ( from) {
//      query = query.where(journals_table[:created_at].gteq(from))
//    }

//    if ( to) {
//      query = query.where(journals_table[:created_at].lteq(to))
//    }

//    query
//  }

//   void activity_journals_table(_activity) {
//    this->activity_journals_table ||= JournalManager.journal_class(activitied_type).arel_table
//  }

//   void activitied_type(_activity = nil) {
//    activity_type = this->class.name
//    namespace = activity_type.deconstantize

//    class_name = activity_type.demodulize
//    class_name.gsub("ActivityProvider", "").constantize
//  }

//   void format_event(event, event_data, activity) {
//    [:event_name, :event_title, :event_type, :event_description, :event_datetime, :event_path, :event_url].each { |a|
//      if ( this->class.method_defined? a) { event[a] = send(a, event_data, activity) ;}
//    }

//    event
//  }

  protected:

//   void journal_table() {
//    this->journal_table ||= Journal.arel_table
//  }

//   void activitied_table() {
//    this->activitied_table ||= activitied_type.arel_table
//  }

//   void work_packages_table() {
//    this->work_packages_table ||= WorkPackage.arel_table
//  }

//   void projects_table() {
//    this->projects_table ||= Project.arel_table
//  }

//   void types_table() {
//    this->types_table = Type.arel_table
//  }

//   void statuses_table() {
//    this->statuses_table = Status.arel_table
//  }

//   void activity_journal_projection_statement(column, name, activity) {
//    projection_statement(activity_journals_table(activity), column, name)
//  }

//   void projection_statement(table, column, name) {
//    table[column].as(name)
//  }

//  class UndefinedEventTypeError : public StandardError{};
//   void event_type(_event, _activity) {
//    raise UndefinedEventTypeError.new("Abstract method event_type called")
//  }

//   void event_name(event, activity) {
//    I18n.t(event_type(event, activity).underscore, scope: "events")
//  }

//   void url_helpers() {
//    this->url_helpers ||= OpenProject::StaticRouting::StaticUrlHelpers.new
//  }
};
}
}
}