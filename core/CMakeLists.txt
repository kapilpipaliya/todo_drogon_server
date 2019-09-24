cmake_minimum_required(VERSION 3.15.1)
project(libjewelcore2)
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

find_package(PostgreSQL)
#find_package(libpqxx REQUIRED)

#find_package (Jsoncpp REQUIRED)
#find_package(Sqlpp11)
#find_package(Sqlpp-connector-postgresql)
#find_package(folly)

# https://gist.github.com/Asher-/617872
#	function processes each sub-directory and then adds each source file in directory
#	each function should cascade back upward in setting variables so that the bottom directory
#	adds its source first, and then the level above it adds its source and passes both up, and so on...
function( recursively_include_src which_directory return_variable )

  if( ${return_variable} STREQUAL "headers" )
    set( file_extension ".h" )
  else( ${return_variable} STREQUAL "headers" )
    set( file_extension ".c" )
  endif( ${return_variable} STREQUAL "headers" )

  #	get list of all files for this directory
  file( GLOB this_directory_all_files "${which_directory}/*" )

  #	get list of source from this directory
  file( GLOB this_directory_src "${which_directory}/*${file_extension}" )

  #	get rid of *.txt
  file( GLOB this_directory_txt "${which_directory}/*.txt" )

  #	get directories only
  if( this_directory_all_files AND this_directory_txt )
    #	remove txt from list of files to get list of directories
    list( REMOVE_ITEM this_directory_all_files ${this_directory_txt} )
  endif( this_directory_all_files AND this_directory_txt )
  if( this_directory_all_files AND this_directory_src )
    #	remove source from list of files to get list of directories
    list( REMOVE_ITEM this_directory_all_files ${this_directory_src} )
    set( this_directory_directories ${this_directory_all_files} )
    #	for each sub-directory, call self with sub-directory as arg
    foreach( this_sub_directory ${this_directory_directories} )
      recursively_include_src( ${this_sub_directory} ${return_variable} )
    endforeach( this_sub_directory ${this_directory_directories} )
  endif( this_directory_all_files AND this_directory_src )

  #	add source files to ${rb_rpdb_src} in PARENT_SCOPE
  if( ${return_variable} STREQUAL "headers" )
    set( rb_rpdb_headers ${rb_rpdb_headers} ${this_directory_src} PARENT_SCOPE )
  else( ${return_variable} STREQUAL "headers" )
    set( rb_rpdb_src ${rb_rpdb_src} ${this_directory_src} PARENT_SCOPE )
  endif( ${return_variable} STREQUAL "headers" )

  set( rb_rpdb_directories ${rb_rpdb_directories} ${which_directory} PARENT_SCOPE )

endfunction( recursively_include_src which_directory return_variable )



set(JEWEL_HDR
    sql/condformat.h
    sql/dba.h
#    data.h

###    sql/sqlitetypes.h # this file is good and it is in the directory
    sql/query.h
    sql/objectidentifier.h
    actor/permission.h
    actor/validation.h
#    csvparser.h
#    sqlitedb.h not needed use mdb.h
#    settings.h
#    dotenvformat.h
#    ciphersettings.h


    strfns.h
)

set(JEWEL_SRC
    sql/condformat.cpp
    sql/dba.cpp
#    data.cpp
actor/permission.cpp
actor/validation.cpp

###    sql/sqlitetypes.cpp
    sql/query.cpp
    sql/objectidentifier.cpp
#    sqltextedit.cpp
#    sqlitedb.cpp not needed ufse mdb.cpp
#    settings.cpp
#    dotenvformat.cpp
#    ciphersettings.cpp


    strfns.cpp
)
include_directories(../models)

AUX_SOURCE_DIRECTORY(./service JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/class JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/auth JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/post JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/account JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/entity JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/material JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/menu JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/mfg JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/product JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/setting JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/todo JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/todo/class JEWEL_SRC)

AUX_SOURCE_DIRECTORY(./service/juser JEWEL_SRC)

AUX_SOURCE_DIRECTORY(./service/madmin JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/madmin/class JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/madmin/modules/catalog JEWEL_SRC)

AUX_SOURCE_DIRECTORY(./service/muser JEWEL_SRC)

