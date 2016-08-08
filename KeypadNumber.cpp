#include "Arduino.h"
#include "KeypadNumber.h"

KeypadNumber::KeypadNumber()
{
  reset();
}

void KeypadNumber::reset()
{
  this->_digits[0] = 0;
  this->_digits[1] = 0;  
  this->_digits[2] = 0;
  this->_index = 0;
}

void KeypadNumber::addDigit(int digit)
{
  if(digit < 0 || digit > 9)
    return;
  
  if(this->_index < NDIGITS-1)
  {
    this->_digits[this->_index] = (byte)digit;
    this->_index++;
  }
}

int KeypadNumber::getLength()
{
  return this->_index+1;
}

int KeypadNumber::getNumber()
{
  int i, num=0;
  for(i = this->_index; i >= 0; i--)
  {
    num += this->_digits[i] * pow(10, i);
  }

  return num;
  
}


