#include "ParcheminBig.h"

#include "Interface/InterfaceSprite.h"
#include "../Animation/AnimationUnit.hpp"
#include "../Animation/AnimationGroupParallel.h"

#include <iostream>
#include <string>
#include <random>
#include <filesystem>
#include <fstream>
#include <vector>
#include "pugixml.hpp"


static std::random_device rd; // Get random number from hardware
static std::mt19937 gen(rd()); // Seed generator


static const std::filesystem::path resourcesPath = std::filesystem::path("Resources") / "poemes";

ParcheminBig::ParcheminBig(const sf::Vector2f &position, TextureGestioner &textureGestioner) : InteractibleObject{ std::make_unique<InterfaceSprite>("Resources/parcheminEmpty.png", textureGestioner, 1, 0.2) }, titre{ "Titre", 3 }, contenu{ "blablabla", 3 }
{
	set_offset(sf::Vector2i(384,256));

	std::error_code ec;
	std::filesystem::path dir = std::filesystem::absolute(resourcesPath, ec);
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
	contenu.set_position(position + sf::Vector2f(get_size().x / 4.f, 128*2));

	titre.display(mWindow);
	contenu.display(mWindow);
}

void ParcheminBig::parse(const pugi::xml_node& xml_poeme)
{
	std::string new_containt;

	std::cout << xml_poeme.first_child().name() << '\n';
	for (auto &vers : xml_poeme.children())
	{
		std::cout << "vers" << '\n';
		std::cout << vers.name() << '\n';


	}
}
pugi::xml_node ParcheminBig::add_error(pugi::xml_node poeme) {
	size_t count = std::distance(poeme.begin(), poeme.end());
	std::uniform_int_distribution<> vers_to_change(0, count);
	pugi::xml_node vers = poeme.first_child();
	for (auto i = 0; i < vers_to_change(gen); ++i)
	{
		vers = vers.next_sibling();
	}
	pugi::xml_node mot = vers.last_child();
	std::cout << mot.attribute("replace");
	mot.previous_sibling();
	std::cout << vers.name() << '\n';
	return poeme;
}

bool ParcheminBig::reset_contain()
{
	// Collecte tous les fichiers réguliers du dossier resourcesPath
	
	static std::uniform_int_distribution<> dis(0, 5);

	pugi::xml_document doc;
	doc.load_file("resources/poemes/albatros.xml");
	pugi::xml_node poeme = doc.child("poeme");
	bool correct = (dis(gen) % 2);

	if (correct) { std::cout << "correct\n"; }
	else {
		std::cout << "not correct\n";
		add_error(poeme);
	}


	std::cout << doc.find_child("strophe") << '\n';
	//parse(doc.first_child().first_child());

	return correct;
}