#AUX_SOURCE_DIRECTORY(./service/openproj/controllers JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/controllers/concerns JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/controllers/news JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/controllers/oauth JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/controllers/time_entries JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/controllers/users JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/controllers/work_packages JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/helpers JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/mailers JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/activity JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/attribute_help_text JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/concerns JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/custom_actions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/custom_actions/actions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/custom_actions/actions/strategies JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/custom_actions/conditions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/custom_field JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/custom_value JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/group JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/journal JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/menu_items JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/mixins JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/permitted_params JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/project JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/columns JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/filters/shared JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/filters/shared/custom_fields JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/filters/strategies JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/members JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/members/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/members/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/news JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/news/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/news/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/operators JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/principals JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/principals/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/principals/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/projects JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/projects/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/projects/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/queries JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/queries/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/relations JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/relations/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/relations/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/roles JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/roles/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/time_entries JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/time_entries/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/time_entries/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/users JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/users/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/users/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/versions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/versions/filters JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/versions/orders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/work_packages JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/work_packages/columns JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/work_packages/common JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/queries/work_packages/filter JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/query JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/repository JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/setting JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/token JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/type JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/user JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/user_password JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/version JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/work_package JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/work_package/exporter JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/models/work_package/pdf_export JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/policies JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/policies/scm JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders/basic_data JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders/demo_data JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders/development_data JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders/random_data JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders/standard_seeder JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/seeders/standard_seeder/basic_data JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/api JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/api/v3 JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/attachments JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/authorization JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/base_services JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/changesets JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/concerns JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/custom_actions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/members JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/oauth JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/projects JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/queries JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/relations JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/reports JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/roles JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/scm JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/sessions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/settings JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/shared JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/time_entries JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/users JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/versions JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/workflows JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/work_packages JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/work_packages/bulk JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/services/work_packages/shared JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/uploaders JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/validators JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/workers JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/workers/attachments JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/workers/oauth JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/workers/projects JEWEL_SRC)
#AUX_SOURCE_DIRECTORY(./service/openproj/workers/scm JEWEL_SRC)

recursively_include_src(./service/openproj JEWEL_SRC)

#file(GLOB JEWEL_SRC3
#    ./service/openproj/*.h
#)

#set(JEWEL_RESOURCES
#    languages.qrc
#)
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers)

include_directories(..)

add_library(${PROJECT_NAME}
    SHARED
    ${JEWEL_HDR}
    ${JEWEL_SRC}
    # ${JEWEL_SRC3}
    # ${JEWEL_RESOURCES}
)

#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers/concerns )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers/news )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers/oauth )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers/time_entries )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers/users )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/controllers/work_packages )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/helpers )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/mailers )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/activity )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/attribute_help_text )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/concerns )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/custom_actions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/custom_actions/actions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/custom_actions/actions/strategies )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/custom_actions/conditions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/custom_field )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/custom_value )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/group )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/journal )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/menu_items )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/mixins )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/permitted_params )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/project )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/columns )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/filters/shared )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/filters/shared/custom_fields )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/filters/strategies )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/members )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/members/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/members/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/news )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/news/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/news/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/operators )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/principals )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/principals/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/principals/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/projects )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/projects/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/projects/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/queries )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/queries/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/relations )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/relations/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/relations/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/roles )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/roles/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/time_entries )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/time_entries/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/time_entries/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/users )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/users/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/users/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/versions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/versions/filters )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/versions/orders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/work_packages )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/work_packages/columns )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/work_packages/common )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/queries/work_packages/filter )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/query )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/repository )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/setting )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/token )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/type )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/user )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/user_password )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/version )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/work_package )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/work_package/exporter )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/models/work_package/pdf_export )


#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/policies )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/policies/scm )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders/basic_data )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders/demo_data )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders/development_data )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders/random_data )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders/standard_seeder )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/seeders/standard_seeder/basic_data )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/api )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/api/v3 )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/attachments )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/authorization )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/base_./services )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/changesets )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/concerns )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/custom_actions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/members )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/oauth )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/projects )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/queries )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/relations )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/reports )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/roles )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/scm )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/sessions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/settings )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/shared )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/time_entries )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/users )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/versions )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/workflows )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/work_packages )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/work_packages/bulk )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/./services/work_packages/shared )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/uploaders )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/validators )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/workers )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/workers/attachments )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/workers/oauth )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/workers/projects )
#include_directories(${PROJECT_NAME} PRIVATE ./service/openproj/workers/scm )

#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})#OR
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION /home/kapili3)

#set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
#    libpqxx::pqxx_shared
#    libjewelconnection
#    ${JSONCPP_LIBRARY}
#    folly.a
#    folly
)

#add_subdirectory(connection)
