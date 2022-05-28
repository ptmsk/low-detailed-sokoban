#ifndef CONSTANT_H_
#define CONSTANT_H_

// configuration
const float SPRITESIZE = 64.0;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

// block
const int AIR = 0;
const int WALL = 1;
const int PLAYER = 2;
const int BOX = 3;
const int TARGET = 4;
const int TARGET_FILLED = 5;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif