#pragma once
#include "base_activity_provider.h"
namespace openproj {
namespace models {
namespace Activity {
class NewsActivityProvider : public Activity::BaseActivityProvider {
//  acts_as_activity_provider type: 'news',
//                            permission: :view_news

//   void extend_event_query(_query, _activity) {
//  }

//   void event_query_projection(activity) {
//    [
//      activity_journal_projection_statement(:title, 'title', activity),
//      activity_journal_projection_statement(:project_id, 'project_id', activity)
//    ]
//  }

  protected:

//   void event_title(event, _activity) {
//    event['title']
//  }

//   void event_type(_event, _activity) {
//    'news'
//  }

//   void event_path(event, _activity) {
//    url_helpers.news_path(url_helper_parameter(event))
//  }

//   void event_url(event, _activity) {
//    url_helpers.news_url(url_helper_parameter(event))
//  }

  private:

//   void url_helper_parameter(event) {
//    event['journable_id']
//  }
};
}
}
}