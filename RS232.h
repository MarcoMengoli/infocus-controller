#ifndef RS232_H
#define RS232_H

  #include "Arduino.h"
  #include <SoftwareSerial.h>
  
  class RS232
  {
    public:
      RS232(int pinTx, int pinRx, int baudrate=115200);
      ~RS232();
      void writeRequest(String mess);
      String readResponse();
  
    private:
      int _pinTx;
      int _pinRx;
      SoftwareSerial* _swSerial;
  };

#endif
