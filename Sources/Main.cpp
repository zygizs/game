#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "Variables.h"
#include "Game.cpp"

using namespace sf;
using namespace std;

void GameOverSplash(Font& F1)
{
    Text GO;
    GO.setFont(F1);
    GO.setCharacterSize(2);
    GO.setColor(Color::Red);
    GO.setStyle(Text::Bold);
    GO.setString("Game Over");
    //GO.setPosition(5, 5);
}

void Menu(float& delay)
{
    do
    {
        cout << "\033[1;32m1. Slug\033[0m\n";
        cout << "\033[1;33m2. Worm\033[0m\n";
        cout << "\033[1;31m3. Python\033[0m\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            //Difficulty = "Slug";
            delay = 0.15;
            Pause = false;
            break;
        case 2:
            //Difficulty = "Worm";
            delay = 0.10;
            Pause = false;
            break;
        case 3:
            //Difficulty = "Python";
            delay = 0.05;
            Pause = false;
            break;
        }
    } while (choice == NULL);
} 

void Draw(RenderWindow& window, Sprite& S1, Sprite& S2, Sprite& S3)
{
    //DrawGrid
    for (int i = 0; i < GridWidth; i++)
        for (int j = 0; j < GridHeight; j++)
        {
            S1.setPosition(i * Pixel, j * Pixel);  window.draw(S1);
        }

    //DrawSnake
    for (int i = 0; i < Length; i++)
    {
        S2.setPosition(Snake[i].x * Pixel, Snake[i].y * Pixel);  window.draw(S2);
    }

    //DrawFood
    S3.setPosition(Food.x * Pixel, Food.y * Pixel);  window.draw(S3);
}

void Check(RenderWindow& window, Clock& clock, float& timer, float& delay)
{
    //TimeCheck
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    //MovementCheck
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

    //DelayCheck
    if (timer > delay) { timer = 0; Tick(); }

    //GameOver
    if (GameOver == true)
        window.close();

    //Pause
    if (Keyboard::isKeyPressed(Keyboard::P)) { cout << "Pause" << endl; Pause = true; }

    //Score
    /*Score Read();
    Score CountCur();
    int temp = Score.GetCur();
    switch (choice)
    {
    case 1:
        Slug CountSlug();
        break;
    case 2:
        Worm CountWorm();
        break;
    case 3:
        Python CountPython();
        break;
    }
    Score Write();*/

        
}

int main()
{
    
    //Seed
    srand(time(0));

    //Window
    RenderWindow window(VideoMode(Width, Height), "Snake");


    //LoadTextures
    Texture T1, T2, T3;
    Font F1;
    T1.loadFromFile("Resources/white.png");
    T2.loadFromFile("Resources/red.png");
    T3.loadFromFile("Resources/green.png");
    F1.loadFromFile("Resources/times new roman.ttf");
    Sprite S1(T1);
    Sprite S2(T2);
    Sprite S3(T3);

    //TimerSettings
    Clock clock;
    float timer = 0, delay;

    //FirstSpawnPosition
    for (int i = 0; i < Length; i++)
    {
        Snake[i].x = GridWidth / 3 - i;
        Snake[i].y = GridHeight / 3;
    }
    Food.x = GridWidth / 2;
    Food.y = GridHeight / 2;

    Menu(delay);
  
    if (Pause == false)
        while (window.isOpen())
        {

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
            }
            if (Pause == false)
               Check(window, clock, timer, delay);

            window.clear();

            Draw(window, S1, S2, S3);   
             
            if (Pause == true)
                GameOverSplash(F1);
                
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
