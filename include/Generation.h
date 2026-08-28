#include "Paddle.h"
#include "Ball.h"

#include <vector>
#include <iostream>
using namespace std;

#pragma once
class Generation
{
public:
	Generation();											//generation zero only
	Generation(vector<int>, vector<int>, vector<float>);	//all generations after zero

	bool run();


	vector<int> paddleScores;				//hold the amount of collisions each paddle had with the ball
	vector<int> paddleYSens;				//hold the sensitivity value for each paddle
	vector<float> paddleMultiplier;			//hold the multiplier value for each paddle

	pair<int, float> generate_paddle_values(vector<int>, vector<int>, vector<float>);			//generate paddle values using past generation data
	pair<int, float> generate_paddle_values();
	pair<int, float> mutate_paddle_values(vector<int>, vector<int>, vector<float>);		//chance encounter of mutation in relation to past generation data
	pair<int, float> crossover_paddle_values(vector<int>, vector<int>, vector<float>);	//cross-over past generation data


	void sort_scores();			//sort the scores in order, re-arrange sensitivity and multiplier vectors accordingly

	//getters and setters

	vector <Paddle> getPaddleData();		//get all current gen paddle data
	vector <Ball> getBallData();			//get all current gen ball data

	bool getOver();
	void setOver(bool);

	bool getSorted();
	void setSorted(bool);


private:
	bool over = false;				//is the generation over
	bool sorted = false;			//is the score data sorted

	int mutation_rate = 30;			//percentage chance of mutation
	int population_size = 10;		//number of paddles and ball pairs

	vector<float> otherMultiplierValues;
	vector<int> otherSensitivityValues;

	std::vector<Paddle> paddles;	//hold all current gen paddle data
	std::vector<Ball> balls;		//hold all current gen ball data

};

