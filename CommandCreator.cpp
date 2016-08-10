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
  static String secondLineOnOff[1] = {"0 off   1 on"};
  static String secondLine0_100step1[1] = {"0:100,1"};
  static String secondLineAspectRatio[7] = {"0  Auto", "1  Nativo", "2  4:3", "3  16:9", "4  Letterbox", "5  Panorama", "6  16:10"};
  
  
  static ProjCommand commands[N_COMMANDS] = 
    { 
        ProjCommand("Zoom ALLARGA", "MZI", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Zoom STRINGI", "MZO", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Fuoco AVANTI", "MFF", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Fuoco INDIETRO", "MFN", CommandType::ONE, 1, 1, 1, secondLineOneControl, 1),
        ProjCommand("Aspetto", "ARZ", CommandType::CHOICE, 0, 6, 1, secondLineAspectRatio, 7),
        ProjCommand("Luminosita", "BRT", CommandType::RANGE, 0, 100, 1, secondLine0_100step1, 1),
        ProjCommand("Contrasto", "CON", CommandType::RANGE, 0, 100, 1, secondLine0_100step1, 1),
        ProjCommand("Accensione", "PWR", CommandType::ZERO_ONE, 0, 1, 1, secondLineOnOff, 1)
    };

  return commands;
}


int getNumberOfCommands()
{
  return N_COMMANDS;
}

String fill16chars(String str)
{
  return fillNchars(str, 16);
}

String fillNchars(String str, int n)
{
  int len = str.length();
  
  if (len == n)
    return str;
    
  if(len > n)
    return str.substring(0,n);
  
  for(int i = 0; i < n-len; i++)
  {
    str += " ";
  }

  return str;
}

