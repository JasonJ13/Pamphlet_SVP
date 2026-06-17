#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID { Test, Cyrano};
}

class TextureGestioner
{

private:
	std::map<Textures::ID, std::shared_ptr<sf::Texture>> textures;
	

public:
	TextureGestioner();
	~TextureGestioner() = default;

	sf::Sprite load(Textures::ID id, const std::string_view &file_name);
};

