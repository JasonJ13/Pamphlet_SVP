
#include "Parchemin.h"

#include <memory>

#include "../Game.h"

#include "Interface/InterfaceRectangle.h"


Parchemin::Parchemin(const sf::Vector2f &position, TextureGestioner &textureGestioner, const int &priority)
: InteractibleObject{std::make_unique<InterfaceRectangle>(0,0, sf::Color::Black, 0)}, parcheminLittle{}, parcheminBig{}
{
	parcheminLittle = std::make_shared<ParcheminLittle>(position, textureGestioner);
	parcheminLittle->desactivate();
	parcheminBig = std::make_shared<ParcheminBig>(position, textureGestioner);
	parcheminBig->desactivate();
	set_hitbox_size(sf::Vector2f(128,128));

	good = parcheminBig->reset_contain();
}


void Parchemin::set_position_parchemin(const sf::Vector2f &new_position)
{


	state = new_position.x < SIZE_X / 3;

	if (state)
	{
		parcheminLittle->set_position(new_position);
		parcheminBig->set_position(-256, -256);
		set_hitbox_size(sf::Vector2f(128, 128));

	}
	else
	{
		parcheminBig->set_position(new_position);
		parcheminLittle->set_position(-256, -256);
		set_hitbox_size(parcheminBig->get_size());
	}
}
void Parchemin::set_position_parchemin(const sf::Vector2i &new_position) { set_position_parchemin(sf::Vector2f{ new_position }); }

void Parchemin::_grabed(const sf::Vector2i &mouse_position)
{
	if (state) parcheminLittle->grabed(mouse_position);
	else parcheminBig->grabed(mouse_position);
}

void Parchemin::_hold(const sf::Vector2i &mouse_position)
{ 
	
	set_position_parchemin(mouse_position);
}

void Parchemin::_release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position)
{

	if (mouse_position.x < SIZE_X / 3 && mouse_position.y < SIZE_Y / 2)
	{
		answering = 1;
	}
	else if (mouse_position.x < SIZE_X / 6 && mouse_position.y > SIZE_Y * 3 / 4)
	{
		answering = -1;
	}
	
}

void Parchemin::_update(sf::RenderWindow &mWindow, const float &deltaSec)
{
	if (state) position = (parcheminLittle->get_position());
	else position = (parcheminBig->get_position());
}

std::string_view Parchemin::get_title() const { return titre; }
std::string_view Parchemin::get_theme() const { return theme; }
std::vector<std::shared_ptr<InteractibleObject>> Parchemin::get_parchemins() const { return { parcheminLittle, parcheminBig }; }


void Parchemin::activate_parchemin()
{
	parcheminLittle->set_position(position);
	parcheminLittle->activate();
	parcheminBig->set_position(-256, -256);
	parcheminBig->activate();
}

bool Parchemin::have_gave_respond() const { return answering != 0; }
bool Parchemin::have_gave_good_respond() const
{
	return ((answering == 1 && good) || (answering == -1 && !good));
}

void Parchemin::reset()
{
	answering = 0;
	good = parcheminBig->reset_contain();
	parcheminLittle->set_position(1600 / 6, 0);
	parcheminLittle->play_animation("throw");
}