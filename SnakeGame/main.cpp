#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;

const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score, nTail;

int tailX[100], tailY[100];


enum eDirection {
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

eDirection dir;


void Setup()
{
	gameOver = false;
	dir = STOP; //Stop the snake
	x = width / 2; //Center the snake
	y = height / 2;

	//Place fruit in random position
	fruitX = rand() % width;
	fruitY = rand() % height;

	score = 0; //reset score
	nTail = 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) {
				cout << "#";
				//cout << " ";
			}

			if (j == x && i == y) {
				cout << "O";
			}
			else if (j == fruitX && i == fruitY)
			{
				cout << "F";
			}
			else {

				bool print = false;
				
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";

						print = true;
					}
				}
				
				
				if (!print) {
					cout << " ";
				}


			}

			if (j == width - 1) {
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << endl;
	cout << "Score: " << score << endl;

	//troubleshooting
	cout << "nTail: " << nTail << endl;
	cout << "tailX: " << tailX << endl;
	cout << "tailY: " << tailY << endl;



}

void Input()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() 
{

	int prevX = tailX[0];
	int prevY = tailY[0];

	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	}

	//This will make it so touching the borders will make you lose the game.
	/*	
	if (x < 0 || y < 0 || x > width || y > height) {
		gameOver = true;
	}
	*/

	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}


	if (x == fruitX && y == fruitY) {
		score += 10;
		nTail += 1;

		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}