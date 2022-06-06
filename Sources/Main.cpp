#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "Header.h"

using namespace sf;
using namespace std;

//
//Draw
//
void DrawMenu(RenderWindow& window, Font& F1, float& Delay, int& Choice, int& State, SnakeC Snake[])
{

    Text SnakeText;
    SnakeText.setFont(F1);
    SnakeText.setCharacterSize((GridWidth + GridHeight) * 1.55);
    SnakeText.setFillColor(Color(40, 42, 48));
    SnakeText.setStyle(Text::Bold);
    SnakeText.setString("Snake");
    SnakeText.setPosition(Width / 3, Height / 8);

    Text SlugText;
    SlugText.setFont(F1);
    SlugText.setCharacterSize((GridWidth + GridHeight) * 0.65);
    SlugText.setFillColor(Color(40, 42, 48));
    SlugText.setStyle(Text::Bold);
    SlugText.setString("  W\nSlug");
    SlugText.setPosition(Width / 2.25, Height / 1.65);

    Text WormText;
    WormText.setFont(F1);
    WormText.setCharacterSize((GridWidth + GridHeight) * 0.65);
    WormText.setFillColor(Color(40, 42, 48));
    WormText.setStyle(Text::Bold);
    WormText.setString("   A\nWorm");
    WormText.setPosition(Width / 4.5, Height / 1.15);

    Text PythonText;
    PythonText.setFont(F1);
    PythonText.setCharacterSize((GridWidth + GridHeight) * 0.65);
    PythonText.setFillColor(Color(40, 42, 48));
    PythonText.setStyle(Text::Bold);
    PythonText.setString("   D\nPython");
    PythonText.setPosition(Width / 1.65, Height / 1.15);

    Text ExitText;
    ExitText.setFont(F1);
    ExitText.setCharacterSize((GridWidth + GridHeight) * 0.65);
    ExitText.setFillColor(Color(40, 42, 48));
    ExitText.setStyle(Text::Bold);
    ExitText.setString("  S\nExit");
    ExitText.setPosition(Width / 2.25, Height / 1.15);

    window.draw(SnakeText);
    window.draw(SlugText);
    window.draw(WormText);
    window.draw(PythonText);
    window.draw(ExitText);

    if (State != 1)
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            Delay = 0.15; Choice = 1; Snake->Direction = 3; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            Delay = 0.10; Choice = 2; Snake->Direction = 0; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            Delay = 0.05; Choice = 3; Snake->Direction = 2; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            window.close();
    }
}

void DrawOSD(RenderWindow& window, Font& F1, Slug& Sl, Worm& Wo, Python& Py, int& Choice)
{

    Text CurrentScore;
    CurrentScore.setFont(F1);
    CurrentScore.setCharacterSize(GridWidth + GridHeight);
    CurrentScore.setFillColor(Color(40, 42, 48));
    CurrentScore.setStyle(Text::Bold);
    CurrentScore.setPosition(!Width, Height);
    if (Choice == 1) { CurrentScore.setString(to_string(Sl.GetCur())); }
    else if (Choice == 2) { CurrentScore.setString(to_string(Wo.GetCur())); }
    else if (Choice == 3) { CurrentScore.setString(to_string(Py.GetCur())); }

    Text TopScore;
    TopScore.setFont(F1);
    TopScore.setCharacterSize(GridWidth + GridHeight);
    TopScore.setFillColor(Color(40, 42, 48));
    TopScore.setStyle(Text::Bold);
    TopScore.setPosition(Width - (GridWidth + GridHeight) * 2, Height);
    if (Choice == 1) { TopScore.setString(to_string(Sl.SlugTop())); }
    else if (Choice == 2) { TopScore.setString(to_string(Wo.WormTop())); }
    else if (Choice == 3) { TopScore.setString(to_string(Py.PythonTop())); }

    Text GameMode;
    GameMode.setFont(F1);
    GameMode.setCharacterSize(GridWidth + GridHeight);
    GameMode.setFillColor(Color(40, 42, 48));
    GameMode.setStyle(Text::Bold);
    GameMode.setPosition(Width / 2.5, Height);
    if (Choice == 1) { GameMode.setString("Slug"); }
    else if (Choice == 2) { GameMode.setString("Worm"); }
    else if (Choice == 3) { GameMode.setString("Python"); }


    sf::RectangleShape Line(sf::Vector2f(300, 300));

    Line.setSize(sf::Vector2f(Width, 4));
    Line.setPosition(sf::Vector2f(0, Height));
    Line.setFillColor(Color(40, 42, 48));

    window.draw(CurrentScore);
    window.draw(TopScore);
    window.draw(GameMode);
    window.draw(Line);
}

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

