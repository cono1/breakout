#pragma once

namespace bricks
{
const int quantX = 14;
const int quantY = 5;

struct Brick
{
bool isActive;
float x;
float y;
float width;
float height;
};

void initBrick(Brick brick[quantY][quantX]);
//void updateBrick(Brick brick[sizeX]);
void drawBrick(Brick brick[quantY][quantX]);
}