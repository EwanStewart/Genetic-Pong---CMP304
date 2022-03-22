#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Paddle
{
	public:
		Paddle(int c[3], int, float);	//constructor: color, ball y sensitivity, multiplier
		void draw_paddle();				//creates paddle to draw on screen
		void move_paddle(CircleShape);	//move paddle in respect to the ball
		bool bounds(float);				//check bounds of the screen when moving
		bool collide(CircleShape);		//check collision between paddle and ball

		//getters and setters
		int getBallYSensitivity();		
		int getScore();
		float getMultiplier();
		RectangleShape getRect();		//get the paddle object

	private:

		//used for the AI to learn to track the ball
		float multiplier = 0;	
		int ball_y_sensitivity = 0;

		float speed = 4.5f;		//amount of units the paddle moves in one movement

		int score = 0;			//track the amount of times the paddle collides with the ball

		RectangleShape rect;	//paddle on screen object

		//paddle draw params
		int colour[3];
		int x_pos = 20;
		int y_pos = 300;
		int width = 20;
		int height = 60;

};

