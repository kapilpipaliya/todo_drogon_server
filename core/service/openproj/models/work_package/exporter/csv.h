#pragma once
#include "../exporter/base.h"
namespace openproj {
namespace models {
namespace WorkPackageN {
namespace Exporter {
class CSV : public WorkPackageN::Exporter::Base {
  // include Redmine::I18n
  // include CustomFieldsHelper
  // include ActionView::Helpers::TextHelper
  // include ActionView::Helpers::NumberHelper

//   void list() {
//    serialized = CSV.generate(col_sep: l(:general_csv_separator)) { |csv|
//      headers = csv_headers
//      csv << this->class.encode_csv_columns(headers)

//      work_packages.each { |work_package|
//        row = csv_row(work_package)
//        csv << this->class.encode_csv_columns(row)
//      }
//    }

//    yield success(serialized)
//  }

//   void encode_csv_columns(columns, encoding = l(:general_csv_encoding)) {
//    columns.map { |cell|
//      Redmine::CodesetUtil.from_utf8(cell.to_s, encoding)
//    }
//  }

  private:

//   void success(serialized) {
//    WorkPackageN::Exporter::Success
//      .new format: :csv,
//           title: title,
//           content: serialized,
//           mime_type: 'text/csv'
//  }

//   void title() {
//    title = query.new_record? ? l(:label_work_package_plural) : query.name

//    "#{title}.csv"
//  }

  // fetch all headers
//   void csv_headers() {
//    headers = []

//    valid_export_columns.each_with_index { |column, _|
//      headers << column.caption
//    }

//    headers << CustomField.human_attribute_name(:description)

//    // because of
//    // https://support.microsoft.com/en-us/help/323626/-sylk-file-format-is-not-valid-error-message-when-you-open-file
//    if ( headers[0].start_with?('ID')) {
//      headers[0] = headers[0].downcase
//    }

//    headers
//  }

  // fetch all row values
//   void csv_row(work_package) {
//    row = valid_export_columns.collect { |column|
//      csv_format_value(work_package, column)
//    }

//    if ( !row.empty?) {

//      row << if ( work_package.description) {
//               work_package.description.squish
//             else
//               ''
//             }
//    }

//    row
//  }

//   void csv_format_value(work_package, column) {
//    if ( column.is_a?(Queries::WorkPackages::Columns::CustomFieldColumn)) {
//      csv_format_custom_value(work_package, column)
//    else
//      value = work_package.send(column.name)

//      case value
//      when Date
//        format_date(value)
//      when Time
//        format_time(value)
//      else
//        value
//      }
//    }.to_s
//  }

//   void csv_format_custom_value(work_package, column) {
//    cv = work_package
//         .custom_values
//         .select { |v| v.custom_field_id == column.custom_field.id }

//    cv
//      .map { |v| show_value(v) }
//      .join('; ')
//  }
};
}
}
}
}