#include "bricks.h"

#include <time.h>
#include <iostream>

#include "sl.h"

namespace bricks
{
void initBrick(Brick brick[quantY][quantX])
{
	srand(time(NULL));
	int firstBrickYPosition = 500;
	int space = 13;

	for (int i = 0; i < quantY; i++)
	{
		for (int j = 0; j < quantX; j++)
		{
			brick[i][j].width = 60.f;
			brick[i][j].height = 35.5f;
			brick[i][j].x = j * (brick[i][j].width + space) + brick[i][j].width / 2;
			brick[i][j].y = i * (brick[i][j].height + space) + firstBrickYPosition;
			brick[i][j].isActive = true;
			brick[i][j].r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.5 + 0.5;
			brick[i][j].g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX * 4.0);
			brick[i][j].b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX * 2.0);

		}
	}
}

void deactiveBrick(Brick brick[quantY][quantX], int posX, int posY, int& activeBricksLeft)
{
	if (brick[posX][posY].isActive)
	{
		brick[posX][posY].isActive = false;
		activeBricksLeft--;
	}

	if (!brick[posX][posY].isActive)
	{
		brick[posX][posY].width = 0;
		brick[posX][posY].height = 0;
	}
}

void drawBrick(Brick brick[quantY][quantX])
{
	for (int i = 0; i < quantY; i++)
	{
		for (int j = 0; j < quantX; j++)
		{
			if(brick[i][j].isActive)
			slSetForeColor(brick[i][j].r, brick[i][j].g, brick[i][j].b, 1);
			slRectangleFill(brick[i][j].x, brick[i][j].y, brick[i][j].width, brick[i][j].height);
		}
	}
}

void clearBricks(Brick brick[quantY][quantX])
{
	for (int i = 0; i < quantY; i++)
	{
		for (int j = 0; j < quantX; j++)
		{
			brick[i][j].width = 0.0f;
			brick[i][j].height = 0.0f;
			brick[i][j].isActive = false;
		}
	}
}
}
