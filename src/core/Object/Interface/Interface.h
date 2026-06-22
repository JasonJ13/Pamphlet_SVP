
#pragma once

#include <SFML/Graphics.hpp>

class Interface
{
private :
	int priority;

	virtual sf::Vector2f _get_position() const = 0;
	virtual sf::Angle _get_angle() const = 0;
	virtual sf::Vector2f _get_size() const = 0;

	virtual void _set_position(const sf::Vector2f &position) = 0;
	virtual void _set_angle(const sf::Angle &angle) = 0;
	virtual void _set_size(const sf::Vector2f &size) = 0;

	virtual void _display(sf::RenderWindow &window) const = 0;


public :
	  Interface(const int &priority = 0);

		int get_priority() const;
		sf::Vector2f get_position() const;
		sf::Angle get_angle() const;
		sf::Vector2f get_size() const;


		void set_position(const sf::Vector2f &position);
		void set_position(const float &x, const float &y);

		void set_angle(const sf::Angle& angle);
		void set_angle(const float &angle);

		void set_size(const sf::Vector2f& size);
		void set_size(const float &ratio);

		void set_priority(const int &prio);

		void display(sf::RenderWindow &window) const;
};
