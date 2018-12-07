#ifndef GANE_H
#define GAME_H

#include <vector>
using namespace std;

struct Member
{
	int path[6*6];
	int fitness=0;

};
// population 500 is the maxium set
struct Population
{
	std::vector<Member>Members = std::vector<Member>(500);
};

class Game
{
public:
	Game();
	void createPopulation();
	void calFitness();
	void sortPopulation();
	void cullPopulation();
	void addPopulation();
	Member makeChild(vector<Member>parents);
	void mutate();
	bool checkPlayer(int aiH,int aiL);
	void display();
	void displayGrid();
	void gameLoop(char input);
	void update();
	
private:
	static const int GRID_H = 6;
	static const int GRID_L = 6;
	 int aI_locationh = GRID_H-1;
	 int AI_LOACTIONL = GRID_L-1;
	 int playerLocationY = 0;
	 int playerLocationX = 0;
	int mutationRate = 10;
	Population p;
	int grid[GRID_H][GRID_L];


};
#endif