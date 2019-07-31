#include "pdb.h"

#include <string>
#include <vector>

#include <iostream>
using namespace std;

connection DD("user=postgres dbname=susant");

P_DB::P_DB()
{
    init();
}

P_DB::~P_DB()
{
    delete C;
}

bool P_DB::init()
{
    try {
        C = new connection("user=postgres dbname=susant");
        if (C->is_open()) {
            cout << "Opened database successfully: " << C->dbname() << endl;
            return true;
        } else {
            cout << "Can't open database" << endl;
            return false;
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return false;
    }
}

