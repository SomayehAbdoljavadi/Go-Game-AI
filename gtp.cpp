#include <sstream> 
#include <iostream> 
#include <algorithm>
#include "gtp.h" 
#include "size.h"

using namespace std;
  
GTP::GTP():go_engine(&main_goban)
{
  early_pass = true;
}

int GTP::GTP_loop()
{
  
#ifdef LOG
  std::string filename = "log";
  filename.append(PROGVERSION);
  filename.append(".txt");
  engine_log.open(filename);
#endif
  loop = true;
  while (loop && getline(cin, command_string)) {
#ifdef LOG
    engine_log << command_std::string;
    engine_log.flush();
#endif
    parse(command_string);  
    exec();
  }
#ifdef LOG
  engine_log.close();
#endif
  return 0;
}

int GTP::parse(const std::string &command_str)
{  
  std::stringstream auxstream(command_str);
  std::string auxstring;
  float auxint;
  int id;
  cmd_args.clear();
  cmd_int_args.clear();
  
  //TODO: findfirstof(#) and eliminate
  //TODO: handle empty lines
  
  auxstream >> auxstring;
  std::stringstream tempstream(auxstring);
  
  if (tempstream >> id) {
    //TODO:handle negative IDs??
    cmd_id = auxstring;
    cmd_id.append(" ");
    auxstream >> cmd_name;
  } else {
    cmd_id = " ";
    cmd_name = auxstring;
  }
  
  cmd = string_to_cmd(cmd_name);
  
  while (auxstream.good()) {
    auxstream >> auxstring;
    cmd_args.insert(cmd_args.end(), auxstring);
    
    tempstream.clear(); //!!!!
    tempstream.str(auxstring);
    tempstream >> auxint;
    cmd_int_args.insert(cmd_int_args.end(), auxint);
  }
  return 0;
}

int GTP::exec(){
  response = "=";
  response.append(cmd_id);
  
  switch (cmd) {
    case PROTOCOL_VERSION:
      protocol_version();
      break;
    case NAME:
      name();
      break;
    case VERSION:
      version();
      break;
    case KNOWN_COMMAND:
      known_command();
      break;
    case LIST_COMMANDS:
      list_commands();
      break;
    case QUIT:
      quit();
      break;
    case BOARDSIZE:
      boardsize();
      break;
    case CLEAR_BOARD:
      clear_board();
      break;
    case KOMI:
      komi();
      break;
    case PLAY:
      play();
      break;
    case GENMOVE:
      genmove();
      break;
    case SHOWBOARD:
      showboard();
      break;
    case FIXED_HANDICAP:
      fixed_handicap();
      break;
    case LEVEL:
      level();
      break;
    case TIME_SETTINGS:
      time_settings();
      break;
    case TIME_LEFT:
      time_left();
      break;
    case FINAL_SCORE:
      final_score();
      break;
    case FINAL_STATUS_LIST:
      final_status_list();
      break;
    case KGS_TIME_SETTINGS:
      kgs_time_settings();
      break;
    case KGS_GENMOVE_CLEANUP:
      kgs_genmove_cleanup();
      break;
    default:
      unknown_command();
      break;
  }
  response.append("\n\n");
  std::cout << response;
  
#ifdef LOG
  engine_log << response;
  engine_log.flush();
#endif
  return 0;
}

int GTP::string_to_cmd(const std::string &command_str)
{
  for (int cmd = 0; cmd < NCOMMANDS; cmd++) {
    if (!command_str.compare(COMMANDS[cmd])) {
      return cmd;
    }
  }
  return -1;
}

int GTP::char_to_color(std::string &color)
{
  transform(color.begin(), color.end(), color.begin(), ::tolower);
  
  if (!color.compare("white") || !color.compare("w")) return 1;
  else {
    if (!color.compare("black") || !color.compare("b")) return 0;
    else return -1;
  }
}

int GTP::char_to_coordinate(std::string &coordinate)
{
  int coord;
  transform(coordinate.begin(), coordinate.end(), coordinate.begin(), ::toupper);
  
  if (!coordinate.compare("PASS")) return 0;
  
  std::stringstream auxstream(coordinate.substr(1,2));
  if (auxstream >> coord && coord <= main_goban.get_size()) {
    coord = (coord - 1)*main_goban.get_size();
  } else {
      return -1;
  }
  
  for (int i = 0; i < main_goban.get_size(); i++) {
    if (coordinate[0] == COORDINATES[i]) {
      coord += i+1;
      return coord;
    }
  }
  return -1;
}

void GTP::print_coordinate(int coord)
{
  if (coord == -1) {
    response.append("resign");
  } else {
    coord_to_char(coord, response, main_goban.get_size());
  }
}

void GTP::perft(int max)
{
  clock_t t = clock();
  go_engine.perft(max);
  t = clock() - t;
  float ts = (float)t/CLOCKS_PER_SEC;
  std::cerr << "Finish " << ts << ":" << max/ts << "pps.\n";
}
