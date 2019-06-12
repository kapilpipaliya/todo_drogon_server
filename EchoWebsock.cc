#include "EchoWebsock.h"
#include <map>

#include "core/tables/functions.h"

Json::Value getAllData(Table &t, Json::Value &in)
{
    t.updateFilterBase(in[0]);
    t.select();
    return t.getJsonData();
}
Json::Value getAllHeaderData(Table &t)
{
    return t.getJsonHeaderData();
}
Json::Value getAllHiddenColumns(Table &t)
{
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
    auto a = t.m_query.selectedColumns();
    Json::Value r(Json::arrayValue);
    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
        r.append(a[i].offset);
    }
    return r;
}
Json::Value getAllTooltipOffsetColumns(Table &t)
{
    auto a = t.m_query.selectedColumns();
    Json::Value r(Json::arrayValue);
    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
        r.append(a[i].tooltipOffset);
    }
    return r;
}
Json::Value getAllColumnTypes(Table &t)
{
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
        Table a;
        accessorySetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_account_data", [](Json::Value in) {
        Table a;
        accountSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_account_heading_data", [](Json::Value in) {
        Table a;
        accountHeadingSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_color_data", [](Json::Value in) {
        Table a;
        colorSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_entity_data", [](Json::Value in) {
        Table a;
        entitySetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_gem_clarity_data", [](Json::Value in) {
        Table a;
        gemClaritySetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_gem_shape_data", [](Json::Value in) {
        Table a;
        gemShapeSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_gem_size_data", [](Json::Value in) {
        Table a;
        gemSizeSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_gem_type_data", [](Json::Value in) {
        Table a;
        gemTypeSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_global_setting_data", [](Json::Value in) {
        Table a;
        globalSettingSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_log_data", [](Json::Value in) {
        Table a;
        logSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_material_type_data", [](Json::Value in) {
        Table a;
        materialTypeSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_material_data", [](Json::Value in) {
        Table a;
        materialSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_metal_purity_data", [](Json::Value in) {
        Table a;
        metalPuritySetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_order_data", [](Json::Value in) {
        Table a;
        orderSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_part_group_data", [](Json::Value in) {
        Table a;
        partGroupSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_part_type_data", [](Json::Value in) {
        Table a;
        partTypeSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_product_data", [](Json::Value in) {
        Table a;
        productSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_rate_on_data", [](Json::Value in) {
        Table a;
        rateOnSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_sale_data", [](Json::Value in) {
        Table a;
        saleSetupQuery(a);
        return getAllData(a, in);
    });
    fns.emplace("get_transaction_data", [](Json::Value in) {
        Table a;
        transactionSetupQuery(a);
        return getAllData(a, in);
    });

    fns.emplace("get_accessory_h_data", [](Json::Value in) {
        Table a;
        accessorySetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_account_h_data", [](Json::Value in) {
        Table a;
        accountSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_account_heading_h_data", [](Json::Value in) {
        Table a;
        accountHeadingSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_color_h_data", [](Json::Value in) {
        Table a;
        colorSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_entity_h_data", [](Json::Value in) {
        Table a;
        entitySetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_clarity_h_data", [](Json::Value in) {
        Table a;
        gemClaritySetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_shape_h_data", [](Json::Value in) {
        Table a;
        gemShapeSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_size_h_data", [](Json::Value in) {
        Table a;
        gemSizeSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_gem_type_h_data", [](Json::Value in) {
        Table a;
        gemTypeSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_global_setting_h_data", [](Json::Value in) {
        Table a;
        globalSettingSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_log_h_data", [](Json::Value in) {
        Table a;
        logSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_material_type_h_data", [](Json::Value in) {
        Table a;
        materialTypeSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_material_h_data", [](Json::Value in) {
        Table a;
        materialSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_metal_purity_h_data", [](Json::Value in) {
        Table a;
        metalPuritySetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_order_h_data", [](Json::Value in) {
        Table a;
        orderSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_part_group_h_data", [](Json::Value in) {
        Table a;
        partGroupSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_part_type_h_data", [](Json::Value in) {
        Table a;
        partTypeSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_product_h_data", [](Json::Value in) {
        Table a;
        productSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_rate_on_h_data", [](Json::Value in) {
        Table a;
        rateOnSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_sale_h_data", [](Json::Value in) {
        Table a;
        saleSetupQuery(a);
        return getAllHeaderData(a);
    });
    fns.emplace("get_transaction_h_data", [](Json::Value in) {
        Table a;
        transactionSetupQuery(a);
        return getAllHeaderData(a);
    });

    // Hidden columns
    fns.emplace("get_accessory_hidden_columns", [](Json::Value in) {
        Table a;
        accessorySetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_account_hidden_columns", [](Json::Value in) {
        Table a;
        accountSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_account_heading_hidden_columns", [](Json::Value in) {
        Table a;
        accountHeadingSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_color_hidden_columns", [](Json::Value in) {
        Table a;
        colorSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_entity_hidden_columns", [](Json::Value in) {
        Table a;
        entitySetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_clarity_hidden_columns", [](Json::Value in) {
        Table a;
        gemClaritySetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_shape_hidden_columns", [](Json::Value in) {
        Table a;
        gemShapeSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_size_hidden_columns", [](Json::Value in) {
        Table a;
        gemSizeSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_gem_type_hidden_columns", [](Json::Value in) {
        Table a;
        gemTypeSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_global_setting_hidden_columns", [](Json::Value in) {
        Table a;
        globalSettingSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_log_hidden_columns", [](Json::Value in) {
        Table a;
        logSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_material_type_hidden_columns", [](Json::Value in) {
        Table a;
        materialTypeSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_material_hidden_columns", [](Json::Value in) {
        Table a;
        materialSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_metal_purity_hidden_columns", [](Json::Value in) {
        Table a;
        metalPuritySetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_order_hidden_columns", [](Json::Value in) {
        Table a;
        orderSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_part_group_hidden_columns", [](Json::Value in) {
        Table a;
        partGroupSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_part_type_hidden_columns", [](Json::Value in) {
        Table a;
        partTypeSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_product_hidden_columns", [](Json::Value in) {
        Table a;
        productSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_rate_on_hidden_columns", [](Json::Value in) {
        Table a;
        rateOnSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_sale_hidden_columns", [](Json::Value in) {
        Table a;
        saleSetupQuery(a);
        return getAllHiddenColumns(a);
    });
    fns.emplace("get_transaction_hidden_columns", [](Json::Value in) {
        Table a;
        transactionSetupQuery(a);
        return getAllHiddenColumns(a);
    });

    // Offset columns
    fns.emplace("get_accessory_offset_columns", [](Json::Value in) {
        Table a;
        accessorySetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_account_offset_columns", [](Json::Value in) {
        Table a;
        accountSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_account_heading_offset_columns", [](Json::Value in) {
        Table a;
        accountHeadingSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_color_offset_columns", [](Json::Value in) {
        Table a;
        colorSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_entity_offset_columns", [](Json::Value in) {
        Table a;
        entitySetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_clarity_offset_columns", [](Json::Value in) {
        Table a;
        gemClaritySetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_shape_offset_columns", [](Json::Value in) {
        Table a;
        gemShapeSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_size_offset_columns", [](Json::Value in) {
        Table a;
        gemSizeSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_gem_type_offset_columns", [](Json::Value in) {
        Table a;
        gemTypeSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_global_setting_offset_columns", [](Json::Value in) {
        Table a;
        globalSettingSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_log_offset_columns", [](Json::Value in) {
        Table a;
        logSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_material_type_offset_columns", [](Json::Value in) {
        Table a;
        materialTypeSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_material_offset_columns", [](Json::Value in) {
        Table a;
        materialSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_metal_purity_offset_columns", [](Json::Value in) {
        Table a;
        metalPuritySetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_order_offset_columns", [](Json::Value in) {
        Table a;
        orderSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_part_group_offset_columns", [](Json::Value in) {
        Table a;
        partGroupSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_part_type_offset_columns", [](Json::Value in) {
        Table a;
        partTypeSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_product_offset_columns", [](Json::Value in) {
        Table a;
        productSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_rate_on_offset_columns", [](Json::Value in) {
        Table a;
        rateOnSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_sale_offset_columns", [](Json::Value in) {
        Table a;
        saleSetupQuery(a);
        return getAllOffsetColumns(a);
    });
    fns.emplace("get_transaction_offset_columns", [](Json::Value in) {
        Table a;
        transactionSetupQuery(a);
        return getAllOffsetColumns(a);
    });

    // Tooltip Offset columns
    fns.emplace("get_accessory_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        accessorySetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_account_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        accountSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_account_heading_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        accountHeadingSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_color_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        colorSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_entity_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        entitySetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_clarity_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        gemClaritySetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_shape_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        gemShapeSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_size_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        gemSizeSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_gem_type_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        gemTypeSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_global_setting_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        globalSettingSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_log_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        logSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_material_type_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        materialTypeSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_material_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        materialSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_metal_purity_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        metalPuritySetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_order_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        orderSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_part_group_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        partGroupSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_part_type_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        partTypeSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_product_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        productSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_rate_on_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        rateOnSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_sale_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        saleSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });
    fns.emplace("get_transaction_tooltip_offset_columns", [](Json::Value in) {
        Table a;
        transactionSetupQuery(a);
        return getAllTooltipOffsetColumns(a);
    });

    // Column columns
    fns.emplace("get_accessory_column_types", [](Json::Value in) {
        Table a;
        accessorySetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_account_column_types", [](Json::Value in) {
        Table a;
        accountSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_account_heading_column_types", [](Json::Value in) {
        Table a;
        accountHeadingSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_color_column_types", [](Json::Value in) {
        Table a;
        colorSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_entity_column_types", [](Json::Value in) {
        Table a;
        entitySetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_clarity_column_types", [](Json::Value in) {
        Table a;
        gemClaritySetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_shape_column_types", [](Json::Value in) {
        Table a;
        gemShapeSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_size_column_types", [](Json::Value in) {
        Table a;
        gemSizeSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_gem_type_column_types", [](Json::Value in) {
        Table a;
        gemTypeSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_global_setting_column_types", [](Json::Value in) {
        Table a;
        globalSettingSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_log_column_types", [](Json::Value in) {
        Table a;
        logSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_material_type_column_types", [](Json::Value in) {
        Table a;
        materialTypeSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_material_column_types", [](Json::Value in) {
        Table a;
        materialSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_metal_purity_column_types", [](Json::Value in) {
        Table a;
        metalPuritySetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_order_column_types", [](Json::Value in) {
        Table a;
        orderSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_part_group_column_types", [](Json::Value in) {
        Table a;
        partGroupSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_part_type_column_types", [](Json::Value in) {
        Table a;
        partTypeSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_product_column_types", [](Json::Value in) {
        Table a;
        productSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_rate_on_column_types", [](Json::Value in) {
        Table a;
        rateOnSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_sale_column_types", [](Json::Value in) {
        Table a;
        saleSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("get_transaction_column_types", [](Json::Value in) {
        Table a;
        transactionSetupQuery(a);
        return getAllColumnTypes(a);
    });
    fns.emplace("save_accessory_data", [](Json::Value in) {
        fprintf(stdout, "%s\n", in.toStyledString().c_str());
        fflush(stdout);

        auto material_id1 = in.get("material_id", 0).asInt();
        auto slug1 = in.get("slug", "").asString();
        auto name1 = in.get("name", "").asString();

        Table a;
        accessorySetupQuery(a);

        Json::Value ret;
        /* temporary
        bool ok = a.insertRow(material_id1, slug1, name1);
        if (!ok) {
            ret["ok"]=false;
            ret["error"]=a.insertError;
        } else {
            ret["ok"]=true;
        }*/
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
