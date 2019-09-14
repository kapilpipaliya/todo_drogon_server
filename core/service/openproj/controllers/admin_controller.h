#pragma once
#include "application_controller.h"
class AdminController : public ApplicationController {
public:
  // layout 'admin'

  // before_action :require_admin

  // menu_item :plugins, only: [:plugins]
  // menu_item :info, only: [:info]
  // menu_item :admin_overview, only: [:index]

   void index() {
//    this->menu_nodes = Redmine::MenuManager.items(:admin_menu).children
//    this->menu_nodes.delete_if ( { |node| node.name === :enterprise } unless OpenProject::Configuration.ee_manager_visible?) {
//    this->menu_nodes.delete_if ( { |node| node.name === :admin_overview }) {
  }

   void projects() {
//    redirect_to controller: 'projects', action: 'index'
  }

   void plugins() {
//    this->plugins = Redmine::Plugin.all.sort
  }

   void test_email() {
//    raise_delivery_errors = ActionMailer::Base.raise_delivery_errors
//    // Force ActionMailer to raise delivery errors so we can catch it
//    ActionMailer::Base.raise_delivery_errors = true
//    begin
//      this->test = UserMailer.test_mail(User.current).deliver_now
//      flash[:notice] = I18n.t(:notice_email_sent, value: User.current.mail)
//    rescue => e
//      flash[:error] = I18n.t(:notice_email_error, value: Redmine::CodesetUtil.replace_invalid_utf8(e.message.dup))
//    }
//    ActionMailer::Base.raise_delivery_errors = raise_delivery_errors
//    redirect_to controller: '/settings', action: 'edit', tab: 'notifications'
  }

   void force_user_language() {
//    available_languages = Setting.find_by(name: 'available_languages').value
//    User.where(['language not in (?)', available_languages]).each { |u|
//      u.language = Setting.default_language
//      u.save
//    }

//    redirect_to :back
  }

   void info() {
//    this->db_adapter_name = ActiveRecord::Base.connection.adapter_name
//    this->checklist = [
//      [:text_default_administrator_account_changed, User.default_admin_account_changed?],
//      [:text_database_allows_tsv, OpenProject::Database.allows_tsv?]
//    ]

//    // Add local directory test if ( we're not using fog) {
//    if ( OpenProject::Configuration.file_storage?) {
//      repository_writable = File.writable?(OpenProject::Configuration.attachments_storage_path)
//      this->checklist << [:text_file_repository_writable, repository_writable]
//    }

//    if ( OpenProject::Database.allows_tsv?) {
//      this->checklist += plaintext_extraction_checks
//    }

//    this->storage_information = OpenProject::Storage.mount_information
  }

   void default_breadcrumb() {
//    case params[:action]
//    when 'plugins'
//      l(:label_plugins)
//    when 'info'
//      l(:label_information)
//    }
  }

   bool show_local_breadcrumb() {
    return true;
  }

  private:

   void plaintext_extraction_checks() {
//    [
//      [:'extraction.available.pdftotext', Plaintext::PdfHandler.available?],
//      [:'extraction.available.unrtf',     Plaintext::RtfHandler.available?],
//      [:'extraction.available.catdoc',    Plaintext::DocHandler.available?],
//      [:'extraction.available.xls2csv',   Plaintext::XlsHandler.available?],
//      [:'extraction.available.catppt',    Plaintext::PptHandler.available?],
//      [:'extraction.available.tesseract', Plaintext::ImageHandler.available?]
//    ]
  }
};
