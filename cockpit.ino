/*
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
 * This project is partialy based on Crow from https://github.com/dawikur/crow
 * Copyright 2016, Dawid Kurek, <dawikur@gmail.com>
*/

#include <Keyboard.h>
#include "debounce.hpp"

int SW1 = 3;
int SW2 = 6;

int joyPin1 = A0;
int joyPin2 = A1;

DebouncedButton buttons[] = {DebouncedButton(SW1, 'L'), DebouncedButton(SW2, 'U')};
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(joyPin1, INPUT);
  pinMode(joyPin2, INPUT);
  pinMode(15, INPUT);
/*   
//copy from firmware.ino @ crow by Dawid Kurek <dawikur@gmail.com>
  static HIDSubDescriptor customerNode(
    Crow::Reports::CustomerDescriptor,
    sizeof(Crow::Reports::CustomerDescriptor));
  HID().AppendDescriptor(&customerNode);

  static HIDSubDescriptor keyboardNode(
    Crow::Reports::KeyboardDescriptor,
    sizeof(Crow::Reports::KeyboardDescriptor));
  HID().AppendDescriptor(&keyboardNode);

  static HIDSubDescriptor pointerNode(Crow::Reports::PointerDescriptor,
                                      sizeof(Crow::Reports::PointerDescriptor));
  HID().AppendDescriptor(&pointerNode);
  */
  Keyboard.begin();
}

 int treatValue(int data) {
  return (data * 9 / 1024);
 }

// the loop function runs over and over again forever
void loop() {
  for (auto&& button : buttons)
    button.loop();

  int value1, value2;
    // reads the value of the variable resistor
  value1 = analogRead(joyPin1);  
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);            
  // reads the value of the variable resistor
  value2 = analogRead(joyPin2);  
  Serial.print("J ");
  Serial.print(treatValue(value1));
  Serial.print("\t");
  Serial.println(treatValue(value2));
  delay(1000);
}

