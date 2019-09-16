#pragma once
#include "../../base.h"
namespace openproj {
namespace Queries::Filters::Shared {
  namespace CustomFields {
    class Base : public openproj::Queries::Filters::Base {
      // include Queries::Filters::Serializable

//      attr_reader :custom_field
//      attr_reader :custom_field_context

//      validate :custom_field_valid

//       Base(custom_field:, custom_field_context:, **options) {
//        name = :"cf_#{custom_field.id}"

//        this->custom_field = custom_field
//        this->custom_field_context = custom_field_context
//        this->model = custom_field_context.model
//        super(name, options)
//      }

//       void create!(custom_field:, custom_field_context:, **options) {
//        new(custom_field: custom_field, custom_field_context: custom_field_context, **options)
//      }

//       void project() {
//        context.try(:project)
//      }

//       void available?() {
//        custom_field.present?
//      }

//       void order() {
//        20
//      }

//       void human_name() {
//        custom_field.name
//      }

//       void allowed_values() {
//        custom_field.possible_values_options(project)
//      }

//       void type_strategy() {
//        this->type_strategy ||= type_strategy_class.new(self)
//      }

//       void strategies() {
//        strategies = Queries::Filters::STRATEGIES.dup
//        // Override the integer and float strategies
//        strategies[:integer] = Queries::Filters::Strategies::CfInteger
//        strategies[:float] = Queries::Filters::Strategies::CfFloat

//        strategies
//      }

//       void type() {
//        case custom_field.field_format
//        when 'float'
//          :float
//        when 'int'
//          :integer
//        when 'text'
//          :text
//        when 'date'
//          :date
//        else
//          :string
//        }
//      }

//       void where() {
//        model_db_table = model.table_name
//        cv_db_table = CustomValue.table_name

//        <<-SQL
//          #{model_db_table}.id IN
//          (SELECT #{model_db_table}.id
//          FROM #{model_db_table}
//          #{custom_field_context.where_subselect_joins(custom_field)}
//          WHERE #{operator_strategy.sql_for_field(values_replaced, cv_db_table, 'value')})
//        SQL
//      }

//       void error_messages() {
//        messages = errors.full_messages
//                         .join(" #{I18n.t('support.array.sentence_connector')} ")

//        human_name + I18n.t(default: ' %<message>s', message: messages)
//      }

      protected:

//       void type_strategy_class() {
//        strategies[type] || strategies[:inexistent]
//      }

//       void custom_field_valid() {
//        if ( invalid_custom_field_for_context?) {
//          errors.add(:base, I18n.t('activerecord.errors.models.query.filters.custom_fields.invalid'))
//        }
//      }

//       void invalid_custom_field_for_context?() {
//        if ( project) {
//          invalid_custom_field_for_project?
//        else
//          invalid_custom_field_globally?
//        }
//      }

//       void invalid_custom_field_globally?() {
//        !custom_field_context.custom_fields(project).exists?(custom_field.id)
//      }

//       void invalid_custom_field_for_project?() {
//        !custom_field_context.custom_fields(project).map(&:id).include? custom_field.id
//      }
    };
  }
}
}
