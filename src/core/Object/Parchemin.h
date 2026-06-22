#pragma once

#include "ParcheminBig.h"
#include "ParcheminLittle.h"

#include "Object/InteractibleObject.h"
#include "../TextureGestioner.h"



class Parchemin : public InteractibleObject
{

private :
	std::shared_ptr<ParcheminBig> parcheminBig;
	std::shared_ptr<ParcheminLittle> parcheminLittle;

	std::string_view titre;
	std::string_view theme;

  // 1 -> little / 0 -> big
	int state = 1;

	bool good = true;
	int answering = 0;

	void _grabed(const sf::Vector2i &mouse_position) override;
	void _hold(const sf::Vector2i &mouse_position) override;
	void _release(const sf::Vector2i &mouse_position, const sf::Vector2f &last_position = sf::Vector2f{}) override;

	void _update(sf::RenderWindow &mWindow, const float &deltaSec) override;

	void set_position_parchemin(const sf::Vector2f &new_position);
	void set_position_parchemin(const sf::Vector2i &new_position);

	

public :
	Parchemin(const sf::Vector2f &position, TextureGestioner &textureGestioner, const int &priority = 0);

	std::string_view get_title() const;
	std::string_view get_theme() const;
	std::vector<std::shared_ptr<InteractibleObject>> get_parchemins() const;

	void activate_parchemin();

	bool have_gave_respond() const;
	bool have_gave_good_respond() const;

	void reset();
};
