#include "game.h"

// Private Functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "MyGame");
}

// Constructor & Destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}
// Accessors

// Functions

void Game::pollEvents()
{
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}
void Game::update()
{
    this->pollEvents();
}

/*
    @return void

    - clear old frame

    - return objects

    - display frame in window

    Renders the Game objects.
*/
void Game::render()
{
    this->window->clear(sf::Color(20, 0, 0, 255));

    // Draw game objects

    this->window->display();
}

const bool Game::isRunning() const
{
    return this->window->isOpen();
}

/*
Future Reference ( I used pointers, The reasons are explained below, Use this video If i forget how SFML or C++ functions.
https://www.youtube.com/watch?v=kxb0GvBNOGU&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=6
*/