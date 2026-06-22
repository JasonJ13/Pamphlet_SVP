#pragma once


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string_view>

#include "Animation/Animation.h"
#include "Interface/Interface.h"


class GameObject
{
private:
	/*
	* Si plusieurs objets sont sur la même position, la priorite permet de determiner qu'elle objet est pris en compte et est affiche en premier
	* Hyppothèse : Des objets superposé ont des priorites differentes
	*/
	std::unique_ptr<Interface> interface;

	std::unordered_map<std::string_view, std::unique_ptr<Animation>> animations;

	virtual void _update(sf::RenderWindow &mWindow, const float &deltaSec) = 0;

	bool active = true;


protected:
	sf::Vector2f position;
	sf::Angle angle;
	sf::Vector2f size;

	void add_animation(std::unique_ptr<Animation> animation, std::string_view animation_name);


public:
	 GameObject(const float &x, const float &y, const sf::Sprite &sprite, const sf::Vector2f &size = sf::Vector2f{ 1, 1 }, const int &priority = 0);
	 GameObject(const sf::Vector2f& position, const sf::Sprite& sprite, const sf::Vector2f &size = sf::Vector2f{ 1, 1 }, const int &priority = 0);
	 GameObject(std::unique_ptr<Interface> &&interface);
	 virtual ~GameObject() = default;

	 sf::Vector2f get_position() const;
	 int get_priority() const;
	 sf::Vector2f get_size() const;
	 Interface *get_interface() const;

	 void move(const float &dx, const float &dy);
	 void move(const sf::Vector2i &dp);

	 void set_priority(const int &prio);

	 void set_position(const float &x, const float &y);
	 void set_position(const sf::Vector2f &new_position);
	 void set_position(const sf::Vector2i &new_position);

	 void set_size(const float &scale);
	 void set_size(const sf::Vector2f &scale);

	 void update(sf::RenderWindow& mWindow, const float &deltaSec);

	 void activate();
	 void desactivate();

	 void play_animation(std::string_view animation_name);
};
