#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <time.h>

#include "Variables.h"

using namespace std; 

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

//class Score
//{
//protected:
//    int CurScore;
//    int StoredScore[3];
//    
//public:
//    Score(){}
//    ~Score() {}
//    void Read()
//    {
//        ifstream Score;
//        Score.open("ScoreStorage.txt");
//        for (int i = 0; i < 4; i++)
//            Score >> StoredScore[i];
//    }
//    void Write()
//    {
//        ofstream Score;
//        Score.open("ScoreStorage.txt");
//        for (int i = 0; i < 4; i++)
//            Score << StoredScore[i];
//    }
//    void CountCur()
//    {
//        CurScore = Length - 3;
//    }
//    int GetCur
//    {
//        return CurScore;
//    }
//};
//class Slug :public Score
//{
//public:
//    void SlugCount()
//    {
//        StoredScore[0] = 25 * CurScore
//    }
//};
//class Worm :public Score
//{
//public:
//    void WormCount()
//    {
//        StoredScore[1] = 50 * CurScore
//    }
//};
//class Python :public Score
//{
//public:
//    void PythonCount()
//    {
//        StoredScore[2] = 75 * CurScore
//    }
//};

void GameSettings()
{
    //Seed
    srand(time(0));


    //FirstSpawnPosition
    for (int i = 0; i < Length; i++)
    {
        Snake[i].x = GridWidth / 3 - i;
        Snake[i].y = GridHeight / 3;
    }
    Food.x = GridWidth / 2;
    Food.y = GridHeight / 2;

}


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
    if (Snake[0].x > GridWidth) { cout << "Game Over" << endl; Pause = true; }  if (Snake[0].x < 0) { cout << "Game Over" << endl; Pause = true; }
    if (Snake[0].y > GridHeight) { cout << "Game Over" << endl; Pause = true; }  if (Snake[0].y < 0) { cout << "Game Over" << endl; Pause = true; }

    //Ouroboros
    for (int i = 1; i < Length; i++)
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y) { cout << "Game Over" << endl; Pause = true; }
}
