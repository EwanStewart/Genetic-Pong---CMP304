#pragma once
#include "Generation.h"

class GeneticPong
{
public:
	void create_new_generation();	//creates generation zero
	bool run_generation();			//runs generation until algorithm meets end condition

	//getters and setters
	vector<Ball> get_balls();
	vector<Paddle> get_paddles();
	vector<Generation> get_generations();
	Generation get_current_generation();
	int get_current_generation_value();

private:
	vector<Generation> gens;	//holds every generations data
	int current_generation = -1;
	bool over = false;
	bool gameOver = false;
};

