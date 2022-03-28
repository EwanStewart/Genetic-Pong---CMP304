#include "GeneticPong.h"
#include <iostream>
#include <fstream>
void GeneticPong::create_new_generation()	//creates generation zero
{
	current_generation++;
	gens.push_back(*new Generation);		//add a new generation to the generation vector
}

bool GeneticPong::run_generation()
{
		if (over) {											//if current generation is over
			if (!gens[current_generation].getSorted()) {	//if the current generation's paddle data hasn't been sorted
				gens[current_generation].sort_scores();		//sort in order lowest to highest
			}
			gens.push_back(* new Generation(gens[current_generation].paddleScores,
				gens[current_generation].paddleYSens, gens[current_generation].paddleMultiplier));	//push a new generation
			over = false;																			//reset over bool, as new generation
			current_generation++;
		}
		else {										//if generation still running
			over = gens[current_generation].run();	//continue running
			if (!over) {							//if the game is not over
				for (int i = 0; i < gens[current_generation].getPaddleData().size(); i++) {	//check if any paddle score meets end condition
					if (gens[current_generation].getPaddleData()[i].getScore() == 30) {
						std::ofstream outfile;
						outfile.open("data.txt", std::ios_base::app); //record best paddle data
						outfile << current_generation << " " << gens[current_generation].getPaddleData()[i].getBallYSensitivity() << " "
								<< gens[current_generation].getPaddleData()[i].getMultiplier() << " "
								<< gens[current_generation].getBallData()[i].getSpeed() - gens[current_generation].getPaddleData()[i].getSpeed() << endl;	
						return true;	//end
					}
				}
			}
		}

		return false;	//continue

}

vector<Ball> GeneticPong::get_balls()
{
	return gens[current_generation].getBallData();
}

vector<Paddle> GeneticPong::get_paddles()
{
	return gens[current_generation].getPaddleData();
}

Generation GeneticPong::get_current_generation()
{
	return gens[current_generation];
}

int GeneticPong::get_current_generation_value()
{
	return current_generation;
}


vector<Generation> GeneticPong::get_generations()
{
	return gens;
}

