#pragma once

#include <SFML/Graphics.hpp>


class GameObject
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

 private:
	 /*
	 * Paramètre visuel de l'objet
	 */
	float x;
	float y;

	/*
	 * Section de l'objet dans le jeu
	 */
	int chunk;

	/*
	* Offset de la sourie sur l'object
	*/
	sf::Vector2i offset;

 public:
	 GameObject(float x, float y);

	 void move(float dx, float dy);
	 void set_position(sf::Vector2i new_position);

	 /*
	 * Fonction appelé lorsque la souris click sur l'objet
	 */
	 void grabed(sf::Vector2i mouse_position);

	 /*
	 * Correspondance de l'objet avec une position
	 */
	 bool in_chunk(int chunk_clicked) const;
	 bool is_hit(sf::Vector2i position) const;

	 void display(sf::RenderWindow& mWindow) const;
	 
};