#include "Game.h"
#include <algorithm>
#include<ctime>
#include<iostream>
Game::Game()
{
	for (int i = 0; i < GRID_H; i++)
	{
		for (int j = 0; j < GRID_L; j++)
		{
			grid[i][j] = 1;
		}
	}

}

void Game::calFitness()
{
	//add extra loop
	int tempAiLocationH = aI_locationh;
	int tempAiLocationL = AI_LOACTIONL;
	bool playerFound = false;
	int move = 0;
	for (int j = 0; j < p.Members.size(); j++) {

		int tempAiLocationH = aI_locationh;
		int tempAiLocationL = AI_LOACTIONL;
		playerFound = false;
		for (int i = 0; i < GRID_H*GRID_L; i++)
		{
			move = p.Members.at(j).path[i];
			if (playerFound == false)
			{
				switch (move)
				{
				case 0:

					break;
				case 1:
					tempAiLocationH = tempAiLocationH - 1;
					if (tempAiLocationH>=6||tempAiLocationL>=6||tempAiLocationH<0|| tempAiLocationL<0)
					{
						
						p.Members.at(j).fitness = p.Members.at(j).fitness + 100;
						break;
					}
					
					
					playerFound = checkPlayer(tempAiLocationH, tempAiLocationL);
					p.Members.at(j).fitness++;
					break;

				case 2:
					tempAiLocationL++;
					if (tempAiLocationH>=6 || tempAiLocationL>=6 || tempAiLocationH<0 || tempAiLocationL<0)
					{

						p.Members.at(j).fitness = p.Members.at(j).fitness + 100;
						break;
					}
					
					
					playerFound = checkPlayer(tempAiLocationH, tempAiLocationL);
					p.Members.at(j).fitness++;
					break;
				case 3:
					tempAiLocationH++;
					if (tempAiLocationH>=6 || tempAiLocationL>=6 || tempAiLocationH<0 || tempAiLocationL<0)
					{

						p.Members.at(j).fitness = p.Members.at(j).fitness + 100;
						break;
					}

					
					playerFound = checkPlayer(tempAiLocationH, tempAiLocationL);
					p.Members.at(j).fitness++;
					break;
				case 4:
					tempAiLocationL = tempAiLocationL - 1;
					if (tempAiLocationH>=6 || tempAiLocationL>=6 || tempAiLocationH<0 || tempAiLocationL<0)
					{

						p.Members.at(j).fitness = p.Members.at(j).fitness + 100;
						break;
					}

					
					playerFound = checkPlayer(tempAiLocationH, tempAiLocationL);
					p.Members.at(j).fitness++;
					break;
				}
			}
			else {
				p.Members.at(j).path[i] = 0;
			}
		}
	}
}

void Game::sortPopulation()
{
	std::sort(p.Members.begin(), p.Members.end(), [](Member const &a, Member &b) {return a.fitness > b.fitness; });
}

bool Game::checkPlayer(int aiH,int aiL)
{
	if (aiH == playerLocationY && aiL == playerLocationX)
	{
		return true;
	}
	return false;
}
void Game::cullPopulation()
{
	for (int j = 0; j <= p.Members.size() / 2; j++)
	{
		p.Members.erase(p.Members.begin());
	}
}
void Game::addPopulation()
{
	for (int j = 0; j < p.Members.size()-1; j++)
	{
		int randomP = rand() % p.Members.size()+0;
		int randomp2 = rand() % p.Members.size()+0;
		if (p.Members.size() <= 500)
		{
			vector<Member>parents{ p.Members.at(randomp2),p.Members.at(randomP) };
			p.Members.push_back(makeChild(parents));
		}
	}
}
Member Game::makeChild(vector<Member>parents)
{
	Member child;
	srand(time(NULL));

	int crossPoint = rand() % (GRID_H*GRID_L) + 0;
	int crossEnd = rand() % (GRID_H*GRID_L) + crossPoint;
	for (int i = 0; i < GRID_H*GRID_L; i++)
	{
		if ((i >= crossPoint) && (i <= crossEnd))
		{
			child.path[i] = parents.at(1).path[i];

		}
		else {
			child.path[i] = parents.at(0).path[i];
		}
	}
	return child;
}

void Game::mutate()
{
	for (int j = 0; j < p.Members.size(); j++)
	{
		if ((rand() % 1000) < mutationRate)
		{
			srand(time(NULL));
			int swap = rand() % (GRID_H*GRID_L)+0;
			int swap2 = rand() % (GRID_H*GRID_L) + 0;
			int s;
			int s2;
			for (int i = 0; i < GRID_H*GRID_L; i++) {
				if (swap == i)
				{
					s = p.Members.at(j).path[i];
					for (int x = 0; x < GRID_H*GRID_L; x++)
					{
						if (swap2 == x)
						{
							s2 = p.Members.at(j).path[x];;
							p.Members.at(j).path[i] = s;
							p.Members.at(j).path[x] = s2;
						}
					}
				
				}
			}


		}
		
	}
}

