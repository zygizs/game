#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "Header.h"

using namespace sf;
using namespace std;

//
//Draw
//
void DrawMenu(RenderWindow& window, Font& F1, float& Delay, int& Choice, int& Direction, int& State)
{

    Text Snake;
    Snake.setFont(F1);
    Snake.setCharacterSize((GridWidth + GridHeight) * 1.55);
    Snake.setFillColor(Color(40, 42, 48));
    Snake.setStyle(Text::Bold);
    Snake.setString("Snake");
    Snake.setPosition(Width / 3, Height / 8);

    Text Slug;
    Slug.setFont(F1);
    Slug.setCharacterSize((GridWidth + GridHeight) * 0.65);
    Slug.setFillColor(Color(40, 42, 48));
    Slug.setStyle(Text::Bold);
    Slug.setString("  W\nSlug");
    Slug.setPosition(Width / 2.25, Height / 1.65);

    Text Worm;
    Worm.setFont(F1);
    Worm.setCharacterSize((GridWidth + GridHeight) * 0.65);
    Worm.setFillColor(Color(40, 42, 48));
    Worm.setStyle(Text::Bold);
    Worm.setString("   A\nWorm");
    Worm.setPosition(Width / 4.5, Height / 1.15);

    Text Python;
    Python.setFont(F1);
    Python.setCharacterSize((GridWidth + GridHeight) * 0.65);
    Python.setFillColor(Color(40, 42, 48));
    Python.setStyle(Text::Bold);
    Python.setString("   D\nPython");
    Python.setPosition(Width / 1.65, Height / 1.15);

    Text Exit;
    Exit.setFont(F1);
    Exit.setCharacterSize((GridWidth + GridHeight) * 0.65);
    Exit.setFillColor(Color(40, 42, 48));
    Exit.setStyle(Text::Bold);
    Exit.setString("  S\nExit");
    Exit.setPosition(Width / 2.25, Height / 1.15);

    window.draw(Snake);
    window.draw(Slug);
    window.draw(Worm);
    window.draw(Python);
    window.draw(Exit);

    if (State != 1)
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            Delay = 0.15; Choice = 1; Direction = 3; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            Delay = 0.10; Choice = 2; Direction = 0; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            Delay = 0.05; Choice = 3; Direction = 2; State = 1;
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

void DrawGame(RenderWindow& window, Sprite& S1, Sprite& S2, Sprite& S3, SnakeC Snake[], FoodS& Food, int& Length)
{

    //DrawSnake
    for (int i = 0; i < Length; i++)
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
void Tick(SnakeC Snake[], FoodS& Food, int& Direction, int& Length, int& State)
{
    //MovementSlithering
    for (int i = Length; i > 0; --i)
    {
        Snake[i].x = Snake[i - 1].x; Snake[i].y = Snake[i - 1].y;
    }
    cout << Direction << endl;

    //MovementChangeDirection
    if (Direction == 0) Snake[0].x -= 1;
    if (Direction == 1) Snake[0].y += 1;
    if (Direction == 2) Snake[0].x += 1;
    if (Direction == 3) Snake[0].y -= 1;

    //SnakeGrow/FoodSpawn
    if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y))
    {
        Length++;
        Food.x = rand() % GridWidth;
        Food.y = rand() % GridHeight;
    }

    ////SnakeGrow
    //if ((Snake[0].x == Food.x) && (Snake[0].y == Food.y))
    //{
    //    Length++;
    //    Roll = true;
    //}

    ////FoodSpawnFix?!?
    //while (Roll == true)
    //{
    //    TempX = rand() % GridWidth;
    //    TempY = rand() % GridHeight;
    //    for (int i = 1; i < Length; i++)
    //    {

    //        if ((Snake[i].x == Food.x) && (Snake[i].y == Food.y))
    //        {
    //            if (Length - 1 == i) { Food.x = TempX; Food.y = TempY; Roll = false; }
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
    for (int i = 1; i < Length; i++)
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y) { cout << "Game Over" << endl; State = 3; }
}

void RunGame(RenderWindow& window, Clock& GameClock, SnakeC Snake[], FoodS& Food, int& Length, int& State, float& Timer, float& Delay, int& Direction)
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
    if (Timer > Delay) { Timer = 0; Tick(Snake, Food, Direction, Length, State); }

}

void Spawn(SnakeC Snake[], FoodS& Food, int& Length)
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
    RenderWindow window(VideoMode(Width, Height + Pixel * 3), "Snake");

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
    bool GameOver = false;
    bool Pause = false;
    bool Roll = false;
    int TempX;
    int TempY;
    int Choice = 0;
    int State = 0;
    int Length = DefaultLength;
    int Direction = 0;

    Slug Sl;
    Worm Wo;
    Python Py;

    SnakeC Snake[GridWidth * GridHeight];
    FoodS Food;

    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        window.clear(Color(95, 139, 66, 0));
        if (State == 0)//MenuState
        {
            DrawMenu(window, F1, Delay, Choice, Direction, State);
            if (State == 1) 
            { 
                Spawn(Snake, Food, Length); 
                if (Choice == 1) { Sl.Read(); }
                else if (Choice == 2) { Wo.Read(); }
                else if (Choice == 3) { Py.Read(); }
            }
                
        }
        else if (State == 1)//GameState
        {
            RunGame(window, GameClock, Snake, Food, Length, State, Timer, Delay, Direction);
            DrawGame(window, S1, S2, S3, Snake, Food, Length);
            DrawOSD(window, F1, Sl, Wo, Py, Choice);
            if (Choice == 1) { Sl.SlugScore(Length);}
            else if (Choice == 2) { Wo.WormScore(Length);}
            else if (Choice == 3) { Py.PythonScore(Length);}
            //PauseCheck();
        }
        else if (State == 2)//PauseState
        {
            DrawGame(window, S1, S2, S3, Snake, Food, Length);
            //PauseCheck();
        }
        else if (State == 3)//GameOverState
        { 
            DrawGame(window, S1, S2, S3, Snake, Food, Length);
            DrawGameOver(window, F1);
            DrawOSD(window, F1, Sl, Wo, Py, Choice);
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
//Add Pause +-
//Add GameOver +
//Add Sound -
//Rewrite +- :)
 
//Add Original sprites +
//Add Game modes +
//Add Custom game mode "Food Placer" based on the old project -
//Add Highscore system +
//Add OSD for current game mode, highscore +
