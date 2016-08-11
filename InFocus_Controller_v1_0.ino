#include <Wire.h>
#include <LCD16x2.h>
#include <Keypad.h>
#include "KeypadNumber.h"
#include "ProjCommand.h"
#include "CommandCreator.h"
#include "RS232.h"

/*
 * author: Marco Mengoli
 * version: 1.0
 * name: InFocus_Controller_v1_0
 * 
 * Keypad:
 *    pin1 -> col2 (Central col)
 *    pin2 -> row1 (First row)
 *    pin3 -> col1 (First col)
 *    pin4 -> row4 (Last row)
 *    pin5 -> col3 (Last col)
 *    pin6 -> row3 (Third row)
 *    pin7 -> row2 (Second row)
 */


void showCommandOnDisplay(int dir);
void showFirstLineOnDisplay();
void showSecondLineOnDisplay(int dir);
boolean isNewValueCorrect();
void notifyError();

#define pinError 11
#define pinWait 12
#define pinOk 13

#define timeLedOkOn 800

// ############# KEYPAD INIT start
#define pinArd_keypad1 2
#define pinArd_keypad2 3
#define pinArd_keypad3 4
#define pinArd_keypad4 5
#define pinArd_keypad5 6
#define pinArd_keypad6 7
#define pinArd_keypad7 8
#define ROWS 4 //four rows
#define COLS 3 //three columns
char keys[ROWS][COLS] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
        };
