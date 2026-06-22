#include "ParcheminBig.h"

#include "Interface/InterfaceSprite.h"
#include "../Animation/AnimationUnit.hpp"
#include "../Animation/AnimationGroupParallel.h"

#include <iostream>
#include <string>
#include <random>
#include <filesystem>
#include <vector>

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

bool ParcheminBig::reset_contain()
{
	// Collecte tous les fichiers réguliers du dossier resourcesPath
	
	static std::uniform_int_distribution<> dis(0, 5);

	auto &new_poeme = files[0];
	bool correct = (dis(gen) % 2);

	std::cout << new_poeme << '\n';
	if (correct) std::cout << "correct\n";
	else std::cout << "not correct\n";

	

	return correct;
}