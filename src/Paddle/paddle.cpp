#include "paddle.h"

#include "sl.h"

namespace paddle
{
void initPaddle(Paddle& paddle, float posX, float posY)
{
	paddle.x = posX * 0.5;
	paddle.y = posY * 0.1;
	paddle.width = 332;
	paddle.height = 70;
	paddle.speed = 450;
	paddle.texture = slLoadTexture("res/wood.jpg"); //https://www.vecteezy.com/vector-art/3448235-light-brown-cartoon-wood-texture-pattern-wallpaper-background
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
	paddle.x += paddle.speed * slGetDeltaTime();
}

void movePaddleLeft(Paddle& paddle)
{
	paddle.x -= paddle.speed * slGetDeltaTime();
}

}