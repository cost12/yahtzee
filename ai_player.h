#ifndef __AI_PLAYER_
#define __AI_PLAYER_

#include <string>
#include <ctime>
#include <vector>
#include "yahtzee_player.h"

class ai_player: public yahtzee_player {
public:
	ai_player();
	ai_player(int di, int turns);

	void take_turn();

private:
	std::string ai_name();
};

#endif