#pragma once
#include <drogon/HttpController.h>

using namespace drogon;
namespace demo
{
namespace v1
{
class User:public drogon::HttpController<User>
{
public:
    METHOD_LIST_BEGIN
    //use METHOD_ADD to add your custom processing function here;
    //METHOD_ADD(User::get,"/get/{2}/{1}",Get);//path is /demo/v1/User/get/{arg2}/{arg1}
    //METHOD_ADD(User::your_method_name,"/{1}/{2}/list",Get);//path is /demo/v1/User/{arg1}/{arg2}/list
    //ADD_METHOD_TO(User::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /demo/v1//absolute/path/{arg1}/{arg2}/list


    METHOD_ADD(User::allAccessory,"/accessories",Get, Options);
    METHOD_ADD(User::allAccount,"/accounts",Get, Options);
    METHOD_ADD(User::allAccountHeading,"/account_headings",Get, Options);
    METHOD_ADD(User::allColor,"/colors",Get, Options);
    METHOD_ADD(User::allEntity,"/entities",Get, Options);
    METHOD_ADD(User::allGemClarity,"/clarities",Get, Options);
    METHOD_ADD(User::allGemShape,"/shapes",Get, Options);
    METHOD_ADD(User::allGlobalSetting,"/global_settings",Get, Options);
    METHOD_ADD(User::allLog,"/logs",Get, Options);
    METHOD_ADD(User::allMaterial,"/materials",Get, Options);
    //METHOD_ADD(User::allMaterialType,"/material_types",Get, Options);
    METHOD_ADD(User::allMetalPurity,"/purities",Get, Options);
    METHOD_ADD(User::allOrder,"/orders",Get, Options);
    METHOD_ADD(User::allPartGroup,"/part_groups",Get, Options);
    METHOD_ADD(User::allPartType,"/part_types",Get, Options);
    METHOD_ADD(User::allProduct,"/products",Get, Options);
    METHOD_ADD(User::allSale,"/sales",Get, Options);
    METHOD_ADD(User::allTransaction,"/transactions",Get, Options);

    METHOD_ADD(User::login,"/token?userId={1}&passwd={2}",Post,Options);
    METHOD_ADD(User::getInfo,"/{1}/info?token={2}",Get,Options);

    METHOD_ADD(User::newForm,"/accessory",Post,Options);

    METHOD_ADD(User::download, "/download", Get);
    METHOD_ADD(User::download_id, "/download_id", Get);

    METHOD_LIST_END
    //your declaration of processing function maybe like this:
    //void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,int p1,std::string p2);
    //void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
    void login(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string &&userId,
               const std::string &password);
    void newForm(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback);

    void getInfo(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 std::string userId,
                 const std::string &token) const;
    void allAccessory(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allAccount(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allAccountHeading(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allColor(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allEntity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allGemClarity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allGemShape(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allGlobalSetting(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allLog(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allMaterial(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    //void allMaterialType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allMetalPurity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allOrder(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allPartGroup(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allPartType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allProduct(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allSale(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void allTransaction(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void download(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void download_id(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
}
}
