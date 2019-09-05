#include "txn.h"
using namespace  jadmin;

Txn::Txn(const JAdminContextPtr &context_): context(context_)
{

    t.m_table = sqlb::ObjectIdentifier("account", "txn", "a");
}

    void Txn::setupTable()
{

        t.m_query = sqlb::Query(t.m_table);

            //m_query.setRowIdColumn("id");
            t.m_query.selectedColumns() = {
                sqlb::SelectedColumn({"id", "id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"Journal Type", "journal_type_id", "", "a", PG_TYPES::INT8, true, 1, 1}),
                sqlb::SelectedColumn({"jt_name", "name", "", "jt", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Party", "party_id", "", "a", PG_TYPES::INT8, true, 1, 1}),
                sqlb::SelectedColumn({"party_slug", "slug", "", "party", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"no", "no", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"sequence_id", "sequence_id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"Date", "date", "", "a", PG_TYPES::TIMESTAMP}),
                sqlb::SelectedColumn({"entity_id", "entity_id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"account_id", "account_id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"tax_included", "tax_included", "", "a", PG_TYPES::BOOL}),
                sqlb::SelectedColumn({"due_date", "due_date", "", "a", PG_TYPES::TIMESTAMP}),
                sqlb::SelectedColumn({"till", "till", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"order_number", "order_number", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"quo_number", "quo_number", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"Currency", "currency_id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"invoice", "invoice", "", "a", PG_TYPES::BOOL}),
                sqlb::SelectedColumn({"amount_bc", "amount_bc", "", "a", PG_TYPES::DOUBLE}),
                sqlb::SelectedColumn({"amount_tc", "amount_tc", "", "a", PG_TYPES::DOUBLE}),
                sqlb::SelectedColumn({"net_amount_bc", "net_amount_bc", "", "a", PG_TYPES::DOUBLE}),
                sqlb::SelectedColumn({"net_amount_tc", "net_amount_tc", "", "a", PG_TYPES::DOUBLE}),
                sqlb::SelectedColumn({"notes", "notes", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"internal_notes", "internal_notes", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"description", "description", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"status_id", "status_id", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"branch_id", "branch_id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"ship_via", "ship_via", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"language_code", "language_code", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"po_number", "po_number", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"shipping_point", "shipping_point", "", "a", PG_TYPES::TEXT}),
                sqlb::SelectedColumn({"on_hold", "on_hold", "", "a", PG_TYPES::BOOL}),
                sqlb::SelectedColumn({"force_closed", "force_closed", "", "a", PG_TYPES::BOOL}),
                sqlb::SelectedColumn({"reverse", "reverse", "", "a", PG_TYPES::BOOL}),
                sqlb::SelectedColumn({"terms", "terms", "", "a", PG_TYPES::INT4}),
                sqlb::SelectedColumn({"is_return", "is_return", "", "a", PG_TYPES::BOOL}),
                // sqlb::SelectedColumn({"created_date", "created_date", "", "a", PG_TYPES::date}),
                sqlb::SelectedColumn({"is_approved", "is_approved", "", "a", PG_TYPES::BOOL}),
                sqlb::SelectedColumn({"approved_by_id", "approved_by_id", "", "a", PG_TYPES::INT8}),
                sqlb::SelectedColumn({"approved_at", "approved_at", "", "a", PG_TYPES::TIMESTAMP}),
                sqlb::SelectedColumn({"order_item", "order_item",
                                      "json_agg( distinct jsonb_build_array(o_i.id, o_i.post_id, o_i.pcs, o_i.purity_id, o_i.tone_id, o_i.clarity_id, o_i.price, o_i.instruction))",
                                      "o_i", PG_TYPES::PSJSON, false}),

                sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
                sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
                sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
                sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
                };

            auto jt = sqlb::ObjectIdentifier("account", "journal_type", "jt");
        auto party = sqlb::ObjectIdentifier("entity", "entity", "party");
        auto order_item = sqlb::ObjectIdentifier("order1", "order_item", "o_i");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

            t.m_query.joins() = {
                sqlb::Join("left", jt, "jt.id = a.journal_type_id"),
                sqlb::Join("left", party, "party.id = a.party_id"),
                sqlb::Join("left", order_item, "o_i.txn_id = a.id"),
                sqlb::Join("left", u1, "a.create_user_id = u1.id"),
                sqlb::Join("left", u2, "a.update_user_id = u2.id"),
                };
        t.m_query.groupBy() = {
            sqlb::GroupByColumn("a", "id"),
            sqlb::GroupByColumn("jt", "id"),
            sqlb::GroupByColumn("party", "id"),
            sqlb::GroupByColumn("u1", "id"),
            sqlb::GroupByColumn("u2", "id"),
            };
}

json Txn::del(const json event, const json args) {
    // to support global filter, get first all ids b selected filter and for each id delete.
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto txn_id = args[0][0].get<int>();
        auto txn_del = "DELETE FROM account.txn WHERE id = $1";
        auto order_item_del = "DELETE FROM order1.order_item WHERE txn_id = $1";
        transPtr->execSqlSync(order_item_del, txn_id);
        transPtr->execSqlSync(txn_del, txn_id);

        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
void save_txn_order_item(json &args, std::shared_ptr<Transaction> transPtr, int txn_id) {
    std::string strSqlPostCategories = "SELECT id, post_id, pcs, purity_id, tone_id, clarity_id, price, instruction FROM order1.order_item where txn_id = $1";
    std::string strSqlPostCategorySimpleFind = "SELECT id, txn_id, post_id, pcs, purity_id, tone_id, clarity_id, price, instruction FROM order1.order_item WHERE id = $1";
    std::string strSqlPostCategoryDel = "DELETE FROM order1.order_item WHERE id = $1";
    std::string strSqlPostCategoryInsert = "INSERT INTO order1.order_item (txn_id, post_id, pcs, purity_id, tone_id, clarity_id, price, instruction) VALUES ($1, $2, $3, $4, $5, $6, $7, $8) RETURNING id;";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE order1.order_item SET (txn_id, post_id, pcs, purity_id, tone_id, clarity_id, price, instruction) = ROW($2, $3, $4, $5, $6, $7, $8, $9) WHERE id = $1;";

    struct OrderItem {
        int id;
        int post_id;
        int pcs;
        int purity_id;
        int tone_id;
        int clarity_id;
        double price;
        std::string instruction;
    };
    std::vector<OrderItem> newItems; // id Shape	Color	Size	Pcs
    for (auto i : args[0]["o_i_order_item"]) {
        if (!i[1].is_null()) { // to pass null row
            newItems.push_back({i[0].get<int>(), i[1].get<int>(), i[2].get<int>(), i[3].get<int>(), i[4].get<int>(), i[5].get<int>(), i[6].get<float>(), i[7].get<std::string>()});
        }
    }

    auto all_ct = transPtr->execSqlSync(strSqlPostCategories, txn_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<OrderItem>::iterator it = std::find_if(newItems.begin(), newItems.end(),
                                                           [&](OrderItem t) {
                                                               return t.id == r["id"].as<int>();
                                                           });
        if (it == newItems.end()) {// Element not Found
            transPtr->execSqlSync("DELETE FROM order1.order_item WHERE id = $1", r["id"].as<int>());
            transPtr->execSqlSync(strSqlPostCategoryDel, r["id"].as<int>());
        }
    }
    // For each new attachments, insert it if it not already exist.
    for (auto r : newItems) {
        auto y = transPtr->execSqlSync(strSqlPostCategorySimpleFind, r.id);
        if (y.size() == 0) { // insert
            auto i = transPtr->execSqlSync(strSqlPostCategoryInsert, txn_id, r.post_id, r.pcs, r.purity_id, r.tone_id, r.clarity_id, r.price, r.instruction);
        } else { // update
            if (y[0][1].as<int>() != txn_id || y[0][2].as<int>() != r.post_id || y[0][3].as<int>() != r.pcs || y[0][4].as<int>() != r.purity_id || y[0][5].as<int>() != r.tone_id || y[0][6].as<int>() != r.clarity_id || y[0][7].as<double>() != r.price || y[0][8].c_str() != r.instruction) {
                transPtr->execSqlSync(strSqlPostCategoryUpdateAtt, r.id, txn_id,  r.post_id, r.pcs, r.purity_id, r.tone_id, r.clarity_id, r.price, r.instruction);
            }
        }
    }
}

json Txn::ins( json event, json args) {
    std::string strSqlPost =
        "INSERT INTO account.txn "
        "(journal_type_id, party_id, date, description )"
        " VALUES($1, $2, $3, $4)"
        "RETURNING id";

    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto x =
            transPtr->execSqlSync(strSqlPost,
                            args[0]["journal_type_id"].get<int>(), args[0]["party_id"].get<int>(), args[0]["date"].get<std::string>(),
                            args[0]["description"].get<std::string>()
                            );
        auto txn_id = x[0]["id"].as<int>();
        save_txn_order_item(args, transPtr, txn_id);

        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Txn::upd( json event, json args) {
    if (args[0]["id"].get<long>()) {
        std::string strSqlPost =
                "update account.txn set (journal_type_id, party_id, date, description )"
                " = ROW($2, $3, $4, $5) where id=$1";

        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            transPtr->execSqlSync(strSqlPost,
                            args[0]["id"].get<long>(),
                    args[0]["journal_type_id"].get<int>(), args[0]["party_id"].get<int>(), args[0]["date"].get<std::string>(),
                    args[0]["description"].get<std::string>()
                    );
            auto txn_id = args[0]["id"].get<long>();
            save_txn_order_item(args, transPtr, txn_id);

            json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
           SPDLOG_TRACE(e.what());
            json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
