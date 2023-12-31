#ifndef GTPH
#define GTPH

#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include "goban.h"
#include "engine.h"

#define PROTOCOLVERSION "2"
#define PROGVERSION "0.9"
#define PROGNAME "ACE"
//#define LOG

class GTP{

private:
  bool loop, early_pass;
  int cmd;
  std::string cmd_id;
  std::string cmd_name;
  std::vector<std::string> cmd_args;
  std::vector<float> cmd_int_args;
  std::string command_string;
  std::string response;
#ifdef LOG
  ofstream engine_log;
#endif
  Goban main_goban;
  Engine go_engine;
  void protocol_version();
  void name();
  void version();
  void known_command();
  void list_commands();
  void quit();
  void boardsize();
  void clear_board();
  void komi();
  void play();
  void genmove();
  void kgs_genmove_cleanup();
  void unknown_command();
  void showboard();
  void fixed_handicap();
  void level();
  void time_settings();
  void kgs_time_settings();
  void time_left();
  void final_score();
  void final_status_list();
  
  enum {PROTOCOL_VERSION, NAME, VERSION, KNOWN_COMMAND, LIST_COMMANDS,
        QUIT, BOARDSIZE, CLEAR_BOARD, KOMI, PLAY, GENMOVE, SHOWBOARD,
        FIXED_HANDICAP, LEVEL,TIME_SETTINGS, TIME_LEFT, FINAL_SCORE,
        FINAL_STATUS_LIST, KGS_TIME_SETTINGS, KGS_GENMOVE_CLEANUP, NCOMMANDS};

  const std::string COMMANDS[NCOMMANDS]=
        {"protocol_version","name","version","known_command","list_commands",
         "quit","boardsize","clear_board","komi","play","genmove","showboard",
         "fixed_handicap","level","time_settings","time_left","final_score",
         "final_status_list","kgs-time_settings", "kgs-genmove_cleanup"};
      
  int parse(const std::string&);
  int string_to_cmd(const std::string&);
  int char_to_color(std::string&);
  int char_to_coordinate(std::string&);
  void print_coordinate(int);
  
public:
  GTP();
  int GTP_loop();
  int exec();
  void perft(int);
};

#endif
