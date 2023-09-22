#include "sl.h"

#include "Paddle/paddle.h"
#include "Ball/ball.h"
#include "Bricks/bricks.h"

using namespace paddle;
using namespace ball;
using namespace bricks;

void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle);

int main()
{
	const int width = 1024;
	const int height = 768;

	slWindow(width, height, "BREAKOUT", false);

	Paddle paddle;
	Ball ball;
	Brick brick[quantX];

	initPaddle(paddle, width, height);
	initBall(ball, paddle.x, paddle.y);
	initBrick(brick);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		updatePaddle(paddle, width);
		updateBall(ball);
		checkBallLimits(ball, width, height, paddle);

		slSetBackColor(0.5, 0.75, 1.0);
		slSetForeColor(1, 1, 1, 1);

		drawPaddle(paddle);
		drawBall(ball);
		drawBrick(brick);

		slRender();
	}

	slClose();

	return 0;
}

void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle)
{
	if (ball.x < 0 || ball.x > windowWidth)
	{
		ball.dirX *= -1.f;
	}

	if (ball.y > windowHeight)
	{
		ball.x = paddle.x;
		ball.y = paddle.y + ball.height;
	}
}