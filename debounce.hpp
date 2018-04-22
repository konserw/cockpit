/*
 * debounce.h - class for handling switches
 * Based on debounce example from Arduino Studio
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2018, Kamil Strzempowicz
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * >  Debounce
 * (...) 
 * >  created 21 Nov 2006
 * >  by David A. Mellis
 * >  modified 30 Aug 2011
 * >  by Limor Fried
 * >  modified 28 Dec 2012
 * >  by Mike Walters
 * >  modified 30 Aug 2016
 * >  by Arturo Guadalupi
 * >
 * >  This example code is in the public domain.
 * >
 * >  http://www.arduino.cc/en/Tutorial/Debounce
*/

class DebouncedButton
{
  // Variables will change:
  int buttonPin;
  int buttonState;             // the current reading from the input pin
  int lastButtonState = LOW;   // the previous reading from the input pin
  char key;
  // the following variables are unsigned longs because the time, measured in
  // milliseconds, will quickly become a bigger number than can be stored in an int.
  unsigned long lastDebounceTime;  // the last time the output pin was toggled
  static const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
public:
  DebouncedButton(int pin, char _key) {
    buttonPin = pin;
    pinMode(buttonPin, INPUT_PULLUP);
    lastDebounceTime = 0;
    key = _key;
  }

  void loop() {
    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
      if (reading != buttonState) {
        buttonState = reading;
        Serial.print(key);
        Keyboard.print(key);
      }
    }
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
  }
};

