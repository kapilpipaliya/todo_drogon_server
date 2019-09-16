#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
  class WikiSeeder : public Seeder {
  public:
//    attr_reader :project, :key

//     WikiSeeder(project, key) {
//      this->project = project
//      this->key = key
//    }

     void seed_data() {
//      text = project_data_for(key, 'wiki')

//      if ( text.is_a?(String) && text.start_with?("translation missing")) { return ;}

//      user = User.admin.first

//      if ( text.is_a? String) {
//        text = [{title: "Wiki", content: text}]
//      }

//      print '    ↳ Creating wikis'

//      Array(text).each { |data|
//        create_wiki_page!(
//          data,
//          project: project,
//          user: user
//        )
//      }

//      puts
    }

//     void create_wiki_page!(data, project:, user:, parent: nil) {
//      wiki_page = WikiPage.create!(
//        wiki:  project.wiki,
//        title: data[:title],
//        parent: parent
//      )

//      print '.'
//      WikiContent.create!(
//        page:   wiki_page,
//        author: user,
//        text:   data[:content]
//      )

//      if ( data[:children]) {
//        Array(data[:children]).each { |child_data|
//          create_wiki_page!(
//            child_data,
//            project: project,
//            user: user,
//            parent: wiki_page
//          )
//        }
//      }
//    }
  };
}
}
}
