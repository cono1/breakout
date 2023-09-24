#include "game.h"

#include <iostream>

#include "sl.h"

#include "Menu/menu.h"
#include "Paddle/paddle.h"
#include "Ball/ball.h"
#include "Bricks/bricks.h"
#include "Player/player.h"

extern int offset;

namespace game
{
	using namespace menu;
	using namespace paddle;
	using namespace ball;
	using namespace bricks;
	using namespace player;

	void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle, Player& player);
	bool checkBallToPaddCollision(Ball& ball, Paddle paddle);
	bool checkBallToBrickCollision(Ball ball, Brick brick[quantY][quantX], int posX, int posY);
	void printLives(Player player, const int screenWidth, const int screenHeight, const int fontSize);

	static Paddle paddle;
	static Ball ball;
	static Brick brick[quantY][quantX];
	static MenuRect pauseRect;
	static Player player;

	void gameLoop()
	{
		const int width = 1024;
		const int height = 768;
		const int fontSize = 50;

		slWindow(width, height, "BREAKOUT", false);

		int font = slLoadFont("res/PermanentMarker-Regular.ttf");
		slSetFont(font, fontSize);

		CurrentScreen currentScreen = MENU;

		initMenu(width);
		initPaddle(paddle, width, height);
		initBall(ball, paddle.x, paddle.y);
		initBrick(brick);
		initPlayer(player);

		pauseRect.x = 40;
		pauseRect.y = 745;
		pauseRect.width = 35;
		pauseRect.height = 35;
		float initWidth = pauseRect.width;
		float maxWidth = pauseRect.width + 10;

		int activeBricksLeft = quantX * quantY;

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{
			switch (currentScreen)
			{
			case menu::EXIT:
				return;
				break;
			case menu::CREDITS:
				break;
			case menu::RULES:
				break;
			case menu::PLAY:
				updatePaddle(paddle, width);
				updateBall(ball);
				checkBallLimits(ball, width, height, paddle, player);

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
							deactiveBrick(brick, i, j, activeBricksLeft);
						}
					}
				}

				checkPayerStatus(player, activeBricksLeft);


				slSetBackColor(0.5, 0.75, 1.0);
				slSetForeColor(1, 1, 1, 1);

				drawPaddle(paddle);
				drawBrick(brick);
				drawBall(ball);
				printPauseButton(pauseRect);
				printLives(player, width, height, fontSize);

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
	}


	void checkBallLimits(Ball& ball, const int windowWidth, const int windowHeight, Paddle paddle, Player& player)
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

			if (ball.x > ball.x > windowWidth)
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
			decreaseLife(player);
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

	void printLives(Player player, const int screenWidth, const int screenHeight, const int fontSize)
	{
		slSetForeColor(1, 1, 1, 1);
		slSetFontSize(fontSize);
		std::string lives = std::to_string(player.lives);
		slText((screenWidth - slGetTextWidth(lives.c_str())), screenHeight - slGetTextHeight(lives.c_str()), lives.c_str());
	}

}