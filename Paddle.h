#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;


class Paddle
{
	public:
		Paddle(int c[3], int, float);
		void draw_paddle();
		void move_paddle(CircleShape);
		bool bounds(float);
		bool collide(CircleShape);
		RectangleShape getRect();
		int score = 0;
		float multiplier = 0;
		int ball_y_sensitivity = 0;
		float speed = 5.f;

	private:
		int ball_collisions;
		int fitness;
		float follow;
		int x_pos = 20;
		int y_pos = 300;
		int width = 20;
		int height = 60;
		RectangleShape rect;
		int colour[3];

};

