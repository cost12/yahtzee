#include "ai_player.h"

ai_player::ai_player() {
	//dice = di_roll();
  	//board = yahtzee_board();
	name = ai_name();
}

ai_player::ai_player(int di, int turns) {
	dice = di_roll(di, turns);
  	//board = yahtzee_board();
	name = ai_name();
}

std::string ai_player::ai_name() {
	std::vector<std::string> names{"Bob", "Bill", "Alice", "Carol", "Eve", "Fred"};
	std::vector<std::string> letters{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	int r = rand() % names.size();
	int s = rand() % letters.size();
	int t = rand() % 100;
	name = "AI:" + names[r] + letters[s] + std::to_string(t);
	return name;
}


void ai_player::take_turn() {
	/*while (not_done) {
		roll();
		if () {
			choose_to_keep();
		}
		if () {
			choose_to_roll();
		}
		if () {
			if ( board.add_move(command, dice.get_dice()) ) {
          		dice.reset();
          		board.print();
         		std::cout << std::endl;
          		return;
          	}
		}
	}*/
	roll();
	std::vector<std::string> moves{"ones", "twos", "threes", "fours", "fives", "sixes", "3k", "4k", "fh", "ss", "ls", "chance", "yahtzee"};
	int r = rand() % moves.size();

	while ( !board.add_move(moves[r], dice.get_dice()) ) {
		r = rand() % moves.size();
	}
	dice.reset();
    board.print();
    std::cout << std::endl;
}