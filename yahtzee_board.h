#ifndef _YAHTZEE_BOARD__
#define _YAHTZEE_BOARD__

#include <string>
#include <vector>

class yahtzee_board {
public:
  yahtzee_board();

  int total_sum() const ;
  int top_sum() const ;
  bool bonus() const ;
  int moves_left() const ;

  bool add_move(const std::string &type, const std::vector<int> &d);
  bool is_valid_move(const std::string &s);
  //bool is_valid_string(const std::string &s);
  void print();

private:
  int top[6];
  bool top_filled[6];
  bool bottom_filled[7];

  int three_of_a_kind;
  int four_of_a_kind;
  bool full_house;
  bool small_strait;
  bool large_strait;
  int chance;
  int yahtzees;
  bool yahtzee_open;
};

#endif