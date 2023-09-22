#pragma once

namespace paddle
{
struct Paddle
{
	float x;
	float y;
	float width;
	float height;
	float speed;
	int texture;
};

void initPaddle(Paddle& paddle, float posX, float posY);
void updatePaddle(Paddle& paddle, float windowWidth);
void drawPaddle(Paddle paddle);
void movePaddleRight(Paddle& paddle);
void movePaddleLeft(Paddle& paddle);
}