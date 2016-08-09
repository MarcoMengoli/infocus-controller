#include "Arduino.h"
#include "ProjCommand.h"
#include "CommandCreator.h"


/* ProjCommand constructor:
*   String commandName, String commandCode, CommandType type
*   int minRange, int maxRange, int stepRange
*   String* secondLine, int secondLineSize
*/


  
ProjCommand* createArrayOfCommands()
{
  
  static String secondLineOneControl[1] = {"# per eseguire"};
  
  static ProjCommand commands[N_COMMANDS] = { ProjCommand("Zoom ALLARGA", "MZI", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Zoom STRINGI", "MZO", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Fuoco AVANTI", "MFF", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Fuoco INDIETRO", "MFN", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1) };

  for( int i = 0; i < N_COMMANDS; i++)
  {
    Serial.println(String(i) + " - " + commands[i].getCode());
  }


  return commands;
}


int getNumberOfCommands()
{
  return N_COMMANDS;
}

String fill16chars(String str)
{
  str.concat("                ");
  return str.substring(0, 16);
}

