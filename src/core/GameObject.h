#pragma once


#include <SFML/Graphics.hpp>


class GameObject
{
 private:
	 sf::Texture texture;
	 
	 /*
	 * Si plusieurs objets sont sur la même position, la priorite permet de determiner qu'elle objet est pris en compte
	 * Hyppothèse : Des objets superposé ont des priorites differentes
	 */
	 int priority;

 protected :
	 /*
	 * Sprite de l'objet
	 */
	 sf::Sprite sprite;


 public:
	 GameObject(const float& x, const float& y, const std::string_view& sprite_name);

	 void move(float dx, float dy);
	 void move(sf::Vector2i dp);
	 void set_position(float x, float y);
	 void set_position(sf::Vector2f new_position);
	 void set_position(sf::Vector2i new_position);

	 void display(sf::RenderWindow& mWindow) const;
	 
};