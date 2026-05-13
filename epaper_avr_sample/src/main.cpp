#include <Arduino.h>
#include <SPI.h>
#include <SPIFlash.h>

/*
W25Q128FVSG          Arduino ATmega328
CS (Pin 1)     →     Pin 6 (FLASH_CS)
DO (Pin 2)     →     Pin 12 (MISO)
WP (Pin 3)     →     VCC (3.3V)
GND (Pin 4)    →     GND
DI (Pin 5)     →     Pin 11 (MOSI)
CLK (Pin 6)    →     Pin 13 (SCK)
HOLD (Pin 7)   →     VCC (3.3V)
VCC (Pin 8)    →     3.3V (regulated)

GDEY075T7	        Function	      ATmega328 Pin	         Your Code
Pin 4	            CLK	            Pin 13 (SCK)	         Standard SPI
Pin 5	            MOSI (DIN)	    Pin 11 (MOSI)	         Standard SPI
Pin 6	            MISO (DO)	      Pin 12 (MISO)	         Standard SPI
Pin 7	            CS	            Pin 10	               EPD_CS
Pin 8	            DC	            Pin 8	                 EPD_DC
Pin 9	            RST	            Pin 9	                 EPD_RST
Pin 10	          BUSY	          Pin 7	                 EPD_BUSY
Pin 2, 12	        IOVCC	          3.3V (regulated)	     Power
Pin 1, 3, 11	    GND	            GND	                   Ground

ATmega328          E-Paper (GDEY075T7)   Flash (W25Q128FVSG)
Pin 11 (MOSI)  →   Pin 5 (DIN)      &    Pin 5 (DI)
Pin 12 (MISO)  →   Pin 6 (DO)       &    Pin 2 (DO)
Pin 13 (SCK)   →   Pin 4 (CLK)      &    Pin 6 (CLK)
Pin 10 (CS)    →   Pin 7 (CS)
Pin 6 (CS)     →                         Pin 1 (CS)
*/

// Pin definitions for e-paper display (adjust as per your wiring)
#define EPD_CS 10
#define EPD_DC 8
#define EPD_RST 9
#define EPD_BUSY 7

// Pin definition for SPI flash
#define FLASH_CS 6

// E-paper dimensions (for 7.5" waveshare: 800x480)
#define EPD_WIDTH 800
#define EPD_HEIGHT 480

// Font bitmap size (16x16 pixels, 32 bytes per character)
#define FONT_WIDTH 16
#define FONT_HEIGHT 16
#define BYTES_PER_CHAR (FONT_WIDTH * FONT_HEIGHT / 8)  // 32 bytes

// SPIFlash instance
SPIFlash flash(FLASH_CS);

// Custom e-paper functions
void epdSendCommand(uint8_t command) {
  digitalWrite(EPD_DC, LOW);
  digitalWrite(EPD_CS, LOW);
  SPI.transfer(command);
  digitalWrite(EPD_CS, HIGH);
}

void epdSendData(uint8_t data) {
  digitalWrite(EPD_DC, HIGH);
  digitalWrite(EPD_CS, LOW);
  SPI.transfer(data);
  digitalWrite(EPD_CS, HIGH);
}

void epdWaitBusy() {
  while (digitalRead(EPD_BUSY) == HIGH) {
    delay(10);
  }
}

void epdReset() {
  digitalWrite(EPD_RST, LOW);
  delay(10);
  digitalWrite(EPD_RST, HIGH);
  delay(10);
  epdWaitBusy();
}

void epdInit() {
  pinMode(EPD_CS, OUTPUT);
  pinMode(EPD_DC, OUTPUT);
  pinMode(EPD_RST, OUTPUT);
  pinMode(EPD_BUSY, INPUT);

  epdReset();

  // Initialization commands for 7.5" waveshare (800x480)
  epdSendCommand(0x01); // Driver output control
  epdSendData((EPD_HEIGHT - 1) & 0xFF);
  epdSendData(((EPD_HEIGHT - 1) >> 8) & 0xFF);
  epdSendData(0x00);

  epdSendCommand(0x0C); // Booster soft start
  epdSendData(0xD7);
  epdSendData(0xD6);
  epdSendData(0x9D);

  epdSendCommand(0x2C); // Write VCOM register
  epdSendData(0xA8);

  epdSendCommand(0x3A); // Set dummy line period
  epdSendData(0x1A);

  epdSendCommand(0x3B); // Set gate time
  epdSendData(0x08);

  epdSendCommand(0x11); // Data entry mode
  epdSendData(0x03);
  
  epdSendCommand(0x3C); // Border waveform control
  epdSendData(0x80);
}

