#include "Paddle.h"
#include <iostream>



Paddle::Paddle(int c[3], int y_sens, float m)
{
    x_pos = 20;



    ball_y_sensitivity = y_sens;
    multiplier = m;

    int range = 300 - 10 + 1;
    int num = rand() % range + 10;

    for (int i = 0; i < 3; i++) {
        colour[i] = c[i];
    }

    y_pos = 250 + num;

    draw_paddle();
}

bool Paddle::collide(CircleShape circ)
{
    if (circ.getGlobalBounds().intersects(rect.getGlobalBounds())) {
        score++;
        return true;
    }

    return false;
}

void Paddle::draw_paddle()
{
    rect.setFillColor(Color(colour[0], colour[1], colour[2]));
    rect.setSize(sf::Vector2f(width, height));

    int num = (rand() % 350 + 1 - 20) + 100;

    rect.setPosition(x_pos, num);
    
}

bool Paddle::bounds(float direction)
{
    auto a = rect.getPosition();
    if ( ((rect.getPosition().y + direction) >= 20) && ((rect.getPosition().y + direction) <= 445)) {
        return true;
    }
    return false;
}



void Paddle::move_paddle(CircleShape circ)
{
    int balls_y = circ.getPosition().y;


    float range = (balls_y + ball_y_sensitivity) * multiplier;



    if (rect.getPosition().y != range) {
        if (rect.getPosition().y < (range)) {
            if (bounds(speed)) {
                rect.move(0.f, speed);
            }
        }
        else if (rect.getPosition().y > (range)) {
            if (bounds(-speed)) {
                rect.move(0.f, -speed);
            }
        }
    }


}


RectangleShape Paddle::getRect()
{
    return rect;
}
