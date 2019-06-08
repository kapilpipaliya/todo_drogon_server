#include "EchoWebsock.h"
#include <map>


#include "core/tables/Accessory.h"
#include "core/tables/Account.h"
#include "core/tables/AccountHeading.h"
#include "core/tables/Color.h"
#include "core/tables/Entity.h"
#include "core/tables/GemClarity.h"
#include "core/tables/GemShape.h"
#include "core/tables/GemSize.h"
#include "core/tables/GemType.h"
#include "core/tables/GlobalSetting.h"
#include "core/tables/Log.h"
#include "core/tables/Material.h"
#include "core/tables/MaterialType.h"
#include "core/tables/MetalPurity.h"
#include "core/tables/Order.h"
#include "core/tables/PartGroup.h"
#include "core/tables/PartType.h"
#include "core/tables/Product.h"
#include "core/tables/RateOn.h"
#include "core/tables/Sale.h"
#include "core/tables/Transaction.h"

Json::Value getAllData(Table &t, Json::Value &in)
{
    t.init();

    t.updateFilterBase(in[0]);
    t.select();
    return t.getJsonData();
}
Json::Value getAllHeaderData(Table &t)
{
    t.init();
    return t.getJsonHeaderData();
}
Json::Value getAllHiddenColumns(Table &t)
{
    t.init();
    auto a = t.m_query.selectedColumns();
    Json::Value r(Json::arrayValue);
    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
        if(!a[i].isVisible) {
            r.append(i);
        }
    }
    return r;
}
Json::Value getAllOffsetColumns(Table &t)
{
    t.init();
    auto a = t.m_query.selectedColumns();
    Json::Value r(Json::arrayValue);
    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
        r.append(a[i].offset);
    }
    return r;
}
Json::Value getAllTooltipOffsetColumns(Table &t)
{
    t.init();
    auto a = t.m_query.selectedColumns();
    Json::Value r(Json::arrayValue);
    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
        r.append(a[i].tooltipOffset);
    }
    return r;
}
Json::Value getAllColumnTypes(Table &t)
{
    t.init();
    auto a = t.m_query.selectedColumns();
    Json::Value r(Json::arrayValue);
    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
        r.append((int)a[i].column_type);
    }
    return r;
}
std::map<std::string, std::function<Json::Value(Json::Value in)> > fns;


