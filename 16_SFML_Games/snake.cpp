#include <SFML/Graphics.hpp>
#include <time.h>
#include "./SnakeGameLogic.h"

using namespace sf;

int CELL_SIZE=16;
int WINDOW_WIDTH = CELL_SIZE*GRID_WIDTH;
int WINDOW_HEIGHT = CELL_SIZE*GRID_HEIGHT;
const float INITIAL_DELAY = 0.1f;



int snake()
{  
    SnakeGameLogic game;
    srand(time(0));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Texture t1,t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer=0, delay= INITIAL_DELAY;
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time; 

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))  game.setDirection(Left);
        if (Keyboard::isKeyPressed(Keyboard::Right)) game.setDirection(Right);
        if (Keyboard::isKeyPressed(Keyboard::Up))    game.setDirection(Up);
        if (Keyboard::isKeyPressed(Keyboard::Down))  game.setDirection(Down);

        if (timer>delay) {
            timer=0; game.tick();
        }

   ////// draw  ///////
    window.clear();

    for (int i = 0; i < GRID_WIDTH; i++) 
    {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            sprite1.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            window.draw(sprite1);
        }
    }

    for (int i=0;i< game.snakeLength;i++){
        sprite2.setPosition(game.snake[i].x * CELL_SIZE, game.snake[i].y * CELL_SIZE);
        window.draw(sprite2); 
    }
   
    sprite2.setPosition(game.fruit.x * CELL_SIZE, game.fruit.y * CELL_SIZE);
    window.draw(sprite2);

    window.display();
    }

    return 0;
}
