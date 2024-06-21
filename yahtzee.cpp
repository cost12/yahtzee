#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include "yahtzee_player.h"
#include "ai_player.h"


int all_done(yahtzee_player** players, int n) {
  for (int i = 0; i < n; ++i) {
  	if (players[i]->moves_left() != 0) {
  	  return false;
  	}
  }
  return true;
}

bool by_score(yahtzee_player* a, yahtzee_player* b) {
  return a->get_score() > b->get_score();
}


int main(int argc, char* argv[]) {
  srand(time(0));
  int num_players = 2;
  int turn = 0;
  int di = 5;
  int rolls_per_turn = 3;

  if (argc > 1) { num_players = std::atoi(argv[1]); }
  if (argc > 2) { di = std::atoi(argv[2]); }
  if (argc > 3) { rolls_per_turn = std::atoi(argv[3]); }

  //yahtzee_player p[num_players];
  yahtzee_player* players[num_players];
  for (int i = 0; i < num_players; ++i) {
  	std::cout << "Player " << i + 1 << " choose a name: ";
  	std::string name;
  	std::cin >> name;
  	if (name == "AI") {
  		//p[i] = ai_player(di, rolls_per_turn);
  		players[i] = new ai_player(di, rolls_per_turn);
  	} else {
  		//p[i] = yahtzee_player(name, di, rolls_per_turn);
  		players[i] = new yahtzee_player(name, di, rolls_per_turn);
  	}
  }
  
  while (!all_done(players, num_players)) {
  	std::cout << "Your turn, " << players[turn]->get_name() << std::endl;
    players[turn]->take_turn();
    ++turn;
    turn %= num_players;
  }
  
  std::sort(players, &players[num_players], by_score);

  std::cout << "Game over: " << players[0]->get_name() << " wins." << std::endl;
  for (int i = 0; i < num_players; ++i) {
  	std::cout << players[i]->get_name() << ":\t" << players[i]->get_score() << std::endl;
  }

  //for (int i = 0; i < num_players; ++i) {
  //	delete players[i];
  //}

  return 0;
}