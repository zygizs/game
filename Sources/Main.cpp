#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
using namespace sf;
using namespace std;


//Grid
const int A = 8;
const int B = 8;
int grid[A][B]{ 0 };
int sgrid[A][B]{ 0 };
bool checkA[A];
bool checkB[B];


int main()
{
	//Window
	RenderWindow app(VideoMode(480, 852), "Puzzle");

	//Textures/Sprite
	int p = 32; // Text p x p
	int offx = 112;
	int offy = 298;
	Texture t;
	t.loadFromFile("Resources/placehold.jpg");
	Sprite s(t);

	for (int i = 0; i < A; i++ )
		for (int j = 0; j < B; j++)
		{
			sgrid[i][j] = 0;
		}

	while (app.isOpen())
	{
		//Mouse
		Vector2i pos = Mouse::getPosition(app);
		int x = (pos.x - offx) / p;
		int y = (pos.y - offy) / p;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close(); 

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left) { sgrid[x][y] = 10; grid[y][x] = 1;}

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::D) 
				{
					cout << std::endl;
					for (int i = 0; i < A; i++)
					{
						for (int j = 0; j < B; j++)
						{
							cout << grid[i][j] << ' ';
						}
						cout << std::endl;
					}
				}	
		}

		//Check
		for (int i = 0; i < A; i++)
			for (int j = 0; j < B; j++)
			{
				if (grid[i][j] == 0) { checkA[i] = false; continue;}
				else { checkA[i] = true; }
			}
		for (int j = 0; j < B; j++)
			for (int i = 0; i < A; i++)
			{
				if (grid[i][j] == 0) { checkB[j] = false; continue; }
				else { checkB[j] = true; }
			}
		//Delete
		for (int i = 0; i < A; i++)
			if (checkA[i] == true)
				for (int j = 0; j < B; j++)
				{
					sgrid[j][i] = 0;
					grid[i][j] = 0;
				}
		for (int j = 0; j < B; j++)
			if (checkB[j] == true)
				for (int i = 0; i < A; i++)
				{
					sgrid[j][i] = 0;
					grid[i][j] = 0;
				}
			
		app.clear(Color::White);
		for (int i = 0; i < A; i++)
			for (int j = 0; j < B; j++)
			{
				
				s.setTextureRect(IntRect(sgrid[i][j] * p, 0, p, p));
				s.setPosition(offx + i * p, offy + j * p);
				app.draw(s);
			}
		app.display();
	}
	return (0);
}