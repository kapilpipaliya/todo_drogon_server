#pragma once
#include "../exporter/base.h"
namespace openproj {
namespace WorkPackageN {
namespace PdfExport {
class WorkPackageListToPdf : public WorkPackageN::Exporter::Base {
  // include WorkPackageN::PdfExport::Common
  // include WorkPackageN::PdfExport::Attachments

  // attr_accessor :pdf,
//                :options

//   WorkPackageListToPdf(object, options = {}) {
//    super

//    this->cell_padding = options.delete(:cell_padding)

//    this->pdf = get_pdf(current_language)

//    pdf.options[:page_size] = 'EXECUTIVE'
//    pdf.options[:page_layout] = :landscape
//  }

//   void render!() {
//    write_title!
//    write_work_packages!

//    write_footers!

//    success(pdf.render)
//  rescue Prawn::Errors::CannotFit
//    error(I18n.t(:error_pdf_export_too_many_columns))
//  rescue StandardError => e
//    Rails.logger.error { "Failed to generated PDF export: #{e} #{e.message}." }
//    error(I18n.t(:error_pdf_failed_to_export, error: e.message))
//  }

//   void project() {
//    query.project
//  }

//   void write_title!() {
//    pdf.title = heading
//    pdf.font style: :bold, size: 11
//    pdf.text heading
//    pdf.move_down 20
//  }

//   void title() {
//    "#{heading}.pdf"
//  }

//   void heading() {
//    title = query.new_record? ? I18n.t(:label_work_package_plural) : query.name

//    if ( project) {
//      "#{project} - #{title}"
//    else
//      title
//    }
//  }

//   void write_footers!() {
//    pdf.number_pages format_date(Date.today),
//                     at: [pdf.bounds.left, 0],
//                     style: :italic

//    pdf.number_pages "<page>/<total>",
//                     at: [pdf.bounds.right - 25, 0],
//                     style: :italic
//  }

//   void write_work_packages!() {
//    pdf.font style: :normal, size: 8
//    pdf.table(data, column_widths: column_widths)
//  }

//   void column_widths() {
//    widths = valid_export_columns.map { |col|
//      if ( col.name == :subject || text_column?(col)) {
//        4.0
//      else
//        1.0
//      }
//    }
//    ratio = pdf.bounds.width / widths.sum

//    widths.map { |w| w * ratio }
//  }

//   void description_colspan() {
//    valid_export_columns.size
//  }

//   void text_column?(column) {
//    column.is_a?(Queries::WorkPackages::Columns::CustomFieldColumn) &&
//      ['string', 'text'].include?(column.custom_field.field_format)
//  }

//   void data() {
//    [data_headers] + data_rows
//  }

//   void data_headers() {
//    valid_export_columns.map(&:caption).map { |caption|
//      pdf.make_cell caption, font_style: :bold, background_color: 'CCCCCC'
//    }
//  }

//   void data_rows() {
//    previous_group = nil

//    work_packages.flat_map { |work_package|
//      values = valid_export_columns.map { |column|
//        make_column_value work_package, column
//      }

//      result = [values]

//      if ( options[:show_descriptions]) {
//        make_description(work_package.description.to_s).each { |segment|
//          result << [segment]
//        }
//      }

//      if ( options[:show_attachments] && work_package.attachments.exists?) {
//        attachments = make_attachments_cells(work_package.attachments)

//        if ( attachments.any?) {
//          result << [
//            { content: pdf.make_table([attachments]), colspan: description_colspan }
//          ]
//        }
//      }

//      if ( query.grouped? && (group = query.group_by_column.value(work_package)) != previous_group) {
//        label = make_group_label(group)
//        previous_group = group

//        result.insert 0, [
//          pdf.make_cell(label, font_style: :bold,
//                               colspan: valid_export_columns.size,
//                               background_color: 'DDDDDD')
//        ]
//      }

//      result
//    }
//  }

//   void make_column_value(work_package, column) {
//    if ( column.is_a?(Queries::WorkPackages::Columns::CustomFieldColumn)) {
//      make_custom_field_value work_package, column
//    else
//      make_field_value work_package, column.name
//    }
//  }

//   void make_field_value(work_package, column_name) {
//    pdf.make_cell field_value(work_package, column_name),
//                  padding: cell_padding
//  }

//   void make_group_label(group) {
//    if ( group.blank?) {
//      I18n.t(:label_none_parentheses)
//    } else if ( group.is_a? Array) {
//      group.join(', ')
//    else
//      group.to_s
//    }
//  }

//   void make_custom_field_value(work_package, column) {
//    values = work_package
//             .custom_values
//             .select { |v| v.custom_field_id == column.custom_field.id }

//    pdf.make_cell values.map(&:formatted_value).join(', '),
//                  padding: cell_padding
//  }
};
}
}
}
