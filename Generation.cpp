#include "Generation.h"
#include <iostream>
#include <cmath>
#include<math.h>

double GenerateRandom(double min, double max)	//generate random float between range
{
	if (min > max)
	{
		std::swap(min, max);
	}
	return ((int)(((min + (double)rand() * (max - min) / (double)RAND_MAX)) * 100 + .5) / 100.0);
}

pair<int, float> Generation::generate_paddle_values()	//generate paddle paramaters for generation zero
{
	pair <int, float> value(GenerateRandom(0, 500), GenerateRandom(0, 5));
	return value;
}

pair<int, float> Generation::mutate_paddle_values(vector<int> pastScore, vector<int> pastSens, vector<float> pastMulti)
{
	if (!otherMultiplierValues.empty()) {
		int valueToUse = GenerateRandom(1, 10);

		if (valueToUse < 7) {

			if (GenerateRandom(0, 1)) {
				pair <int, float> value(pastSens[population_size - 1], otherMultiplierValues[(GenerateRandom, otherMultiplierValues.size() - 1)]);
				if (GenerateRandom(0, 1)) {
					value.first = GenerateRandom(0, 500);
				}
				else {
					value.second = GenerateRandom(0, 5);
				}
				cout << "mutating" << endl;
				cout << value.first << " " << value.second << endl;
				return value;
			}
			else {
				pair <int, float> value(otherSensitivityValues[(GenerateRandom, otherSensitivityValues.size() - 1)], pastMulti[population_size - 1]);
				if (GenerateRandom(0, 1)) {
					value.first = GenerateRandom(0, 500);
				}
				else {
					value.second = GenerateRandom(0, 5);
				}
				cout << "mutating" << endl;
				cout << value.first << " " << value.second << endl;
				return value;
			}

		} else {
			pair <int, float> value(otherSensitivityValues[(GenerateRandom, otherSensitivityValues.size() -1)], otherMultiplierValues[(GenerateRandom, otherMultiplierValues.size() -1)]);
			if (GenerateRandom(0, 1)) {
				value.first = GenerateRandom(0, 500);
			}
			else {
				value.second = GenerateRandom(0, 5);
			}
			cout << "mutating" << endl;
			cout << value.first << " " << value.second << endl;
			return value;
		}
	}
	else {
		pair <int, float> value(pastSens[population_size - 1], pastMulti[population_size - 1]);
		if (GenerateRandom(0, 1)) {
			value.first = GenerateRandom(0, 500);
		}
		else {
			value.second = GenerateRandom(0, 5);
		}
		cout << "mutating" << endl;
		cout << value.first << " " << value.second << endl;
		return value;
	}
	
	

}

pair<int, float> Generation::generate_paddle_values(vector<int> pastScore, vector<int> pastSens, vector<float> pastMulti)	//generate paddle paramaters using past generation data
{
	if (pastScore[population_size - 1]) {	//check if last generation had a least one collision
		return crossover_paddle_values(pastScore, pastSens, pastMulti);
	}
	else {									//no collisions in last generation
		return generate_paddle_values();	//generate new independant values
	}
}

pair<int, float> Generation::crossover_paddle_values(vector<int> pastScore, vector<int> pastSens, vector<float> pastMulti)
{
	int sensRange = 0;
	float multiRange = 0.f;

	if (GenerateRandom(0, 100) < mutation_rate) {						//30% chance that the paddles ignore cross-over and mutate
		return mutate_paddle_values(pastScore, pastSens, pastMulti);	//return the mutated paddle values
	}
	else {
		int increment, a = 0;
		float b, fIncrement = 0.f;

		if (!otherMultiplierValues.empty()) {
			int valueToUse = GenerateRandom(1, 10);
			int valueToUse2 = GenerateRandom(0, otherMultiplierValues.size()-1);

			if (valueToUse < 7) {
				if (GenerateRandom(0, 1)) {
					cout << "parent and random" << endl;
					sensRange = pastSens[population_size - 1];
					multiRange = otherMultiplierValues[valueToUse2];
				}
				else {
					cout << "parent and random" << endl;
					sensRange = otherSensitivityValues[valueToUse2];
					multiRange = pastMulti[population_size - 1];
				}
			}
			else {
				if (GenerateRandom(0, 1)) {
					cout << "both random parents" << endl;
					sensRange = otherSensitivityValues[GenerateRandom(0, otherSensitivityValues.size()-1)];
					multiRange = otherMultiplierValues[GenerateRandom(0, otherMultiplierValues.size()-1)];
				}
			}

		} else {
			cout << "one parent" << endl;
			sensRange = pastSens[population_size - 1];
			multiRange = pastMulti[population_size - 1];
		}

		cout << sensRange << " " << multiRange << endl;
	
		pair<int, float> value;

		if (GenerateRandom(1, 10) >= 5) {
			increment = GenerateRandom(1, 10);
			fIncrement = float(increment) / 10;

			int iLower = sensRange - increment;
			int iUpper = sensRange + increment;


			int a = GenerateRandom(iLower, iUpper);
			float b = GenerateRandom(multiRange - (fIncrement), multiRange + (fIncrement));

			while (a < 0 || b < 0) {
				a = GenerateRandom(iLower, iUpper);
				b = GenerateRandom(multiRange - (fIncrement), multiRange + (fIncrement));
			}

			pair <int, float> value(a, b);	//take the highest scoring last generation paddle: vectors are pre-sorted
			return value;
		}
		else {
			pair <int, float> value(sensRange, multiRange);	
			return value;
		}
		
	}
}

