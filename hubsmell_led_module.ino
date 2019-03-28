#include <AM2320.h>

int cds = A0; //조도센서 Analog 0
int cds_led = 2; //조도센서 LED Digital 2

AM2320 dht;
int dht_high_led = 3; //온습도센서 온도 높을때 LED Digital 3 
int dht_low_led = 4; //온습도센서 온도 낮을때 LED Digital 4

int soil_moisture = A1; //토양 수분센서 Analog 1
int soil_moisture_led = 5; //토양 수분센서 LED Digital 5

int on_off_led = 6; //on/off LED Digital 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(cds_led, OUTPUT);

  dht.begin();
  pinMode(dht_high_led, OUTPUT);
  pinMode(dht_low_led, OUTPUT);

  pinMode(soil_moisture_led, OUTPUT);

  pinMode(on_off_led, OUTPUT);
}

void loop() {
  int cds_value = analogRead(cds); //조도센서로 측정된 밝기 값 가져옴.
  float temp_value = dht.getTemperature();
  int soil_value = analogRead(soil_moisture);

  Serial.print("cds = ");
  Serial.println(cds_value);

  /**
   * 조도 센서에 따른 LED 상태
   */
  if(cds_value < 450){
    digitalWrite(cds_led, HIGH);
  }
  else{
    digitalWrite(cds_led, LOW);
  }

  /**
   * 온습도 센서에 따른 LED 상태
   */
  if (dht.measure()) {
    Serial.print("Temperature: ");
    Serial.println(dht.getTemperature());
    Serial.print("Humidity: ");
    Serial.println(dht.getHumidity());

    if(dht.getTemperature() >= 30){
      digitalWrite(dht_high_led, HIGH);
      digitalWrite(dht_low_led, LOW);
    }
    else if(dht.getTemperature() < 28){
      digitalWrite(dht_low_led, HIGH);
      digitalWrite(dht_high_led, LOW);
    }
    else{
      digitalWrite(dht_high_led, LOW);
      digitalWrite(dht_low_led, LOW);
    }
  }
  else {  // error has occured
    int errorCode = dht.getErrorCode();
    switch (errorCode) {
      case 1: Serial.println("ERR: Sensor is offline"); break;
      case 2: Serial.println("ERR: CRC validation failed."); break;
    }    
  }

  /**
   * 토양 수분 센서에 따른 LED 상태
   */
   Serial.print("soil : ");
   Serial.println(soil_value);

   if(soil_value > 500){
    digitalWrite(soil_moisture_led, HIGH);
   }
   else{
    digitalWrite(soil_moisture_led, LOW);
   }

  digitalWrite(on_off_led, HIGH);
  
  delay(1000);
}
