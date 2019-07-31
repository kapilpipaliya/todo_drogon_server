#include "accountsave.h"

delFn(account_type, "account.account_type")
delFn(account, "account.account")
delFn(account_heading, "account.account_heading")
delFn(journal_type, "account.journal_type")
delFn(priority, "account.priority")

save_table(account_type, "account.account_type", "name", "$1", "$2", "where id=$1", in["name"].asString())
save_table(account, "account.account", "name", "$1", "$2", "where id=$1", in["name"].asString())
save_table(account_heading, "account.account_heading", "name", "$1", "$2", "where id=$1", in["name"].asString())
save_table(journal_type, "account.journal_type", "name", "$1", "$2", "where id=$1", in["name"].asString())

void save_txn_order_item(Json::Value &in, pqxx::work &txn, int txn_id) {
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
  for (auto i : in["o_i_order_item"]) {
    if (!i[1].isNull()) { // to pass null row
      newItems.push_back({i[0].asInt(), i[1].asInt(), i[2].asInt(), i[3].asInt(), i[4].asInt(), i[5].asInt(), i[6].asDouble(), i[7].asString()});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, txn_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<OrderItem>::iterator it = std::find_if(newItems.begin(), newItems.end(),
                                                             [&](OrderItem t) {
                                                                 return t.id == r[0].as<int>();
                                                             });
    if (it == newItems.end()) {// Element not Found
      txn.exec_params("DELETE FROM order1.order_item WHERE id = $1", r[0].as<int>());
      txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : newItems) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.id);
    if (y.size() == 0) { // insert
      auto i = txn.exec_params(strSqlPostCategoryInsert, txn_id, r.post_id, r.pcs, r.purity_id, r.tone_id, r.clarity_id, r.price, r.instruction);
    } else { // update
      if (y[0][1].as<int>() != txn_id || y[0][2].as<int>() != r.post_id || y[0][3].as<int>() != r.pcs || y[0][4].as<int>() != r.purity_id || y[0][5].as<int>() != r.tone_id || y[0][6].as<int>() != r.clarity_id || y[0][7].as<double>() != r.price || y[0][8].c_str() != r.instruction) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, txn_id,  r.post_id, r.pcs, r.purity_id, r.tone_id, r.clarity_id, r.price, r.instruction);
      }
    }
  }
}

void save_txn(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  if (in["id"].asInt()) {
    std::string strSqlPost =
            "update account.txn set (journal_type_id, party_id, date, description )"
            " = ROW($2, $3, $4, $5) where id=$1";

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSqlPost,
                      in["id"].asInt(),
                      in["journal_type_id"].asInt(), in["party_id"].asInt(), in["date"].asString(),
                      in["description"].asString()
      );
      auto txn_id = in["id"].asInt();
      save_txn_order_item(in, txn, txn_id);

      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSqlPost =
            "INSERT INTO account.txn "
            "(journal_type_id, party_id, date, description )"
            " VALUES($1, $2, $3, $4)"
            "RETURNING id";

    pqxx::work txn{DD};
    try {
      pqxx::result x =
              txn.exec_params(strSqlPost,
                              in["journal_type_id"].asInt(), in["party_id"].asInt(), in["date"].asString(),
                              in["description"].asString()
              );
      auto txn_id = x[0]["id"].as<int>();
      save_txn_order_item(in, txn, txn_id);

      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

void delete_txn(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  pqxx::work txn{DD};
  try {
    auto txn_del = "DELETE FROM account.txn WHERE id = $1";
    auto order_item_del = "DELETE FROM order1.order_item WHERE txn_id = $1";
    txn.exec_params(order_item_del, in[0].asInt());
    txn.exec_params(txn_del, in[0].asInt());

    txn.commit();
    simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
  }
}

save_table(priority, "account.priority", "name, url, description", "$1, $2, $3", "$2, $3, $4", "where id=$1", in["name"].asString(), in["url"].asString(), in["description"].asString())
