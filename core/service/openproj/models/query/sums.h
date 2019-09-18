#pragma once
namespace openproj {
namespace models {
namespace QueryN::Sums {
  // include ActionView::Helpers::NumberHelper

//   void next_in_same_group?(issue = cached_issue) {
//    caching_issue issue { |issue|
//      !last_issue? &&
//        query.group_by_column.value(issue) == query.group_by_column.value(work_packages[issue_index + 1])
//    }
//  }

//   void last_issue?(issue = cached_issue) {
//    caching_issue issue { |_issue|
//      issue_index == work_packages.size - 1
//    }
//  }

//   void issue_index(issue = cached_issue) {
//    caching_issue issue { |issue|
//      work_packages.find_index(issue)
//    }
//  }

//   void grouped_sum_of_issue(column, issue = cached_issue) {
//    grouped_sum_of column, group_for_issue(issue)
//  }

//   void grouped_sum_of(column, group) {
//    sum_of column, group
//  }

//   void grouped_sums(column) {
//    work_packages
//      .map { |wp| query.group_by_column.value(wp) }
//      .uniq
//      .inject({}) { |group_sums, current_group|
//        work_packages_in_current_group = work_packages.select { |wp| query.group_by_column.value(wp) == current_group }
//        // TODO: sum_of only works fast when passing an AR::Relation
//        group_sums.merge current_group => sum_of(column, work_packages_in_current_group)
//      }
//  }

//   void total_sum_of(column) {
//    sum_of(column, work_packages)
//  }

//   void sum_of(column, collection) {
//    return nil unless should_be_summed_up?(column)

//    sum = column.sum_of(collection)

//    crunch(sum)
//  }

//   void caching_issue(issue) {
//    this->cached_issue = issue unless this->cached_issue == issue
//    block_given? ? yield(issue) : issue
//  }

//   void cached_issue() {
//    this->cached_issue
//  }

//   void mapping_for(column) {
//    if ( column.respond_to? :real_value) {
//      method(:number_to_currency)
//    else
//      // respond_to? :call, but do nothing
//      this->nilproc ||= Proc.new { |val| val }
//    }
//  }

//   void crunch(num) {
//    if ( num.nil? or num.integer?) { return num ;}
//    Float(format '%.2f', num.to_f)
//  }

//   void group_for_issue(issue = this->current_issue) {
//    caching_issue issue { |issue|
//      work_packages.select { |is|
//        query.group_by_column.value(issue) == query.group_by_column.value(is)
//      }
//    }
//  }

//   void should_be_summed_up?(column) {
//    column.summable? && Setting.work_package_list_summable_columns.include?(column.name.to_s)
//  }

//   void column_total_sums() {
//    query.columns.map { |column| total_sum_of(column) }
//  }

//   void all_total_sums() {
//    query.available_columns.select { |column|
//      column.summable? && Setting.work_package_list_summable_columns.include?(column.name.to_s)
//    }.inject({}) { |result, column|
//      sum = total_sum_of(column)
//      result[column] = sum unless sum.nil?
//      result
//    }
//  }

//   void all_sums_for_group(group) {
//    return nil unless query.grouped?

//    group_work_packages = work_packages.select { |wp| query.group_by_column.value(wp) == group }
//    query.available_columns.inject({}) { |result, column|
//      sum = sum_of(column, group_work_packages)
//      result[column] = sum unless sum.nil?
//      result
//    }
//  }

//   void column_group_sums() {
//    query.group_by_column && query.columns.map { |column| grouped_sums(column) }
//  }
}
}
}