#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int GRID_WIDTH=30,GRID_HEIGHT=20;
int CELL_SIZE=16;
int WINDOW_WIDTH = CELL_SIZE*GRID_WIDTH;
int WINDOW_HEIGHT = CELL_SIZE*GRID_HEIGHT;

const int MAX_SNAKE_LENGTH = 100;

enum Direction {
    Down = 0,
    Left = 1,
    Right = 2,
    Up = 3
};

Direction direction = Up ;

int snakeLength=4;

struct Snake 
{ int x,y;}  snakeObject[MAX_SNAKE_LENGTH];

struct Fruit
{ int x,y;} fruits;

void Tick()
 {
    for (int i=snakeLength;i>0;--i)
     {snakeObject[i].x=snakeObject[i-1].x; snakeObject[i].y=snakeObject[i-1].y;}

    if (direction== Down) snakeObject[0].y+=1;      
    if (direction== Left) snakeObject[0].x-=1;        
    if (direction== Right) snakeObject[0].x+=1;         
    if (direction==Up) snakeObject[0].y-=1;   

    if ((snakeObject[0].x==fruits.x) && (snakeObject[0].y==fruits.y)) 
     {snakeLength++; fruits.x=rand()%GRID_WIDTH; fruits.y=rand()%GRID_HEIGHT;}

    if (snakeObject[0].x>GRID_WIDTH) snakeObject[0].x=0;  if (snakeObject[0].x<0) snakeObject[0].x=GRID_WIDTH;
    if (snakeObject[0].y>GRID_HEIGHT) snakeObject[0].y=0;  if (snakeObject[0].y<0) snakeObject[0].y=GRID_HEIGHT;
 
    for (int i=1;i<snakeLength;i++)
     if (snakeObject[0].x==snakeObject[i].x && snakeObject[0].y==snakeObject[i].y)  snakeLength=i;
 }

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Texture t1,t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer=0, delay=0.1;

    fruits.x=10;
    fruits.y=10; 
    
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

        if (Keyboard::isKeyPressed(Keyboard::Left)) direction=Left ;   
        if (Keyboard::isKeyPressed(Keyboard::Right)) direction= Right ;    
        if (Keyboard::isKeyPressed(Keyboard::Up)) direction= Up;
        if (Keyboard::isKeyPressed(Keyboard::Down)) direction=Down ;

        if (timer>delay) {timer=0; Tick();}

   ////// draw  ///////
    window.clear();

    for (int i=0; i<GRID_WIDTH; i++) 
      for (int j=0; j<GRID_HEIGHT; j++) 
        { sprite1.setPosition(i*CELL_SIZE, j*CELL_SIZE);  window.draw(sprite1); }

    for (int i=0;i<snakeLength;i++)
        { sprite2.setPosition(snakeObject[i].x*CELL_SIZE, snakeObject[i].y*CELL_SIZE);  window.draw(sprite2); }
   
    sprite2.setPosition(fruits.x*CELL_SIZE, fruits.y*CELL_SIZE);  window.draw(sprite2);    

    window.display();
    }

    return 0;
}
