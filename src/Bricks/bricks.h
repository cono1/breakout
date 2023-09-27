#pragma once

namespace bricks
{
const int quantX = 14; //14
const int quantY = 5; //5

struct Brick
{
bool isActive;
float x;
float y;
float width;
float height;
float r;
float g;
float b;
};

void initBrick(Brick brick[quantY][quantX]);
void deactiveBrick(Brick brick[quantY][quantX], int posX, int posY, int& activeBricksLeft);
void drawBrick(Brick brick[quantY][quantX]);
void clearBricks(Brick brick[quantY][quantX]);
}