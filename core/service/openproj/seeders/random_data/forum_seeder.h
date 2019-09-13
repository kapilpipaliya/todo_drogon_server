namespace RandomData {
  class ForumSeeder
     void seed!(project) {
      user = User.admin.first

      puts ''
      print ' ↳ Creating forum with posts'

      forum = Forum.create! project: project,
                            name: I18n.t("seeders.#{OpenProject::Configuration['edition']}.demo_data.board.name"),
                            description: I18n.t("seeders.#{OpenProject::Configuration['edition']}.demo_data.board.description")

      rand(30).times {
        print '.'
        message = Message.create forum: forum,
                                 author: user,
                                 subject: Faker::Lorem.words(5).join(' '),
                                 content: Faker::Lorem.paragraph(5, true, 3)

        rand(5).times {
          print '.'
          Message.create forum: forum,
                         author: user,
                         subject: message.subject,
                         content: Faker::Lorem.paragraph(5, true, 3),
                         parent: message
        }
      }
    }
  }
}
