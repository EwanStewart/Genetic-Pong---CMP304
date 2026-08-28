#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Ball
{
	public:

		Ball(int c[3]);					//ball constructor

		void draw_ball();
		bool move_ball();

		//getters and setters
		int getDirection();
		float getSpeed();
		CircleShape get_circ();
		bool getBallOut();

		void setDirection(int);

	private:

		int colour[3];
		int direction;
		float speed = 5.f;
		bool ballOut = false;
		CircleShape circ;

};

