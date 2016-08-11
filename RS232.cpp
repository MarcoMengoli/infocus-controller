#include "Arduino.h"
#include "RS232.h"
#include <SoftwareSerial.h>


RS232::RS232(int pinTx, int pinRx, int baudrate)
{
  this->_pinTx = pinTx;
  this->_pinRx = pinRx;
  this->_swSerial = new SoftwareSerial(pinRx, pinTx);
  this->_swSerial->begin(baudrate);
}

RS232::~RS232()
{
  if (NULL != this->_swSerial)
  {
    delete this->_swSerial;
  }
}

void RS232::writeRequest(String mess)
{
  if (NULL != this->_swSerial)
  {
    this->_swSerial->print(mess);
  }
}

String RS232::readResponse()
{
  String response="";

  if (NULL != this->_swSerial)
  {
    
    while (this->_swSerial->available())
    {
      response += this->_swSerial->readString();
      delay(10);
    }
  }
  
  return response;
}

String RS232::waitResponse(int timeout)
{
  String response = "";
  int start = millis();

  if (NULL != this->_swSerial)
  {
    while ((this->_swSerial->available() || response=="") && (start + timeout) <= millis())
    {
      response += this->_swSerial->readString();
      delay(10);
    }
  }

  return response;
}

void RS232::cleanBuffer()
{
  while (this->_swSerial->available())
  {
    this->_swSerial->readString();
  }
}


