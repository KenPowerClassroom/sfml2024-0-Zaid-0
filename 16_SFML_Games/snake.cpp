#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int GRID_WIDTH=30,GRID_HEIGHT=20;
int CELL_SIZE=16;
int WINDOW_WIDTH = CELL_SIZE*GRID_WIDTH;
int WINDOW_HEIGHT = CELL_SIZE*GRID_HEIGHT;

const int MAX_SNAKE_LENGTH = 100;

int dir,num=4;

struct Snake 
{ int x,y;}  s[MAX_SNAKE_LENGTH];

struct Fruit
{ int x,y;} f;

void Tick()
 {
    for (int i=num;i>0;--i)
     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;      
    if (dir==1) s[0].x-=1;        
    if (dir==2) s[0].x+=1;         
    if (dir==3) s[0].y-=1;   

    if ((s[0].x==f.x) && (s[0].y==f.y)) 
     {num++; f.x=rand()%GRID_WIDTH; f.y=rand()%GRID_HEIGHT;}

    if (s[0].x>GRID_WIDTH) s[0].x=0;  if (s[0].x<0) s[0].x=GRID_WIDTH;
    if (s[0].y>GRID_HEIGHT) s[0].y=0;  if (s[0].y<0) s[0].y=GRID_HEIGHT;
 
    for (int i=1;i<num;i++)
     if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
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

    f.x=10;
    f.y=10; 
    
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

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;   
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;    
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;

        if (timer>delay) {timer=0; Tick();}

   ////// draw  ///////
    window.clear();

    for (int i=0; i<GRID_WIDTH; i++) 
      for (int j=0; j<GRID_HEIGHT; j++) 
        { sprite1.setPosition(i*CELL_SIZE, j*CELL_SIZE);  window.draw(sprite1); }

    for (int i=0;i<num;i++)
        { sprite2.setPosition(s[i].x*CELL_SIZE, s[i].y*CELL_SIZE);  window.draw(sprite2); }
   
    sprite2.setPosition(f.x*CELL_SIZE, f.y*CELL_SIZE);  window.draw(sprite2);    

    window.display();
    }

    return 0;
}
