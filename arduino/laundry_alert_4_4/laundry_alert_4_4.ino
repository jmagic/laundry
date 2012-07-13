/* Laundry Alert

----------------------------------------------------

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------
*/

int washerlightPin = 0;  //define a pin for Photo resistor this reads the washers on/off light
int dryerlightPin = 1;   //same for dryer
int washerledPin = 11;   //define a LED pin for indicator in living room
int dryerledPin = 12;    //same for dryer
int buttonPin = 7; // reset button to clear alerts

int fast_alert_length = 15; //number of seconds to flash fast (initial indication to get your attention)
int slow_alert_length = 5;  //number of seconds between slow flash (continue to indicate but dont be annoying)
int inByte = 0;         // incoming serial byte

int lastwasherState = 0;    // used to store old status
int lastdryerState = 0;     // same as washer
int alert = 0;
int lastalert = 5;  // used to store alert status alert 00 is all off ; alert 01 is washer on; alert 10 is dryer on; alert 11 all on
int washerState = 0;  // stores actual status (probably redundant could just measure at the time)
int dryerState = 0;   // same for dryer
int buttonState = 0;  // same for button
unsigned long dryer_time = 0;  // used to track how long the light has been flashing
unsigned long washer_time = 0; // same as dryer
unsigned long dryer_slow = 0;  // timing for flashes
unsigned long washer_slow = 0; // same

void setup()
{
    Serial.begin(9600);  //Begin serial communcation
    pinMode( washerledPin, OUTPUT );
    pinMode( dryerledPin, OUTPUT );
    pinMode( buttonPin, INPUT );
    //Serial.println("Welcome to the laundry_alert");
    //digitalWrite( buttonPin, HIGH);
}

void get_input() // read all values and set the status (could be eliminated)
  {
       
    if (analogRead(washerlightPin) >= 200)
      { 
        washerState = 1;
      }
    else
      { 
        washerState = 0;
      }
    if (analogRead(dryerlightPin) >= 200)
      { 
        dryerState = 1;
      }
    else
      { 
        dryerState = 0;
      }
    buttonState = digitalRead(buttonPin);
  } 


int flash_it(int flashPin) //flash the indicator for the dryer or the washer
{
  /*Serial.print("Flashpin:");
  Serial.println(flashPin);
  Serial.print("millis:");
  Serial.println((millis()/1000)); //*/
  
  digitalWrite(flashPin, HIGH);
  delay(100);
  digitalWrite(flashPin, LOW);
  delay(100);
}

void flash_wash() //flash the washer either fast or slow depending on how long its been on (i think this could be combined with the dryer)
{
   if ((millis() - washer_time) <= (fast_alert_length * 1000))  // flash fast
  {
    flash_it(washerledPin);
    washer_slow = millis();
   // Serial.println("washer_flash");
  }
  if ((millis() - washer_slow) >= (slow_alert_length * 1000)) // flash slow
  {
    flash_it(washerledPin);
    washer_slow = millis();
  //  Serial.println("washer_flash");
  }
}

void flash_dry() //same as washer
{
  if ( (millis() - dryer_time) <= (fast_alert_length * 1000))
  {
    flash_it(dryerledPin);
    dryer_slow  = millis();
   // Serial.println("dryer_flash");
  }
  if ( (millis() - dryer_slow) >= (slow_alert_length * 1000))
  {
    flash_it(dryerledPin);
    dryer_slow  = millis();
    //Serial.println("dryer_flash");
  }
}
void sound()  //flash the appropiate lights
{
    //testing 
    //alert = 11;
    if (alert == 11)
     
     {
        flash_wash();
        flash_dry();
     }
     
    if (alert == 10 )
      {
        flash_dry();
      }
      
    if (alert == 1)
      {
        flash_wash();
      }  
    }

void send_serial() {
    switch (alert) {
        case 0: 
          Serial.print(0);
          break;
        case 1: 
          Serial.print(1);
          break;
        case 10:
          Serial.print(2);
          break; 
        case 11:
          Serial.print(3);
          break; 
          }
        }
void setAlert(int check) 
  {
    if (alert != 1 and alert != 11 and check == 1)
    {
      alert = alert + 1;
    }
    if (alert != 10 and alert != 11 and check == 10)
    {
      alert = alert + 10;
    }   
  }

void loop()
{
    
    get_input();
    //Serial.println(analogRead(washerlightPin));
    //delay(1000);
    if (Serial.available() >= 1) {
      inByte = Serial.read();
      if (inByte == 'R'){
        alert = 0;
      } 
      if (inByte == 'T'){
          //Serial.print("got a T");
          washerState = 1;
          dryerState = 1;
      }
      if (inByte == 'S'){
          send_serial();
      }
    }     
      //Serial.print(alert);
      //Serial.print(old_alert);  
      if (alert != lastalert) {
        lastalert = alert;
        send_serial();
      }
      
      /* check the old status vs the new status.
      this is due to the way the washer works.  
      If light is off, and then it turns on = the washer is starting
      light is on, then it turns off = the washer is finished and it is time to indicate 
      if they are the same then ignore*/
    
    
    if (washerState !=  lastwasherState)
     {    
      
        if (lastwasherState == 1)
         {
          setAlert(1);
          washer_time = millis();
          lastwasherState = 0;
         }
        if (alert == 1 or alert == 11)
         {
           alert = alert - 1;
           lastwasherState = 1;
         }
        if (lastwasherState == 0)
         {
          lastwasherState = 1;
         }
          
      }   
     if (dryerState !=  lastdryerState)     
      { 
        if (lastdryerState == 1)
         {
          setAlert(10);
          dryer_time = millis();
          lastdryerState = 0;
         }
        if (alert == 10 or alert == 11)
         {
           alert = alert - 10;      
           lastdryerState = 1;
         }
        if (lastdryerState == 0)
         {
          lastdryerState = 1;
         }
      }  
     
   /*if ((digitalRead(buttonPin)) == 0)
     {
        alert = 0;
        washer_time = 0;
        dryer_time = 0;
     } */
     //Serial.println(digitalRead(buttonPin));
     //if (alert != 0)
     //{
       sound();
     //}
     
   delay(10); //short delay helps with light sensors
}
