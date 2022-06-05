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
int Score::GetCur()
{
    return CurScore;
}

void Slug::SlugScore(int& Length)
{
    CurScore = 25 * (Length - DefaultLength);
    if (CurScore > StoredScore[0])
        StoredScore[0] = CurScore;
}
int Slug::SlugTop()
{
    return StoredScore[0];
}

void Worm::WormScore(int& Length)
{
    CurScore = 50 * (Length - DefaultLength);
    if (CurScore > StoredScore[1])
        StoredScore[1] = CurScore;
}
int Worm::WormTop()
{
    return StoredScore[1];
}

void Python::PythonScore(int& Length)
{
    CurScore = 75 * (Length - DefaultLength);
    if (CurScore > StoredScore[2])
        StoredScore[2] = CurScore;
}
int Python::PythonTop()
{
    return StoredScore[2];
}
