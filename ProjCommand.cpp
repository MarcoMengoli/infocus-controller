#include "Arduino.h"
#include "ProjCommand.h"

ProjCommand::ProjCommand(String commandName, String commandCode, CommandType type, int minRange, int maxRange, int stepRange, String* secondLine, int secondLineSize)
{
  this->_name = commandName;
  this->_command = commandCode;
  this->_type = type;

  this->_secondLine = secondLine;
  this->_secondLineSize = secondLineSize;
  
  this->_min = minRange;
  this->_max = maxRange;
  this->_step = stepRange;
}


String ProjCommand::getName()
{
  return this->_name;
}
String ProjCommand::getCode()
{
  return this->_command;
}

String* ProjCommand::getSecondLineVector()
{
  return this->_secondLine;
}
String ProjCommand::getSecondLineFromIndex(int index)
{
  if (index >= 0 && index < this->_secondLineSize)
  {
    return this->_secondLine[index];
  }
}
int ProjCommand::getMin()
{
  return this->_min;
}
int ProjCommand::getMax()
{
  return this->_max;
}
int ProjCommand::getStep()
{
  return this->_step;
}

