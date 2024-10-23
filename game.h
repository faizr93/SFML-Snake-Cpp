#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


/*
    Class that acts as Game Engine
    Wrapper Class
*/
class Game
{
private:
    // Window and Other Class Objects
    sf::RenderWindow *window; // without pointers, the object gets destroyed after functions completion.
    sf::Event ev;
    sf::RectangleShape *snake_head;
    sf::VideoMode *video_mode;
    sf::Clock *clock;
    // Variables
    const char UP = 'w';
    const char DOWN = 's';
    const char RIGHT = 'd';
    const char LEFT = 'a';
    const float GRID_CELL_SIZE = 25;
    const uint32_t WINDOW_HEIGHT = 500;
    const uint32_t WINDOW_WIDTH = 500;
    
    char dir;

    // Private Functions.
    void initVariables();
    void initWindow();
    void initSnakeSegments();
    void moveSnakeHead(float x, float y);
    void moveSnake();

public:
    // Constructors & Destructors
    Game();
    ~Game();

    //Accessors
    const bool isRunning() const;

    // Functions
    void pollEvents();
    void update();
    void render();
};
