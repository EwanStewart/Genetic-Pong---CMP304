#include "Ball.h"

Ball::Ball(int c[3])  
{
    for (int i = 0; i < 3; i++) {   //set the colour to match the ball
        colour[i] = c[i];
    }

    direction = rand() % 2;     //random start direction
    draw_ball();                
}


bool Ball::move_ball()
{
    int randomDirection = rand() % 2;

    switch (direction)  //dependant on onscreen collisions with walls or paddle set movement direction
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
    int y_pos = (rand() % 500 - 100);   //random y position to spread the balls out
    circ.setPosition(480,y_pos);
}


CircleShape Ball::get_circ()
{
    return circ;
}

bool Ball::getBallOut()
{
    return ballOut;
}

void Ball::setDirection(int val)
{
    direction = val;
}


int Ball::getDirection()
{
    return direction;
}

float Ball::getSpeed() {
    return speed;
}






