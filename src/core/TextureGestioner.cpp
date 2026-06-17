
#include <iostream>
#include <string>
#include <string_view>

#include "TextureGestioner.h"


TextureGestioner::TextureGestioner() : textures{} {}

sf::Sprite TextureGestioner::load(Textures::ID id, const std::string_view &file_name)
{

	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile(std::string(file_name)))
	{
		textures[id] = texture;

		return sf::Sprite{ *texture.get()};
	}
	else
	{
		std::cout << "no texture has name " << file_name << std::endl;
		abort();
	}
}

