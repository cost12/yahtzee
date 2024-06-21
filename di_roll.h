#ifndef _DI_ROLL__
#define _DI_ROLL__

#include <vector>
#include <ctime>
#include <iostream>

class di_roll {
public:
  di_roll();
  di_roll(int di, int turns);
  bool roll();
  int roll_one();
  void choose_to_keep(unsigned int di);
  void choose_to_roll(unsigned int di);
  void reset();
  void print();
  int roll_count() const { return roll_num; }
  const std::vector<int>& get_dice() const { return values; }

private:
  std::vector<int> values;
  std::vector<bool> hold;
  int roll_num;
  int turns;
};

#endif