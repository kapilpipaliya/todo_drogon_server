#pragma once
#include "activerecord.h"
#include "JournalVersions.h"
namespace openproj {
namespace models {
class JournalVersion : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::JournalVersions {
};
}

}