byte rowPins[ROWS] = {pinArd_keypad2, pinArd_keypad7, pinArd_keypad6, pinArd_keypad4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {pinArd_keypad3, pinArd_keypad1, pinArd_keypad5}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
// ############# KEYPAD INIT END

// ############# PRESSEDNUMBERS INIT start
KeypadNumber keyNum = KeypadNumber();
// ############# PRESSEDNUMBERS INIT end


// ############# RS232 INIT start
#define pinArd_swSerialRx 9
#define pinArd_swSerialTx 10
RS232 ser = RS232(pinArd_swSerialRx, pinArd_swSerialTx);
// ############# RS232 INIT end

// ############# PROJCOMMANDS INIT start
ProjCommand* commands;
int currentCommand;
int currentSecondLine;
int currentIntValue;
String secLine; // must be global to be visibile by some functions
// ############# PROJCOMMANDS INIT end


// ############# LCD INIT start
LCD16x2 lcd;
// ############# LCD INIT end


// ############# 4 BUTTONS INIT start
int buttons;
// ############# 4 BUTTONS INIT end


void setup()
{
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  keypad.setHoldTime(1200);               // Default is 1000mS
  keypad.setDebounceTime(150);           // Default is 50mS

  Serial.println("STARTED");

  Wire.begin();
  lcd.lcdClear();

  commands = createArrayOfCommands();

  currentIntValue = -1;
  currentCommand = 0;
  
  showCommandOnDisplay(0);

  pinMode(pinOk, OUTPUT);
  pinMode(pinWait, OUTPUT);
  pinMode(pinError, OUTPUT);
}

void loop()
{
  // the 4 buttons of the LCD
  buttons = lcd.readButtons();
  
  if( !(buttons & 0x01))
  {
    Serial.println("DOWN");
    showCommandOnDisplay(+1);
  }
  else if( !(buttons & 0x02)) 
  { 
    Serial.println("UP");
    showCommandOnDisplay(-1);
  }
  else if( !(buttons & 0x04))
  {
    Serial.println("DX");
    showSecondLineOnDisplay(-1);
  }
  else if( !(buttons & 0x08))  
  {
    Serial.println("SX");
    showSecondLineOnDisplay(+1);
  }

  if (Serial.available())
  {
    currentIntValue = Serial.readString().toInt();
    showSecondLineOnDisplay(1);
  }

  // keypad (numbers and *,#)
  char key = keypad.getKey();
    
  delay(10);
  
}

void keypadEvent(KeypadEvent key) // KeypadEvent IS A CHAR!
{
  if (keypad.getState() == PRESSED)
  {
    switch (key)
    {
      case '#':
        // OK, send the number
        //Serial.println("#");
        digitalWrite(ledWait, HIGH);
        if (isNewValueCorrect())
        {
          ser.writeRequest(createCommandWriteString());
          Serial.println(createCommandWriteString());

          // wait for the response, or at least a minimum time to perform another # (InFocus documentation suggests about 3 seconds)
          lcd.lcdClear();delay(30);showCommandOnDisplay(0);delay(30);lcd.lcdClear();delay(30);showCommandOnDisplay(0);
          
        }
        else
        {
          Serial.println("ERROR!!");
          digitalWrite(ledWait, LOW);
          notifyError();
          showCommandOnDisplay(0);
        }
        
        break;
      case '*':
        currentIntValue = millis()%100;
        showSecondLineOnDisplay(0);
        //Serial.println("*"); break;
      default:
        int k = key-'0'; // conversion char to int
        //Serial.println(String(k));
        keyNum.addDigit(k);
        //Serial.println("Keypad number: " + String(keyNum.getNumber()) + ", length: " + String(keyNum.getLength()) );
        showSecondLineOnDisplay(0);
        break;
    }    
  }
}


String createCommandWriteString()
{
  int currentNum = keyNum.getNumber();
  String cmd = "(" + commands[currentCommand].getCode();
  String choiceVal;
  int spaceIndex;
  switch(commands[currentCommand].getType())
  {
    case CommandType::ONE:
      cmd += "1";
      break;
    case CommandType::ZERO_ONE:
      cmd += String(currentNum);
        break;
    case CommandType::RANGE:
      cmd += String(currentNum);
        break;
    case CommandType::CHOICE:
      spaceIndex = secLine.indexOf(" ");
      cmd += secLine.substring(0, spaceIndex);
  }

  return cmd + ")";
}

void showCommandOnDisplay(int dir)
{
  lcd.lcdClear();
  keyNum.reset();
  currentIntValue = -1;
  int nCommands = getNumberOfCommands();

  if(dir > 0)
  {
    currentCommand = (currentCommand == nCommands-1 ? 0 : currentCommand+1);
  }
  else if(dir < 0)
  {
    currentCommand = (currentCommand == 0 ? nCommands-1 : currentCommand-1);
  }
  
  showFirstLineOnDisplay();
  currentSecondLine = 0;
  showSecondLineOnDisplay(0);
}

void showFirstLineOnDisplay()
{
  lcd.lcdGoToXY(1,1);
  //Serial.println("FIRST  LINE: " + String(fill16chars(commands[currentCommand].getName())));
  lcd.lcdWrite((char*)fill16chars(commands[currentCommand].getName()).c_str(), false);
}


void showSecondLineOnDisplay(int dir)
{
  if(dir != 0)
  {
    int totSecondLine = commands[currentCommand].getNumberOfSecondLines();

    if( dir > 0)
    {
      currentSecondLine = (currentSecondLine == totSecondLine-1 ? 0 : currentSecondLine+1);
    }
    else
    {
      currentSecondLine = (currentSecondLine == 0 ? totSecondLine-1 : currentSecondLine-1);
    }
  }
  

  secLine = commands[currentCommand].getSecondLineFromIndex(currentSecondLine);
  //Serial.println("SECOND LINE (cur): " + secLine);

  if(commands[currentCommand].getType() == CommandType::RANGE)
  {
    
    secLine = fillNchars(secLine, 7);
    //Serial.println("SECOND LINE (fill): " + secLine);
    secLine.concat(" ");
    
    if (currentIntValue >= 0 )
    {
      secLine.concat(String(currentIntValue));
    }
    
    if (keyNum.getLength() > 0)
    {
      String num = String(keyNum.getNumber());
      secLine.concat("->"+num);

      for(int j = 0; j < keyNum.getMaxNumberOfDigits()-num.length(); j++)
      {
        secLine.concat("_");
      }
    }
  }
  
  secLine = fillNchars(secLine, 16);
  
  //Serial.println("SECOND LINE (next): " + secLine);
  
  lcd.lcdGoToXY(1,2);

  lcd.lcdWrite((char*)secLine.c_str(), false);
}

boolean isNewValueCorrect()
{
  int currentNum = keyNum.getNumber();
  int stepVal, remain, floorValue, ceilValue;
  switch(commands[currentCommand].getType())
  {
    case CommandType::ONE: return true;
    case CommandType::CHOICE: return true;
    case CommandType::ZERO_ONE: if (currentNum == 0 || currentNum == 1) return true; else return false;
    case CommandType::RANGE:
      stepVal = commands[currentCommand].getStep(); 
      if (currentNum < commands[currentCommand].getMin() || currentNum > commands[currentCommand].getMax())
        return false;

      remain = currentNum % stepVal;
      if (remain == 0)
        return true;

      floorValue = ((int)(currentNum / stepVal)) * stepVal;
      ceilValue = ((int)(currentNum / stepVal)+1) * stepVal;
      
      if (ceilValue - currentNum <= currentNum - floorValue)
      {
         keyNum.setValue(ceilValue);
      }
      else
      {
        keyNum.setValue(floorValue);
      }

      return true;

  }
  
}


void notifyError()
{  
  digitalWrite(pinError, HIGH);
  delay(50);
  digitalWrite(pinError, LOW);
  delay(50);
  digitalWrite(pinError, HIGH);
  delay(50);
  digitalWrite(pinError, LOW);
  delay(50);
  digitalWrite(pinError, HIGH);
  delay(50);
  digitalWrite(pinError, LOW);
  delay(50);
}

