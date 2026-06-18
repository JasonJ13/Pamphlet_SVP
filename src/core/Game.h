#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>
#include <memory>
#include <ranges>

#include "Object/GameObject.h"
#include "Object/InteractibleObject.h"
#include "Object/Parchemin.h"
#include "TextureGestioner.h"

static constexpr int SIZE_X = 1080;
static constexpr int SIZE_Y = 960;

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

	 bool isButtonPressed = false;

	 std::vector<std::shared_ptr<GameObject>> gameObjects{};
	 std::vector<std::shared_ptr<InteractibleObject>> interactibleObjects{};
	 

	 void render(float deltaTime);

	 std::shared_ptr<InteractibleObject> get_object_from_position(sf::Vector2i position);


 public:
	Game();
	~Game() = default;

	void run();

};