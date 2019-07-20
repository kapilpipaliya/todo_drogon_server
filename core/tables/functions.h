#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include <QString>


#include <json/json.h>
#include "core/tables/Table.h"

#include <drogon/WebSocketController.h>
using namespace drogon;


#define getAllDataMacro(s, f)\
    fns.emplace("get_"  s  "_data", [](const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
        Table a;\
        f(a);\
        Json::Value jresult;\
        jresult[0]=event_name;\
        jresult[1]=getAllData(a, in);\
        wsConnPtr->send(jresult.toStyledString());\
    });
#define getAllHDataMacro(s, f)\
    fns.emplace("get_" s "_h_data", [](const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
        Table a;\
        f(a);\
        Json::Value jresult;\
        jresult[0]=event_name;\
        jresult[1]=getAllHeaderData(a);\
        wsConnPtr->send(jresult.toStyledString());\
    });
//#define getAllHiddenColumnsMacro(s, f)\
//    fns.emplace("get_" s "_hi_columns_data", [](const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
//        Table a;\
//        f(a);\
//        Json::Value jresult;\
//        jresult[0]=event_name;\
//        jresult[1]=getAllHiddenColumns(a);\
//        wsConnPtr->send(jresult.toStyledString());\
//    });
//#define getAllOffsetColumnsMacro(s, f)\
//    fns.emplace("get_" s "_o_columns_data", [](const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
//        Table a;\
//        f(a);\
//        Json::Value jresult;\
//        jresult[0]=event_name;\
//        jresult[1]=getAllOffsetColumns(a);\
//        wsConnPtr->send(jresult.toStyledString());\
//    });
//#define getAllTooltipOffsetColumnsMacro(s, f)\
//    fns.emplace("get_" s "_t_offset_columns_data", [](const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
//        Table a;\
//        f(a);\
//        Json::Value jresult;\
//        jresult[0]=event_name;\
//        jresult[1]=getAllTooltipOffsetColumns(a);\
//        wsConnPtr->send(jresult.toStyledString());\
//    });
//#define getAllColumnTypesMacro(s, f)\
//    fns.emplace("get_" s "_column_types", [](const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
//        Table a;\
//        f(a);\
//        Json::Value jresult;\
//        jresult[0]=event_name;\
//        jresult[1]=getAllColumnTypes(a);\
//        wsConnPtr->send(jresult.toStyledString());\
//    });
#define getAllTheColumns(s, f)\
    getAllDataMacro(s, f)\
    getAllHDataMacro(s, f)

#define CRUD(s, s1)\
    getAllTheColumns(s, query_##s1)\
    fns.emplace("save_" s "_data", save_##s1);\
    fns.emplace("del_" s "_data", delete_##s1);

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}


// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

static inline void ReplaceAll2(std::string &str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

Json::Value getAllData(Table &t, Json::Value &in);
Json::Value getAllHeaderData(Table &t);
//Json::Value getAllHiddenColumns(Table &t);
//Json::Value getAllOffsetColumns(Table &t);
//Json::Value getAllTooltipOffsetColumns(Table &t);
//Json::Value getAllColumnTypes(Table &t);

QString rtrimChar(const QString& s, QChar c);
std::string rtrimChar(const std::string& s, char c);

// Material:
void query_metal(Table & t);
void query_purity(Table & t);
void query_tone(Table & t);
void query_accessory(Table & t);


void query_clarity(Table & t);
void query_shape(Table & t);
void query_d_color(Table & t);
void query_cs_color(Table & t);
void query_size(Table & t);
void query_diamond_size(Table & t);
void query_color_stone_size(Table & t);

//
void query_account(Table & t);
void query_account_heading(Table & t);

// entity
void query_address_type(Table & t);
void query_contact_type(Table & t);
void query_entity_type(Table & t);
void query_entity(Table & t);

//
void query_global_setting(Table & t);
void query_currency(Table & t);
void query_log(Table & t);

//
void query_order(Table & t);
//
void query_part_group(Table & t);
void query_part_type(Table & t);
void query_sale(Table & t);
void query_transaction(Table & t);
//--------------Products
void query_product_options(Table & t);
void query_product(Table & t);
void query_post(Table & t);
void query_category(Table & t);
void query_tag(Table & t);
void query_shipping_class(Table & t);
void query_setting_type(Table & t);
void query_certified_by(Table & t);

//Extra


void serveImages(std::string & path);

void processCookie(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr);
void deleteSession(const WebSocketConnectionPtr& wsConnPtr);
std::string getEventName(const WebSocketConnectionPtr& wsConnPtr);

#endif // FUNCTIONS_H
