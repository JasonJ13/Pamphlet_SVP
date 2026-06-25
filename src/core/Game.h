#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <utility>
#include <iostream>
#include <memory>
#include <ranges>

#include "Object/GameObject.h"
#include "Object/InteractibleObject.h"
#include "Object/Parchemin.h"
#include "Object/FixObject.h"
#include "TextureGestioner.h"

#include "Object/Interface/InterfaceText.h"

static constexpr int SIZE_X{ 1600 };
static constexpr int SIZE_Y{ 900 };

static constexpr sf::Color MAIN_COLOR{ 48, 64, 0 };

class Game {


	struct
	{
		sf::Vector2i position;
		bool held;
		std::shared_ptr<InteractibleObject> objhold;
 		sf::Vector2f old_position;
	} mouse_information;

 private :
	 sf::RenderWindow mWindow{ sf::VideoMode({SIZE_X, SIZE_Y}), "S'il vous plait un panphlet" };
	 static const sf::Time TimePerFrame;
	 
	 int score = 0;
	 std::shared_ptr<Parchemin> parchemin;
	 std::shared_ptr<InterfaceText> scoreInterface;

	 bool isButtonPressed = false;

	 std::vector<std::shared_ptr<GameObject>> gameObjects{};
	 std::vector<std::shared_ptr<InteractibleObject>> interactibleObjects{};
	 
	 std::shared_ptr<InteractibleObject> get_object_from_position(sf::Vector2i position);

	 void new_character();

	 void prepare();
	 void click_gestioner();
	 void update(float deltaTime);

	 


 public:
	Game();
	~Game() = default;

	void run();

};