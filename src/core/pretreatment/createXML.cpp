#include <sqlite3.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <pugixml.hpp>
#include <algorithm>
#include <vector>

#include "createXML.h"

using select_result = std::vector<std::vector<std::string>>;
constexpr int NB_FIELD = 4;

static int callback(void* p, int argc, char** argv, [[maybe_unused]] char** azColName) {
  std::vector<std::string> infos;
  for (auto i = 0; i < argc; i++) {
    infos.emplace_back(argv[i]);
  }
  auto container = static_cast<select_result*>(p);
  container->emplace_back(infos);
  std::cout << '\n';
  return 0;
}

static void fill_xml(pugi::xml_node mot, std::vector<std::string> choice) {
  mot.append_attribute("phono") = choice[1];
  mot.append_attribute("nature") = choice[2];
  mot.append_attribute("nbsyll") = choice[3];
  mot.append_attribute("replace") = true;
}

static void user_choice(pugi::xml_node mot, select_result possibilities) {
  if (possibilities.size() == 0) {
    std::cout << "Word not in database\n";
    mot.append_attribute("replace") = false;
    return;
  }
  
  if (possibilities.size() == 1) {
    std::cout << "No homonyme\n";
    fill_xml(mot, possibilities[0]);
    return;
  }

  int selection;
  for (auto i = 0; i < possibilities.size(); ++i) {
    std::cout << i << ": ";
    for (auto j = 1; j < NB_FIELD; ++j) {
      std::cout << possibilities[i][j] << ' ';
    }
    std::cout << '\n';
  }
  
  std::cout << "Select homonyme : ";
  std::cin >> selection;
  while (std::cmp_greater_equal(selection, possibilities.size()) || selection < -1) {
    std::cout << "Error: negative number or bigger than the number of possibilities." << '\n';
    std::cout << "Select homonyme : ";
    std::cin >> selection;
  }
  if (selection == -1) {
    std::cout << "Choose not to replace";
    mot.append_attribute("replace") = false;
  }
  else {
    fill_xml(mot, possibilities[selection]);
  }
  std::cout << '\n';
}

static select_result select_word(sqlite3* db, std::string_view word_to_select) {
  char* zErrMsg;
  select_result possibilities;
  
  /* Create SQL statement */
  const auto sql{ std::format(R"(SELECT * from WORDS WHERE WORD = "'{}'")", word_to_select) };
  /* Execute SQL statement */
  if (auto rc = sqlite3_exec(db, sql.c_str(), callback, &possibilities, &zErrMsg); rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << '\n';
    sqlite3_free(zErrMsg);
  }
  else {
    std::cout << "Operation done successfully\n";
  }
  std::cout << '\n';
  return possibilities; 
}

static void parse_text(sqlite3* db, std::ifstream& text, pugi::xml_node poeme) {
  std::string line;
  std::string word;
  select_result possibilities;

  
  while (std::getline(text, line))
  {
    std::stringstream lineStream{ line };
    pugi::xml_node vers = poeme.append_child("vers");
    pugi::xml_node mot;

    while (lineStream >> word)
    {
      std::string word_to_select = word;

      word_to_select.replace(0, 1, 1, (char)std::tolower(word.front()));

      //on doit créer un nouveau string et pas un string_view car back() renvoie un char et append_child prend des string en argument.
      if (std::string ponc{ word_to_select.back() }; ponc == "." || ponc == "," || ponc == ";") {
        word_to_select.pop_back();
        possibilities = select_word(db, word_to_select);

        mot = vers.append_child(word_to_select);
        mot.append_attribute("majuscule") = (word_to_select != word);

        pugi::xml_node p = vers.append_child(ponc);
        p.append_attribute("nature") = "PON";
        p.append_attribute("replace") = false;
      }
      else {
        possibilities = select_word(db, word_to_select);
        mot = vers.append_child(word_to_select);
        mot.append_attribute("majuscule") = (word_to_select != word);
      }
      std::cout << "Word : \"" << word << "\" in" << '\n' << line << '\n' << "is:" << '\n';
      user_choice(mot, possibilities);
    }
  }
}

void create_xml(sqlite3* db) {
  std::ifstream text("resources/originals/poemes/L\'albatros.txt");

  if (!text.is_open()) {
    std::cerr << "Can't open file" << '\n';
  }

  pugi::xml_document doc;

  // tag::code[]
  // add node with some name
  pugi::xml_node poeme = doc.append_child("poeme");
  poeme.append_attribute("titre") = "L\'albatros";
  poeme.append_attribute("auteur") = "Charles Baudelaire";


  // end::code[]

  parse_text(db, text, poeme);

  doc.print(std::cout);
  doc.save_file("resources/poemes/albatros.xml");
  sqlite3_close(db);
}