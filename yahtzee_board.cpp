#include "yahtzee_board.h"
#include <algorithm>
#include <iostream>

yahtzee_board::yahtzee_board() {
  for (int i = 0; i < 6; ++i) {
  	top[i] = 0;
  	top_filled[i] = false;
  	bottom_filled[i] = false;
  }
  bottom_filled[6] = false;

  three_of_a_kind = 0;
  four_of_a_kind = 0;
  full_house = false;
  small_strait = false;
  large_strait = false;
  chance = 0;
  yahtzees = 0;
}

int yahtzee_board::total_sum() const {
	int sub = top_sum() + 35*bonus() + three_of_a_kind + four_of_a_kind + 25*full_house + 30*small_strait + 40*large_strait + chance;
	if (yahtzees >= 1) {
		sub += 50 + 100*(yahtzees - 1);
	}
	return sub;
}

int yahtzee_board::top_sum() const {
	int sum = 0;
	for (int i = 0; i < 6; ++i) {
    sum += top[i];
	}
  return sum;
}

bool yahtzee_board::bonus() const {
	return top_sum() >= 63;
}

int yahtzee_board::moves_left() const {
	int moves = 0;
	for (int i = 0; i < 6; ++i) {
		if (!top_filled[i])     { ++moves; }
		if (!bottom_filled[i]) { ++moves; }
	}
	if (!bottom_filled[6]) { ++moves; }
	return moves;
}

int matches(const std::vector<int> &dice, int n) {
	int matches = 0;
	for (unsigned int i = 0; i < dice.size(); ++i) {
		if (dice[i] == n) {
			++matches;
		}
	}
	return matches;
}

bool n_of_a_kind(const std::vector<int> &dice, int n) {
	for (unsigned int i = 0; i < dice.size(); ++i) {
		if (matches(dice, dice[i]) >= n) {
			return true;
		}
	}
	return false;
}

int sum(const std::vector<int> &dice) {
	int sum = 0;
	for (unsigned int i = 0; i < dice.size(); ++i) {
		sum += dice[i];
	}
	return sum;
}

bool is_full_house(const std::vector<int> &dice) {
	for (unsigned int i = 0; i < dice.size(); ++i) {
		int m = matches(dice, dice[i]);
		if (m != 2 && m != 3) { return false; }
	}
	return true;
}

bool straight(const std::vector<int> &dice, int n) {
	int length = 1;
	if (length >= n) { return true; }
	unsigned int i = 0;
	while (i < dice.size() - 1) {
		if (dice[i+1] - dice[i] == 1) {
			++length;
			if (length >= n) { return true; }
		} else if (dice[i+1] != dice[i]) {
			length = 1;
		}
		++i;
	}
	return false;
}

bool yahtzee_board::add_move(const std::string &type, const std::vector<int> &d) {
	int amount = 0;
	std::vector<int> dice(d.begin(), d.end());
	std::sort(dice.begin(), dice.end());
	if (type == "ones") {
		if (!top_filled[0]) {
			amount = 1*matches(dice, 1);
			top[0] = amount;
			top_filled[0] = true;
			return true;
		}
	} else if (type == "twos") {
    if (!top_filled[1]) {
    	    amount = 2*matches(dice, 2);
			top[1] = amount;
			top_filled[1] = true;
			return true;
		}
	} else if (type == "threes") {
    if (!top_filled[2]) {
    	    amount = 3*matches(dice, 3);
			top[2] = amount;
			top_filled[2] = true;
			return true;
		}
	} else if (type == "fours") {
    if (!top_filled[3]) {
    	    amount = 4*matches(dice, 4);
			top[3] = amount;
			top_filled[3] = true;
			return true;
		}
	} else if (type == "fives") {
    if (!top_filled[4]) {
    	    amount = 5*matches(dice, 5);
			top[4] = amount;
			top_filled[4] = true;
			return true;
		}
	} else if (type == "sixes") {
    if (!top_filled[5]) {
    	    amount = 6*matches(dice, 6);
			top[5] = amount;
			top_filled[5] = true;
			return true;
		}
	} else if (type == "3k") {
    if (!bottom_filled[0]) {
    		amount = sum(dice);
			three_of_a_kind = amount*n_of_a_kind(dice, 3);
			bottom_filled[0] = true;
			return true;
		}
	} else if (type == "4k") {
    if (!bottom_filled[1]) {
    		amount = sum(dice);
			four_of_a_kind = amount*n_of_a_kind(dice, 4);
			bottom_filled[1] = true;
			return true;
		}
	} else if (type == "fh") {
    if (!bottom_filled[2]) {
			full_house = is_full_house(dice);
			bottom_filled[2] = true;
			return true;
		}
	} else if (type == "ss") {
    if (!bottom_filled[3]) {
			small_strait = straight(dice, 4);
			bottom_filled[3] = true;
			return true;
		}
	} else if (type == "ls") {
    if (!bottom_filled[4]) {
			large_strait = straight(dice, 5);
			bottom_filled[4] = true;
			return true;
		}
	} else if (type == "chance") {
    if (!bottom_filled[5]) {
    		amount = sum(dice);
			chance = amount;
			bottom_filled[5] = true;
			return true;
		}
	} else if (type == "yahtzee") {
		if ( !(bottom_filled[6] && yahtzees == 0) ) {
			yahtzees += n_of_a_kind(dice, 5);
			bottom_filled[6] = true;
			return true;
		}
	} else {
		std::cout << "Error: no type \"" << type << "\"" << std::endl;
	}
	return false;
}

bool yahtzee_board::is_valid_move(const std::string &s) {
	std::vector<std::string> rolls{"ones", "twos", "threes", "fours", "fives", "sixes", "3k", 
													"4k", "fh", "ss", "ls", "chance", "yahtzee"};
	for (unsigned int i = 0; i < rolls.size(); ++i) {
		if (s == rolls[i]) { return true; }
	}
	return false;
}

void yahtzee_board::print() {
	std::vector<std::string> categories{"ones", "twos", "threes", "fours", "fives", "sixes", "bonus", "top sum",
			"3 of a kind", "4 of a kind", "full house", "small straight", "large strait", "chance     ", "yahtzee     ", "total"};
	for (unsigned int i = 0; i < categories.size(); ++i) {
		if (i < 6) {
			if (top_filled[i]) {
				std::cout << categories[i] << "\t\t" << top[i] << std::endl;
			} else {
				std::cout << categories[i] << "\t\t" << "XX" << std::endl;
			}
		} else if (i == 6) {
			if (bonus()) {
				std::cout << categories[i] << "\t\t" << "35" << std::endl;
			} else {
				std::cout << categories[i] << "\t\t" << "XX" << std::endl;
			}
		} else if (i == 7) {
			std::cout << categories[i] << "\t\t" << top_sum() + 35*bonus() << std::endl;
		} else if (i < 15) {
			int bottom[7] = {three_of_a_kind, four_of_a_kind, full_house*25, small_strait*30, large_strait*40, chance, yahtzees*50};
			if (yahtzees > 1) { bottom[i] += 50*(yahtzees - 1); }
			if (bottom_filled[i-8]) {
				std::cout << categories[i] << "\t" << bottom[i-8] << std::endl;
			} else {
				std::cout << categories[i] << "\t" << "XX" << std::endl;
			}
		} else if (i == 15) {
			std::cout << categories[i] << "\t\t" << total_sum() << std::endl;
		}
	}
}