#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>
#include <memory>
#include <ranges>

#include "GameObject.h"

class Game {

	struct
	{
		sf::Vector2i position;
		int chunk;
		bool held;
		GameObject *objhold;
	} mouse_information;

 private :
	 sf::RenderWindow mWindow{ sf::VideoMode({640, 480}), "S'il vous plait un panphlet" };
	 static const sf::Time TimePerFrame;

	 std::vector<std::unique_ptr<GameObject>> gameObjects{};

	 void render();


 public:
	Game();

	void run();

};