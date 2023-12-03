// instalation des differents Librairies 
#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
unsigned long delayTime;
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 16


Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
int led = 11;
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif


#define PIN        6 

#define NUMPIXELS 16 


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 


void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

    if (! bme.begin(0x77, &Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Default Test --");
    Serial.println("normal mode, 16x oversampling for all, filter off,");
    Serial.println("0.5ms standby period");
    delayTime = 5000;
    
  Serial.println("OLED FeatherWing test");
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 

  Serial.println("OLED begun");
  display.display();
  delay(1000);

  //  buffer
  display.clearDisplay();
  display.display();

  Serial.println("IO test");
  
  pixels.begin();
 

 
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.display(); 






  // les display 
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Connecting to SSID\n'adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0,0);
  display.display(); 
  display.clearDisplay();
}

void loop() {
  digitalWrite(led,HIGH);                 
  int valCapteur = analogRead (A0);
  valCapteur = map (valCapteur, 0, 1023, 0, 255);
  Serial.println(valCapteur);
  analogWrite (led,valCapteur);
 
 display.setCursor(0,0);
  printValues();
  display.display(); 
  display.clearDisplay();
  
  


    pixels.clear(); 

    for (int i = 0; i < NUMPIXELS; i++) {
      if (bme.readTemperature() < 20)
       {pixels.setPixelColor(i, pixels.Color(0, 255, 0));
        
       }
      else if ((bme.readTemperature() > 20)&& (bme.readTemperature()< 30))
       {pixels.setPixelColor(i, pixels.Color( 250, 127, 0));
          
       }
      else
       {pixels.setPixelColor(i, pixels.Color(255, 0, 0));
         
       }
    pixels.show();
    delay(DELAYVAL);
    
        
    }
  pixels.clear();
  pixels.show();
}
void printValues() {
    display.print("Temp = ");
    display.print(bme.readTemperature());
    display.println(" *C");

    display.print("Pres = ");

    display.print(bme.readPressure() / 100.0F);
    display.println(" hPa");

    display.print("Alti = ");
    display.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    display.println(" m");

    display.print("Hum = ");
    display.print(bme.readHumidity());
    display.println(" %");
    display.println();
}
