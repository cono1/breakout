#include "player.h"

namespace player
{
void initPlayer(Player& player)
{
	player.lives = 4;
	player.won = false;
}

void decreaseLife(Player& player)
{
	if(player.lives > 0)
	player.lives -= 1;
}

void checkPayerStatus(Player player, int activeBircksLeft)
{
	if (activeBircksLeft <= 0)
	{
		player.won = true;
	}
}
}