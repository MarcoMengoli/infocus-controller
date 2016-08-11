#ifndef KEYPADNUMBER_H
#define KEYPADNUMBER_H

  #include "Arduino.h"

  #define NDIGITS 10

  class KeypadNumber
  {
    public:
      KeypadNumber();
      void reset();
      void addDigit(int digit);
      int getNumber();
      int getLength();
      int getMaxNumberOfDigits();
      void setMaxNumberOfDigits(int nDigits);
      void setMaxNumberOfDigitsByMaxValue(int maxValue);
      void setValue(int num);
      
    private:
      int _digits[NDIGITS];
      int _index;
      int _maxDigits;
  };

#endif