void Game::display()
{

		
		cout << "fitness: " << p.Members.back().fitness<<endl;
		cout << "path: ";
		for (int i = 0; i < GRID_H*GRID_L; i++)
		{
			cout << p.Members.back().path[i]<<" ";
		}
		cout << endl;
		
}
void Game::displayGrid() {
	int tempGrid[GRID_H][GRID_L];

	int tempAiLocationH = aI_locationh;
	int tempAiLocationL = AI_LOACTIONL;
	int move = 0;

	for (int i = 0; i < GRID_H; i++)
	{
		for (int j = 0; j < GRID_L; j++)
		{
			tempGrid[i][j] = 1;
		}
	}
	tempGrid[0][0] = 2;
	tempGrid[GRID_H][GRID_L] = 3;

	for (int i = 0; i < GRID_H*GRID_L; i++)
	{
		move = p.Members.back().path[i];
		switch (move)
		{
		case 0:

			break;
		case 1:
			if (tempAiLocationH>6 || tempAiLocationL>6 || tempAiLocationH<0 || tempAiLocationL<0)
			{

				break;
			}

			tempGrid[tempAiLocationH][tempAiLocationL] = 0;
			tempAiLocationH--;


			break;

		case 2:
			if (tempAiLocationH>6 || tempAiLocationL>6 || tempAiLocationH<0 || tempAiLocationL<0)
			{

				break;
			}

			tempGrid[tempAiLocationH][tempAiLocationL] = 0;
			tempAiLocationL++;


			break;
		case 3:
			if (tempAiLocationH>6 || tempAiLocationL>6 || tempAiLocationH<0 || tempAiLocationL<0)
			{

				break;
			}

			tempGrid[tempAiLocationH][tempAiLocationL] = 0;
			tempAiLocationH++;


			break;
		case 4:
			if (tempAiLocationH>6 || tempAiLocationL>6 || tempAiLocationH<0 || tempAiLocationL<0)
			{


				break;
			}

			tempGrid[tempAiLocationH][tempAiLocationL] = 0;
			tempAiLocationL--;


			break;
		}
	}

	for (int i = 0; i < GRID_H-1; i++)
	{
		for (int j = 0; j < GRID_L-1; j++)
		{
			cout << tempGrid[i][j] << " ";
		}
		cout << endl;
	}

}

void Game::gameLoop(char input)
{
	switch (input)
	{
	case 'w':
		playerLocationY--;
		if (playerLocationY > 6 || playerLocationX > 6 || playerLocationY < 0 || playerLocationX < 0)
		{
			playerLocationY++;
			cout << "invalid move" << endl;
		}
		break;
	case 'd':
		playerLocationX++;
		if (playerLocationY > 6 || playerLocationX > 6 || playerLocationY < 0 || playerLocationX < 0)
		{
			playerLocationX--;
			cout << "invalid move" << endl;
		}
		break;
	case 'a':
		playerLocationX--;
		if (playerLocationY > 6 || playerLocationX > 6 || playerLocationY < 0 || playerLocationX < 0)
		{
			playerLocationX++;
			cout << "invalid move" << endl;
		}
		break;
	case 's':
		playerLocationY++;
		if (playerLocationY > 6 || playerLocationX > 6 || playerLocationY < 0 || playerLocationX < 0)
		{
			playerLocationY--;
			cout << "invalid move" << endl;
		}
		break;
	}
}

void Game::update()
{	
	int move;
	for (int i = 0; i < GRID_H; i++)
	{
		for (int j = 0; j < GRID_L; j++)
		{
			grid[i][j] = 1;
		}
	}
	grid[playerLocationY][playerLocationX] = 2;
	
	move = p.Members.back().path[0];
	switch (move)
	{
	case 0:

		break;
	case 1:

		aI_locationh--;


		break;

	case 2:


		
		AI_LOACTIONL++;


		break;
	case 3:

		aI_locationh++;


		break;
	case 4:

		AI_LOACTIONL--;


		break;
	}

	grid[aI_locationh][AI_LOACTIONL] = 3;
	for (int i = 0; i < GRID_H; i++)
	{
		
		for (int j = 0; j < GRID_L; j++)
		{

			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

void Game::createPopulation()
{



	srand(time(NULL));
	for (int i = 0; i < p.Members.size(); i++)
	{
		for (int j = 0; j < GRID_H*GRID_L; j++)
		{
			p.Members.at(i).path[j] = rand() % 4 + 1;
		}
	}
	grid[playerLocationY][playerLocationX] = 2;
	grid[aI_locationh][AI_LOACTIONL] = 3;
}