#pragma once

namespace bricks
{
const int quantX = 10; //14
const int quantY = 1; //5

struct Brick
{
bool isActive;
float x;
float y;
float width;
float height;
};

void initBrick(Brick brick[quantY][quantX]);
void deactiveBrick(Brick brick[quantY][quantX], int posX, int posY, int& activeBricksLeft);
void drawBrick(Brick brick[quantY][quantX]);
void clearBricks(Brick brick[quantY][quantX]);
}