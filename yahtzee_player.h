#ifndef _YAHTZEE_PLAYER__
#define _YAHTZEE_PLAYER__

#include <string>
#include "yahtzee_board.h"
#include "di_roll.h"

class yahtzee_player {
public:
  yahtzee_player();
  yahtzee_player(const std::string &n);
  yahtzee_player(const std::string &n, int di, int turns);

  void roll();
  virtual void take_turn();
  void add_move(const std::string &type, int amount);
  int moves_left();
  const std::string& get_name() const { return name; }
  int get_score() const { return board.total_sum(); }

protected:
  bool is_valid_move(const std::string &s);

  yahtzee_board board;
  di_roll dice;
  std::string name;
};

#endif