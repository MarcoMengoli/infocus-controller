#ifndef COMMANDCREATOR_H
#define COMMANDCREATOR_H

  #include "ProjCommand.h"

  #define N_COMMANDS 8

  ProjCommand* createArrayOfCommands();
  int getNumberOfCommands();

  
  String fill16chars(String str);
  String fillNchars(String str, int n);

#endif
