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
    int randomDirection = rand() % 2;

    switch (direction)
    {
    case 0:
        circ.move(-speed, speed);   
        break;
    case 1:
        circ.move(-speed, -speed);  
        break;
    case 2:
        circ.move(speed, -speed);
    case 3: 
        circ.move(speed, speed);
    case 4:                        
        circ.move(speed, 0);
    default:
        break;
    }



    if ((circ.getPosition().y > 480)) { //bottom wall
        direction = 1;
    }
    else if ((circ.getPosition().x >= 590)) {   //initial start
        //randomDirection = 0;
        if (randomDirection) {
            direction = 0;
        }
        else {
            direction = 1;
        }
    }
    else if ((circ.getPosition().y < 10)) { //top wall
            direction = 0;
    }
    else if ((circ.getPosition().x <= 0)) { //past the paddle
        direction = 9;
        return true;
    }
    
    return false;
    


}

void Ball::draw_ball()
{
    circ.setRadius(5);
    circ.setFillColor(Color(colour[0], colour[1], colour[2]));
    int num = (rand() % 250 - 100);
    int y_pos = 250 + num;
    circ.setPosition(480,y_pos);
}




CircleShape Ball::get_circ()
{
    return circ;
}

void Ball::reset()
{
    circ.setPosition(480, 300);
}






