#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"

class InteractibleObject : public GameObject
{
	/*
	* Hitbox de l'objet, différente du visuel
	*/
	struct
	{
		float x;
		float y;
		float sizeX;
		float sizeY;
	} hitbox;

 private :
	/*
	* Position relative de la sourie sur l'objet
	*/
	sf::Vector2i offset;


 public :
	 InteractibleObject(const float &x, const float &y, const sf::Sprite &sprite, const sf::Vector2f &size);
	 InteractibleObject(const sf::Vector2f& position, const sf::Sprite &sprite, const sf::Vector2f &size);
	 ~InteractibleObject() = default;
	 /*
	 * Fonction appelé lorsque la souris attrape l'objet
	 */
	 void grabed(sf::Vector2i mouse_position);

	 /*
	 * Correspondance de l'objet avec une position
	 */
	 bool is_hit(sf::Vector2i position) const;

	 void set_position(float x, float y);
	 void set_position(sf::Vector2f new_position);
	 void set_position(sf::Vector2i new_position);
};