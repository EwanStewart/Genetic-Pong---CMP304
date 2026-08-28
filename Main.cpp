#include "SFML/Graphics.hpp"
#include "GeneticPong.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

Font font;
//screen dimensions
int height = 500;
int width = 600;

bool fontLoaded = false;

void loadFont() {   //find any usable font on the system
    const std::vector<std::string> candidates = {
        "font/arial.ttf",
        "../font/arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
    };

    for (size_t i = 0; i < candidates.size() && !fontLoaded; i++) {
        fontLoaded = font.loadFromFile(candidates[i]);
    }

    if (!fontLoaded) {
        cerr << "No font found; on-screen text is disabled." << endl;
    }
}

Text setText(int size, Color c, int x, int y, String s) {   //set text helper

    Text title;
    title.setFont(font);
    title.setCharacterSize(size);
    title.setFillColor(c);
    title.setPosition(x, y);
    title.setString(s);
    return title;
}

int main() {

    srand(static_cast<unsigned int>(time(NULL)));
    loadFont();
    bool endCondition = false;                                  

    RenderWindow window(VideoMode(width, height), "AI Pong");   //create sfml window

    GeneticPong pong;                                           //create instance of generational pong
    pong.create_new_generation();                               //create generation zero

    while (window.isOpen())
    {

        Event event;
        Text currentGenerationText = setText(15, Color::Black, 0, 0, "Generation: " + to_string(pong.get_current_generation_value()));  //current generation count text
        Text gameEndText = setText(15, Color::Black, 0, 50, "Algorithm Over");

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White); //set the background to white
        
        if (!endCondition && pong.get_current_generation_value() != 100) {  //keep running the algorithm until the end condition is triggered or generation count > 100
            endCondition = pong.run_generation();
            for (size_t i = 0; i < pong.get_paddles().size(); i++) {   //draw each paddle and ball on-screen
                window.draw(pong.get_paddles()[i].getRect());
                window.draw(pong.get_balls()[i].get_circ());
            }
        } else {
            if (fontLoaded) {
                window.draw(gameEndText);   //draw the end screen text
            }
        }


        if (fontLoaded) {
            window.draw(currentGenerationText);
        } //display current generation on-screen
        window.display();                   //update screen

        //std::this_thread::sleep_for(std::chrono::milliseconds(1)); //enable to watch in real-time
    }

    return 0;

}
