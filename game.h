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
    // Variables
    // Window
    sf::RenderWindow *window; // without pointers, the object gets destroyed after functions completion.
    sf::Event ev;
    // Private Functions.
    void initVariables();
    void initWindow();

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
