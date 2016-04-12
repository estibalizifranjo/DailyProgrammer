#include <iostream>
#include <fstream>

/******************************************************************************/
/******************************* CHALLENGE 260 ********************************/
/******************************************************************************/

enum DoorStates {
  doorClosed,
  doorOpen,
  doorClosing,
  doorOpening,
  stopWhileOpening,
  stopWhileClosing
};

enum Inputs { button_clicked, cycle_complete };

static DoorStates automata[6][2] = {
    /*                      button_clicked,    cycle_complete */
    /* doorClosed,       */ {doorOpening, doorClosed},
    /* doorOpen,         */ {doorClosing, doorOpen},
    /* doorClosing,      */ {stopWhileClosing, doorClosed},
    /* doorOpening,      */ {stopWhileOpening, doorOpen},
    /* stopWhileOpening, */ {doorClosing, stopWhileOpening},
    /* stopWhileClosing  */ {doorOpening, stopWhileClosing}};

const char* toString(DoorStates state) {
  switch (state) {
  case doorClosed:
    return "Door closed";
  case doorOpen:
    return "Door open";
  case doorClosing:
    return "Door closing";
  case doorOpening:
    return "Door opening";
  case stopWhileClosing:
    return "Stop while closing";
  case stopWhileOpening:
    return "Stop while opening";
  }
}

void move(DoorStates &currentState, Inputs input) {
  currentState = automata[currentState][input];
  std::cout << toString(currentState) << std::endl;
}

void printInput(Inputs input) {
  switch (input) {
  case Inputs::button_clicked:
    std::cout << " > Button clicked" << std::endl;
    break;
  case Inputs::cycle_complete:
    std::cout << " > Cycle complete" << std::endl;
    break;
  }
}

int main(int argc, char *argv[]) {
  std::ifstream fileStream(argv[1]);
  if (!fileStream) {
    std::cerr << "ERROR while opening file";
    exit(-1);
  }

  DoorStates currentState = doorClosed;
  std::string line;

  while (fileStream >> line) {
    Inputs input;
    if (line == "button_clicked") {
      input = Inputs::button_clicked;
    } else {
      input = Inputs::cycle_complete;
    }
    printInput(input);
    move(currentState, input);
  }

  return 0;
}
