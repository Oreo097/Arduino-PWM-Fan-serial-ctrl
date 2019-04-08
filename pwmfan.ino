#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define YLED 03
#define RLED 02
#define SPKR 04
#define FAN1 10
#define FAN2 11
#define OLED_RESET 05

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

int temp = 0;
char info[5] = {"t000f"};
int commu();
int ctrl();
int freq = 0;

Adafruit_SSD1306 display(OLED_RESET);

/*const unsigned char PROGMEM logo32[] =
{0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xF0,0xF0,0xE0,0xE0,0xC0,0xC0,0xFF,
0xFF,0xC0,0xC0,0xE0,0xE0,0xF0,0xF0,0xFF,0xFF,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x1F,0x1F,0x0F,0x0F,0x07,0x07,0x03,0x03,0xFF,
0xFF,0x03,0x03,0x07,0x07,0x0F,0x0F,0xFF,0xFF,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF};*/

void setup()
{
  pinMode(YLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(SPKR, OUTPUT);
  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);

  digitalWrite(YLED, LOW);
  digitalWrite(RLED, HIGH);
  digitalWrite(SPKR, LOW);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  /*display.drawBitmap(0,32,logo32,32,32,WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();*/
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("H.tStudios");
  display.display();
  delay(2000);
  while (!Serial)
  {
    ;
  }
  Serial.print("start");
  display.display();
  while (Serial.read() != 's')
  {
    ;
  }
  Serial.println("done");
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("START");
  display.display();

  digitalWrite(RLED, HIGH);
  digitalWrite(SPKR, HIGH);
  delay(100);
  digitalWrite(YLED, LOW);
  digitalWrite(RLED, LOW);
  digitalWrite(SPKR, LOW);
  delay(100);
  display.clearDisplay();
  display.println(info);
  display.display();
  Serial.println(info);
}

void loop()
{
  digitalWrite(RLED, HIGH);
   display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(info);
    display.println(freq);
    display.display();
  commu();
  ctrl();
}

int commu()
{
  char a;
  a = Serial.read();
  delay(2);
  if (a == 't')
  {
    info[0] = a;
    digitalWrite(YLED, HIGH);
    for (int i = 1; i < 6; i++)
    {
      info[i] = Serial.read();
      Serial.println(info[i]);
      delay(2);
    }
    Serial.println(info);
   
}
}
int ctrl()
{
  switch (info[4])
  {
  case 'a':
    freq = 255;
    break;
  case 'b':
    freq = 200;
    break;
  case 'c':
    freq = 150;
    break;
  case 'd':
    freq = 100;
    break;
  case 'e':
    freq = 50;
    break;
  case 'f':
    freq = 0;
    break;
  default:
    Serial.println("?");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("unkonwn data");
    display.display();
    digitalWrite(SPKR,HIGH);
    delay(500);
    digitalWrite(SPKR,LOW);
  }
  analogWrite(FAN1, freq);
  analogWrite(FAN2, freq);
  digitalWrite(YLED, LOW);
}

/*void showlogo(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  srandom(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random() % display.width();
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random() % 5 + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
	icons[f][XPOS] = random() % display.width();
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random() % 5 + 1;
      }
    }
   }
}*/
