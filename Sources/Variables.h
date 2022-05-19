#pragma once


int const GridWidth = 32;
int const GridHeight = 24;
int const Pixel = 16;
int const Width = Pixel * GridWidth + Pixel * 2;
int const Height = Pixel * GridHeight + Pixel * 2;
int const DefaultLength = 3;
//string Difficulty = "Error";
bool GameOver = false;
bool Pause = false;
int Choice;
int State = 0;
int Length = DefaultLength;
int Direction;


//FIX FOOD ON SNAKE