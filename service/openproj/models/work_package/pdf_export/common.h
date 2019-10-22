#pragma once
namespace openproj {
namespace models {
namespace WorkPackageN::PdfExport::Common {
  // include Redmine::I18n
  // include ActionView::Helpers::TextHelper
  // include ActionView::Helpers::NumberHelper
  // include CustomFieldsHelper
  // include WorkPackageN::PdfExport::ToPdfHelper

//   void field_value(work_package, attribute) {
//    value = work_package.send(attribute)

//    if ( value.is_a? Date) {
//      format_date value
//    } else if ( value.is_a? Time) {
//      format_time value
//    else
//      value.to_s
//    }
//  }

//   void success(content) {
//    WorkPackageN::Exporter::Success
//      .new format: :csv,
//           title: title,
//           content: content,
//           mime_type: "application/pdf"
//  }

//   void error(message) {
//    WorkPackageN::Exporter::Error.new message
//  }

//   void cell_padding() {
//    this->cell_padding ||= [2, 5, 2, 5]
//  }

  //
  // Creates a number of cell rows to show the description.
  //
  // The description is split into many smaller cells so that
  // prawn-table does not go crazy with long texts causing
  // empty pages in between.
  //
  // The fact that prawn-table can"t handle multi-page table cells
  // is a known, unsolved issue. Hence this workaround.
  //
  // @param description [String] The work package"s description
  // @param options [Hash] Allows changing the number of lines per cell
  //                       through the :max_lines_per_cell option.
  // @return [Array] An array of rows to be added to the work packages table.
//   void make_description(description, options = {}) {
//    lines = description.lines
//    max = options[:max_lines_per_cell] || max_lines_per_description_cell

//    if ( lines.size > max_lines_per_description_cell) {
//      cells = split_description lines, max: max, cell_options: Hash(options[:cell_options])

//      format_description_segments!(cells)
//    else
//      [make_single_description(description, Hash(options[:cell_options]))]
//    }
//  }

  //
  // Formats the cells so that they appear to be one big cell.
//   void format_description_segments!(cells) {
//    cells.first.padding[0] = cell_padding[0] // top padding
//    cells.last.padding[2] = cell_padding[2] // bottom padding
//    cells.last.borders = [:left, :right, :bottom]
//    cells
//  }

//   void split_description(lines, max: max_lines_per_description_cell, cell_options: {}) {
//    head = make_description_segment lines.take(max).join, cell_options

//    if ( lines.size > max) {
//      [head] + split_description(lines.drop(max), max: max, cell_options: cell_options)
//    else
//      [head]
//    }
//  }

//   void make_description_segment(description, options = {}) {
//    cell_options = {
//      borders: [:left, :right],
//      padding: [0, cell_padding[1], 0, cell_padding[3]]
//    }

//    make_single_description description, cell_options.merge(options)
//  }

//   void make_single_description(description, options = {}) {
//    cell_options = { colspan: description_colspan }

//    pdf.make_cell description, cell_options.merge(options)
//  }

//   void max_lines_per_description_cell() {
//    3
//  }

//   void description_colspan() = 0;
}
}
}