#pragma once

#include <drogon/HttpController.h>

using namespace drogon;
namespace demo {
    namespace v1 {
        class User : public drogon::HttpController<User> {
        public:
            METHOD_LIST_BEGIN
                //use METHOD_ADD to add your custom processing function here;
                //METHOD_ADD(User::get,"/get/{2}/{1}",Get);//path is /demo/v1/User/get/{arg2}/{arg1}
                //METHOD_ADD(User::your_method_name,"/{1}/{2}/list",Get);//path is /demo/v1/User/{arg1}/{arg2}/list
                //ADD_METHOD_TO(User::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /demo/v1//absolute/path/{arg1}/{arg2}/list

                METHOD_ADD(User::login, "/token?userId={1}&passwd={2}", Post, Options);
                METHOD_ADD(User::getInfo, "/{1}/info?token={2}", Get, Options);

                METHOD_ADD(User::download, "/download", Get);
                METHOD_ADD(User::download_id, "/download_id", Get);
                METHOD_ADD(User::thumb_id, "/thumb_id", Get);

            METHOD_LIST_END

            //your declaration of processing function maybe like this:
            //void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,int p1,std::string p2);
            //void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
            void login(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string &&userId,
                       const std::string &password);

            void getInfo(const HttpRequestPtr &req,
                         std::function<void(const HttpResponsePtr &)> &&callback,
                         const std::string& userId,
                         const std::string &token) const;


            void download(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
            void download_id(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
            void thumb_id(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        };
    }
}
