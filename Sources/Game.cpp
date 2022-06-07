#include <fstream>
#include <iostream>

#include "Header.h"

using namespace std; 

void Score::Read()
{
    ifstream ScoreStorage("ScoreStorage.txt");
    for (int i = 0; i < 3; i++)
    {
        ScoreStorage >> StoredScore[i];
        cout << StoredScore[i];
    }
}
void Score::Write()
{
    ofstream ScoreStorage("ScoreStorage.txt");
    for (int i = 0; i < 3; i++)
    {
        ScoreStorage << StoredScore[i] << " ";
        cout << StoredScore[i];
    }
}

int Slug::CurrentScore(SnakeC Snake[])
{
    CS = 25 * (Snake->Length - DefaultLength);
    if (CS > StoredScore[0])
        StoredScore[0] = CS;
    return CS;
}
int Slug::TopScore()
{
    return StoredScore[0];
}

int Worm::CurrentScore(SnakeC Snake[])
{
    CS = 50 * (Snake->Length - DefaultLength);
    if (CS > StoredScore[1])
        StoredScore[1] = CS;
    return CS;
}
int Worm::TopScore()
{
    return StoredScore[1];
}

int Python::CurrentScore(SnakeC Snake[])
{
    CS = 75 * (Snake->Length - DefaultLength);
    if (CS > StoredScore[2])
        StoredScore[2] = CS;
    return CS;
}
int Python::TopScore()
{
    return StoredScore[2];
}
