#pragma once

#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


Game::Game() : mouse_information{ sf::Vector2i {0,0}, 0, false, nullptr } {}


void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  // Objet de test
  gameObjects.push_back(std::make_unique<GameObject>(20,20));

  
  std::unique_ptr<GameObject> obj_hold;
  
  while (mWindow.isOpen()) {
    
    while (const std::optional event = mWindow.pollEvent()) {

      // Détection de la fermeture de la fenètre
      if (event->is<sf::Event::Closed>()) mWindow.close();

      // Détection d'un changement de taille dans la fenètre
      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
        mWindow.setView(sf::View(visibleArea));
      }
    }
    sf::Vector2i pos = mWindow.getPosition();

    // Redéfinition des paramètres de positions de la sourie
    mouse_information.position = sf::Mouse::getPosition() - mWindow.getPosition();
    mouse_information.chunk = 0;
  

    //Test de l'image
    sf::Texture test_texture{};
    if (!test_texture.loadFromFile("resources/Cyrano.png"))
    {
      assert(false && "Image test non chargee");
    }
    sf::Sprite sprite_test{ test_texture };
    sprite_test.setPosition(sf::Vector2f(100, 100));


    // Gestion du click
    bool isButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if (isButtonPressed && !mouse_information.held)
    {
      mouse_information.held = true;

      // Nouvelle objet cliqué
      for (auto &gameobj : gameObjects)// | std::views::filter([](const auto &gameobj) { return gameobj->in_chunk(0); }))
      {
        if (gameobj->is_hit(mouse_information.position))
        {
          mouse_information.objhold = gameobj.get();
          mouse_information.objhold->grabed(mouse_information.position);
        }
      }
    }

    // Clique relaché
    else if (!isButtonPressed && mouse_information.held)
    {
      mouse_information.held = false;
      mouse_information.objhold = nullptr;
    }

    // Clique maintenu avec objet
    else if (mouse_information.objhold != nullptr)
    {
      mouse_information.objhold->set_position(mouse_information.position);
    }
    
    
    
    render();
  }
  

  return;
}


void Game::render() 
{
  mWindow.clear();

  //mWindow.draw(sprite_test);

  for (const auto &gameObject : gameObjects)
  {
    gameObject->display(mWindow);
  }

  mWindow.display();

  return;
}