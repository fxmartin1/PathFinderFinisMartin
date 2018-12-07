#include "Game.h"
#include <iostream>

void main()
{
	Game g;
	bool moveMade = false;
	int gen = 100;
	for (char i = NULL; i = 'q'; i = NULL)
	{
		g.createPopulation();
		i = NULL;
		cin >> i;
		system("CLS");
		g.gameLoop(i);
		for (int j = 0; j < 100; j++)
		{
			cout << "Generation: " << j << endl;
			g.calFitness();
			g.sortPopulation();
			g.display();
			g.cullPopulation();
			g.addPopulation();
			g.mutate();
			system("CLS");
			
		
		}
		g.calFitness();
		g.sortPopulation();
		g.update();
		cout << "Best path: " << endl;
		g.display();


	}



}