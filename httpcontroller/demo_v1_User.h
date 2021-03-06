#pragma once
#include <drogon/HttpController.h>

namespace http::v1 {
class User : public drogon::HttpController<User> {
 public:
  METHOD_LIST_BEGIN
  // use METHOD_ADD to add your custom processing function here;
  // METHOD_ADD(User::get,"/get/{2}/{1}",Get);//path is
  // /demo/v1/User/get/{arg2}/{arg1}
  // METHOD_ADD(User::your_method_name,"/{1}/{2}/list",Get);//path is
  // /demo/v1/User/{arg1}/{arg2}/list
  // ADD_METHOD_TO(User::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path
  // is /demo/v1//absolute/path/{arg1}/{arg2}/list
  METHOD_ADD(User::download_id, "/download_id/{1}/{2}", drogon::Get);
  METHOD_ADD(User::thumb_id, "/thumb_id/{1}/{2}", drogon::Get);
  METHOD_ADD(User::music_id, "/music_id/{1}", drogon::Get);
  METHOD_LIST_END
  // void get(const drogon::HttpRequestPtr& req,std::function<void (const
  // HttpResponsePtr &)> &&callback,int p1,std::string p2); void
  // your_method_name(const drogon::HttpRequestPtr& req,std::function<void
  // (const drogon::HttpResponsePtr &)> &&callback,double p1,int p2) const;
  void download_id(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback, long id,
      int version);
  void thumb_id(const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                long id, int version);
  void music_id(const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                const std::string &file);
};
}  // namespace http::v1
