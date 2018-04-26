/*
 * Joy.hpp
 * Handling joystick input for cockpit project
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
*/

// #include <Keyboard.h>


enum class JoyState { low, dead, high };

class JoyAxis {
  static const int dead_zone = 1;
  JoyState lastState;
  char lowKey;
  char highKey;
  int pin;
public:
  JoyAxis(char _lowKey, char _highKey) {
    lastState = JoyState::dead;
    lowKey = _lowKey;
    highKey = _highKey;
  }

  void loop(int value) {
    JoyState state = JoyState::dead;
    if (value < -dead_zone) {
      state = JoyState::low;
    }
    else if ( value > dead_zone) {
      state = JoyState::high;
    }
    if (state != lastState) {
      if (lastState == JoyState::high)
        Keyboard.release(highKey);
      else if (lastState == JoyState::low)
        Keyboard.release(lowKey);
      if (state == JoyState::high) {
        Serial.print(highKey);
        Keyboard.press(highKey);
      }
      else if (state == JoyState::high) {
        Serial.print(lowKey);
        Keyboard.press(lowKey);
      }
    }
    lastState = state;
  }
};

class JoyController {
  static const int joyPin1 = A0;
  static const int joyPin2 = A1;
  static const int joyButton = 15;
  static const char RIGHT = 'E';
  static const char LEFT = 'Q';
  static const char FWD = ']';
  static const char BACK = '[';

  JoyAxis x;
  JoyAxis y;

public:

  int treatValue(int data) {
    return (data -512) * 20 / 1024;
  }

  JoyController() :
  x(RIGHT, LEFT),
  y(FWD, BACK)
  {
    pinMode(joyPin1, INPUT);
    pinMode(joyPin2, INPUT);
    pinMode(joyButton, INPUT);
    
  }

  void loop() {
    int value1, value2;
      // reads the value of the variable resistor
    value1 = treatValue(analogRead(joyPin1));  
    // this small pause is needed between reading
    // analog pins, otherwise we get the same value twice
    delay(100);            
    // reads the value of the variable resistor
    value2 = treatValue(analogRead(joyPin2)) ; //correct reading error  

    x.loop(value1);
    y.loop(value2);

    /*
    Serial.print("J ");
    Serial.print(value1);
    Serial.print("\t");
    Serial.println(value2);
    delay(100);
    */
  }
};
    

