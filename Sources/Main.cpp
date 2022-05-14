#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace sf;
using namespace std;

int const GridWidth = 30;
int const GridHeight = 20;
int Pixel = 16;
int Width = Pixel * GridWidth;
int Height = Pixel * GridHeight;
int Direction;
int Length = 3;

class Cords
{
public:
    int x, y;
};
class Snake :public Cords
{
}  Snake[GridWidth * GridHeight];

struct Food :public Cords
{
} Food;


void Tick()
{
    //MovementSlithering
    for (int i = Length; i > 0; --i)
    {
        Snake[i].x = Snake[i - 1].x; Snake[i].y = Snake[i - 1].y;
    }
    cout << Direction << endl;

    //MovementChangeDirection
    if (Direction == 0) Snake[0].y += 1;
    if (Direction == 1) Snake[0].x -= 1;
    if (Direction == 2) Snake[0].x += 1;
    if (Direction == 3) Snake[0].y -= 1;

    //SnakeGrow/FoodSpawn
    if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y))
    {
        Length++; Food.x = rand() % GridWidth; Food.y = rand() % GridHeight;
    }

    //BorderCheck //FixHitBox
    if (Snake[0].x > GridWidth) cout << "Game Over" << endl;  if (Snake[0].x < 0) cout << "Game Over" << endl;
    if (Snake[0].y > GridHeight) cout << "Game Over" << endl; if (Snake[0].y < 0) cout << "Game Over" << endl;

    //Ouroboros
    for (int i = 1; i < Length; i++)
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y)  cout << "Game Over" << endl;
}

int main()
{
    //Seed
    srand(time(0));

    //Window
    RenderWindow window(VideoMode(Width, Height), "Snake Game!");

    //LoadTextures
    Texture t1, t2, t3;
    t1.loadFromFile("Resources/white.png");
    t2.loadFromFile("Resources/red.png");
    t3.loadFromFile("Resources/green.png");
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    //TimerSettings
    Clock clock;
    float timer = 0, delay = 0.1;

    //FirstSpawnPosition
    Snake[0].x = GridWidth / 3;
    Snake[0].y = GridHeight / 3;
    Food.x = GridWidth / 2;
    Food.y = GridHeight / 2;

    while (window.isOpen())
    {
        //Time
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        //MovementDirections
        if (Direction != 2)
            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
                Direction = 1;
        if (Direction != 1)
            if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
                Direction = 2;
        if (Direction != 0)
            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
                Direction = 3;
        if (Direction != 3)
            if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
                Direction = 0;

        //CheckDelay
        if (timer > delay) { timer = 0; Tick(); }

        window.clear();

        //DrawGrid
        for (int i = 0; i < GridWidth; i++)
            for (int j = 0; j < GridHeight; j++)
            {
                sprite1.setPosition(i * Pixel, j * Pixel);  window.draw(sprite1);
            }

        //DrawSnake
        for (int i = 0; i < Length; i++)
        {
            sprite2.setPosition(Snake[i].x * Pixel, Snake[i].y * Pixel);  window.draw(sprite2);
        }

        //DrawFood
        sprite3.setPosition(Food.x * Pixel, Food.y * Pixel);  window.draw(sprite3);

        window.display();
    }

    return 0;
}
//Add Menu
//Add Pause
//Add GameOver
//Add Sound
//Rewrite
 
//Add Original sprites
//Add Game modes
//Add Custom game mode "Food Placer" based on the old project 
//Add Highscore system
//Add OSD for current game mode + highscore.
