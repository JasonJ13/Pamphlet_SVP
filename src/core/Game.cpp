#pragma once

#include "Game.h"
#include "GameObject.h"
#include "InteractibleObject.h"
#include "TextureGestioner.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
TextureGestioner texturesGestioner{};

Game::Game() : mouse_information{ sf::Vector2i {0,0}, false, nullptr, sf::Vector2f{0,0} } {}


InteractibleObject *Game::get_object_from_position(sf::Vector2i position)
{
  sf::Vector2i cell = position / 256;

  int priority = -1;
  InteractibleObject *object_selected = nullptr;

  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if (cell.x + i >= 0 && cell.x + i < (SIZE_X / 256) && cell.y + j >= 0 && cell.y + j < (SIZE_Y / 256))
      {
      }
    }
  }

  if (object_selected != nullptr)
  {
    std::cout << "object selected" << '\n';
  }

  return object_selected;
}


void Game::new_Game_Object(sf::Vector2f position, std::string_view file_name)
{
  auto sprite = texturesGestioner.load(Textures::ID::Test, file_name);
  gameObjects.push_back(std::make_unique<GameObject>(position, sprite, sf::Vector2f{ 0.25, 0.25 }));
}

void Game::new_Interactible_Object(sf::Vector2f position, std::string_view file_name)
{
  auto sprite = texturesGestioner.load(Textures::ID::Cyrano, file_name);
  auto new_object = std::make_unique<InteractibleObject>(position, sprite, sf::Vector2f{ 4, 4 });

  gameObjects.push_back(std::move(new_object));
}


void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;


  new_Game_Object(sf::Vector2f{ 0, (SIZE_Y - 256) / 2  }, "resources/test.jpg");
  //new_Interactible_Object(sf::Vector2f{ 250,250 }, "resources/Cyrano.png");
  

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
        //std::remove(positionIO[mouse_information.old_position.x / 256][mouse_information.old_position.y / 256].begin(),
          //positionIO[mouse_information.old_position.x / 256][mouse_information.old_position.y / 256].end(), mouse_information.objhold);

        sf::Vector2f new_position = mouse_information.objhold->get_position();
        //positionIO[new_position.x / 256][new_position.y / 256].push_back(mouse_information.objhold);
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
