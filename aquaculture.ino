// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_BMP085.h>

 
 Servo myServo;
int l1 = D6;
int led = D7;
int l2 = D2;
int r1 = D3;
int r2 = D4;
Adafruit_BMP085 bmp;

void setup()
{
    myServo.attach(A4);
   pinMode(l1, OUTPUT);
   pinMode(l2, OUTPUT);
   pinMode(r1, OUTPUT);
   pinMode(r2, OUTPUT);
   pinMode(led, OUTPUT);

   Particle.function("led",BotControl);
   
   myServo.write(120);
   digitalWrite(led,HIGH);
   // Nothing to do here
   Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	  while(1) Particle.process();
  }
}


void loop()
{
   
  
  Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    Serial.println();
    delay(500);
     char sensorInfo[64];
     Serial.println(sensorInfo);
    sprintf(sensorInfo, "Temperature=%.2f °C, Pressure=%.2f hPa", bmp.readTemperature(), bmp.readPressure());
    Particle.publish("PhotonTemp", sensorInfo,PRIVATE);
   
}



int BotControl(String command) {
   
    if (command=="WaterPumpInletOn") {
        digitalWrite(l1,HIGH);
        return 1;
    }
    else if (command=="WaterPumpInletOff") {
        digitalWrite(l1,LOW);
        return 1;
    }
    else if (command=="WaterPumpOutletOn") {
        digitalWrite(l2,HIGH);
        return 1;
    }
    else if (command=="WaterPumpOutletOff") {
        digitalWrite(l2,LOW);
        return 1;
    }
    else if (command=="FreshWaterPump") {
                
        digitalWrite(l1,HIGH);
        digitalWrite(l2,HIGH);
        digitalWrite(led,HIGH);

        return 1;
    }
    else if (command=="STOP"){
        digitalWrite(l1,LOW);
        digitalWrite(l2,LOW);
        digitalWrite(led,LOW);
        return 0;
    }
    else if (command=="FeederON"){
        digitalWrite(led,HIGH);
        myServo.write(180);
        delay(20);
        return 1;
    }
    else if (command=="FeederOFF"){
        digitalWrite(led,LOW);
        myServo.write(0);
        delay(20);
        return 1;
    }
    else {
       return -1;
    }
}
