/**
 *
 *  RestfulExportCardConfigurationsCtrlBase.h
 *  DO NOT EDIT. This file is generated by drogon_ctl automatically.
 *  Users should implement business logic in the derived class.
 */

#pragma once

#include "ExportCardConfigurations.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the export_card_configurations table.
 */

class RestfulExportCardConfigurationsCtrlBase
{
  public:
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                ExportCardConfigurations::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   ExportCardConfigurations::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   ExportCardConfigurations::PrimaryKeyType &&id);
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
          "name", // the alias for the name column.
          "per_page", // the alias for the per_page column.
          "page_size", // the alias for the page_size column.
          "orientation", // the alias for the orientation column.
          "rows", // the alias for the rows column.
          "active", // the alias for the active column.
          "description"  // the alias for the description column.
    };
};
