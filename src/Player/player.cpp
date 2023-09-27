#include "player.h"

namespace player
{
void initPlayer(Player& player)
{
	player.lives = 3;
	player.maxLives = 3;
	player.won = false;
}

void decreaseLife(Player& player)
{
	if(player.lives > 0)
	player.lives -= 1;
}

void updatePlayer(Player& player, int activeBircksLeft)
{
	if (activeBircksLeft <= 0)
	{
		player.won = true;
	}
}
}