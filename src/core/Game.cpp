#pragma once

#include "Game.h"
#include "Object/GameObject.h"
#include "Object/InteractibleObject.h"
#include "Object/Character.h"
#include "TextureGestioner.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
TextureGestioner texturesGestioner{};

Game::Game() : mouse_information{ sf::Vector2i {0,0}, false, nullptr, sf::Vector2f{0,0} } {}


std::shared_ptr<InteractibleObject> Game::get_object_from_position(sf::Vector2i position)
{

  int priority = -1;
  std::shared_ptr<InteractibleObject>object_selected = nullptr;

  for (auto &interactibleObject : interactibleObjects)
  {
    if (priority < interactibleObject->get_priority() && interactibleObject->is_hit(position))
    {
      object_selected = interactibleObject;
      priority = object_selected->get_priority();
    }
  }

  if (object_selected != nullptr)
  {
    //std::cout << "object selected" << '\n';
  }

  return object_selected;
}


void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;


  gameObjects.push_back(std::make_shared<Character>(sf::Vector2f(0, 64), texturesGestioner));
  auto parchemin = std::make_shared<Parchemin>(sf::Vector2f(100, 100),texturesGestioner);

  interactibleObjects.push_back(parchemin);
  gameObjects.push_back(std::move(parchemin));
  

  while (mWindow.isOpen()) {
    
    sf::Time deltaTime = clock.restart();
    float deltaSec = deltaTime.asSeconds();

    while (const std::optional event = mWindow.pollEvent()) {

      // Détection de la fermeture de la fenètre
      if (event->is<sf::Event::Closed>())
      {
        mWindow.close();
        return;
      }
      // Détection d'un changement de taille dans la fenètre
      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
        mWindow.setView(sf::View(visibleArea));
      }
    }
    

    // Redéfinition des paramètres de positions de la sourie
    mouse_information.position = sf::Mouse::getPosition() - mWindow.getPosition();

    // Gestion du click

    // Clique appuye
    isButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    
    if (isButtonPressed && !mouse_information.held)
    {
      mouse_information.held = true;

      mouse_information.objhold = get_object_from_position(mouse_information.position);
      if (mouse_information.objhold != nullptr)
      {
        mouse_information.old_position = mouse_information.objhold->get_position();
        mouse_information.objhold->grabed(mouse_information.position);
      }
    }

    // Clique relache
    else if (!isButtonPressed && mouse_information.held)
    {
      if (mouse_information.objhold != nullptr)
      {

        sf::Vector2f new_position = mouse_information.objhold->get_position();
      }

      mouse_information.held = false;
      mouse_information.objhold = nullptr;
    }

    // Clique maintenu avec objet
    else if (mouse_information.objhold != nullptr)
    {
      mouse_information.objhold->set_position(mouse_information.position);
    }

    mWindow.clear();
    render(deltaSec);

  }



  return;
}


void Game::render(float deltaSec)
{
  

  for (const auto &gameObject : gameObjects)
  {
    gameObject->display(mWindow, deltaSec);
  }
  
  mWindow.display();

  return;
}
