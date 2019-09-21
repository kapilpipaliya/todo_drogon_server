/**
 *
 *  RestfulGridWidgetsCtrlBase.h
 *  DO NOT EDIT. This file is generated by drogon_ctl automatically.
 *  Users should implement business logic in the derived class.
 */

#pragma once

#include <drogon/HttpController.h>

#include "GridWidgets.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the grid_widgets table.
 */

class RestfulGridWidgetsCtrlBase
{
  public:
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                GridWidgets::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   GridWidgets::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   GridWidgets::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);


//    void update(const HttpRequestPtr &req,
//                std::function<void(const HttpResponsePtr &)> &&callback);

    orm::DbClientPtr getDbClient() 
    {
        return drogon::app().getDbClient(_dbClientName);
    }
    void enableMasquerading(const std::vector<std::string> &pMasqueradingVector)
    {
        _masquerading = true;
        _masqueradingVector = pMasqueradingVector;
    }
    void disableMasquerading()
    {
        _masquerading = false;
    }
  protected:
    const std::string _dbClientName = "sce";
    bool _masquerading = true;
    /**
     * The items in the vector are aliases of column names in the table.
     * if one item is set to an empty string, the related column is not sent to clients.
     */
    std::vector<std::string> _masqueradingVector={
          "id", // the alias for the id column.
          "start_row", // the alias for the start_row column.
          "end_row", // the alias for the end_row column.
          "start_column", // the alias for the start_column column.
          "end_column", // the alias for the end_column column.
          "identifier", // the alias for the identifier column.
          "options", // the alias for the options column.
          "grid_id"  // the alias for the grid_id column.
    };
};
