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
  
    private:
      byte _digits[NDIGITS];
      byte _index;
  };

#endif
