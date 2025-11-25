#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int GRID_WIDTH=30,GRID_HEIGHT=20;
int CELL_SIZE=16;
int WINDOW_WIDTH = CELL_SIZE*GRID_WIDTH;
int WINDOW_HEIGHT = CELL_SIZE*GRID_HEIGHT;
const float INITIAL_DELAY = 0.1f;

const int MAX_SNAKE_LENGTH = 100;

enum Direction {
    Down = 0,
    Left = 1,
    Right = 2,
    Up = 3
};

struct Snake { int x, y; };
struct Fruit { int x, y; };

class SnakeGameLogic {
public:
    SnakeGameLogic() {
        snakeLength = 4;
        direction = Down;
        fruit.x = 10;
        fruit.y = 10;
        snake[0].x = GRID_WIDTH / 2;
        snake[0].y = GRID_HEIGHT / 2;
    }

    void setDirection(Direction d) {
        direction = d;
    }

    void tick() {
        for (int i = snakeLength; i > 0; --i) {
            snake[i] = snake[i - 1];
        }

        if (direction == Down)  snake[0].y += 1;
        if (direction == Left)  snake[0].x -= 1;
        if (direction == Right) snake[0].x += 1;
        if (direction == Up)    snake[0].y -= 1;

        if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
            snakeLength++;
            fruit.x = rand() % GRID_WIDTH;
            fruit.y = rand() % GRID_HEIGHT;
        }

        if (snake[0].x > GRID_WIDTH)  snake[0].x = 0;
        if (snake[0].x < 0)           snake[0].x = GRID_WIDTH;
        if (snake[0].y > GRID_HEIGHT) snake[0].y = 0;
        if (snake[0].y < 0)           snake[0].y = GRID_HEIGHT;

        for (int i = 1; i < snakeLength; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                snakeLength = i;
        }
    }

    Snake snake[MAX_SNAKE_LENGTH];
    Fruit fruit;
    int snakeLength;
    Direction direction;
};

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
