#include "Arduino.h"
#include "MapFloat.h"

#define BT_InPin 34
int sensorValue;          
float calibration = 0.16; 
float bat_percentage;
float BT=0;

void setup() 
        {
        Serial.begin(115200);
        }

void loop() 
        {        
        BT = BT_Cal();
        delay(100); 
        Serial.print(F("BT = "));   
        Serial.print(BT); 
        Serial.println("%");  
        delay(2000); 
        }


float BT_Cal()
          {
B_Rep:    int BTS=0;
          for(int bt=0;bt<10;bt++)
                {
                sensorValue = analogRead(BT_InPin);
                delay(10);
                Serial.print("sensorValue = "); Serial.println(sensorValue);
                BTS = BTS + sensorValue;                
                }
          sensorValue = BTS /10;   
          
          Serial.print("sensor Total Value = "); Serial.println(sensorValue);

          float voltage = (((sensorValue*3.3)/4095)*2 + calibration);
          Serial.print("Battery Voltage = ");
          Serial.print(voltage);
          Serial.println(" V");
          
          //2.8V as Battery Cut off Voltage & 3.6V as Maximum Voltage for Lifepo4
          bat_percentage = mapFloat(voltage, 2.8, 3.6, 0, 100); 
          
          if(bat_percentage < 100)
                {
                return bat_percentage;  
                }else goto B_Rep;
          }      
