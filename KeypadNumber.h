#ifndef KEYPADNUMBER_H
#define KEYPADNUMBER_H

  #include "Arduino.h"

  #define NDIGITS 3
  
  class KeypadNumber
  {
    public:
      KeypadNumber();
      void reset();
      void addDigit(int digit);
      int getNumber();
      int getLength();
      int getMaxNumberOfDigits();
  
    private:
      int _digits[NDIGITS];
      int _index;
  };

#endif
