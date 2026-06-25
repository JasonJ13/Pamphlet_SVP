#include "Game.h"
#include "TextureGestioner.h"

#include <algorithm>

#include "Object/GameObject.h"
#include "Object/InteractibleObject.h"
#include "Object/Character.h"
#include "Object/FixObject.h"

#include "Object/Interface/InterfaceRectangle.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


TextureGestioner texturesGestioner{};

Game::Game() : mouse_information{ sf::Vector2i {0,0}, false, nullptr, sf::Vector2f{0.f,0.f} } { }


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

  return object_selected;
}


void Game::new_character()
{
  auto new_character = std::make_shared<Character>(sf::Vector2f(-128.f, -2.f), texturesGestioner);
  
  parchemin = new_character->get_parchemin();
  for (auto parchemin : parchemin->get_parchemins())
  {
    gameObjects.push_back(parchemin);
  }
  
  interactibleObjects.push_back(parchemin);
  gameObjects.push_back(std::move(new_character));
}


void Game::prepare()
{
  auto separationRectangle = std::make_unique<InterfaceRectangle>(8, SIZE_Y, sf::Color::Black, 5);
  separationRectangle->set_position(SIZE_X / 3, 0);
  gameObjects.push_back(std::make_unique<FixObject>(std::move(separationRectangle)));

  scoreInterface = std::make_unique<InterfaceText>(std::to_string(score), 10);

  auto leftRectangle = std::make_unique<InterfaceRectangle>(SIZE_X / 3, SIZE_Y, sf::Color{ 64, 32, 0 }, 2);
  gameObjects.push_back(std::make_shared<FixObject>(std::move(leftRectangle)));

  gameObjects.push_back(std::make_shared<FixObject>(sf::Vector2f(0.f, SIZE_Y / 2), "resources/table.png", texturesGestioner, sf::Vector2f(2.1, 2.1), 4));
  gameObjects.push_back(std::make_shared<FixObject>(sf::Vector2f(0.f, SIZE_Y - 256), "resources/bin.png", texturesGestioner, sf::Vector2f(4.f, 4.f), 4));

  new_character();
}


void Game::click_gestioner()
{
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
      mouse_information.objhold->release(mouse_information.position, mouse_information.old_position);
    }

    mouse_information.held = false;
    mouse_information.objhold = nullptr;
  }

  // Clique maintenu avec objet
  else if (mouse_information.objhold != nullptr)
  {
    mouse_information.objhold->hold(mouse_information.position);
  }
}




void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  sf::Image icon = sf::Image{};
  if (!icon.loadFromFile("resources/parchemin.png"))
  {
    std::cout << "icon not found\n";
    abort();
  }
  mWindow.setIcon(icon);

  prepare();

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
    

    click_gestioner();

    mWindow.clear(MAIN_COLOR);
    update(deltaSec);

  }



  return;
}


void Game::update(float deltaSec)
{
  
  if (parchemin->have_gave_respond())
  {
    if (parchemin->have_gave_good_respond())
    {
      score = score + 10;
      scoreInterface->set_string(std::to_string(score));
    }
    else
    {
      score = score - 5;
      scoreInterface->set_string(std::to_string(score));
    }
    parchemin->reset();
  }

  std::sort(gameObjects.begin(), gameObjects.end(),
    [](const auto &a, const auto &b)
    {
      return a->get_priority() < b->get_priority();
    });

  

  for (const auto &gameObject : gameObjects)
  {

    gameObject->update(mWindow, deltaSec);
  }
  scoreInterface->display(mWindow);

  mWindow.display();

  return;
}
