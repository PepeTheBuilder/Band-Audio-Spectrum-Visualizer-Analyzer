// #include <AltSoftSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

#define RX 0
#define TX 1

#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION "0.6.6"
#define MODE_LED_BEHAVIOUR "MODE"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

int LL = 0, LM = 0, MM = 0, MH = 0, HH = 0;
////TODO: make the cotrol work aka main loop and findout why SoftwareSerial.h doesn't work

#define PIN 9
#define NUMPIXELS 128
#define INTENSITY 5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int llow[24] = {};
int lmed[24] = {};
int mmed[24] = {};
int mhigh[24] = {};
int hhigh[24] = {};



void setup() {
  Serial.begin(9600);
  pixels.begin();  // This initializes the NeoPixel library.
  BasicSetup();
}

void loop() {
  // if (bluetoothSerial.available()) {
  //   String data = bluetoothSerial.readStringUntil('\n');  // Read until newline character
  //   parseAndSendData(data);
  // }
  // dummyControl();
  Chat();
}

void dummyControl() {

  matrixForm(1, llow);
  matrixForm(5, lmed);
  matrixForm(3, mmed);
  matrixForm(6, mhigh);
  matrixForm(3, hhigh);
  delay(10);
  lightThemUp();

  matrixForm(0, llow);
  matrixForm(2, lmed);
  matrixForm(4, mmed);
  matrixForm(1, mhigh);
  matrixForm(7, hhigh);
  delay(10);
  lightThemUp();
}

void parseAndSendData(String data) {
  // Parse the input data into separate frequency bands
  int ll, lm, mm, mh, hh;
  sscanf(data.c_str(), "%d %d %d %d %d\n", &ll, &lm, &mm, &mh, &hh);

  // Print the parsed data to the serial monitor
  Serial.print("LL: ");
  Serial.println(ll);
  Serial.print("LM: ");
  Serial.println(lm);
  Serial.print("MM: ");
  Serial.println(mm);
  Serial.print("MH: ");
  Serial.println(mh);
  Serial.print("HH: ");
  Serial.println(hh);

  matrixForm(ll, llow);
  matrixForm(lm, lmed);
  matrixForm(mm, mmed);
  matrixForm(mh, mhigh);
  matrixForm(hh, hhigh);
  delay(10);
  lightThemUp();

}

void matrixForm(int freq, int* vector) {
  for (int i = 0; i < 24; i++)
    vector[i] = 0;

  switch (freq) {
    case 0:
      vector[11] = INTENSITY;
      vector[12] = INTENSITY;
      return;
    case 1:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;
      return;
    case 2:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;

      vector[10] = INTENSITY;
      vector[13] = INTENSITY;
      return;
    case 3:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;

      vector[10] = INTENSITY;
      vector[13] = INTENSITY;

      vector[9] = INTENSITY;
      vector[14] = INTENSITY;

      vector[2] = INTENSITY;
      vector[18] = INTENSITY;
      vector[5] = INTENSITY;
      vector[21] = INTENSITY;
      return;
    case 4:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;

      vector[10] = INTENSITY;
      vector[13] = INTENSITY;

      vector[9] = INTENSITY;
      vector[14] = INTENSITY;

      vector[2] = INTENSITY;
      vector[18] = INTENSITY;
      vector[5] = INTENSITY;
      vector[21] = INTENSITY;
      return;
    case 5:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;

      vector[10] = INTENSITY;
      vector[13] = INTENSITY;

      // vector[9]=INTENSITY;
      // vector[14]=INTENSITY;

      vector[2] = INTENSITY;
      vector[18] = INTENSITY;
      vector[5] = INTENSITY;
      vector[21] = INTENSITY;

      vector[8] = INTENSITY;
      vector[15] = INTENSITY;

      return;
    case 6:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;

      vector[10] = INTENSITY;
      vector[13] = INTENSITY;

      vector[9] = INTENSITY;
      vector[14] = INTENSITY;

      vector[2] = INTENSITY;
      vector[18] = INTENSITY;
      vector[5] = INTENSITY;
      vector[21] = INTENSITY;

      vector[8] = INTENSITY;
      vector[15] = INTENSITY;

      return;
    case 7:
      vector[3] = INTENSITY;
      vector[11] = INTENSITY;
      vector[19] = INTENSITY;
      vector[4] = INTENSITY;
      vector[12] = INTENSITY;
      vector[20] = INTENSITY;

      vector[10] = INTENSITY;
      vector[13] = INTENSITY;

      vector[9] = INTENSITY;
      vector[14] = INTENSITY;

      vector[2] = INTENSITY;
      vector[18] = INTENSITY;
      vector[5] = INTENSITY;
      vector[21] = INTENSITY;

      vector[8] = INTENSITY;
      vector[15] = INTENSITY;

      vector[1] = INTENSITY;
      vector[6] = INTENSITY;
      vector[17] = INTENSITY;
      vector[22] = INTENSITY;

      return;
    default:
      vector[11] = INTENSITY;
      vector[12] = INTENSITY;
      return;
  }
}

