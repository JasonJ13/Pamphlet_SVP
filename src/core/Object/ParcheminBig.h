#pragma once

#include "Object/InteractibleObject.h"
#include "../TextureGestioner.h"

#include "Interface/InterfaceText.h"
#include <pugixml.hpp>

class ParcheminBig : public InteractibleObject
{

private :

	InterfaceText titre;
	InterfaceText contenu;


	std::vector<std::filesystem::path> files;

	void _grabed(const sf::Vector2i &mouse_position) override;
	void _hold(const sf::Vector2i &mouse_position) override;
	void _release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position = sf::Vector2f{}) override;

	void _update(sf::RenderWindow &mWindow, const float &deltaSec) override;

	pugi::xml_node add_error(pugi::xml_node poeme);

public :
	ParcheminBig(const sf::Vector2f &position, TextureGestioner &textureGestioner);

	bool reset_contain();
};
