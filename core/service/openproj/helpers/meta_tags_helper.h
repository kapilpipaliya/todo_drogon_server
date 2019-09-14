namespace MetaTagsHelper {
  //
  // Use meta-tags to output title and site name
   void output_title_and_meta_tags() {
    display_meta_tags site: Setting.app_title,
                      title: html_title_parts,
                      separator: ' | ', // Update the TitleService when changing this!
                      reverse: true
  }

  //
  // Writer of html_title as string
   void html_title(*args) {
    title = []

    raise "Don't use html_title getter" if ( args.empty?) {

    this->html_title ||= []
    this->html_title += args
  }

  //
  // The html title parts currently defined
   void html_title_parts() {
    [].tap { |parts|
      parts << h(this->project.name) if ( this->project) {
      parts.concat this->html_title.map(&:to_s) if ( this->html_title) {
    }
  }
}
