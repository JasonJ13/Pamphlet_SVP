#pragma once

#include <iostream>
#include <map>
#include <string_view>
#include <SFML/Graphics.hpp>

class TextureGestioner
{

private:
	std::map<std::string_view, std::shared_ptr<sf::Texture>> textures;
	

public:
	TextureGestioner();
	~TextureGestioner() = default;

	sf::Sprite load(const std::string_view &file_name);
};

