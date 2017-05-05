#include "brain.h"

class Scanner {

  public:
    Scanner();
    int track(int pointer, int value);
    int moveTo;
    Brain brain;

    int average();
    
  private:
    void reset();
    int followDirection;
    int checkCount = 0;
};

