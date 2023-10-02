#include <ctime>
#include "gtp.h"
#include "zobrist.h"
#include "engine.h"

int main()
{

  //srand(unsigned(time(NULL)));
  init_genrand64(16669666165875248481ULL);

  GTP gtp;
  //gtp.perft(100000);
  gtp.GTP_loop();
  return 0;
}