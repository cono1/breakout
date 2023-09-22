#pragma once

namespace bricks
{
const int quantX = 5;
const int quantY = 10;

struct Brick
{
bool isActive;
float x;
float y;
float width;
float height;
};

void initBrick(Brick brick[quantX]);
//void updateBrick(Brick brick[sizeX]);
void drawBrick(Brick brick[quantX]);
}