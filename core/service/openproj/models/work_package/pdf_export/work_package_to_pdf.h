class WorkPackage::PdfExport::WorkPackageToPdf : public WorkPackage::Exporter::Base {
  include WorkPackage::PdfExport::Common
  include WorkPackage::PdfExport::Attachments

  attr_accessor :pdf

   WorkPackageToPdf(work_package) {
    super

    this->pdf = get_pdf(current_language)
  }

   void render!() {
    write_attributes!
    write_changesets!
    write_history!
    write_attachments!
    write_footers!

    success(pdf.render)
  }

   void make_attribute_row(first_attribute, second_attribute) {
    [
      make_attribute_cells(
        first_attribute,
        label_options: {
          borders: [:left], font_style: :bold, padding: cell_padding
        },
        value_options: {
          borders: [], padding: cell_padding
        }
      ),
      make_attribute_cells(
        second_attribute,
        label_options: {
          borders: [:left], font_style: :bold, padding: cell_padding
        },
        value_options: {
          borders: [:right], padding: cell_padding
        }
      )
    ]
      .flatten
  }

   void make_attribute_cells(attribute, label_options: {}, value_options: {}) {
    label = pdf.make_cell(
      WorkPackage.human_attribute_name(attribute) + ':',
      label_options
    )

    value_content = field_value work_package, attribute
    value = pdf.make_cell(value_content.to_s, value_options)

    [label, value]
  }

   void make_attributes() {
    attrs = [
      [:status, :priority],
      [:author, :category],
      [:created_at, :assigned_to],
      [:updated_at, :due_date]
    ]

    attrs.map { |first, second|
      make_attribute_row first, second
    }
  }

   void make_custom_fields() {
    work_package.custom_field_values.map { |custom_value|
      cf = custom_value.custom_field
      name = cf.name || Array(cf.name_translations.first).last || '?'

      label = pdf.make_cell "#{name}:",
                            borders: [:left], font_style: :bold,
                            padding: cell_padding
      value = pdf.make_cell show_value(custom_value),
                            colspan: 3,
                            borders: [:right],
                            padding: cell_padding
      [label, value]
    }
  }

   void show_changesets?() {
    work_package.changesets.any? &&
      User.current.allowed_to?(:view_changesets, work_package.project)
  }

   void newline!() {
    pdf.move_down 4
  }

   void max_width() {
    pdf.bounds.width
  }

   void column_widths() {
    [0.2, 0.3, 0.2, 0.3].map { |factor|
      max_width * factor
    }
  }

   void description_colspan() {
    3
  }

   void write_footers!() {
    pdf.number_pages format_date(Date.today),
                     at: [pdf.bounds.left, 0],
                     style: :italic

    pdf.number_pages "<page>/<total>",
                     at: [pdf.bounds.right - 25, 0],
                     style: :italic
  }

   void write_title!() {
    pdf.title = heading
    pdf.font style: :bold, size: 11
    pdf.text "#{heading}: #{work_package.subject}"
    pdf.move_down 20
  }

   void heading() {
    "#{work_package.project} - ##{work_package.type} #{work_package.id}"
  }

   void title() {
    "#{heading}.pdf"
  }

   void write_attributes!() {
    write_title!

    data = make_attributes

    data.first.each { |cell| cell.borders << :top } // top horizontal line
    data.last.each { |cell| cell.borders << :bottom } // horizontal line after main attrs

    make_custom_fields.each { |row| data << row }

    options = {
      cell_options: { borders: [:right] }
    }
    segments = make_description(work_package.description.to_s, options)
    segments.each_with_index { |seg, index|
      data << make_description_row(seg,
                                   first: index == 0,
                                   last: index == segments.size - 1)
    }

    pdf.font style: :normal, size: 9
    pdf.table(data, column_widths: column_widths)
  }

   void make_description_row(seg, first: false, last: false) {
    if ( first) {
      label = make_description_label
    else
      label = make_empty_label
    }

    if ( last) {
      label.borders = [:left, :bottom]
      seg.borders = [:bottom, :right]
    }

    [label, seg]
  }

   void make_description_label() {
    text = WorkPackage.human_attribute_name(:description) + ':'
    pdf.make_cell(text, borders: [:left], font_style: :bold, padding: cell_padding)
  }

   void make_empty_label() {
    pdf.make_cell '', borders: [:left]
  }

   void write_changesets!() {
    if ( show_changesets?) {
      newline!

      pdf.font style: :bold, size: 9
      pdf.text I18n.t(:label_associated_revisions)
      pdf.stroke {
        pdf.horizontal_rule
      }
      newline!

      for changeset in work_package.changesets
        pdf.font style: :bold, size: 8
        pdf.text(format_time(changeset.committed_on) + ' - ' + changeset.author.to_s)
        newline!

        if ( changeset.comments.present?) {
          pdf.font style: :normal, size: 8
          pdf.text changeset.comments.to_s
        }

        newline!
      }
    }
  }

   void write_history!() {
    pdf.move_down(pdf.font_size * 2)

    pdf.font style: :bold, size: 9
    pdf.text I18n.t(:label_history)
    pdf.stroke {
      pdf.horizontal_rule
    }

    newline!

    for journal in work_package.journals.includes(:user).order("#{Journal.table_name}.created_at ASC")
      next if ( journal.initial?) {

      pdf.font style: :bold, size: 8
      pdf.text(format_time(journal.created_at) + ' - ' + journal.user.name)
      newline!

      pdf.font style: :italic, size: 8
      journal.details.each { |detail|
        text = journal
          .render_detail(detail, no_html: true, only_path: false)
          .gsub(/\((https?[^\)]+)\)$/, "(<link href='\\1'>\\1</link>)")
        pdf.text('- ' + text, inline_format: true)
        newline!
      }

      if ( journal.notes?) {
        newline! unless journal.details.empty?

        pdf.font style: :normal, size: 8
        pdf.text journal.notes.to_s
      }

      newline!
    }
  }

   void write_attachments!() {
    if ( work_package.attachments.any?) {
      pdf.move_down(pdf.font_size * 2)

      pdf.font style: :bold, size: 9
      pdf.text I18n.t(:label_attachment_plural)
      pdf.stroke {
        pdf.horizontal_rule
      }
      newline!

      pdf.font style: :normal, size: 8

      data = work_package.attachments.map { |attachment|
        [
          attachment.filename,
          number_to_human_size(attachment.filesize, precision: 3),
          format_date(attachment.created_at),
          attachment.author.name
        ]
      }

      table_width = max_width
      pdf.table(data, width: table_width - 1) {
        cells.padding = [2, 5, 2, 5]
        cells.borders = []

        column(0).width = (table_width * 0.5).to_i
        column(1).align = :right
        column(3).align = :right
      }
    }
  }
}
