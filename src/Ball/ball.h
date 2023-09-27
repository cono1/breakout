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
	float speedX;
	float speedY;
	int texture;
};

void initBall(Ball& ball, float x, float y);
void updateBall(Ball& ball);
void drawBall(Ball ball);
void restartBall(Ball& ball, float x, float y);
void clearBall(Ball& ball);
}