int howLight(int pos) {
  if (pos < 24) return llow[pos];
  else if (pos < 48) return lmed[pos - 24];
  else if (pos < 72) return mmed[pos - 48];
  else if (pos < 96) return mhigh[pos - 72];
  else if (pos < 120) return hhigh[pos - 96];
  else
    return 0;
}

void lightThemUp() {

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

    int intens = howLight(i);
    if (intens == 0) {
      pixels.setPixelColor(i, pixels.Color(0, 0, INTENSITY));
    } else {
      pixels.setPixelColor(i, pixels.Color(INTENSITY, 0, 0));  // Moderately bright red color.
    }
    pixels.show();  // This sends the updated pixel color to the hardware.
  }
  delay(500);
}

void Chat() {
  // Check for user input
  char inputs[BUFSIZE + 1];

  if (getUserInput(inputs, BUFSIZE)) {
    // Send characters to Bluefruit
    Serial.print("[Send] ");
    Serial.println(inputs);

    ble.print("AT+BLEUARTTX=");
    ble.println(inputs);

    // check response status
    if (!ble.waitForOK()) {
      Serial.println(F("Failed to send?"));
    }
  }

  // Check for incoming characters from Bluefruit
  ble.println("AT+BLEUARTRX");
  ble.readline();
  if (strcmp(ble.buffer, "OK") == 0) {
    // no data
    return;
  }

  // Some data was found, store it in a char array
  char receivedData[BUFSIZE + 1];
  strncpy(receivedData, ble.buffer, BUFSIZE);
  receivedData[BUFSIZE] = '\0';

  Serial.print(F("[Recv] "));
  Serial.println(receivedData);
  parseAndSendData(receivedData);
  ble.waitForOK();
}
bool getUserInput(char buffer[], uint8_t maxSize) {
  // timeout in 100 milliseconds
  TimeoutTimer timeout(100);

  memset(buffer, 0, maxSize);
  while ((!Serial.available()) && !timeout.expired()) { delay(1); }

  if (timeout.expired()) return false;

  delay(2);
  uint8_t count = 0;
  do {
    count += Serial.readBytes(buffer + count, maxSize);
    delay(2);
  } while ((count < maxSize) && (Serial.available()));

  return true;
}
void BasicSetup() {
  while (!Serial)
    ;  // required for Flora & Micro
  delay(500);


  Serial.println(F("Adafruit Bluefruit Project"));
  Serial.println(F("---------------------------------------"));

  Serial.print(F("Initialising the Bluefruit LE module: "));

  if (!ble.begin(VERBOSE_MODE)) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println(F("OK!"));

  if (FACTORYRESET_ENABLE) {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if (!ble.factoryReset()) {
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter 5 different neubers to send to Bluefruit"));
  Serial.println();
  while (!ble.isConnected()) {
    delay(500);
  }
  if (ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION)) {
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }
  ble.verbose(false);  // debug info is a little annoying after this point!
}
// A small helper
void error(const __FlashStringHelper* err) {
  Serial.println(err);
  while (1)
    ;
}