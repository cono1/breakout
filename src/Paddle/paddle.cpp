#include "paddle.h"

#include "sl.h"

namespace paddle
{
void initPaddle(Paddle& paddle, float posX, float posY)
{
	paddle.x = static_cast<float>(posX * 0.5);
	paddle.y = static_cast<float>(posY * 0.1);
	paddle.width = 220;
	paddle.height = 30;
	paddle.speed = 450;
	paddle.texture = slLoadTexture("res/padd.jpg"); //https://www.vecteezy.com/vector-art/7544384-abstract-geometric-gradient-color-halftone-modern-shape-background
	//https://www.vecteezy.com/members/graphoboy9158803
}

void updatePaddle(Paddle& paddle, float windowWidth)
{
	if (slGetKey(SL_KEY_RIGHT) && paddle.x + (paddle.width / 2) < windowWidth)
	{
		movePaddleRight(paddle);
	}

	if (slGetKey(SL_KEY_LEFT) && paddle.x - (paddle.width / 2) > 0)
	{
		movePaddleLeft(paddle);
	}
}

void drawPaddle(Paddle paddle)
{
	slSprite(paddle.texture, paddle.x, paddle.y, paddle.width, paddle.height);
}

void movePaddleRight(Paddle& paddle)
{
	paddle.x += static_cast<float>(paddle.speed * slGetDeltaTime());
}

void movePaddleLeft(Paddle& paddle)
{
	paddle.x -= static_cast<float>(paddle.speed * slGetDeltaTime());
}

void clearPaddle(Paddle& paddle)
{
	paddle.width = 0;
	paddle.height = 0;
}
}