#include "ball.h"

#include <time.h>
#include <cmath>
#include <cstdlib>

#include "sl.h"
int offset = 10;
namespace ball
{
void initBall(Ball& ball, float x, float y)
{
	srand(time(NULL));
	ball.dirX = rand() % 300 - 150;
	ball.dirY = 100.f;
	ball.width = 30.f;
	ball.height = 30.f;
	ball.x = x;
	ball.y = y + ball.height + offset;
	ball.speedX = 3.f;
	ball.speedY= 3.f;
	ball.texture = slLoadTexture("res/watermelon.jpg");
}

void updateBall(Ball& ball)
{
	ball.x += ball.dirX * ball.speedX * slGetDeltaTime();
	ball.y += ball.dirY * ball.speedY * slGetDeltaTime();
}

void drawBall(Ball ball)
{
	slSprite(ball.texture, ball.x, ball.y, ball.width, ball.height);
}

void restartBall(Ball& ball, float x, float y)
{
	srand(time(NULL));
	ball.dirX = rand() % 300 - 150;
	ball.dirY = 100.f;
	ball.x = x;
	ball.y = y + ball.height + offset;
}

void clearBall(Ball& ball)
{
	ball.height = 0;
	ball.width = 0;
}
}