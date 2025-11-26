#pragma once
#include <cstdlib>

int GRID_WIDTH = 30, GRID_HEIGHT = 20;
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
