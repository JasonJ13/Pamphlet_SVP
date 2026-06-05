
#include "GameObject.h"


GameObject::GameObject(float x, float y) : x{x}, y{y}, offset{sf::Vector2i{0,0}}, hitbox{0, 0, 100, 100}, chunk{0} {}


void GameObject::move(float dx, float dy)
{
	x = x + dx;
	y = y + dy;
	hitbox.x = hitbox.x + dx;
	hitbox.y = hitbox.y + dy;
}

void GameObject::set_position(sf::Vector2i new_position)
{
	x = new_position.x - offset.x;
	y = new_position.y - offset.y;
	hitbox.x = new_position.x - 10 - offset.x;
	hitbox.y = y = new_position.y - 10 - offset.y;
}



bool GameObject::in_chunk(int chunk_clicked) const
{
	return chunk_clicked == chunk;
}

bool GameObject::is_hit(sf::Vector2i position) const
{
	if (position.x < hitbox.x || position.x > hitbox.x + hitbox.sizeX)
	{
		return false;
	}
	if (position.y < hitbox.y || position.y > hitbox.y + hitbox.sizeY)
	{
		return false;
	}

	return true;
}

void GameObject::grabed(sf::Vector2i mouse_position)
{
	offset.x = mouse_position.x - x;
	offset.y = mouse_position.y - y;
}


void GameObject::display(sf::RenderWindow &mWindow) const
{
	sf::CircleShape circle{ 20 };

	circle.setPosition(sf::Vector2f{ x,y });

	mWindow.draw(circle);
}