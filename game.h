#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>

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
    sf::RectangleShape *snake_segment; //A Single Snake Segment, with color, position
    sf::RectangleShape *food;
    sf::VideoMode *video_mode;
    sf::Clock *clock;
    
    sf::Vector2f snake_pos; // The Snake Segments Current Position Stored in Vector2f
    std::vector<sf::Vector2f> vec_snake_positions; //A Vector(dynamic array) Storing Snake's Previous Positions as vector2f
    // Variables
    static const char UP = 'w';
    static const char DOWN = 's';
    static const char RIGHT = 'd';
    static const char LEFT = 'a';
    static const uint32_t WINDOW_HEIGHT = 500;
    static const uint32_t WINDOW_WIDTH = 500;
    const float GRID_CELL_SIZE = 25;
    char dir;
    int snake_length = 1550;

    // Private Functions.
    void initVariables();
    void initWindow();
    void initSnakeSegments();
    void initFood();
    bool isSelfCollided();
    bool isFoodCollided();
    

public:
    // Constructors & Destructors
    Game();
    ~Game();

    //Accessors
    const bool isRunning() const;

    // Functions
    void generateFood();
    void moveSnakeHead(float x, float y);
    void moveSnake();
    void setDirection();
    void wrapSnakePos();
    void pollEvents();
    void update();
    void render();
};
