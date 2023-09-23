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
extern int offset;

void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle);
bool checkBallToPaddCollision(Ball& ball, Paddle paddle);
bool checkBallToBrickCollision(Ball ball, Brick brick[quantY][quantX], int posX, int posY);

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
initBall(ball, paddle.x, paddle.y);
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
		updateBall(ball);
		checkBallLimits(ball, width, height, paddle);

		if (checkCollision(pauseRect, initWidth, maxWidth) && slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			std::cout << "en pausa";
			currentScreen = PAUSE;
		}

		for (int i = 0; i < quantY; i++)
		{
			for (int j = 0; j < quantX; j++)
			{
				if (checkBallToBrickCollision(ball, brick, i, j))
				{
					deactiveBrick(brick, i, j);
				}
			}
		}

		slSetBackColor(0.5, 0.75, 1.0);
		slSetForeColor(1, 1, 1, 1);

		drawPaddle(paddle);
		drawBrick(brick);
		drawBall(ball);
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
		slSetForeColor(1, 0.5, 1, 1);

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
	if (checkBallToPaddCollision(ball, paddle))
	{
		ball.y = paddle.y + ball.height + offset;
		ball.dirX *= -1.f;
		ball.dirY *= -1.f;
	}

	if (ball.x < 0 || ball.x > windowWidth)
	{
		if (ball.x < 0)
			ball.x += ball.width;

		if(ball.x > ball.x > windowWidth)
			ball.x -= ball.width;

		ball.dirX *= -1.f;
	}

	if (ball.y >= windowHeight)
	{
		ball.y -= ball.width;
		ball.dirY *= -1.f;
	}

	if (ball.y < 0)
	{
		restartBall(ball, static_cast<float>(paddle.x), static_cast<float>(paddle.y));
	}
}

bool checkBallToPaddCollision(Ball& ball, Paddle paddle)
{
	if (paddle.x + (paddle.width / 2) >= ball.x &&
		paddle.x - (paddle.width / 2) <= ball.x + ball.width &&
		paddle.y + (paddle.height / 2) >= ball.y &&
		paddle.y - (paddle.width / 2) <= ball.y + ball.height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkBallToBrickCollision(Ball ball, Brick brick[quantY][quantX], int posX, int posY)
{
	if (brick[posX][posY].x + (brick[posX][posY].width / 2) >= ball.x &&
		brick[posX][posY].x - (brick[posX][posY].width / 2) <= ball.x + ball.width &&
		brick[posX][posY].y + (brick[posX][posY].height / 2) >= ball.y &&
		brick[posX][posY].y - (brick[posX][posY].width / 2) <= ball.y + ball.height)
	{
		return true;
	}
	else
	{
		return false;
	}
}