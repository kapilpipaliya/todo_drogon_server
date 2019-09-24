#ifndef OPENPROJ_MODELS_ATTRIBUTE_HELP_TEXT_H
#define OPENPROJ_MODELS_ATTRIBUTE_HELP_TEXT_H


#include "activerecord.h"
#include "AttributeHelpTexts.h"

namespace openproj {

namespace models {

class AttributeHelpText : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::AttributeHelpTexts {
  public:
    inline void available_types() {
    //    subclasses.map { |child| child.name.demodulize }
      };

    //   void used_attributes(type) {
    //    where(type: type)
    //      .select(:attribute_name)
    //      .distinct
    //      .pluck(:attribute_name)
    //  }
    inline void all_by_scope() {
    //    all.group_by(&:attribute_scope)
      };

    //   void visible(user) {
    //    scope = AttributeHelpText.subclasses[0].visible_condition(user)
    //    AttributeHelpText.subclasses[1..-1].each { |subclass|
    //      scope = scope.or(subclass.visible_condition(user))
    //    }
    //    scope
    //  }
    // validates_presence_of :help_text
    // validates_uniqueness_of :attribute_name, scope: :type
    inline void attribute_caption() {
    //    this->caption ||= this->class.available_attributes[attribute_name]
      };

    virtual void attribute_scope() = 0;

    virtual void type_caption() = 0;

    virtual void visible_condition() = 0;

    virtual void available_attributes() = 0;

};

} // namespace openproj::models

} // namespace openproj
#endif
