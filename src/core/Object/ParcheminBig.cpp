#include "ParcheminBig.h"

#include "Interface/InterfaceSprite.h"
#include "../Animation/AnimationUnit.hpp"
#include "../Animation/AnimationGroupParallel.h"

#include <iostream>
#include <string>
#include <string_view>
#include <random>
#include <filesystem>
#include <fstream>
#include <vector>
#include "pugixml.hpp"
#include "sqlite3.h"
using namespace std::literals;

static std::random_device rd; // Get random number from hardware
static std::mt19937 gen(rd()); // Seed generator


static const std::filesystem::path resourcesPath = std::filesystem::path("resources") / "poemes";
static sqlite3* db;

ParcheminBig::ParcheminBig(const sf::Vector2f &position, TextureGestioner &textureGestioner) : InteractibleObject{ std::make_unique<InterfaceSprite>("Resources/parcheminEmpty.png", textureGestioner, 1, 0.2) }, titre{ "Titre", 3 }, contenu{ "blablabla", 3 }
{
	set_offset(sf::Vector2i(384,256));

	std::error_code ec;
	std::filesystem::path dir = std::filesystem::absolute(resourcesPath, ec);
	sqlite3_open("resources/database/words.db", &db);
	if (ec) {
		std::cerr << "reset_contain: impossible de résoudre le chemin " << resourcesPath << ": " << ec.message() << '\n';
		abort();
	}

	if (!std::filesystem::exists(dir)) {
		std::cerr << "reset_contain: dossier introuvable : " << dir << '\n';
		abort();
	}

	if (!std::filesystem::is_directory(dir)) {
		std::cerr << "reset_contain: le chemin n'est pas un dossier : " << dir << '\n';
		abort();
	}

	for (auto const &entry : std::filesystem::directory_iterator(dir, ec)) {
		if (ec) {
			std::cerr << "reset_contain: erreur lors de l'itération : " << ec.message() << '\n';
			break;
		}
		if (entry.is_regular_file()) {
			files.push_back(entry.path());
		}
	}

	if (files.empty()) {
		// Aucun fichier trouvé
		abort();
	}

}

void ParcheminBig::_grabed(const sf::Vector2i &mouse_position)
{
}
void ParcheminBig::_hold(const sf::Vector2i &mouse_position)
{

}
void ParcheminBig::_release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position)
{
}

void ParcheminBig::_update(sf::RenderWindow &mWindow, const float &deltaSec)
{
	titre.set_position(position + sf::Vector2f(get_size().x / 2.f - 32, 128));
	contenu.set_position(position + sf::Vector2f(get_size().x / 4.f, 128*3/2));

	titre.display(mWindow);
	contenu.display(mWindow);
}

void ParcheminBig::parse(const pugi::xml_node& xml_poeme)
{
	std::string new_string = "";

	titre.set_string(xml_poeme.attribute("titre").as_string());
	for (auto &vers : xml_poeme.children())
	{
		for (auto &word : vers.children())
		{
			std::string mot = word.attribute("label").as_string();
			if (mot != "" && word.attribute("majuscule").as_bool()) { mot.replace(0, 1, 1, (char)std::toupper(mot.front())); }
			if (word.name() == "mot"sv)	new_string =  new_string + " " + mot;
			else new_string += word.attribute("label").as_string();
		}
		new_string += '\n';
	}

	contenu.set_string( new_string );
}

static int callback(void* p, int argc, char** argv, [[maybe_unused]] char** azColName) {
	std::vector<std::string> infos;
	for (auto i = 0; i < argc; i++) {
		infos.emplace_back(argv[i]);
	}
	auto container = static_cast<std::vector<std::vector<std::string>>*>(p);
	container->emplace_back(infos);
	return 0;
}

static void replace_word (pugi::xml_node* mot) {
	char* zErrMsg;
	std::vector<std::vector<std::string>> possibilities;
	/* Create SQL statement */
	const auto sql{ std::format(R"(SELECT * from WORDS WHERE PHONO != "{}" AND TYPE = "{}" AND NBSYLL = {})", mot->attribute("phono").as_string(),
																																																						mot->attribute("nature").as_string(),
																																																						mot->attribute("nbsyll").as_int())};
	/* Execute SQL statement */
	if (auto rc = sqlite3_exec(db, sql.c_str(), callback, &possibilities, &zErrMsg); rc != SQLITE_OK) {
		std::cerr << "SQL error: " << zErrMsg << '\n';
		sqlite3_free(zErrMsg);
	}

	std::uniform_int_distribution<> selected(0, possibilities.size());
	auto new_word = possibilities[selected(gen)][0];
	new_word.erase(0, 1);   //delete the ' '
	new_word.erase(new_word.size() - 1, 1);
	mot->attribute("label").set_value(new_word);
	return;
}

void ParcheminBig::add_error(pugi::xml_node* poeme) {
	size_t count = std::distance(poeme->begin(), poeme->end());
	bool error_added = false;
	while (!error_added) {
		std::uniform_int_distribution<> vers_to_change(0, count);
		pugi::xml_node vers = poeme->first_child();

		for (auto i = 0; i < vers_to_change(gen); ++i)
		{
			vers = vers.next_sibling();
		}
		pugi::xml_node mot = vers.last_child();
		if (mot.name() == "ponc"sv) {
			mot = mot.previous_sibling();
		}
		if (mot.attribute("replace").as_bool()) {
			replace_word(&mot);
			error_added = true;
		}
	}

	return;
}

bool ParcheminBig::reset_contain()
{
	// Collecte tous les fichiers réguliers du dossier resourcesPath
	
	static std::uniform_int_distribution<> dis(0, 5);

	pugi::xml_document doc;
	doc.load_file("resources/poemes/albatros.xml");
	pugi::xml_node poeme = doc.child("poeme");
	bool correct = (dis(gen) % 2);

	if (!correct) { add_error(&poeme); }


	parse(poeme);

	return correct;
}