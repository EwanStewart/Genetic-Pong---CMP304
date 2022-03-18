#pragma once
#include "Structs.h"
#include "SFML/Graphics.hpp"
using namespace sf;

class Ball
{
	public:

		Ball(int c[3]);					//ball constructor
		BallPosition getPosition();			//ball return x,y position
		void draw_ball();
		bool move_ball();
		int direction;
		CircleShape get_circ();
		void reset();
		void hit();
		bool ballOut = false;
	private:

		CircleShape circ;
		int colour[3];
};

