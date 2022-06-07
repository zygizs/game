#pragma once

int const GridWidth = 21;
int const GridHeight = 15;
int const Pixel = 16;
int const Width = Pixel * GridWidth;
int const Height = Pixel * GridHeight;
int const DefaultLength = 3;

class CordC
{
public:
    int x, y;
};
class SnakeC :public CordC
{
public:
    int Length;
    int Direction;
};

class Snake
{
public:
    int Length;
    int Direction;
    CordC mas[4];
};

struct FoodS :public CordC
{    
};

class Score
{
protected:
    int CurScore;
    int StoredScore[3];

public:
    Score() {}
    ~Score() {}
    void Read();
    void Write();
    int GetCur();
};
class Slug :public Score
{
public:
    void SlugScore(SnakeC Snake[]);
    int SlugTop();
};
class Worm :public Score
{
public:
    void WormScore(SnakeC Snake[]);
    int WormTop();
};
class Python :public Score
{
public:
    void PythonScore(SnakeC Snake[]);
    int PythonTop();
};