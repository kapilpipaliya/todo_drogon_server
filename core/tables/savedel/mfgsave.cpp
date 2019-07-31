#include "mfgsave.h"

delFn(department_type, "mfg.department_type");

delFn(department, "mfg.department");

delFn(casting, "mfg.casting");

delFn(wax_setting, "mfg.wax_setting");

delFn(metal_issue, "mfg.metal_issue");

delFn(mfg_txn, "mfg.mfg_txn");

delFn(refining, "mfg.refining");

delFn(m_transfer, "mfg.m_transfer");

save_table(department_type, "mfg.department_type", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(department, "mfg.department", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(casting, "mfg.casting", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(wax_setting, "mfg.wax_setting", "date, department_id, employee_id, description, status_id",
           "$1, $2, $3, $4, $5", "$2, $3, $4, $5, $6", "where id=$1", in["date"].asString(),
           in["department_id"].asInt(), in["employee_id"].asInt(), in["description"].asString(),
           in["status_id"].asString());

save_table(metal_issue, "mfg.metal_issue", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(mfg_txn, "mfg.mfg_txn", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(refining, "mfg.refining", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(m_transfer, "mfg.m_transfer", "name", "$1", "$2", "where id=$1", in["name"].asString());
