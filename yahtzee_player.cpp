#include "yahtzee_player.h"
#include "yahtzee_board.h"
#include <iostream>
#include <string>

yahtzee_player::yahtzee_player() {
  dice = di_roll();
  board = yahtzee_board();
  name = "AI";
}

yahtzee_player::yahtzee_player(const std::string &n) {
  dice = di_roll();
  board = yahtzee_board();
  name = n;
}

yahtzee_player::yahtzee_player(const std::string &n, int di, int turns) {
  dice = di_roll(di, turns);
  board = yahtzee_board();
  name = n;
}

void yahtzee_player::roll() {
  if (dice.roll()) {
  	dice.print();
  } else {
  	std::cout << "Your turn is over, pick a move" << std::endl;
  }
}

bool is_number(const std::string &s) {
  for (std::string::const_iterator s_itr = s.begin(); s_itr != s.end(); ++s_itr) {
    if (!std::isdigit(*s_itr)) { return false; }
  }
  return true;
}

void yahtzee_player::take_turn() {
	std::string command;
	int num = 0;
	std::string current_action = "";
	while (std::cin >> command) {
    if (command == "hold") {
      current_action = "hold";
    } else if (command == "release") {
      current_action = "release";
    } else if (command == "print") {
      current_action = "print";
    } else if (command == "dice") {
      if (current_action == "print") {
        dice.print();
      } else {
        std::cout << "Invalid command: \"" << command << "\" try again." << std::endl;
      }
    } else if (command == "score") {
      if (current_action == "print") {
        board.print();
      } else {
        std::cout << "Invalid command: \"" << command << "\" try again." << std::endl;
      }
    } else if (command == "roll") {
      roll();
    } else if (is_number(command)) {
      if (current_action == "hold") {
        num = std::stoi(command);
        dice.choose_to_keep(num);
      } else if (current_action == "release") {
        num = std::stoi(command);
        dice.choose_to_roll(num);
      } else {
      	std::cout << "Invalid command: \"" << command << "\" try again." << std::endl;
      }
    } else if (board.is_valid_move(command)) {
      if (dice.roll_count() > 0) {
        if ( board.add_move(command, dice.get_dice()) ) {
          dice.reset();
          board.print();
          std::cout << std::endl;
          return;
        } else {
          std::cout << "Nice try, you can't do that" << std::endl;
        }
      } else {
      	std::cout << "Nice try, roll first" << std::endl;
      }
    } else {
      std::cout << "Invalid command: \"" << command << "\" try again." << std::endl;
    }
	}
}

int yahtzee_player::moves_left() {
	return board.moves_left();
}