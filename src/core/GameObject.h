#pragma once


#include <SFML/Graphics.hpp>
#include <variant>

#include "Animation.hpp"

// Variant-based container of animation types (ajoutez d'autres Animation<T> si nécessaire)
using AnimationVariant = std::variant<Animation<sf::Angle>, Animation<sf::Vector2f>, Animation<float>>;


class GameObject
{
private:
	/*
	* Si plusieurs objets sont sur la même position, la priorite permet de determiner qu'elle objet est pris en compte et est affiche en premier
	* Hyppothèse : Des objets superposé ont des priorites differentes
	*/
	int priority;
	sf::Vector2f position;
	sf::Angle angle;
	std::vector<AnimationVariant> animations;

protected:
	/*
	* Sprite de l'objet
	*/
	sf::Sprite sprite;

	void create_animation();


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

	 //AnimationVariant *add_animation();

};
