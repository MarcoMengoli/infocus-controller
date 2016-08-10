#include "Arduino.h"
#include "KeypadNumber.h"

KeypadNumber::KeypadNumber()
{
  reset();
}

void KeypadNumber::reset()
{
  for(int i = 0; i < NDIGITS; i++)
    this->_digits[i] = 0;
  
  this->_index = 0;
}

void KeypadNumber::addDigit(int digit)
{
  if(digit < 0 || digit > 9)
    return;

  if (this->_index == NDIGITS)
    this->_index = 0;
  
  if(this->_index < NDIGITS)
  {
    this->_digits[this->_index] = (byte)digit;
    this->_index++;
  }

  for(int i = 0; i < NDIGITS; i++)
    Serial.println("this->_digits[" + String(i) + "]: " + String(this->_digits[i]));
}

int KeypadNumber::getLength()
{
  return this->_index;
}

int KeypadNumber::getNumber()
{
  int num=0;
  for(int i = 0; i < this->_index; i++)
  {
    int mult = 1;
    for(int j = 0; j < this->_index-i-1; j++)
    {
      mult = mult * 10;
    }
    num += this->_digits[i] * mult;
  }

  return num;
  
}

int KeypadNumber::getMaxNumberOfDigits()
{
  return NDIGITS;
}


