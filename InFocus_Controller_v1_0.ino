#include <Keypad.h>
#include "KeypadNumber.h"
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


void showCommandOnDisplay();

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
// ############# PROJCOMMANDS INIT end

void setup()
{
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  keypad.setHoldTime(1200);               // Default is 1000mS
  keypad.setDebounceTime(50);           // Default is 50mS

  Serial.println("STARTED");

  commands = createArrayOfCommands();
  currentCommand = 0;

  
}

void loop()
{
  char key = keypad.getKey();
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

void showCommandOnDisplay()
{
  
}

