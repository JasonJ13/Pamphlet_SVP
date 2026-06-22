
#include "InterfaceText.h"
#include "Interface.h"

InterfaceText::InterfaceText(const std::string &string, const int &priority) : Interface{ priority }, text{ font, string } 
{
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Red);
}

sf::Vector2f InterfaceText::_get_position() const { return text.getPosition(); }
sf::Angle InterfaceText::_get_angle() const { return text.getRotation(); }
sf::Vector2f InterfaceText::_get_size() const { return text.getScale(); }

void InterfaceText::_set_position(const sf::Vector2f &position) { text.setPosition(position); };
void InterfaceText::_set_angle(const sf::Angle &angle) { text.setRotation(angle); }
void InterfaceText::_set_size(const sf::Vector2f &size) { text.setScale(size); }
void InterfaceText::set_string(const std::string &string) { text.setString(string); }

void InterfaceText::_display(sf::RenderWindow &window) const { window.draw(text); }
