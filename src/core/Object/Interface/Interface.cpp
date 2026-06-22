
#include "Interface.h"


Interface::Interface(const int &priority) : priority{ priority } {}


int Interface::get_priority() const { return priority; }
sf::Vector2f Interface::get_position() const { return _get_position(); }
sf::Angle Interface::get_angle() const { return _get_angle(); }
sf::Vector2f Interface::get_size() const { return _get_size(); }


void Interface::set_position(const sf::Vector2f &position) { _set_position(position); }
void Interface::set_position(const float &x, const float &y) { set_position(sf::Vector2f{ x, y }); }

void Interface::set_angle(const sf::Angle &angle) { _set_angle(angle); }
void Interface::set_angle(const float &angle) { set_angle(sf::degrees(angle)); }

void Interface::set_size(const sf::Vector2f &size) { _set_size(size); };
void Interface::set_size(const float &ratio) { set_size(sf::Vector2f{ ratio, ratio }); }

void Interface::set_priority(const int &prio) { priority = prio; }

void Interface::display(sf::RenderWindow & window) const
{
	_display(window);
}