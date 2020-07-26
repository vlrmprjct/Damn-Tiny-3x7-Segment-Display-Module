// ATMEL ATTINY84
//                          +-\/-+
//                    VCC  1|    |14  GND
//             (D10)  PB0  2|x   |13  AREF (D 0)
//             (D 9)  PB1  3|x   |12  PA1  (D 1)
//                    PB3  4|    |11  PA2  (D 2)
//  PWM  INT0  (D 8)  PB2  5|x   |10  PA3  (D 3)
//  PWM        (D 7)  PA7  6|    |9   PA4  (D 4)
//  PWM        (D 6)  PA6  7|    |8   PA5  (D 5)        PWM
//
//
//  These pin numbers will probably not work with your hardware
//  pin  8 = DATA IN
//  pin  9 = CLK
//  pin 10 = LOAD

#include "LedControl.h";

LedControl lc = LedControl(8, 9, 10, 1);

void setup() {
    lc.shutdown(0,false);
    lc.setIntensity(0,10);
    lc.clearDisplay(0);

    // Noise from unused pin
    randomSeed(analogRead(A6));
}

void printDigit(int v) {
    int ones, tens, hundreds;

    if (v < -999 || v > 999)
    return;

    ones = v % 10;
    v = v / 10;
    tens = v % 10;
    v = v / 10;
    hundreds = v;

    (hundreds == 0)
        ? lc.setChar(0, 0, ' ', false)
        : lc.setDigit(0, 0, (byte)hundreds, false);
    (tens == 0 && hundreds == 0)
        ? lc.setChar(0, 1, ' ', false)
        : lc.setDigit(0, 1, (byte)tens, false);

    lc.setDigit(0, 2, (byte)ones, false);
}

void loop() {
    printDigit(random(0, 999));
    delay(1000);
}
