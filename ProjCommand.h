#ifndef PROJCOMMAND_H
#define PROJCOMMAND_H

  #include "Arduino.h"

  typedef enum { ZERO_ONE, CHOICE, RANGE, ONE } CommandType;
  
  class ProjCommand
  {
    public:
      ProjCommand(String commandName, String commandCode, CommandType type, int minRange, int maxRange, int stepRange, String* secondLine, int secondLineSize);

      String getName();
      String getCode();
      String* getSecondLineVector();
      String getSecondLineFromIndex(int index);
      int getMin();
      int getMax();
      int getStep();
      
    private:
      String _name;
      String _command;
      CommandType _type;
      
      String* _secondLine;
      int _secondLineSize;
      
      int _min;
      int _max;
      int _step;
  };

#endif
