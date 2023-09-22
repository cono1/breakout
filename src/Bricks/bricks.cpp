#include "bricks.h"

#include "sl.h"

namespace bricks
{
void initBrick(Brick brick[quantX])
{
	int firstBrickYPosition = 70;

	for (int i = 0; i < quantX; i++)
	{
		for (int j = 0; j < quantY; j++)
		{
			brick[i].width = 50.f;
			brick[i].height = 20.5f;
			brick[i].isActive = true;
			brick[i].x = j * brick[i].x + brick[i].width ;
			brick[i].y = i * brick[i].height + firstBrickYPosition;
		}
	}
}

void drawBrick(Brick brick[quantX])
{
	for (int i = 0; i < quantX; i++)
	{
		slRectangleFill(brick[i].x, brick[i].y, brick[i].width, brick[i].height);
	}
}
}
