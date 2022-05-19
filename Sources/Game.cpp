#include <fstream>
#include <iostream>

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

class Score
{
protected:
    int CurScore;
    int StoredScore[3];

public:
    Score() {}
    ~Score() {}
    void Read()
    {
        ifstream ScoreStorage("ScoreStorage.txt");
        for (int i = 0; i < 3; i++)
        {
            ScoreStorage >> StoredScore[i];
            cout << StoredScore[i];
        }
    }
    void Write()
    {
        ofstream ScoreStorage("ScoreStorage.txt");
        for (int i = 0; i < 3; i++)
        {
            ScoreStorage << StoredScore[i] << " ";
            cout << StoredScore[i];
        }     
    }
    int GetCur()
    {
        return CurScore;
    }
};
class Slug :public Score
{
public:
    void SlugScore()
    {
        CurScore = 25 * (Length - DefaultLength);
        if (CurScore > StoredScore[0])
            StoredScore[0] = CurScore;
    }
    int SlugTop()
    {
        return StoredScore[0];
    }
};
class Worm :public Score
{
public:
    void WormScore()
    {
        CurScore = 50 * (Length - DefaultLength);
        if (CurScore > StoredScore[1])
            StoredScore[1] = CurScore;
    }
    int WormTop()
    {
        return StoredScore[1];
    }
};
class Python :public Score
{
public:
    void PythonScore()
    {
        CurScore = 75 * (Length - DefaultLength);
        if (CurScore > StoredScore[2])
            StoredScore[2] = CurScore;
    }
    int PythonTop()
    {
        return StoredScore[2];
    }
};




void Tick()
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
        Length++; Food.x = rand() % GridWidth; Food.y = rand() % GridHeight;
    }

    //BorderCheck
    if (Snake[0].x > GridWidth - 1) { cout << "A" << endl; State = 3; }  if (Snake[0].x < 0) { cout << "C" << endl; State = 3; }
    if (Snake[0].y > GridHeight - 1) { cout << "B" << endl; State = 3; }  if (Snake[0].y < 0) { cout << "D" << endl; State = 3; }

    //Ouroboros
    for (int i = 1; i < Length; i++)
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y) { cout << "Game Over" << endl; State = 3; }
}