void epdClear() {
  epdSendCommand(0x24); // Write RAM
  for (int i = 0; i < EPD_WIDTH * EPD_HEIGHT / 8; i++) {
    epdSendData(0xFF);
  }
  epdSendCommand(0x22); // Display update control
  epdSendData(0xC4);
  epdSendCommand(0x20); // Master activation
  epdWaitBusy();
}

void epdDrawBitmap(const uint8_t* bitmap, int x, int y, int w, int h) {
  // Simplified: assume bitmap is 1-bit, and draw at position
  // For full implementation, need to handle partial bytes, etc.
  // This is a basic version; for text, it works if aligned.

  epdSendCommand(0x24); // Write RAM
  // Set RAM address
  epdSendCommand(0x4E); // RAM X address start
  epdSendData(x / 8);
  epdSendCommand(0x4F); // RAM Y address start
  epdSendData(y & 0xFF);
  epdSendData((y >> 8) & 0xFF);

  // Send bitmap data (assuming w*h/8 bytes)
  for (int i = 0; i < w * h / 8; i++) {
    epdSendData(bitmap[i]);
  }
}
// Set partial window for partial updates (coordinates in pixels)
void epdSetPartialWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  // Define the area for partial update
  epdSendCommand(0x90);  // Partial display refresh configuration
  epdSendData((x / 8) & 0xFF);
  epdSendData(((x + w) / 8) & 0xFF);
  epdSendData(y & 0xFF);
  epdSendData((y >> 8) & 0xFF);
  epdSendData((y + h) & 0xFF);
  epdSendData(((y + h) >> 8) & 0xFF);
  epdSendData(0x00);
}
// Full render - complete refresh (slower, but clean display)
void epdFullUpdate() {
  epdSendCommand(0x22);  // Display update control
  epdSendData(0xC4);      // Full update mode
  epdSendCommand(0x20);  // Master activation
  epdWaitBusy();
}

// Partial render - update only changed region (faster, may cause ghosting)
void epdPartialUpdate() {
  epdSendCommand(0x22);  // Display update control
  epdSendData(0xCF);      // Partial update mode
  epdSendCommand(0x20);  // Master activation
  epdWaitBusy();
}

// Generic update function (defaults to full update)
void epdUpdate(bool fullRefresh = true) {
  if (fullRefresh) {
    epdFullUpdate();
  } else {
    epdPartialUpdate();
  }
}

// Function to read bitmap for a character from flash
void readCharBitmap(char c, uint8_t* buffer) {
  uint32_t address = (uint32_t)(c - ' ') * BYTES_PER_CHAR;  // Assuming ASCII starting from space
  flash.readBytes(address, buffer, BYTES_PER_CHAR);
}

// Function to draw text on e-paper
void drawText(const char* text, int x, int y) {
  int cursorX = x;
  int cursorY = y;
  for (int i = 0; text[i] != '\0'; i++) {
    uint8_t bitmap[BYTES_PER_CHAR];
    readCharBitmap(text[i], bitmap);
    epdDrawBitmap(bitmap, cursorX, cursorY, FONT_WIDTH, FONT_HEIGHT);
    cursorX += FONT_WIDTH;
    // Handle line wrapping if needed
  }
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  
  // Initialize SPI flash
  if (!flash.initialize()) {
    Serial.println("SPI Flash initialization failed!");
    while (1);
  }
  Serial.println("SPI Flash initialized.");
  
  // Initialize e-paper display
  epdInit();
  epdClear();
  drawText("Hello World!", 10, 10);
  epdUpdate();
}

void loop() {
  // Nothing to do in loop for this example
}