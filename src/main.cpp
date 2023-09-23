#include "sl.h"

#include <iostream>

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
	Brick brick[quantY][quantX];
	MenuRect pauseRect;

	pauseRect.x = 40;
	pauseRect.y = 745;
	pauseRect.width = 35;
	pauseRect.height = 35;
	float initWidth = pauseRect.width;
	float maxWidth = pauseRect.width + 10;

	initMenu(width);
	initPaddle(paddle, width, height);
	//initBall(ball, paddle.x, paddle.y);
	initBrick(brick);

	CurrentScreen currentScreen = MENU;

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		switch (currentScreen)
		{
		case menu::EXIT:
			return 0;
			break;
		case menu::CREDITS:
			break;
		case menu::RULES:
			break;
		case menu::PLAY:
			updatePaddle(paddle, width);
			//updateBall(ball);
			//checkBallLimits(ball, width, height, paddle);
			if (checkCollision(pauseRect, initWidth, maxWidth) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				std::cout << "en pausa";
				currentScreen = PAUSE;
			}
			slSetBackColor(0.5, 0.75, 1.0);
			slSetForeColor(1, 1, 1, 1);

			drawPaddle(paddle);
			//drawBall(ball);
			drawBrick(brick);
			printPauseButton(pauseRect);

			slRender();
			break;
		case menu::MENU:
			slSetBackColor(0.5, 0.75, 1.0);
			slSetForeColor(1, 1, 1, 1);

			updateMenu(currentScreen);
			printMenu(width, height, fontSize, "BREAKOUT");

			slRender();
			break;
		case menu::PAUSE:
			slSetBackColor(0.5, 0.75, 1.0);
			slSetForeColor(1, 1, 1, 1);

			updateMenu(currentScreen);
			printMenu(width, height, fontSize, "PAUSED");

			slRender();
			break;
		default:
			break;
		}
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