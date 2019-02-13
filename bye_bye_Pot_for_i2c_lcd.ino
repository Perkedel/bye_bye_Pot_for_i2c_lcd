#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //original, multiple: original, New, SR.
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//by JOELwindows7
//Perkedel Technologies
//GNU GPL v3

/*
 * With I2C, no need Pot. potentiometer is built in on the I2C backpack itself!
 * you can use leftover potentiometer out as a part of your programming.
 * no longer just sit on behind the scene for LCD contrast.
 * 
 * If your LCD is blank, turn the small blue square pot with screwdriver, until the display is well looking.
 * that's how to set contrast.
 * 
 * You cannot turn backlight dim however. you need some other mechanic.
 * https://stackoverflow.com/questions/49086184/how-do-i-dim-the-backlight-on-an-20x4-lcd-display-with-the-i2c-connected-on-an-a
 * this is because the backlight is based on transistor on that I2C LCD.
 * 
 * that's succ.
 * 
 * Joel wants to make better I2C breakout that adds dimmer.
 * though it needs different library from JOEL. LiquidCrystal_I2C_Perkedel.h yes.
 * don't worry, it is compatible with original LiquidCrystal_I2C.h library for compatibility reason. backlight still ON and OFF no dim.
 */

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  lcd.init(); lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Bye Pot! for I2C");
  Serial.begin(56700);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(String("Potval = ") + String(analogRead(A0)) + String("x   ")); 
  //untouched cell will retain its cell value. use empty character after the potval number to clear out cell. otherwise, it will have frozen weird looking reading!
  Serial.println(String("Potval = ") + String(analogRead(A0)) + String("x   "));
}