void DrawGame(RenderWindow& window, Sprite& S1, Sprite& S2, Sprite& S3, SnakeC Snake[], FoodS& Food)
{

    //DrawSnake
    for (int i = 0; i < Snake->Length; i++)
    {
        if (Snake[0].y > GridHeight - 1 && i == 0) { continue; }
        S2.setPosition(Snake[i].x * Pixel, Snake[i].y * Pixel);
        window.draw(S2);
    }

    //DrawFood
    S3.setPosition(Food.x * Pixel, Food.y * Pixel);
    window.draw(S3);
}

//
//Run
//
void Tick(SnakeC Snake[], FoodS& Food, int& State)
{
    //MovementSlithering
    for (int i = Snake->Length; i > 0; --i)
    {
        Snake[i].x = Snake[i - 1].x; Snake[i].y = Snake[i - 1].y;
    }
    cout << Snake->Direction << endl;

    //MovementChangeDirection
    if (Snake->Direction == 0) Snake[0].x -= 1;
    if (Snake->Direction == 1) Snake[0].y += 1;
    if (Snake->Direction == 2) Snake[0].x += 1;
    if (Snake->Direction == 3) Snake[0].y -= 1;

    //SnakeGrow/FoodSpawn
    if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y))
    {
        Snake->Length++;
        Food.x = rand() % GridWidth;
        Food.y = rand() % GridHeight;
    }

    //bool Roll = false;
    //int TempX = 0;
    //int TempY = 0;

    ////SnakeGrow
    //if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y))
    //{
    //    Snake ->Length++;
    //    Roll = true;
    //}

    ////FoodSpawnFix?!?
    //while (Roll == true)
    //{
    //    TempX = rand() % GridWidth;
    //    TempY = rand() % GridHeight;
    //    for (int i = 1; i < Snake->Length; i++)
    //    {
    //        if ((Snake[i].x == Food.x) && (Snake[i].y == Food.y))
    //        {
    //            if (Snake->Length - 1 == i) { Food.x = TempX; Food.y = TempY; Roll = false; continue; }
    //            break;
    //        } 
    //    }
    //}

    //BorderCheck
    if (Snake[0].x > GridWidth - 1) { cout << "A" << endl; State = 3; }
    if (Snake[0].y > GridHeight - 1) { cout << "B" << endl; State = 3; }
    if (Snake[0].x < 0) { cout << "C" << endl; State = 3; }
    if (Snake[0].y < 0) { cout << "D" << endl; State = 3; }

    //Ouroboros
    for (int i = 1; i < Snake->Length; i++)
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y) { cout << "Game Over" << endl; State = 3; }
}

void RunGame(RenderWindow& window, Clock& GameClock, SnakeC Snake[], FoodS& Food, int& State, float& Timer, float& Delay)
{
    //TimeCheck
    float Time = GameClock.getElapsedTime().asSeconds();
    GameClock.restart();
    Timer += Time;

    //MovementCheck
    if (Snake->Direction != 2)
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
            Snake->Direction = 0;
    if (Snake->Direction != 0)
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
            Snake->Direction = 2;
    if (Snake->Direction != 1)
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
            Snake->Direction = 3;
    if (Snake->Direction != 3)
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            Snake->Direction = 1;

    //DelayCheck
    if (Timer > Delay) { Timer = 0; Tick(Snake, Food, State); }

}

