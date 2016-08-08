#ifndef PROJCOMMAND_H
#define PROJCOMMAND_H

  #include "Arduino.h"
  #include "ProjCommand.h"

  \* constructor:
  *   String commandName, String commandCode, CommandType type
  *   int minRange, int maxRange, int stepRange
  *   String* secondLine, int secondLineSize
  *\
  
  ProjCommand commands[4];
  String secondLineOneControl[] = {"# per eseguire"};

  
  commands[0] = ProjCommand("Zoom ALLARGA", "MZI", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1);
  commands[1] = ProjCommand("Zoom STRINGI", "MZO", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1);
  commands[2] = ProjCommand("Fuoco AVANTI", "MFF", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1);
  commands[3] = ProjCommand("Fuoco INDIETRO", "MFN", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1);
 
 
 
 
 int minRange, int maxRange, int stepRange, 
 ;



#endif
