#pragma once
namespace openproj {
namespace service {
class ParseSchemaFilterParamsService{
public:
  // extend ActiveModel::Naming
  // extend ActiveModel::Translation

  // attr_accessor :user

   void i18n_scope() {
//    :activerecord
  }

//   ParseSchemaFilterParamsService(user:) {
//    this->user = user
//  }

//   void call(filter) {
//    error_message = check_error_in_filter(filter)

//    if ( error_message) {
//      error(error_message)
//    else
//      pairs = valid_project_type_pairs(filter)

//      success(pairs)
//    }
//  }

  private:

//   void check_error_in_filter(filter) {
//    if ( !filter.first["id"]) {
//      :id_filter_required
//    } else if ( filter.first["id"]["operator"] != "=") {
//      :unsupported_operator
//    } else if ( filter.first["id"]["values"].any? { |id_string| !id_string.match(/\d+-\d+/) }) {
//      :invalid_values
//    }
//  }

//   void parse_ids(filter) {
//    ids_string = filter.first["id"]["values"]

//    ids_string.map { |id_string|
//      id_string.split("-")
//    }
//  }

//   void error(message) {
//    errors = ActiveModel::Errors.new(self)
//    errors.add(:base, message)
//    ServiceResult.new(errors: errors)
//  }

//   void success(result) {
//    ServiceResult.new(success: true, result: result)
//  }

//   void valid_project_type_pairs(filter) {
//    ids = parse_ids(filter)

//    projects_map = projects_by_id(ids.map(&:first))
//    types_map = types_by_id(ids.map(&:last))

//    valid_ids = only_valid_pairs(ids, projects_map, types_map)

//    string_pairs_to_object_pairs(valid_ids, projects_map, types_map)
//  }

//   void projects_by_id(ids) {
//    Project.visible(user).where(id: ids).group_by(&:id)
//  }

//   void types_by_id(ids) {
//    Type.where(id: ids).group_by(&:id)
//  }

//   void only_valid_pairs(id_pairs, projects_map, types_map) {
//    id_pairs.reject { |project_id, type_id|
//      projects_map[project_id.to_i].nil? || types_map[type_id.to_i].nil?
//    }
//  }

//   void string_pairs_to_object_pairs(string_pairs, projects_map, types_map) {
//    string_pairs.map { |project_id, type_id|
//      [projects_map[project_id.to_i].first, types_map[type_id.to_i].first]
//    }
//  }
};
}
}
