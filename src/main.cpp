#include "sl.h"

#include "Menu/menu.h"
#include "Paddle/paddle.h"
#include "Ball/ball.h"
#include "Bricks/bricks.h"

using namespace menu;
using namespace paddle;
using namespace ball;
using namespace bricks;

void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle);

int main()
{
	const int width = 1024;
	const int height = 768;
	const int fontSize = 50;

	slWindow(width, height, "BREAKOUT", false);

	int font = slLoadFont("res/PermanentMarker-Regular.ttf");
	slSetFont(font, fontSize);

	Paddle paddle;
	Ball ball;
	Brick brick[quantX];

	initMenu(width);
	initPaddle(paddle, width, height);
	initBall(ball, paddle.x, paddle.y);
	initBrick(brick);
	CurrentScreen currentScreen = MENU;

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		updateMenu(currentScreen);
		/*updatePaddle(paddle, width);
		updateBall(ball);
		checkBallLimits(ball, width, height, paddle);*/

		slSetBackColor(0.5, 0.75, 1.0);
		slSetForeColor(1, 1, 1, 1);

		printMenu(width, height, fontSize);
		/*drawPaddle(paddle);
		drawBall(ball);
		drawBrick(brick);*/

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