void Spawn(SnakeC Snake[], FoodS& Food)
{
    Snake->Length = DefaultLength;
    for (int i = 0; i < Snake->Length; i++)
    {
        Snake[i].x = 0;
        Snake[i].y = 0;
    }
    for (int i = 0; i < Snake->Length; i++)
    {
        Snake[i].x = GridWidth / 2;
        Snake[i].y = GridHeight / 2 - 1;
    }
    Food.x = GridWidth / 4;
    Food.y = GridHeight / 4;
}

//void PauseCheck()
//{
//    //Pause
//    if (Keyboard::isKeyPressed(Keyboard::P)) { cout << "Pause" << endl; Pause = !Pause; }
//    if (Pause == true) { State = 2; }
//    else { State = 1; }
//}


int main()
{
    
    //Seed
    srand(time(nullptr));

    //Window
    RenderWindow GameWindow(VideoMode(Width, Height + Pixel * 3), "Snake");

    //LoadTextures
    Texture T1, T2, T3;
    Font F1;
    //T1.loadFromFile("Resources/white.png");
    T2.loadFromFile("Resources/Snake.png");
    T3.loadFromFile("Resources/Food.png");
    F1.loadFromFile("Resources/Font.otf");
    Sprite S1(T1);
    Sprite S2(T2);
    Sprite S3(T3);

    //Variables
    Clock GameClock;
    float Timer = 0, Delay;
    int State = 0;
    int Choice = 0;
    bool GameOver = false;
    bool Pause = false;
   
    Slug Sl;
    Worm Wo;
    Python Py;

    SnakeC Snake[GridWidth * GridHeight];
    FoodS Food;

    while (GameWindow.isOpen())
    {

        Event e;
        while (GameWindow.pollEvent(e))
        {
            if (e.type == Event::Closed)
                GameWindow.close();
        }
        GameWindow.clear(Color(95, 139, 66, 0));
        if (State == 0)//MenuState
        {
            DrawMenu(GameWindow, F1, Delay, Choice, State, Snake);
            if (State == 1) 
            { 
                Spawn(Snake, Food); 
                switch (Choice) { case 1: Sl.Read(); break; case 2: Wo.Read(); break; case 3: Py.Read(); break; }
            }
                
        }
        else if (State == 1)//GameState
        {
            RunGame(GameWindow, GameClock, Snake, Food, State, Timer, Delay);
            DrawGame(GameWindow, S1, S2, S3, Snake, Food);
            DrawOSD(GameWindow, F1, Sl, Wo, Py, Choice);
            switch (Choice) { case 1: Sl.SlugScore(Snake); break; case 2: Wo.WormScore(Snake); break; case 3: Py.PythonScore(Snake); break; }
            //PauseCheck();
        }
        else if (State == 2)//PauseState
        {
            DrawGame(GameWindow, S1, S2, S3, Snake, Food);
            //PauseCheck();
        }
        else if (State == 3)//GameOverState
        { 
            DrawGame(GameWindow, S1, S2, S3, Snake, Food);
            DrawGameOver(GameWindow, F1);
            DrawOSD(GameWindow, F1, Sl, Wo, Py, Choice);
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                State = 0;
                switch (Choice) { case 1: Sl.Write(); break; case 2: Wo.Write(); break; case 3: Py.Write(); break; }
            }
        }        
        GameWindow.display();
    }  
    return 0;
}

//Add Menu +
//Add Pause +-
//Add GameOver +
//Add Sound -
//Rewrite +- :)
 
//Add Original sprites +
//Add Game modes +
//Add Custom game mode "Food Placer" based on the old project -
//Add Highscore system +
//Add OSD for current game mode, highscore +
