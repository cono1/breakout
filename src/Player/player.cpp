#include "player.h"

namespace player
{
void initPlayer(Player& player)
{
	player.lives = 4;
}

void decreaseLife(Player& player)
{
	if(player.lives > 0)
	player.lives -= 1;
}
}