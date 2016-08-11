#include "Arduino.h"
#include "KeypadNumber.h"

KeypadNumber::KeypadNumber()
{
  reset();
}

void KeypadNumber::reset()
{
  for(int i = 0; i < this->_maxDigits; i++)
    this->_digits[i] = 0;
  
  this->_index = 0;
}

void KeypadNumber::addDigit(int digit)
{
  if(digit < 0 || digit > 9)
    return;

  if (this->_index == this->_maxDigits)
  {
    this->reset();
  }
  
  if(this->_index < this->_maxDigits)
  {
    this->_digits[this->_index] = digit;
    this->_index++;
  }

  for(int i = 0; i < this->_maxDigits; i++)
    Serial.println("this->_digits[" + String(i) + "]: " + String(this->_digits[i]));
}

int KeypadNumber::getLength()
{
  return this->_index;
}

int KeypadNumber::getNumber()
{
  if (this->_index == 0)
    return -1;
    
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
  return this->_maxDigits;
}


void KeypadNumber::setValue(int num)
{
  String s = String(num);
  this->reset();
  for(int i = 0; i < s.length() || i < this->_maxDigits; i++)
  {
    this->_digits[this->_index] = s[i];
    this->_index++;
  }
}


void KeypadNumber::setMaxNumberOfDigits(int nDigits)
{
  if (nDigits > 0 && nDigits <= NDIGITS)
    this->_maxDigits = nDigits;
}
void KeypadNumber::setMaxNumberOfDigitsByMaxValue(int maxValue)
{
  String s = String(maxValue);
  this->setMaxNumberOfDigits(s.length());
}
      