void EchoWebsock::defineFns()
{

    //fns.insert(std::pair<std::string, std::function<Json::Value()>>("get_accessory_data", get_accessory_data));
    //Inserts a new element in the map if its key is unique.

    fns.emplace("get_accessory_data", [](Json::Value in) {
        Accessory a;
        return getAllData(a, in);
    });
    fns.emplace("get_account_data", [](Json::Value in) {
        Account a;
        return getAllData(a, in);
    });
    fns.emplace("get_account_heading_data", [](Json::Value in) {
        AccountHeading a;
        return getAllData(a, in);
    });
    fns.emplace("get_color_data", [](Json::Value in) {
        Color a;
        return getAllData(a, in);
    });
    fns.emplace("get_entity_data", [](Json::Value in) {
        Entity a;
        return getAllData(a, in);
    });
    fns.emplace("get_gem_clarity_data", [](Json::Value in) {
        GemClarity a;
        return getAllData(a, in);
    });
    fns.emplace("get_gem_shape_data", [](Json::Value in) {
        GemShape a;
        return getAllData(a, in);
    });
    fns.emplace("get_gem_size_data", [](Json::Value in) {
        GemSize a;
        return getAllData(a, in);
    });
    fns.emplace("get_gem_type_data", [](Json::Value in) {
        GemType a;
        return getAllData(a, in);
    });
    fns.emplace("get_global_setting_data", [](Json::Value in) {
        GlobalSetting a;
        return getAllData(a, in);
    });
    fns.emplace("get_log_data", [](Json::Value in) {
        Log a;
        return getAllData(a, in);
    });
    fns.emplace("get_material_type_data", [](Json::Value in) {
        MaterialType a;
        return getAllData(a, in);
    });
    fns.emplace("get_material_data", [](Json::Value in) {
        Material a;
        return getAllData(a, in);
    });
    fns.emplace("get_metal_purity_data", [](Json::Value in) {
        MetalPurity a;
        return getAllData(a, in);
    });
    fns.emplace("get_order_data", [](Json::Value in) {
        Order a;
        return getAllData(a, in);
    });
    fns.emplace("get_part_group_data", [](Json::Value in) {
        PartGroup a;
        return getAllData(a, in);
    });
    fns.emplace("get_part_type_data", [](Json::Value in) {
        PartType a;
        return getAllData(a, in);
    });
    fns.emplace("get_product_data", [](Json::Value in) {
        Product a;
        return getAllData(a, in);
    });
    fns.emplace("get_rate_on_data", [](Json::Value in) {
        RateOn a;
        return getAllData(a, in);
    });
    fns.emplace("get_sale_data", [](Json::Value in) {
        Sale a;
        return getAllData(a, in);
    });
    fns.emplace("get_transaction_data", [](Json::Value in) {
        Transaction a;
        return getAllData(a, in);
    });

    fns.emplace("get_accessory_h_data", [](Json::Value in) {
        Accessory a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_account_h_data", [](Json::Value in) {
        Account a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_account_heading_h_data", [](Json::Value in) {
        AccountHeading a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_color_h_data", [](Json::Value in) {
        Color a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_entity_h_data", [](Json::Value in) {
        Entity a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_clarity_h_data", [](Json::Value in) {
        GemClarity a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_shape_h_data", [](Json::Value in) {
        GemShape a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_size_h_data", [](Json::Value in) {
        GemSize a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_type_h_data", [](Json::Value in) {
        GemType a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_global_setting_h_data", [](Json::Value in) {
        GlobalSetting a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_log_h_data", [](Json::Value in) {
        Log a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_material_type_h_data", [](Json::Value in) {
        MaterialType a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_material_h_data", [](Json::Value in) {
        Material a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_metal_purity_h_data", [](Json::Value in) {
        MetalPurity a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_order_h_data", [](Json::Value in) {
        Order a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_part_group_h_data", [](Json::Value in) {
        PartGroup a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_part_type_h_data", [](Json::Value in) {
        PartType a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_product_h_data", [](Json::Value in) {
        Product a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_rate_on_h_data", [](Json::Value in) {
        RateOn a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_sale_h_data", [](Json::Value in) {
        Sale a;
        return getAllHeaderData(a);
    });
    fns.emplace("get_transaction_h_data", [](Json::Value in) {
        Transaction a;
        return getAllHeaderData(a);
    });

    // Hidden columns
    fns.emplace("get_accessory_hidden_columns", [](Json::Value in) {
        Accessory a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_account_hidden_columns", [](Json::Value in) {
        Account a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_account_heading_hidden_columns", [](Json::Value in) {
        AccountHeading a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_color_hidden_columns", [](Json::Value in) {
        Color a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_entity_hidden_columns", [](Json::Value in) {
        Entity a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_clarity_hidden_columns", [](Json::Value in) {
        GemClarity a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_shape_hidden_columns", [](Json::Value in) {
        GemShape a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_size_hidden_columns", [](Json::Value in) {
        GemSize a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_type_hidden_columns", [](Json::Value in) {
        GemType a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_global_setting_hidden_columns", [](Json::Value in) {
        GlobalSetting a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_log_hidden_columns", [](Json::Value in) {
        Log a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_material_type_hidden_columns", [](Json::Value in) {
        MaterialType a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_material_hidden_columns", [](Json::Value in) {
        Material a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_metal_purity_hidden_columns", [](Json::Value in) {
        MetalPurity a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_order_hidden_columns", [](Json::Value in) {
        Order a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_part_group_hidden_columns", [](Json::Value in) {
        PartGroup a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_part_type_hidden_columns", [](Json::Value in) {
        PartType a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_product_hidden_columns", [](Json::Value in) {
        Product a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_rate_on_hidden_columns", [](Json::Value in) {
        RateOn a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_sale_hidden_columns", [](Json::Value in) {
        Sale a;
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_transaction_hidden_columns", [](Json::Value in) {
        Transaction a;
        return getAllHiddenColumns(a);
    });

    // Offset columns
    fns.emplace("get_accessory_offset_columns", [](Json::Value in) {
        Accessory a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_account_offset_columns", [](Json::Value in) {
        Account a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_account_heading_offset_columns", [](Json::Value in) {
        AccountHeading a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_color_offset_columns", [](Json::Value in) {
        Color a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_entity_offset_columns", [](Json::Value in) {
        Entity a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_clarity_offset_columns", [](Json::Value in) {
        GemClarity a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_shape_offset_columns", [](Json::Value in) {
        GemShape a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_size_offset_columns", [](Json::Value in) {
        GemSize a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_type_offset_columns", [](Json::Value in) {
        GemType a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_global_setting_offset_columns", [](Json::Value in) {
        GlobalSetting a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_log_offset_columns", [](Json::Value in) {
        Log a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_material_type_offset_columns", [](Json::Value in) {
        MaterialType a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_material_offset_columns", [](Json::Value in) {
        Material a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_metal_purity_offset_columns", [](Json::Value in) {
        MetalPurity a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_order_offset_columns", [](Json::Value in) {
        Order a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_part_group_offset_columns", [](Json::Value in) {
        PartGroup a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_part_type_offset_columns", [](Json::Value in) {
        PartType a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_product_offset_columns", [](Json::Value in) {
        Product a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_rate_on_offset_columns", [](Json::Value in) {
        RateOn a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_sale_offset_columns", [](Json::Value in) {
        Sale a;
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_transaction_offset_columns", [](Json::Value in) {
        Transaction a;
        return getAllOffsetColumns(a);
    });

    // Tooltip Offset columns
    fns.emplace("get_accessory_tooltip_offset_columns", [](Json::Value in) {
        Accessory a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_account_tooltip_offset_columns", [](Json::Value in) {
        Account a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_account_heading_tooltip_offset_columns", [](Json::Value in) {
        AccountHeading a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_color_tooltip_offset_columns", [](Json::Value in) {
        Color a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_entity_tooltip_offset_columns", [](Json::Value in) {
        Entity a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_clarity_tooltip_offset_columns", [](Json::Value in) {
        GemClarity a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_shape_tooltip_offset_columns", [](Json::Value in) {
        GemShape a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_size_tooltip_offset_columns", [](Json::Value in) {
        GemSize a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_type_tooltip_offset_columns", [](Json::Value in) {
        GemType a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_global_setting_tooltip_offset_columns", [](Json::Value in) {
        GlobalSetting a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_log_tooltip_offset_columns", [](Json::Value in) {
        Log a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_material_type_tooltip_offset_columns", [](Json::Value in) {
        MaterialType a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_material_tooltip_offset_columns", [](Json::Value in) {
        Material a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_metal_purity_tooltip_offset_columns", [](Json::Value in) {
        MetalPurity a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_order_tooltip_offset_columns", [](Json::Value in) {
        Order a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_part_group_tooltip_offset_columns", [](Json::Value in) {
        PartGroup a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_part_type_tooltip_offset_columns", [](Json::Value in) {
        PartType a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_product_tooltip_offset_columns", [](Json::Value in) {
        Product a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_rate_on_tooltip_offset_columns", [](Json::Value in) {
        RateOn a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_sale_tooltip_offset_columns", [](Json::Value in) {
        Sale a;
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_transaction_tooltip_offset_columns", [](Json::Value in) {
        Transaction a;
        return getAllTooltipOffsetColumns(a);
    });

    // Column columns
    fns.emplace("get_accessory_column_types", [](Json::Value in) {
        Accessory a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_account_column_types", [](Json::Value in) {
        Account a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_account_heading_column_types", [](Json::Value in) {
        AccountHeading a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_color_column_types", [](Json::Value in) {
        Color a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_entity_column_types", [](Json::Value in) {
        Entity a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_clarity_column_types", [](Json::Value in) {
        GemClarity a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_shape_column_types", [](Json::Value in) {
        GemShape a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_size_column_types", [](Json::Value in) {
        GemSize a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_type_column_types", [](Json::Value in) {
        GemType a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_global_setting_column_types", [](Json::Value in) {
        GlobalSetting a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_log_column_types", [](Json::Value in) {
        Log a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_material_type_column_types", [](Json::Value in) {
        MaterialType a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_material_column_types", [](Json::Value in) {
        Material a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_metal_purity_column_types", [](Json::Value in) {
        MetalPurity a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_order_column_types", [](Json::Value in) {
        Order a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_part_group_column_types", [](Json::Value in) {
        PartGroup a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_part_type_column_types", [](Json::Value in) {
        PartType a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_product_column_types", [](Json::Value in) {
        Product a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_rate_on_column_types", [](Json::Value in) {
        RateOn a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_sale_column_types", [](Json::Value in) {
        Sale a;
        return getAllColumnTypes(a);
    });
    fns.emplace("get_transaction_column_types", [](Json::Value in) {
        Transaction a;
        return getAllColumnTypes(a);
    });
    fns.emplace("save_accessory_data", [](Json::Value in) {
        fprintf(stdout, "%s\n", in.toStyledString().c_str());
        fflush(stdout);

        auto material_id1 = in.get("material_id", 0).asInt();
        auto slug1 = in.get("slug", "").asString();
        auto name1 = in.get("name", "").asString();

        Accessory a;

        bool ok = a.insertRow(material_id1, slug1, name1);

        Json::Value ret;
        if (!ok) {
            ret["ok"]=false;
            ret["error"]=a.insertError;
        } else {
            ret["ok"]=true;
        }
        return ret;
    });
}

void EchoWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    //debug
    //fprintf(stdout, "%s\n", message.c_str());
    //fflush(stdout);

    Json::Reader reader;
    Json::Value valin;
    reader.parse(message,  valin);

    if (valin.type() != Json::ValueType::arrayValue) {
        return wsConnPtr->send("");
    }

    auto event = valin[0].asString();
    auto data = valin[1];

    Json::Value jresult;
    jresult[0]=event;
    auto f = fns.find(event);
    if (f != fns.end()) {
        jresult[1]=f->second(data);
    } else {
        jresult[1]=Json::arrayValue;
    }
    // send json according to event result:
    wsConnPtr->send(jresult.toStyledString());
}
void EchoWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
    // create connection to the database and keep it open.
}
void EchoWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