Generation::Generation() //constructor for generation zero
{

	int rgb[3];			//paddle, ball RGB value


	for (int i = 0; i < population_size; i++) {				//generate a ball and paddle for length of the population size

		pair<int, float> paddleValues = generate_paddle_values();

		for (int i = 0; i < 3; i++)							//generate an RGB value for both the ball and paddle
		{
			rgb[i] = rand() % 256;
		}

		paddles.push_back(* new Paddle(rgb, paddleValues.first, paddleValues.second));							
		balls.push_back(* new Ball(rgb));

	}
	
}

Generation::Generation(vector<int> pastScore, vector<int> pastSens, vector<float> pastMulti)
{

	int rgb[3];			//paddle, ball RGB value

	int highestScore = pastScore[population_size - 1];
	int highestMultiplier = pastMulti[population_size - 1];
	int highestSensitivity = pastSens[population_size - 1];


	for (int i = 0; i < pastScore.size() - 1; i++) {
		if (((pastScore[i] == highestScore || (pastScore[i] >= 3)) && (pastSens[i] != highestSensitivity && pastMulti[i] != highestMultiplier))) {
			otherMultiplierValues.push_back(pastMulti[i]);
			otherSensitivityValues.push_back(pastSens[i]);
		}
	}

	for (int i = 0; i < population_size; i++) {				//generate a ball and paddle for length of the population size

		pair<int, float> paddleValues = generate_paddle_values(pastScore, pastSens, pastMulti);

		for (int i = 0; i < 3; i++)							//generate an RGB value for both the ball and paddle
		{
			rgb[i] = rand() % 256;
		}

		Paddle paddle(rgb, paddleValues.first, paddleValues.second);	//create paddle with generated parameters
		Ball ball(rgb);													//create ball

		paddles.push_back(paddle);										//push to vector: holds all object information for the generation
		balls.push_back(ball);

	}
}

bool Generation::run()
{
	bool out;


	for (int i = 0; i < balls.size(); i++) {
		out = balls[i].move_ball();
		if (out) {
			paddleScores.push_back(paddles[i].getScore());
			paddleMultiplier.push_back(paddles[i].getMultiplier());
			paddleYSens.push_back(paddles[i].getBallYSensitivity());

			balls.erase(balls.begin() + i);		//remove ball/paddle from pool to be drawn
			paddles.erase(paddles .begin() + i);
		}
	}

	for (int i = 0; i < paddles.size(); i++) {

		if (paddles[i].collide(balls[i].get_circ())) {	//if ball and paddle collide change the balls direction
			balls[i].setDirection(4);
		}

	    paddles[i].move_paddle(balls[i].get_circ());
		
	}

	if (balls.size() == 0) {	//if generation has no balls alive, end
		return true;
	}

	return false;
}

std::vector<Paddle> Generation::getPaddleData()
{
	return paddles;
}

std::vector<Ball> Generation::getBallData()
{
	return balls;
}

void Generation::sort_scores()
{
	int i, j, temp = 0;
	
	int n = paddleScores.size();


	for (i = 0; i < population_size; i++) {	//bubble sort scores
		for (j = i + 1; j < population_size; j++)
		{
			if (paddleScores[j] < paddleScores[i]) {
				temp = paddleScores[i];
				paddleScores[i] = paddleScores[j];
				paddleScores[j] = temp;

				temp = paddleMultiplier[i];
				paddleMultiplier[i] = paddleMultiplier[j];
				paddleMultiplier[j] = temp;

				temp = paddleYSens[i];
				paddleYSens[i] = paddleYSens[j];
				paddleYSens[j] = temp;
			}
		}
	}



	
	for (i = 0; i < 10; i++) {	//output each balls data
		cout << "score: " + to_string(paddleScores[i]) + " multiplier: " + to_string(paddleMultiplier[i]) + " sens: " + to_string(paddleYSens[i]) << endl;
	}
	cout << endl;
	
	sorted = true;

}

bool Generation::getOver()
{
	return over;
}

void Generation::setOver(bool value)
{
	over = value;
}

bool Generation::getSorted()
{
	return sorted;
}

void Generation::setSorted(bool value)
{
	sorted = value;
}
