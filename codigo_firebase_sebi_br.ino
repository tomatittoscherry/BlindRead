#include <WiFi.h>
#include "FirebaseESP32.h"

#define WIFI_SSID "Fibertel WiFi270 2.4GHz"
#define WIFI_PASSWORD "01426583072"
#define API_KEY "AIzaSyBG39wWL0MsEmhTjeGLkF9bbe6GcjQsAQU"
#define DATABASE_URL "https://blind-read-app-fb-default-rtdb.firebaseio.com/"

//#define PIN_SENSOR 15
//#define PIN_PULSADOR 2
//int boton;

FirebaseData firebaseData;

//int count = 0;
bool signupOK = false;

#include <SPI.h>
#include <Wire.h>  
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17
#define BTN_PIN 25


Adafruit_MLX90614 mlx = Adafruit_MLX90614();



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


float temperatura;

#define CANTIDAD_MEDICIONES 1000


void setup() {
  Serial.begin(9600);
  Serial.println("siii");
  //Serial.println(sensorProbar);
  //pinMode(PIN_PULSADOR, INPUT_PULLUP);

  Serial.begin(115200);
  pinMode(BTN_PIN,INPUT_PULLUP);
  if(!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  

  
  display.clearDisplay();
  display.display();
  delay(1000);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,28);
  display.println("Blind Read");
  display.display();

//    delay(1000);

  //display.println(temperatura);
 // display.display();
}

void loop()
{
     if(!digitalRead(BTN_PIN)){
    for(int i = 0; i < CANTIDAD_MEDICIONES; i++)
    temperatura += mlx.readObjectTempC(); // temperatura = temperatura + mlx.readObjectTempC();

    temperatura = temperatura / CANTIDAD_MEDICIONES;

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5,10);
    display.println("Temperatura actual:");
    display.print(temperatura);
    display.display();
    delay(5000);
    display.clearDisplay();
    display.display();
  }
  else{
   float ay =  mlx.readObjectTempC();
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      Serial.print("Connecting to Wi-Fi");
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
      }
      Serial.println(" ");
      Firebase.begin(DATABASE_URL, API_KEY);
      Firebase.reconnectWiFi(true);
      
//      Firebase.setInt(firebaseData, "/test/int", count);
      Firebase.setFloat(firebaseData, "/test/float",temperatura);
}
