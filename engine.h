#ifndef ENGINEH
#define ENGINEH
#include <vector>
#include "zobrist.h"
#include "goban.h"
#include "amaf.h"
#include "tree.h"

#define INFINITE -1u/2

class Engine{
 private:
  const bool HEAVY = true, LIGHT = false;
  
  Goban *main_goban;
  int tree_size, max_playouts;
  int rand_movs, simul_len, discarded;
  Tree tree;
  AmafBoard amaf;
  mutable clock_t fin_clock, max_time, byo_time;

  int get_best_move() const;
  int play_random_game(bool heavy);
  void back_up_results(int result, Node *node_history[], int nnodes, bool side);
  void print_PV() const;

 public:
  Engine(Goban *goban);
  void reset();
  void set_playouts(int playouts);
  void set_times(int main_time, int byo_time, int stones);
  void set_times(int time_left, int stones);
  float score(std::vector<int> *dead);
  int generate_move(bool early_pass);
  void perft(int max);
  void report_move(int move) { tree.promote(move); }
};
#endif
