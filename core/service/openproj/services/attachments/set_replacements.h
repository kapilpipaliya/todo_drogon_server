namespace Attachments {
  namespace SetReplacements {
    // extend ActiveSupport::Concern

    included {
      private:

       void set_attributes(attributes) {
        set_attachments_attributes(attributes)

        super
      }

       void set_attachments_attributes(attributes) {
        attachment_ids = attributes.delete(:attachment_ids)

        return unless attachment_ids

        work_package.attachments_replacements = Attachment.where(id: attachment_ids)
      }
    }
  }
}
