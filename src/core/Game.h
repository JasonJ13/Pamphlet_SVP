#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>

class Game {

 private :
	 sf::RenderWindow mWindow{ sf::VideoMode({640, 480}), "S'il vous plait un panphlet" };
	 static const sf::Time TimePerFrame;

	 void render();


 public:
	Game();

	void run();

};