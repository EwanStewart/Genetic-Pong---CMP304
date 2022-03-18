#include "Ball.h"
#include <iostream>

Ball::Ball(int c[3])
{
    for (int i = 0; i < 3; i++) {
        colour[i] = c[i];
    }
    direction = rand() % 2;
    draw_ball();
}


bool Ball::move_ball()
{
    float v = 5.f;
    int o = rand() % 2;


        switch (direction)
        {
        case 0:
            circ.move(-v, v);
            break;
        case 1:
            circ.move(-v, -v);
            break;
        case 2:
            circ.move(v, -v);
        case 3:
            circ.move(v, v);
        case 4:
            circ.move(v, 0);
        default:
            break;
        }



        if ((circ.getPosition().y > 480)) {
            if (o) {
                direction = 1;
            }
            else {
                direction = 2;
            }
        }
        else if ((circ.getPosition().x >= 590)) {
            if (o) {
                direction = 0;
            }
            else {
                direction = 1;
            }
        }
        else if ((circ.getPosition().y < 10)) {
                direction = 0;
            
        }
        else if ((circ.getPosition().x <= 0)) {
            direction = 9;
            return true;
            //circ.setPosition(600 - 20, 500 / 2);
        }
    
        return false;
    


}

void Ball::draw_ball()
{
    circ.setRadius(10);
    circ.setFillColor(Color(colour[0], colour[1], colour[2]));
    int num = (rand() % 350 + 1 - 20) + 100;
    circ.setPosition(480,num);
}




CircleShape Ball::get_circ()
{
    return circ;
}

void Ball::reset()
{
    circ.setPosition(480, 300);
}

void Ball::hit() {
    direction = 2;
}




