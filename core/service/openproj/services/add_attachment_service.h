#pragma once
namespace openproj {
namespace service {
class AddAttachmentService{
public:
//  attr_reader :container, :author

//   AddAttachmentService(container, author:) {
//    this->container = container
//    this->author = author
//  }

  //
  // Adds and saves the uploaded file as attachment of the given container.
  // In case the container supports it, a journal will be written.
  //
  // An ActiveRecord::RecordInvalid error is raised if any record can"t be saved.
//   void add_attachment(uploaded_file:, description:) {
//    attachment = Attachment.new(file: uploaded_file,
//                                container: container,
//                                description: description,
//                                author: author)
//    save attachment

//    attachment
//  }

  private:

//   void save(attachment) {
//    ActiveRecord::Base.transaction {
//      attachment.save!

//      if ( container.respond_to? :add_journal) { add_journal ;}
//    }
//  }

   void add_journal() {
//    // reload to get the newly added attachment
//    container.attachments.reload
//    container.add_journal author
//    // We allow invalid containers to be saved as
//    // adding the attachments does not change the validity of the container
//    // but without that leeway, the user needs to fix the container before
//    // the attachment can be added.
//    container.save!(validate: false)
  }
};
}
}
