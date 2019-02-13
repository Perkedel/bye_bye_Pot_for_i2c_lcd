#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //original, multiple: original, New, SR.
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//by JOELwindows7
//Perkedel Technologies
//GNU GPL v3

/* Connect LCD I2C!
 * https://www.arduino.cc/en/Reference/Wire
 *   Unit = Arduino Pin (Connect to)
 *  Uno, Ethernet = A4 (SDA), A5 (SCL)
    Mega2560 = 20 (SDA), 21 (SCL)
    Leonardo = 2 (SDA), 3 (SCL)
    Due = 20 (SDA), 21 (SCL), SDA1, SCL1
 * 
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
 * 
 * Credits:
 * https://stackoverflow.com/questions/49086184/how-do-i-dim-the-backlight-on-an-20x4-lcd-display-with-the-i2c-connected-on-an-a
 * 
 * Excerpt of Example Arduino LED Blink no delay is from File > Examples > 02.Digital > BlinkWithoutDelay
 * 
 * https://www.arduino.cc/en/Serial/Begin baud rate explanation
 */

//Begin LED Blink no delay
// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
//const long interval = 1000;           // interval at which to blink (milliseconds)
//End LED Blink no delay

long interval = 1000; //nope. no const interval. we'll edit this to pot value.

String LCDcleanup = String("x    ");

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(ledPin, OUTPUT);
  lcd.init(); lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Bye Pot! for I2C");
  Serial.begin(2000000); //56700 is default favourite. however if you want to fast, consider the following performance workload first.
  //i don't fell taste of 2 million baud rate goes that fast. guess it's like radio frequency or something...
  //I see. https://www.arduino.cc/en/Serial/Begin the MEGA has feature to multi-serial. you can have different baud rate for different kinda frequency/
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(String("Potval = ") + String(analogRead(A0)) + String(LCDcleanup)); 
  //untouched cell will retain its cell value. use empty character after the potval number to clear out cell. otherwise, it will have frozen weird looking reading!
  Serial.println(String("Potval = ") + String(analogRead(A0)) + String(LCDcleanup));

  interval = analogRead(A0); //yeah, boai!!!
  
  //Begin LED Blink no delay
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  //End LED Blink no delay

  if(ledState == HIGH){
    LCDcleanup = String("x    ");
  } else if(ledState == LOW) {
    LCDcleanup = String("     ");
  }

  //Since there is no delay, the Arduino workflow becomes much more efficient.
  /*
   * However though, there is caveat! prgramming may becomes complex due to how people were used to delay(int value);.
   * depending on your Arduino edition, they are quite fast without delay.
   * it taste almost like any other computer, it works fast.
   * 
   * If you are making computerized scene, you are obligated to avoid delay, unless for stability troubleshooting reason.
   * this way, you will not feeling any hiccup at all, as the sub-task done asyncronously.
   */
}
