#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
struct BallPosition {
	int x;
	int y;
};
class Ball
{
	public:

		Ball(int c[3]);					//ball constructor
		void draw_ball();
		bool move_ball();
		int direction;
		CircleShape get_circ();
		void reset();
		bool ballOut = false;
	private:

		CircleShape circ;
		int colour[3];
		float speed = 4.8f;
};

