Genetic Pong

Developed using C++ and SFML for graphical display.

A generational approach to AI learning where using genetic techniques such as crossover and mutation, an infinite game of Pong is created.

![image](https://github.com/EwanStewart/Genetic-Pong---CMP304/assets/80590593/e2471123-42ed-4658-b197-1bc5a77969c6)


https://github.com/EwanStewart/Genetic-Pong---CMP304/assets/80590593/a892ecfe-3817-447d-948e-4830cb09584d



## Building on Linux

Install SFML 2 and a compiler:

```bash
sudo apt install build-essential cmake libsfml-dev
```

Build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

Run:

```bash
./build/GeneticPong
```

The program picks up a system font automatically. On-screen text turns off if it finds none.
