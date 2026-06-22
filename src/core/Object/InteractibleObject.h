#pragma once

#include "GameObject.h"

#include "Interface/Interface.h"

#include <SFML/Graphics.hpp>



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


	virtual void _grabed(const sf::Vector2i &mouse_position) = 0;
	virtual void _hold(const sf::Vector2i &mouse_position) = 0;
	virtual void _release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position = sf::Vector2f{}) = 0;

protected :
	void set_hitbox_size(const sf::Vector2f &size);
	void set_offset(const sf::Vector2i &position);

	sf::Vector2f get_hitbox_size() const;

 public :
	 InteractibleObject(const float &x, const float &y, const sf::Sprite &sprite, const sf::Vector2f &size, const int &priority = 0);
	 InteractibleObject(const sf::Vector2f &position, const sf::Sprite &sprite, const sf::Vector2f &size, const int &priority = 0);
	 InteractibleObject(std::unique_ptr<Interface> &&interface);
	 ~InteractibleObject() = default;

	 
	 bool is_hit(sf::Vector2i position) const;

	 void set_position(const float &x, const float &y);
	 void set_position(const sf::Vector2f &new_position);
	 void set_position(const sf::Vector2i &new_position);

	 void grabed(const sf::Vector2i &mouse_position);
	 void hold(const sf::Vector2i &mouse_position);
	 void release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position = sf::Vector2f{});
};