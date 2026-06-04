#pragma once

#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


Game::Game() {}


void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  
  while (mWindow.isOpen()) {
    while (const std::optional event = mWindow.pollEvent()) {

      if (event->is<sf::Event::Closed>()) mWindow.close();

      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
        mWindow.setView(sf::View(visibleArea));
      }
    }
    sf::Vector2i pos = mWindow.getPosition();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      std::cout << sf::Mouse::getPosition().x - pos.x << '\n';
    }
    

    render();
  }
  

  return;
}


void Game::render() 
{
  mWindow.clear();
  mWindow.display();

  return;
}