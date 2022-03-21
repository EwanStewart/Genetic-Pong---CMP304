#include "SFML/Graphics.hpp"
#include "GeneticPong.h"
#include <windows.h>
#include <iostream>


using namespace sf;
using namespace std;

Font font;
int height = 500;
int width = 600;

Text setText(int size, Color c, int x, int y, String s) {   //set text helper

    font.loadFromFile("../font/arial.ttf");

    Text title;
    title.setFont(font);
    title.setCharacterSize(size);
    title.setFillColor(c);
    title.setPosition(x, y);
    title.setString(s);
    return title;
}

int main() {

    srand(time(NULL));
    bool endCondition = false;      //end condition triggered if: paddle reaches 50 collisions in a row.

    RenderWindow window(VideoMode(width, height), "AI Pong");   //create sfml window
    GeneticPong pong;                                           //create instance of generational pong
    pong.create_new_generation();                               //create generation zero

    while (window.isOpen())
    {

        Event event;
        Text currentGenerationText = setText(15, Color::Black, 0, 0, "Generation: " + to_string(pong.get_current_generation_value()));
        Text gameEndText = setText(15, Color::Black, 0, 50, "Game Over");

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color(220, 220, 220));
        
        if (!endCondition && pong.get_current_generation_value() != 100) {  //keep running the generational pong until end condition is triggered or generations > 100
            endCondition = pong.run_generation();

            for (int i = 0; i < pong.get_paddles().size(); i++) {   //draw each paddle and ball on-screen
                window.draw(pong.get_paddles()[i].getRect());
                window.draw(pong.get_balls()[i].get_circ());
            }
        }
        else {
            window.draw(gameEndText);   //draw the end screen text
        }


        window.draw(currentGenerationText); //display current generation on-screen
        window.display();                   //update screen
        //Sleep(1);                         //enable to watch in real-time
    }

    return 0;

}
