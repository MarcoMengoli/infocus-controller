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
void showSecondLineOnDisplay();
void showNextSecondLineOnDisplay();


// ############# KEYPAD INIT start
#define pinArd_keypad1 3
#define pinArd_keypad2 4
#define pinArd_keypad3 5
#define pinArd_keypad4 6
#define pinArd_keypad5 7
#define pinArd_keypad6 8
#define pinArd_keypad7 9
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
#define pinArd_swSerialRx 11
#define pinArd_swSerialTx 12
RS232 ser = RS232(pinArd_swSerialRx, pinArd_swSerialTx);
// ############# RS232 INIT end

// ############# PROJCOMMANDS INIT start
ProjCommand* commands;
int currentCommand;
int currentSecondLine;
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
  currentCommand = 0;
  currentSecondLine = 0;
  
  showCommandOnDisplay(0);
  
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
  }
  else if( !(buttons & 0x08))  
  {
    Serial.println("SX");
  }
    
  delay(100);

  // keypad (numbers and *,#
  //char key = keypad.getKey();
  
}

void keypadEvent(KeypadEvent key)
{
  if (keypad.getState() == PRESSED)
  {
    switch (key)
    {
      case '#':
        // OK, send the number
        Serial.println("#");
        ser.writeRequest(getRequestString());
        break;
      case '*':
        Serial.println("*"); break;
      default:
        keyNum.addDigit(key);
        break;
    }    
  }
}


String getRequestString()
{
  return "";
}

void showCommandOnDisplay(int dir)
{
  int nCommands = getNumberOfCommands();

  if(dir == 0)
  {
    currentCommand = 0;
  }
  else if(dir > 0)
  {
    currentCommand = (currentCommand == nCommands-1 ? 0 : currentCommand+1);
  }
  else
  {
    currentCommand = (currentCommand == 0 ? nCommands : currentCommand-1);
  }
  currentSecondLine = 0;
  

  showFirstLineOnDisplay();
  showSecondLineOnDisplay();
}

void showFirstLineOnDisplay()
{
  lcd.lcdClear();
  
  lcd.lcdGoToXY(1,1);
  Serial.println("FIRST LINE: " + String(fill16chars(commands[currentCommand].getName()).length()));
  lcd.lcdWrite((char*)fill16chars(commands[currentCommand].getName()).c_str(), false);
}

void showSecondLineOnDisplay()
{  
  
  lcd.lcdGoToXY(1,2);
  lcd.lcdWrite((char*)fill16chars(commands[currentCommand].getSecondLineFromIndex(currentSecondLine)).c_str(), false);
}

void showNextSecondLineOnDisplay()
{  
  lcd.lcdGoToXY(0,2);
  int totSecondLine = commands[currentCommand].getNumberOfSecondLines();
  currentSecondLine++;
  currentSecondLine = currentSecondLine % totSecondLine;
  
  showSecondLineOnDisplay();
}

