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

class SnakeC
{
public:
    int Length;
    int Direction;
    CordC S[GridWidth * GridHeight];
};

struct FoodS
{
public:
    CordC F;
    void operator ++(int);
};

class ScoreC
{
protected:
    int Temp;
    int Error;
    int StoredScore[3];
    template <class CP>
    CP Go(CP a, CP b, CP c, CP d, CP e) { return (a - b) * (c / (d * e)); }
public:
    ScoreC();
    virtual ~ScoreC() {}
    void Read();
    void Write();
    virtual int CurrentScore(SnakeC Snake) = 0;
    virtual int TopScore() = 0;
};
class SlugDC :public ScoreC
{
public:
    int CurrentScore(SnakeC Snake);
    int TopScore();
};
class WormDC :public ScoreC
{
public:
    int CurrentScore(SnakeC Snake);
    int TopScore();
};
class PythonDC :public ScoreC
{
public:
    int CurrentScore(SnakeC Snake);
    int TopScore();
};