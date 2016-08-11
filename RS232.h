#ifndef RS232_H
#define RS232_H

  #include "Arduino.h"
  #include <SoftwareSerial.h>
  
  class RS232
  {
    public:
      RS232(int pinTx=9, int pinRx=10, int baudrate=115200);
      ~RS232();
      void writeRequest(String mess);
      String readResponse();
      String waitResponse(int timeout = 5000);
      void cleanBuffer();
  
    private:
      int _pinTx;
      int _pinRx;
      SoftwareSerial* _swSerial;
  };

#endif
