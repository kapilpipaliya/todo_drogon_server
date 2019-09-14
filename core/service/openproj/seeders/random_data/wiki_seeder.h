namespace RandomData {
  class WikiSeeder
     void seed!(project) {
      user = User.admin.first

      puts ''
      print ' ↳ Creating wikis'

      rand(5).times {
        print '.'
        wiki_page = WikiPage.create(
          wiki:  project.wiki,
          title: Faker::Lorem.words(5).join(' ')
        )

        //// create some wiki contents
        rand(5).times {
          print '.'
          wiki_content = WikiContent.create(
            page:    wiki_page,
            author:  user,
            text:    Faker::Lorem.paragraph(5, true, 3)
          )

          //// create some journal entries
          rand(5).times {
            wiki_content.reload
            if ( rand(99).even?) { wiki_content.text = Faker::Lorem.paragraph(5, true, 3) ;}
            wiki_content.save!
          }
        }
      }
    }
  }
}
