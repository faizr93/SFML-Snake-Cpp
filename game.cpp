#include "game.h"
#include <unistd.h>

// Constructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initSnakeSegments();
    this->initFood();
}
// Destructor
Game::~Game()
{
    delete this->window;
    delete this->snake_segment;
    delete this->video_mode;
    delete this->clock;
}

// Private Functions

// Initializes Variables of Class Game
void Game::initVariables()
{
    this->window = nullptr;
    this->snake_segment = nullptr;
    this->dir = UP;
    this->clock = new sf::Clock;
}

// Initializes Window with Const Width and Height, Sets FrameRate Limit.
void Game::initWindow()
{
    this->video_mode = new sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->window = new sf::RenderWindow(*this->video_mode, "MyGame");
    this->window->setFramerateLimit(75);
}

// Initializes All Parts of the Snake such as Head, Middle, Tail
// Initializes Their Color, Size and Position
void Game::initSnakeSegments()
{
    //     initSnakeHead();
    //     initSnakeMidBody();
    //     initSnakeTail();
    this->snake_segment = new sf::RectangleShape;
    snake_segment->setOutlineThickness(3.f);
    snake_segment->setSize(sf::Vector2f(GRID_CELL_SIZE - snake_segment->getOutlineThickness(), GRID_CELL_SIZE - snake_segment->getOutlineThickness()));
    snake_segment->setFillColor(sf::Color::Green);
    snake_segment->setOutlineColor(sf::Color::Transparent);
    snake_segment->setPosition(sf::Vector2f(150.f, 150.f));
}
void Game::initFood()
{
    this->food = new sf::RectangleShape;
    food->setOutlineThickness(3.f);
    food->setSize(sf::Vector2f(GRID_CELL_SIZE - food->getOutlineThickness(), GRID_CELL_SIZE - food->getOutlineThickness()));
    food->setFillColor(sf::Color::Red);
    food->setOutlineColor(sf::Color::Black);
    food->setPosition(sf::Vector2f(150.f, 150.f));
}

void Game::generateFood()
{
    int grid_width = static_cast<int>(WINDOW_WIDTH / GRID_CELL_SIZE);
    int grid_height = static_cast<int>(WINDOW_HEIGHT / GRID_CELL_SIZE);

    // Ensure food doesn't spawn on snake position
    sf::Vector2f food_position;
    bool valid_food_position = false;

    while (!valid_food_position)
    {
        int x = (rand() % grid_width) * GRID_CELL_SIZE;
        int y = (rand() % grid_height) * GRID_CELL_SIZE;
        food_position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));

        valid_food_position = true; // Assume valid until we check against all snake positions
        for (const auto &position : vec_snake_positions)
        {
            if (position == food_position)
            {
                valid_food_position = false; // Found a collision with the snake
                break;
            }
        }
    }
    food->setPosition(food_position);
}

// Accessors
const bool Game::isRunning() const
{
    return this->window->isOpen();
}

// Public Functions

// Tracks All Keypresses (events) and Stores them in Event Variable (ev)
// Takes Appropriate Action based on each Event
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
            setDirection();
            break;
        }
    }
}

// Sets Direction(dir) to KeyPressed
void Game::setDirection() // clang-format off
{  
    switch (ev.key.code) {
        case sf::Keyboard::Up:    dir = UP;    break;
        case sf::Keyboard::Down:  dir = DOWN;  break;
        case sf::Keyboard::Right: dir = RIGHT; break;
        case sf::Keyboard::Left:  dir = LEFT;  break; } 
} 

// Moves Snake Head Based On Dir (Direction Variable)
void Game::moveSnake()
{
    switch(dir) {
        case UP:    moveSnakeHead(0, -GRID_CELL_SIZE); break; // Negative Y value = up in SFML
        case DOWN:  moveSnakeHead(0,  GRID_CELL_SIZE); break;
        case RIGHT: moveSnakeHead( GRID_CELL_SIZE, 0); break;
        case LEFT:  moveSnakeHead(-GRID_CELL_SIZE, 0); break; }
    // clang-format on
}

// Encapsulation of the Move Function
// Moves Snake Head by offset of given Float Parameters
void Game::moveSnakeHead(float x, float y)
{
    this->snake_segment->move(sf::Vector2f(x, y));
}

/* 
Checks Each Position in Storing Vector against Position to be moved to
Returns True if Equal
Returns False if To Be moved Position is a new one.
*/
bool Game::isSelfCollided()
{
    for (const auto &position : vec_snake_positions)
    {
        if (position == snake_pos)
        {
            return true;
        }
        break;
    }
    return false;
}

bool Game::isFoodCollided()
{
    if (snake_pos == food->getPosition()){
        return true;
    }
    return false;
}


// All Game Logic, Runs in Intervals of Given Amount
void Game::update()
{
    if (clock->getElapsedTime().asMilliseconds() >= 400.0f)
    {
        moveSnake();
        wrapSnakePos();
        snake_pos = this->snake_segment->getPosition(); // Get Snake's Position
        if (isSelfCollided())
        {
            vec_snake_positions.clear();
            snake_length = 3;
        }
        if (isFoodCollided()) {
            generateFood();
            snake_length++;
        }
        vec_snake_positions.push_back(snake_pos); // Store Snake's Position

        if (vec_snake_positions.size() > snake_length)
        {
            vec_snake_positions.erase(vec_snake_positions.begin()); // Remove the oldest position
        }
        
        clock->restart(); // Reset the clock
    }
    this->pollEvents();
}

void Game::wrapSnakePos()
{
    sf::Vector2f snake_pos = this->snake_segment->getPosition();  // Get Pos
    snake_pos.x = fmod(snake_pos.x + WINDOW_WIDTH, WINDOW_WIDTH); // Wrap Pos
    snake_pos.y = fmod(snake_pos.y + WINDOW_HEIGHT, WINDOW_HEIGHT);

    this->snake_segment->setPosition(snake_pos);                                                // Set New Pos
    std::cout << "Snake Position: (" << snake_pos.x << ", " << snake_pos.y << ")" << std::endl; // TEMP DEBUG LINE
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
    this->window->clear(); // Clear Old Frame
    // Draw game objects to / Create New Frame
    for (auto &position : vec_snake_positions)
    {
        this->snake_segment->setPosition(position);
        this->window->draw(*this->snake_segment);
        this->window->draw(*this->food);
    }
    this->window->display(); // Display the New Frame
}

/*
Future Reference ( I used pointers, The reasons are explained below, Use this video If i forget how SFML or C++ work.
https://www.youtube.com/watch?v=kxb0GvBNOGU&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=6
*/

