#pragma once
namespace openproj {
namespace seeder {

namespace DemoData {
  namespace References {
//    module_function

//     void url_helpers() {
//      this->url_helpers ||= OpenProject::StaticRouting::StaticRouter.new.url_helpers
//    }

//     void api_url_helpers() {
//      API::V3::Utilities::PathHelper::ApiV3Path
//    }

//     void with_references(str, project) {
//      res = link_work_packages str, project
//      res = link_queries res, project
//      res = link_sprints res, project

//      res
//    }

    //
    // Replaces occurrences of `##child:n` with a link to the given
    // work package's nth child using the standard OpenProject work package
    // link syntax `##<id>`.
//     void link_children(str, work_package) {
//      return str unless str.present? && str.include?("##child:")

//      str.gsub(/##child:\d+/) { |match|
//        index = match.split(":").last.to_i - 1

//        "##" + work_package.children[index].id.to_s
//      }
//    }

    //
    // Links attachments from the given set of attachments, referenced via name.
    // For instance:
    //
    //   `##attachment:"picture.jpg"`
    //
    // @param str [String] String in which to substitute attachment references.
    // @param attachments [ActiveRecord::QueryMethods] Query to set of attachments which can be referenced.
//     void link_attachments(str, attachments) {
//      return str unless str.present?

//      str.gsub(/##attachment(\.id)?:"[^"]+"/) { |match|
//        file = match.split(":", 2).last[1..-2] // strip quotes of part behind :
//        attachment = attachments.where(file: file).first!

//        if ( match.include?(".id")) {
//          attachment.id
//        else
//          api_url_helpers.attachment_content attachment.id
//        }
//      }
//    }

    //
    // Turns `##query:"Gantt chart"` into
    // `/projects/demo-project/work_packages?query_id=1` given there is a query
    // named "Gantt chart" (its ID here being 1).
    //
    // Alternatively `##query.id:"Gantt chart"` is translated into just the ID.`
//     void link_queries(str, project) {
//      link_reference(
//        str,
//        model: Query,
//        find_by: :name,
//        project: project,
//        link: ->(query) { query_link query }
//      )
//    }

    //
    // Turns `##wp:"Some subject"` into
    // `/projects/demo-project/work_packages/42/activity` given there is a work package
    // named "Some subject" (its subject here being "Some subject").
    //
    // Alternatively `##wp.id:"Some subject"` is translated into just the ID.`
//     void link_work_packages(str, project) {
//      link_reference(
//        str,
//        model: WorkPackage,
//        tag: "wp",
//        find_by: :subject,
//        project: project,
//        link: ->(wp) { work_package_link wp }
//      )
//    }

//     void link_sprints(str, project) {
//      return str unless defined? OpenProject::Backlogs

//      link_reference(
//        str,
//        model: Sprint,
//        find_by: :name,
//        project: project,
//        link: ->(sprint) { sprint_link sprint }
//      )
//    }

//     void link_reference(str, model:, find_by:, project:, link:, tag: nil) {
//      return str unless str.present?

//      tag ||= model.name.downcase

//      str.gsub(/###{tag}(\.id)?:"[^"]+"/) { |match|
//        identifier = match.split(":", 2).last[1..-2] // strip quotes of part behind :
//        instance = model.where(find_by => identifier, :project => project).first!

//        if ( match.include?(".id")) {
//          instance.id
//        else
//          link.call instance
//        }
//      }
//    }

//     void query_link(query) {
//      path = url_helpers.project_work_packages_path project_id: query.project.identifier

//      "#{path}?query_id=#{query.id}"
//    }

//     void work_package_link(work_package) {
//      url_helpers.project_work_package_path(
//        id: work_package.id,
//        project_id: work_package.project.identifier,
//        state: "activity"
//      )
//    }

//     void sprint_link(sprint) {
//      url_helpers.backlogs_project_sprint_taskboard_path(
//        sprint_id: sprint.id,
//        project_id: sprint.project.identifier
//      )
//    }
  }
}
}
}
