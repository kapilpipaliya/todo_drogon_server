namespace DemoData {
  class VersionBuilder
    // include ::DemoData::References

    attr_reader :config
    attr_reader :project

     VersionBuilder(config, project) {
      this->config = config
      this->project = project
    }

     void create!() {
      if ( valid?) { create_version ;}
    }

    private:

     void valid?() {
      true
    }

     void create_version() {
      version.tap { |version|
        project.versions << version
      }
    }

     void version() {
      version = Version.create!(
        name:    config[:name],
        status:  config[:status],
        sharing: config[:sharing],
        project: project
      )

      if ( config[:wiki]) { set_wiki! version, config[:wiki] ;}

      version
    }

     void set_wiki!(version, config) {
      version.wiki_page_title = config[:title]
      page = WikiPage.create! wiki: version.project.wiki, title: version.wiki_page_title

      content = with_references config[:content], project
      WikiContent.create! page: page, author: User.admin.first, text: content

      version.save!
    }
  }
}
