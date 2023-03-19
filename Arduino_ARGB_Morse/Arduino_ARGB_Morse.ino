#include <Adafruit_NeoPixel.h>

//** Define according to your hardware
#define PIN            6 // Define the pin to which the data port of the LED strip is connected. Don't forget to put a 370 ohm resistor in between.
#define LED_COUNT      144 // Define the absolute number of LEDs
#define REVERSE        true // Reverse direction when set to true

//** Adafruit_NeoPixel - Please don't change anything
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

//** Customization of the morse code display
uint16_t firstPixelIndex = 0; // For example, if your first pixel is not visible, set firstPixelIndex to 1
uint16_t lastPixelIndex = LED_COUNT - 1; // 'LED_COUNT - 1' is the index of the last pixel. If this value is reduced, correspondingly more pixels will be left out at the end.
// Colors
uint32_t fgColor = strip.Color(0, 0, 255); // Foreground color
uint32_t bgColor = strip.Color(0, 0, 0); // Background color
// Spaces
uint8_t spaceSignals = 2; // Pixels spacing between signals
uint8_t spaceLetters = 4; // Pixels spacing between letters
uint8_t spaceWords = 8; // Pixels spacing between words
// Delays
uint16_t delayDit = 100; // Higher delay makes the show slower
uint16_t delayLines = 2000; // Delay before new line (when there are not enough LEDs for the next signal)

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Turn off all LEDs

  Serial.println(F("Write a text that should be output as morse code"));
}

void loop() {
  if (Serial.available() > 0) {
    // Get the text from serial
    String text = Serial.readStringUntil('\n');

    // First, print back the text on the serial monitor
    Serial.println(text);

    // Convert the text to Morse code
    String morseCode = convertToMorseCode(text);

    // Show Morse code
    displayMorseCode(morseCode);
  }
}

String convertToMorseCode(String message) {
  String morseCode = "";
  message.toUpperCase(); // convert message to uppercase
  for (int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    switch (c) {
      case 'A': morseCode += ".- "; break;
      case 'B': morseCode += "-... "; break;
      case 'C': morseCode += "-.-. "; break;
      case 'D': morseCode += "-.. "; break;
      case 'E': morseCode += ". "; break;
      case 'F': morseCode += "..-. "; break;
      case 'G': morseCode += "--. "; break;
      case 'H': morseCode += ".... "; break;
      case 'I': morseCode += ".. "; break;
      case 'J': morseCode += ".--- "; break;
      case 'K': morseCode += "-.- "; break;
      case 'L': morseCode += ".-.. "; break;
      case 'M': morseCode += "-- "; break;
      case 'N': morseCode += "-. "; break;
      case 'O': morseCode += "--- "; break;
      case 'P': morseCode += ".--. "; break;
      case 'Q': morseCode += "--.- "; break;
      case 'R': morseCode += ".-. "; break;
      case 'S': morseCode += "... "; break;
      case 'T': morseCode += "- "; break;
      case 'U': morseCode += "..- "; break;
      case 'V': morseCode += "...- "; break;
      case 'W': morseCode += ".-- "; break;
      case 'X': morseCode += "-..- "; break;
      case 'Y': morseCode += "-.-- "; break;
      case 'Z': morseCode += "--.. "; break;
      case '0': morseCode += "----- "; break;
      case '1': morseCode += ".---- "; break;
      case '2': morseCode += "..--- "; break;
      case '3': morseCode += "...-- "; break;
      case '4': morseCode += "....- "; break;
      case '5': morseCode += "..... "; break;
      case '6': morseCode += "-.... "; break;
      case '7': morseCode += "--... "; break;
      case '8': morseCode += "---.. "; break;
      case '9': morseCode += "----. "; break;
      case '?': morseCode += "..--.. "; break;
      case '!': morseCode += "-.-.-- "; break;
      case '.': morseCode += ".-.-.- "; break;
      case ',': morseCode += "--..-- "; break;
      case ';': morseCode += "-.-.-. "; break;
      case ':': morseCode += "---... "; break;
      case '+': morseCode += ".-.-. "; break;
      case '-': morseCode += "-....- "; break;
      case '/': morseCode += "-..-. "; break;
      case '=': morseCode += "-...- "; break;
      case ' ': morseCode += "/"; break; // use forward slash for space
      default: break; // ignore other characters
    }
  }
  return morseCode;
}

bool pixelStateBuffer[LED_COUNT];
uint16_t pixelIndex = firstPixelIndex;
void displayMorseCode(String morseCode) {
  // Set all LEDs to bgColor
  strip.fill(bgColor);
  strip.show();

  // Reset pixelIndex to the index of the first pixel
  pixelIndex = firstPixelIndex;

  // Run through all characters of the morse code ('morseCode.length() - 1' because the last char of a sequence is '\0')
  for (int i = 0; i < morseCode.length() - 1; i++) {
    // Get a 'char' from the next character in morse code
    char c = morseCode.charAt(i);

    // Print the character on the serial monitor
    Serial.print(c);

    // Check that it's not the last char
    bool isNotLastChar = i < morseCode.length() - 2; // '- 2' because the last char of a sequence is '\0'

    // Show the char on the strip
    switch (c) {
      case '.': // turn on LED for dot (short flash)
        setPixelOnIndex(1, true);
        if (isNotLastChar)
          setPixelOnIndex(spaceSignals, false);
        delay(delayDit);
        break;
      case '-': // turn on LED for dash (long flash)
        setPixelOnIndex(3, true);
        if (isNotLastChar)
          setPixelOnIndex(spaceSignals, false);
        delay(delayDit * 3);
        break;
      case '/': // space between words (longer delay)
        if (isNotLastChar)
          setPixelOnIndex(spaceWords - spaceLetters, false);
        delay(delayDit * 7);
        break;
      default: // space between letters (short delay)
        if (isNotLastChar)
          setPixelOnIndex(spaceLetters - spaceSignals, false);
        delay(delayDit * 3);
        break;
    }
    strip.show();
  }
  Serial.println();
}

void setPixelOnIndex(uint16_t length, bool on) {
  for (uint8_t l = 0; l < length; l++) {
    if (pixelIndex > lastPixelIndex) scrollOne();
    uint16_t currentPixelIndex = REVERSE ? lastPixelIndex - pixelIndex : pixelIndex;

    strip.setPixelColor(currentPixelIndex, on ? fgColor : bgColor);

    // Store the state of the pixel in the buffer
    pixelStateBuffer[currentPixelIndex] = on;

    // Increase pixelIndex by 1
    pixelIndex++;
  }
}

void scrollOne() {
  // Shift all pixels back by 1 and except the last pixel
  for (uint16_t shiftIndex = 0; shiftIndex < lastPixelIndex; shiftIndex++) {
    uint16_t currentPixelIndex = REVERSE ? lastPixelIndex - shiftIndex : shiftIndex;
    uint16_t nextPixelIndex = REVERSE ? lastPixelIndex - shiftIndex - 1 : shiftIndex + 1;
    bool nextPixelState = pixelStateBuffer[nextPixelIndex];

    strip.setPixelColor(currentPixelIndex, nextPixelState ? fgColor : bgColor);

    // Store the state of the next pixel in the buffer at the currentPixelIndex
    pixelStateBuffer[currentPixelIndex] = nextPixelState;
  }
  // Decrease pixelIndex by 1
  pixelIndex--;
}
