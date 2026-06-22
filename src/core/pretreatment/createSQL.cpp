#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "createSQL.h"

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
  for (auto i = 0; i < argc; i++) {
    std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
  }
  std::cout << '\n';
  return 0;
}

static void delete_database() {
  std::string searchfilename = "resources/database/words.db";
  try {
    if (std::filesystem::remove(searchfilename))
      std::cout << "file " << searchfilename << " deleted.\n";
    else
      std::cout << "file " << searchfilename << " not found.\n";
  }
  catch (const std::filesystem::filesystem_error& err) {
    std::cout << "filesystem error: " << err.what();
  }
}

static void insert_into_database(sqlite3* db, const std::string_view word, const char & phon, const std::string_view type, const int& nb_syllab) {
  char* zErrMsg;
  if (auto short_type{ type.substr(0,3) }; short_type != "NOM" && short_type != "ADJ" && short_type != "VER" && short_type != "ADV" && short_type != "AUX" 
                                           && short_type != "ONO" && short_type != "PRO" && short_type != "PRE" && short_type != "CON" && short_type != "ART") {
    std::cout << word << " " << type << '\n';
  }
  auto s{ std::format(R"(INSERT INTO WORDS (WORD,PHONO,TYPE,NBSYLL) VALUES ("'{}'", "'{}'", "'{}'", '{}');)", word, phon, type, nb_syllab) };

  const auto sql{ std::format(R"(SELECT * from WORDS WHERE NOM = "{}")", word) };
  /* Execute SQL statement */
  if (auto rc = sqlite3_exec(db, s.c_str(), callback, nullptr, &zErrMsg); rc != SQLITE_OK) {
    throw std::format("SQL error: {}", zErrMsg);
    sqlite3_free(zErrMsg);
  }
}

sqlite3* create_sql()
{
  std::ifstream dico("resources/texts/word_list.txt");
  sqlite3* db;
  char* zErrMsg;
  std::string sql;

  if (!dico.is_open()) {
    std::cerr << "Can't open file\n";
  }

  delete_database();

  if (const auto rc = sqlite3_open("resources/database/words.db", &db); rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << '\n';
  }
  else {
    std::cout << "Opened database successfully\n";
  }

  /* Create SQL statement */

  // le mot ayant le plus de lettre dans la liste de mots en a 25.
  // on ne prend que le dernier caractère pour connaitre la rime du mot.
  // les natures des mots dans la liste de mots font tous 3 caractères.
  sql = "CREATE TABLE WORDS("  \
    "WORD    CHAR(25)  NOT NULL," \
    "PHONO   CHAR(1)   NOT NULL," \
    "TYPE    CHAR(3)   NOT NULL," \
    "NBSYLL  INT       NOT NULL );";


  /* Execute SQL statement */
  if (const auto rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg); rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << '\n';
    sqlite3_free(zErrMsg);
  }
  else {
    std::cout << "Table created successfully\n";
  }
  
  std::string line;
  std::string word;
  std::string phon;
  std::string type;
  std::string syllab;
  int err_count = 0;
  while (std::getline(dico, line))
  {
    std::stringstream lineStream{ line };
    if (lineStream >> word >> phon >> type >> syllab) {
      try { 
        auto nb_syllab = stoi(syllab);
        try {
          insert_into_database(db, word, phon.back(), type, nb_syllab);
        }
        catch (std::string& e) {
          std::cout << "Exception: " << e << " at line: " << line << '\n';
          err_count++;
        }
      }
      catch (const std::invalid_argument& e) {
        std::cout << "Exception: " << e.what() << " at line: " << line << '\n';
        err_count++;
      }
    }
  }

  std::cout << err_count << '\n';
  sqlite3_close(db);
  return db;
}
