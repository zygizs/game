#include <fstream>
#include <iostream>

#include "Header.h"

using namespace std; 

//FoodRandomSpawn
void FoodS::operator ++(int)
{
    F.x = rand() % GridWidth;
    F.y = rand() % GridHeight;
};

//ScoreC
ScoreC::ScoreC(): StoredScore{}
{
    Temp = 0;
    Error = 0;
}

//ReadScore
void ScoreC::Read() 
{
    ifstream ScoreStorage("ScoreStorage.txt");
    for (int i = 0; i < 3; i++)
    {
        ScoreStorage >> StoredScore[i];
    }
}

//WriteScore
void ScoreC::Write() 
{
    ofstream ScoreStorage("ScoreStorage.txt");
    for (int i = 0; i < 3; i++)
    {
        ScoreStorage << StoredScore[i] << " ";
    }
}

//SlugDerived
int SlugDC::CurrentScore(SnakeC Snake)
{
    Temp = Go(Snake.Length, DefaultLength, 9999, GridWidth, GridHeight);
    Temp *= 0.75;
    if (Temp > StoredScore[0])
        StoredScore[0] = Temp;
  
    return Temp;
}
int SlugDC::TopScore()
{
    return StoredScore[0];
}

//WormDerived
int WormDC::CurrentScore(SnakeC Snake)
{
    Temp = Go(Snake.Length, DefaultLength, 9999, GridWidth, GridHeight);
    Temp *= 0.95;
    if (Temp > StoredScore[1])
        StoredScore[1] = Temp;
    return Temp;
}
int WormDC::TopScore()
{
    return StoredScore[1];
}

//PythonDerived
int PythonDC::CurrentScore(SnakeC Snake)
{
    Temp = Go(Snake.Length, DefaultLength, 9999, GridWidth, GridHeight);
    Temp *= 1.25;
    if (Temp > StoredScore[2])
        StoredScore[2] = Temp;
    return Temp;
}
int PythonDC::TopScore()
{
    return StoredScore[2];
}
