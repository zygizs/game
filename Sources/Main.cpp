#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "Variables.h"
#include "Game.cpp"

using namespace sf;
using namespace std;


void DrawMenu(RenderWindow& window, Font& F1, float& Delay)
{

    Text Snake;
    Snake.setFont(F1);
    Snake.setCharacterSize(GridWidth + GridHeight);
    Snake.setFillColor(Color::Black);
    Snake.setStyle(Text::Bold);
    Snake.setString("Snake");
    Snake.setPosition(Width / 3, Height / 8);
    window.draw(Snake);

    Text Slug;
    Slug.setFont(F1);
    Slug.setCharacterSize(GridWidth / 2 + GridHeight / 2);
    Slug.setFillColor(Color::Black);
    Slug.setStyle(Text::Bold);
    Slug.setString("  W\nSlug");
    Slug.setPosition(Width / 2.25, Height / 2);
    window.draw(Slug);

    Text Worm;
    Worm.setFont(F1);
    Worm.setCharacterSize(GridWidth / 2 + GridHeight / 2);
    Worm.setFillColor(Color::Black);
    Worm.setStyle(Text::Bold);
    Worm.setString("   A\nWorm");
    Worm.setPosition(Width / 4.5, Height / 1.5);
    window.draw(Worm);

    Text Python;
    Python.setFont(F1);
    Python.setCharacterSize(GridWidth / 2 + GridHeight / 2);
    Python.setFillColor(Color::Black);
    Python.setStyle(Text::Bold);
    Python.setString("   D\nPython");
    Python.setPosition(Width / 1.65, Height / 1.5);
    window.draw(Python);

    Text Exit;
    Exit.setFont(F1);
    Exit.setCharacterSize(GridWidth / 2 + GridHeight / 2);
    Exit.setFillColor(Color::Black);
    Exit.setStyle(Text::Bold);
    Exit.setString("  S\nExit");
    Exit.setPosition(Width / 2.25, Height / 1.5);
    window.draw(Exit);
    if(State != 1)
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)){ 
            Delay = 0.15; Choice = 1; Direction = 3; State = 1; }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)){ 
            Delay = 0.10; Choice = 2; Direction = 0; State = 1;}
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)){ 
            Delay = 0.05; Choice = 3; Direction = 2; State = 1;}
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            window.close();
    }
}

//void DrawGameOver(RenderWindow& window, Font& F1)
//{
//    Text GO;
//    GO.setFont(F1);
//    GO.setCharacterSize(GridWidth + GridHeight);
//    GO.setFillColor(Color::Red);
//    GO.setStyle(Text::Bold);
//    GO.setString("Game Over");
//    GO.setPosition(Width / 5.5, Height / 2.5);
//    window.draw(GO);
//}


void DrawGameOver(RenderWindow& window, Font& F1)
{
    Text GameOver;
    GameOver.setFont(F1);
    GameOver.setCharacterSize(GridWidth + GridHeight);
    GameOver.setFillColor(Color::Red);
    GameOver.setStyle(Text::Bold);
    GameOver.setString("Game\nOver");
    GameOver.setPosition(Width / 2.55, Height / 3);
    window.draw(GameOver);
}

void RunGame(RenderWindow& window, Clock& GameClock, float& Timer, float& Delay)
{
    //TimeCheck
    float Time = GameClock.getElapsedTime().asSeconds();
    GameClock.restart();
    Timer += Time;

    //MovementCheck
    if (Direction != 2)
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
            Direction = 0;
    if (Direction != 0)
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
            Direction = 2;
    if (Direction != 1)
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
            Direction = 3;
    if (Direction != 3)
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            Direction = 1;

    //DelayCheck
    if (Timer > Delay) { Timer = 0; Tick(); }
 
}

void DrawGame(RenderWindow& window, Sprite& S1, Sprite& S2, Sprite& S3)
{
    ////DrawGrid
    //for (int i = 0; i < GridWidth; i++)
    //    for (int j = 0; j < GridHeight; j++)
    //    {
    //        S1.setPosition(i * Pixel, j * Pixel);  window.draw(S1);
    //    }

    //DrawSnake
    for (int i = 0; i < Length; i++)
    {
        S2.setPosition(Snake[i].x * Pixel, Snake[i].y * Pixel);  window.draw(S2);
    }

    //DrawFood
    S3.setPosition(Food.x * Pixel, Food.y * Pixel);  window.draw(S3);
}

//void PauseCheck()
//{
//    //Pause
//    if (Keyboard::isKeyPressed(Keyboard::P)) { cout << "Pause" << endl; Pause = !Pause; }
//    if (Pause == true) { State = 2; }
//    else { State = 1; }
//}

void Spawn()
{
    Length = DefaultLength;
    for (int i = 0; i < Length; i++)
    {
        Snake[i].x = 0;
        Snake[i].y = 0;
    }
    for (int i = 0; i < Length; i++)
    {
        Snake[i].x = GridWidth / 2;
        Snake[i].y = GridHeight / 2 - 1;
    }
    Food.x = GridWidth / 4;
    Food.y = GridHeight / 4;
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
    T2.loadFromFile("Resources/Snake.png");
    T3.loadFromFile("Resources/Food.png");
    F1.loadFromFile("Resources/temp.otf");
    Sprite S1(T1);
    Sprite S2(T2);
    Sprite S3(T3);

    //TimerSettings
    Clock GameClock;
    float Timer = 0, Delay;

    Slug Sl;
    Worm Wo;
    Python Py;

    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        //window.clear(Color(117, 142, 41, 0));
        window.clear(Color(95, 139, 66, 0));
        //window.clear(Color(83, 137, 48, 0));
        if (State == 0)//MenuState
        {
            DrawMenu(window, F1, Delay);
            if (State == 1) 
            { 
                Spawn(); 
                if (Choice == 1) { Sl.Read(); }
                else if (Choice == 2) { Wo.Read(); }
                else if (Choice == 3) { Py.Read(); }
            }
                
        }
        else if (State == 1)//GameState
        {
            RunGame(window, GameClock, Timer, Delay);
            DrawGame(window, S1, S2, S3);
            if (Choice == 1) { Sl.SlugScore();}
            else if (Choice == 2) { Wo.WormScore();}
            else if (Choice == 3) { Py.PythonScore();}
            //PauseCheck();
        }
        else if (State == 2)//PauseState
        {
            DrawGame(window, S1, S2, S3);
            //PauseCheck();
        }
        else if (State == 3)//GameOverState
        { 
            DrawGame(window, S1, S2, S3);
            DrawGameOver(window, F1);
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                State = 0;
                if (Choice == 1) { Sl.Write(); }
                else if (Choice == 2) { Wo.Write(); }
                else if (Choice == 3) { Py.Write(); }
            }
        }        
        window.display();

    }

       
    return 0;
}
//Add Menu +
//Add Pause +
//Add GameOver +
//Add Sound
//Rewrite +- :)
 
//Add Original sprites 
//Add Game modes +
//Add Custom game mode "Food Placer" based on the old project 
//Add Highscore system +
//Add OSD for current game mode, highscore
