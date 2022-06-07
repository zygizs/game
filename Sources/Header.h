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

//class SnakeC :public CordC
//{
//public:
//    int Length;
//    int Direction;
//};

class SnakeC
{
public:
    int Length;
    int Direction;
    CordC Snake[GridWidth * GridHeight];
};

struct FoodS :public CordC{};

class Score
{
protected:
    int CS;
    int StoredScore[3]; 

public:
    Score() {}
    ~Score() {}
    void Read();
    void Write();
    /*virtual int CurrentScore() = 0;
    virtual int TopScore() = 0;*/
};
class Slug :public Score
{
public:
    int CurrentScore(SnakeC Snake[]);
    int TopScore();
};
class Worm :public Score
{
public:
    int CurrentScore(SnakeC Snake[]);
    int TopScore();
};
class Python :public Score
{
public:
    int CurrentScore(SnakeC Snake[]);
    int TopScore();
};