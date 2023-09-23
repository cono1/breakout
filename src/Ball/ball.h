#pragma once

namespace ball
{
struct Ball
{
	float x;
	float y;
	float dirX;
	float dirY;
	float width;
	float height;
	float speed;
	int texture;
};

void initBall(Ball& ball, float paddleX, float paddleY);
void updateBall(Ball& ball);
void drawBall(Ball ball);
void restartBall(Ball& ball, float paddleX, float paddleY);
}