#include "di_roll.h"
#include <ctime>

di_roll::di_roll() {
  values = std::vector<int>(5);
  hold = std::vector<bool>(5);
  roll_num = 0;
  turns = 3;
}

di_roll::di_roll(int di, int turns) {
  values = std::vector<int>(di);
  hold = std::vector<bool>(di);
  roll_num = 0;
  this->turns = turns;
}

bool di_roll::roll() {
	if (roll_num >= turns) { return false; }
  for (unsigned int i = 0; i < values.size(); ++i) {
	  if (!hold[i]) { values[i] = roll_one(); }
  }
  ++roll_num;
  return true;
}

int di_roll::roll_one() {
	return rand() % 6 + 1;
}

void di_roll::choose_to_keep(unsigned int di) {
  if (di < hold.size()) {
	  if (roll_num > 0) {
      hold[di] = true;
    }
  }
}

void di_roll::choose_to_roll(unsigned int di) {
  if (di < hold.size()) {
    hold[di] = false;
  }
}

void di_roll::reset() {
	roll_num = 0;
	for (unsigned int i = 0; i < hold.size(); ++i) {
		hold[i] = false;
	}
}

void di_roll::print() {
  std::cout << "Roll " << roll_num << ":" << std::endl;
  for (unsigned int i = 0; i < values.size(); ++i) {
    std::cout << "[" << i << "]" << "\t";
  }
  std::cout << std::endl;
  for (unsigned int i = 0; i < values.size(); ++i) {
    std::cout << " " << values[i] << "\t";
  }
  std::cout << std::endl;
  for (unsigned int i = 0; i < hold.size(); ++i) {
    if (hold[i]) {
      std::cout << " X" << "\t";
    } else {
      std::cout << "\t";
    }
  }
  std::cout << std::endl;
}