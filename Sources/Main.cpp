#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "Header.h"

using namespace sf;
using namespace std;

//
//Draw
//
void DrawMenu(RenderWindow& GameWindow, Font& F1, float& Delay, int& Choice, int& State, SnakeC& Snake)
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

    GameWindow.draw(SnakeText);
    GameWindow.draw(SlugText);
    GameWindow.draw(WormText);
    GameWindow.draw(PythonText);
    GameWindow.draw(ExitText);

    //MenuChoice
    if (State != 1)
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            Delay = 0.15; Choice = 1; Snake.Direction = 3; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            Delay = 0.10; Choice = 2; Snake.Direction = 0; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            Delay = 0.05; Choice = 3; Snake.Direction = 2; State = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            GameWindow.close();
    }
}

void DrawOSD(RenderWindow& GameWindow, Font& F1, ScoreC* pScore, int& Choice, SnakeC& Snake)
{
    Text CurrentScore;
    CurrentScore.setFont(F1);
    CurrentScore.setCharacterSize(GridWidth + GridHeight);
    CurrentScore.setFillColor(Color(40, 42, 48));
    CurrentScore.setStyle(Text::Bold);
    CurrentScore.setPosition(!Width, Height);
    CurrentScore.setString(to_string(pScore->CurrentScore(Snake)));

    Text TopScore;
    TopScore.setFont(F1);
    TopScore.setCharacterSize(GridWidth + GridHeight);
    TopScore.setFillColor(Color(40, 42, 48));
    TopScore.setStyle(Text::Bold);
    TopScore.setPosition(Width - (GridWidth + GridHeight) * 2, Height);
    TopScore.setString(to_string(pScore->TopScore()));

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

    GameWindow.draw(CurrentScore);
    GameWindow.draw(TopScore);
    GameWindow.draw(GameMode);
    GameWindow.draw(Line);
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

void DrawGame(RenderWindow& GameWindow, Sprite& S1, Sprite& S2, SnakeC& Snake, FoodS& Food)
{
    //DrawSnake
    for (int i = 0; i < Snake.Length; i++)
    {
        if (Snake.S[0].y > GridHeight - 1 && i == 0) { continue; }
        S1.setPosition(Snake.S[i].x * Pixel, Snake.S[i].y * Pixel);
        GameWindow.draw(S1);
    }

    //DrawFood
    S2.setPosition(Food.F.x * Pixel, Food.F.y * Pixel);
    GameWindow.draw(S2);
}

//
//Run
//
void Tick(SnakeC& Snake, FoodS& Food, int& State)
{
    //MovementSlithering
    for (int i = Snake.Length; i > 0; --i)
    {
        Snake.S[i].x = Snake.S[i - 1].x; Snake.S[i].y = Snake.S[i - 1].y;
    }

    //MovementChangeDirection
    if (Snake.Direction == 0) Snake.S[0].x -= 1;
    if (Snake.Direction == 1) Snake.S[0].y += 1;
    if (Snake.Direction == 2) Snake.S[0].x += 1;
    if (Snake.Direction == 3) Snake.S[0].y -= 1;

    bool Roll = false;

    //SnakeGrow
    if ((Snake.S[0].x == Food.F.x) && (Snake.S[0].y == Food.F.y))
    {
        Snake.Length++;
        Roll = true;

        //FoodSpawn
        while (Roll == true)
        {
            Food++;
            for (int i = 0; i < Snake.Length; i++)
            {
                if ((Snake.S[i].x == Food.F.x) && (Snake.S[i].y == Food.F.y)) { break; }
                if (i == Snake.Length - 1) { Roll = false; }
            }
        }
    }

    //BorderCheck
    if (Snake.S[0].x > GridWidth - 1) { State = 2; }
    if (Snake.S[0].y > GridHeight - 1) { State = 2; }
    if (Snake.S[0].x < 0) { State = 2; }
    if (Snake.S[0].y < 0) { State = 2; }

    //Ouroboros
    for (int i = 1; i < Snake.Length; i++)
        if (Snake.S[0].x == Snake.S[i].x && Snake.S[0].y == Snake.S[i].y) { State = 2; }
}

void RunGame(RenderWindow& window, Clock& GameClock, SnakeC& Snake, FoodS& Food, int& State, float& Timer, float& Delay)
{
    //TimeCheck
    float Time = GameClock.getElapsedTime().asSeconds();
    GameClock.restart();
    Timer += Time;

    //MovementCheck
    if (Snake.Direction != 2)
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
            Snake.Direction = 0;
    if (Snake.Direction != 0)
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
            Snake.Direction = 2;
    if (Snake.Direction != 1)
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
            Snake.Direction = 3;
    if (Snake.Direction != 3)
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            Snake.Direction = 1;

    //DelayCheck
    if (Timer > Delay) { Timer = 0; Tick(Snake, Food, State); }

}

void Spawn(SnakeC& Snake, FoodS& Food)
{
    //SnakeStartingLenght
    Snake.Length = DefaultLength;

    //SnakeSpawnPosition
    for (int i = 0; i < Snake.Length; i++)
    {
        Snake.S[i].x = GridWidth / 2;
        Snake.S[i].y = GridHeight / 2 - 1;
    }

    //FoodSpawnPosition
    Food.F.x = GridWidth / 4;
    Food.F.y = GridHeight / 4;
}

int main()
{
    //Seed
    srand(time(nullptr));

    //Window
    RenderWindow GameWindow(VideoMode(Width, Height + Pixel * 3), "Snake");

    //LoadTextures
    Texture T1, T2;
    Font F1;
    T1.loadFromFile("Resources/Snake.png");
    T2.loadFromFile("Resources/Food.png");
    F1.loadFromFile("Resources/Font.otf");
    Sprite S1(T1);
    Sprite S2(T2);

    //Variables
    Clock GameClock;
    float Timer = 0, Delay;
    int State = 0;
    int Choice = 0;
    bool GameOver = false;
    bool Pause = false;

    //Class/Derived/Struct
    ScoreC* pScore = nullptr;
    SnakeC Snake;
    FoodS Food;

    while (GameWindow.isOpen())
    {
        Event ev;
        while (GameWindow.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                GameWindow.close();
        }
        GameWindow.clear(Color(95, 139, 66, 0));
        switch (State)
        {
        case 0://MenuState
            DrawMenu(GameWindow, F1, Delay, Choice, State, Snake);
            if (State == 1) {
                Spawn(Snake, Food);
        switch (Choice) { case 1: pScore = new SlugDC(); break; case 2: pScore = new WormDC(); break; case 3: pScore = new PythonDC(); break; }
                                pScore->Read();
            }
            break;
        case 1://GameState
            RunGame(GameWindow, GameClock, Snake, Food, State, Timer, Delay);
            DrawGame(GameWindow, S1, S2, Snake, Food);
            DrawOSD(GameWindow, F1, pScore, Choice, Snake);
            if (State == 2) { pScore->Write(); }
            break;

        case 2://GameOverState
            DrawGame(GameWindow, S1, S2, Snake, Food);
            DrawGameOver(GameWindow, F1);
            DrawOSD(GameWindow, F1, pScore, Choice, Snake);
            if (Keyboard::isKeyPressed(Keyboard::Enter)) { State = 0; delete pScore; }
            break;
        }
        GameWindow.display();
    }
    return 0;
}