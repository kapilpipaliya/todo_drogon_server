#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H


#include "core/tables/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class PaymentMethod
{
public:
    PaymentMethod(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};


Json::Value get_setting_thumb_data(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);

#endif // PAYMENTMETHOD_H
