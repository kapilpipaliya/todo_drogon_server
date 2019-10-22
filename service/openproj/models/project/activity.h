#pragma once
//require Rails.root.join("config/constants/project_activity")

namespace openproj {
namespace models {
namespace ProjectN::Activity {
//   void included(base) {
//    base.send :extend, Scopes
//  }

  namespace Scopes {
//     void register_latest_project_activity(on:, chain: [], attribute:) {
//      Constants::ProjectActivity.register(on: on,
//                                          chain: chain,
//                                          attribute: attribute)
//    }

//     void latest_project_activity() {
//      this->latest_project_activity ||=
//        Constants::ProjectActivity.registered.map { |params|
//          build_latest_project_activity_for(on: params[:on],
//                                            chain: params[:chain],
//                                            attribute: params[:attribute])
//        }
//    }

//     void with_latest_activity() {
//      Project
//        .select("projects.*")
//        .select("activity.latest_activity_at")
//        .joins("LEFT JOIN (#{latest_activity_sql}) activity ON projects.id = activity.project_id")
//    }

//     void latest_activity_sql() {
//      <<-SQL
//        SELECT project_id, MAX(updated_at) latest_activity_at
//        FROM (#{all_activity_provider_union_sql}) activity
//        GROUP BY project_id
//      SQL
//    }

//     void all_activity_provider_union_sql() {
//      latest_project_activity.join(" UNION ALL ")
//    }

//     void build_latest_project_activity_for(on:, chain:, attribute:) {
//      join_chain = Array(chain).dup.push(on)
//      from = join_chain.first

//      joins = build_joins_from_chain(join_chain)

//      <<-SQL
//        SELECT project_id, MAX(#{on.table_name}.#{attribute}) updated_at
//        FROM #{from.table_name}
//        #{joins.join(" ")}
//        WHERE #{on.table_name}.#{attribute} IS NOT NULL
//        GROUP BY project_id
//      SQL
//    }

//     void build_joins_from_chain(join_chain) {
//      joins = []

//      (0..join_chain.length - 2).each { |i|
//        joins << build_join(join_chain[i + 1],
//                            join_chain[i])
//      }

//      joins
//    }

//     void build_join(right, left) {
//      associations = right.reflect_on_all_associations
//      association = associations.detect { |a| a.class_name == left.to_s }

//      <<-SQL
//        LEFT OUTER JOIN #{right.table_name}
//        ON #{left.table_name}.id =
//           #{right.table_name}.#{association.foreign_key}
//      SQL
//    }
  }
}
}
}