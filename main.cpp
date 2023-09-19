#include "sl.h"

#include "Paddle/paddle.h"

using namespace paddle;

int main()
{
	const int width = 1024;
	const int height = 768;

	slWindow(width, height, "BREAKOUT", false);

	Paddle paddle;
	initPaddle(paddle, width, height);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		updatePaddle(paddle, width);

		slSetBackColor(0.5, 0.75, 1.0);
		slSetForeColor(1, 1, 1, 1);
		drawPaddle(paddle);
		slRender();
	}

	slClose();

	return 0;
}