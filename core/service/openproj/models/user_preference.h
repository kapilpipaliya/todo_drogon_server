#pragma once
#include "activerecord.h"
#include "UserPreferences.h"
namespace openproj {
namespace models {
class UserPreference : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::UserPreferences {
  // belongs_to :user
//  serialize :others

  // validates_presence_of :user
//  validate :time_zone_correctness, if (: -> { time_zone.present? }) {

//  after_initialize :init_other_preferences

//   void [](attr_name) {
//    attribute_present?(attr_name) ? super : others[attr_name]
//  }

//   void []=(attr_name, value) {
//    attribute_present?(attr_name) ? super : others[attr_name] = value
//  }

//   void comments_sorting() {
//    others.fetch(:comments_sorting, OpenProject::Configuration.default_comment_sort_order)
//  }

//   void comments_sorting=(order) {
//    others[:comments_sorting] = order
//  }

//   void comments_in_reverse_order?() {
//    comments_sorting == "desc"
//  }

//   void self_notified?() {
//    !others[:no_self_notified]
//  }

//   void self_notified=(value) {
//    others[:no_self_notified] = !value
//  }

//   void auto_hide_popups=(value) {
//    others[:auto_hide_popups] = to_boolean(value)
//  }

//   void auto_hide_popups?() {
//    others.fetch(:auto_hide_popups) { Setting.default_auto_hide_popups? }
//  }

//   void warn_on_leaving_unsaved?() {
//    // Need to cast here as previous values were "0" / "1"
//    to_boolean(others.fetch(:warn_on_leaving_unsaved) { true })
//  }

//   void warn_on_leaving_unsaved=(value) {
//    others[:warn_on_leaving_unsaved] = to_boolean(value)
//  }

//  // Provide an alias to form builders
//  alias :comments_in_reverse_order :comments_in_reverse_order?
//  alias :warn_on_leaving_unsaved :warn_on_leaving_unsaved?
//  alias :auto_hide_popups :auto_hide_popups?

//   void comments_in_reverse_order=(value) {
//    others[:comments_sorting] = to_boolean(value) ? "desc" : "asc"
//  }

//   void time_zone() {
//    self[:time_zone].presence || Setting.user_default_timezone.presence
//  }

//   void canonical_time_zone() {
//    if ( time_zone.nil?) { return ;}

//    zone = ActiveSupport::TimeZone.new(time_zone)
//    unless zone.nil?
//      zone.tzinfo.canonical_identifier
//    }
//  }

  private:

//   void to_boolean(value) {
//    ActiveRecord::TypeN::Boolean.new.cast(value)
//  }

   void init_other_preferences() {
//    this->others ||= { no_self_notified: true }
  }

   void time_zone_correctness() {
//    if ( time_zone.present? && canonical_time_zone.nil?) { errors.add(:time_zone, :inclusion) ;}
  }
};
}

}
