# Arduino-ARGB-Morse
Generate a morse code from a text (via serial monitor) and display it on an ARGB LED strip and the serial monitor.

## Example
<img src="https://github.com/sepp89117/Arduino-ARGB-Morse/blob/main/example.gif">
"i love github and coding"

## How to use
### Importants
1. Connect an ARGB LED strip to your Arduino. Connect the data port of the ARGB LED strip to a digital pin with a 370 ohm resistor
2. Define the data pin in the sketch on ``#define PIN 6``
3. Define the absolute number of LEDs ``#define LED_COUNT 144``
4. If you want the output to start at the other end of the strip, set ``#define REVERSE`` to true, otherwise to false
5. Upload the sketch and open the serial monitor with 9600 baud
6. Write a text, press enter and enjoy the show
### Optionals
- You can define at which pixel index the display starts ``uint16_t firstPixelIndex = 0;`` and at which it ends ``uint16_t lastPixelIndex = LED_COUNT - 1;``
- You can define the fore ``uint32_t fgColor = strip.Color(0, 0, 255);`` and background color ``uint32_t bgColor = strip.Color(0, 0, 0);``
- You can define the spaces between single signals ``uint8_t spaceSignals = 2;``, letters ``uint8_t spaceLetters = 4;`` and words ``uint8_t spaceWords = 8;``
- You can define the dit delay ``uint16_t delayDit = 100;``. A higher delay makes the show slower and vice versa.

## Libraries used
- Adafruit_NeoPixel (https://github.com/adafruit/Adafruit_NeoPixel) with LGPL-3.0 license
