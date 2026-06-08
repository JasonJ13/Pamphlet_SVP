#pragma once

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
	 InteractibleObject(const float &x, const float &y, const std::string_view &sprite_name)
	 /*
	 * Fonction appelé lorsque la souris attrape l'objet
	 */
	 void grabed(sf::Vector2i mouse_position);

	 /*
	 * Correspondance de l'objet avec une position
	 */
	 bool is_hit(sf::Vector2i position) const;
};