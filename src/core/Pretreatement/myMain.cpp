#include <string>
#include <iostream>

#include "createSQL.h"
#include "createXML.h"

int myMain() {
  sqlite3* db;
  sqlite3_open("resources/database/words.db", &db);
  create_xml(db);
  return 0;
}