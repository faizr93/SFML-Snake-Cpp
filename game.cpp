#include "game.h"
#include <iostream>
#include <vector>
// Constructor & Destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initSnakeSegments();
}

Game::~Game()
{
    delete this->window;
    delete this->snake_head;
    delete this->video_mode;
    delete this->clock;
}

// Private Functions
void Game::initVariables()
{
    this->window = nullptr;
    this->snake_head = nullptr;
    this->dir = UP;
    this->clock = new sf::Clock;
}

void Game::initWindow()
{
    this->video_mode = new sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->window = new sf::RenderWindow(*this->video_mode, "MyGame");
    this->window->setFramerateLimit(75);
}
void Game::initSnakeSegments()
{
    //     initSnakeHead();
    //     initSnakeMidBody();
    //     initSnakeTail();
    this->snake_head = new sf::RectangleShape;

    snake_head->setSize(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
    snake_head->setFillColor(sf::Color::Green);
    snake_head->setOutlineThickness(3.f);
    snake_head->setOutlineColor(sf::Color::Black);
    snake_head->setPosition(sf::Vector2f(150.f, 150.f));
}

// Accessors
const bool Game::isRunning() const
{
    return this->window->isOpen();
}

// Functions

void Game::pollEvents()
{
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
            // Making the Window Closeable
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }

            // Direction Changing Logic
            if (ev.key.code == sf::Keyboard::Up)
            {
                dir = UP;
            }

            if (ev.key.code == sf::Keyboard::Down)
            {
                dir = DOWN;
            }

            if (ev.key.code == sf::Keyboard::Right)
            {
                dir = RIGHT;
            }

            if (ev.key.code == sf::Keyboard::Left)
            {
                dir = LEFT;
            }
            break;
        }
    }
}

void Game::moveSnakeHead(float x, float y)
{
    this->snake_head->move(sf::Vector2f(x, y));
}
void Game::moveSnake()
{
    if (dir == UP)
    {
        moveSnakeHead(0, -GRID_CELL_SIZE);
    }
    if (dir == DOWN)
    {
        moveSnakeHead(0, GRID_CELL_SIZE);
    }
    if (dir == RIGHT)
    {
        moveSnakeHead(GRID_CELL_SIZE, 0);
    }
    if (dir == LEFT)
    {
        moveSnakeHead(-GRID_CELL_SIZE, 0);
    }
}
void Game::update()
{
    if (clock->getElapsedTime().asMilliseconds() >= 500.0f)
    {

        this->moveSnake();
        sf::Vector2f snake_pos = this->snake_head->getPosition();
        if (snake_pos.x > (500.f-GRID_CELL_SIZE))
        {
            this->snake_head->setPosition(0, snake_pos.y);
        }
        if (snake_pos.y > (500.f-GRID_CELL_SIZE)){
            this->snake_head->setPosition(snake_pos.x,0);
        };
        if (snake_pos.x < 0){
            this->snake_head->setPosition((500.f-GRID_CELL_SIZE), snake_pos.y);
        }
        if (snake_pos.y < 0){
            this->snake_head->setPosition(snake_pos.x,(500.f-GRID_CELL_SIZE));
        };
        std::cout << "Snake Position: (" << snake_pos.x << ", " << snake_pos.y << ")" << std::endl;
        clock->restart(); // Reset the clock
    }
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
    this->window->clear();

    // Draw game objects
    this->window->draw(*this->snake_head);

    this->window->display();
}

/*
Future Reference ( I used pointers, The reasons are explained below, Use this video If i forget how SFML or C++ functions.
https://www.youtube.com/watch?v=kxb0GvBNOGU&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=6
*/
