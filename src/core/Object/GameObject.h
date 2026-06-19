#pragma once


#include <SFML/Graphics.hpp>
#include <variant>
#include <unordered_map>
#include <memory>
#include <string_view>

#include "Animation/Animation.h"


class GameObject
{
private:
	/*
	* Si plusieurs objets sont sur la même position, la priorite permet de determiner qu'elle objet est pris en compte et est affiche en premier
	* Hyppothèse : Des objets superposé ont des priorites differentes
	*/
	int priority;
	
	sf::Angle angle;
	sf::Vector2f size;
	std::unordered_map<std::string_view, std::unique_ptr<Animation>> animations;

protected:
	sf::Vector2f position;

	sf::Sprite sprite;

	void add_animation(std::unique_ptr<Animation> animation, std::string_view animation_name);

	void create_animation_position_x(float vend, float duration, std::string_view animation_name, bool cycle = false, bool reverse = false);
	void create_animation_position_y(float vend, float duration, std::string_view animation_name, bool cycle = false, bool reverse = false);
	void create_animation_position(sf::Vector2f vend, float duration, std::string_view animation_name, bool cycle = false, bool reverse = false);
	void create_animation_angle(sf::Angle vend, float duration, std::string_view animation_name, bool cycle = false, bool reverse = false);
	void create_animation_size(sf::Vector2f vend, float duration, std::string_view animation_name, bool cycle = false, bool reverse = false);

	void play_animation(std::string_view animation_name);


public:
	 GameObject(const float &x, const float &y, const sf::Sprite &sprite, const sf::Vector2f &size = sf::Vector2f{ 1, 1 });
	 GameObject(const sf::Vector2f& position, const sf::Sprite& sprite, const sf::Vector2f &size = sf::Vector2f{ 1, 1 });
	 virtual ~GameObject() = default;

	 sf::Vector2f get_position() const;
	 int get_priority() const;

	 void move(float dx, float dy);
	 void move(sf::Vector2i dp);

	 void set_position(float x, float y);
	 void set_position(sf::Vector2f new_position);
	 void set_position(sf::Vector2i new_position);

	 void display(sf::RenderWindow& mWindow, float deltaSec);



};
