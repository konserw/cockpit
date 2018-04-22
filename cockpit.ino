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

#include <ArduinoSTL.h> // from https://github.com/mike-matera/ArduinoSTL cin and cout disabled in ArduinoSTL.cpp
#include <HID.h>
#include <Keyboard.h>
#include "debounce.hpp"

int LED1 = 10;
int LED2 = 16;
int LED3 = 14;
int LED4 = 15;

int SW_1_DOWN = 3;
int SW_1_UP = 6;

//DebouncedButton button1 = DebouncedButton(SW_1_DOWN, LED1);
std::vector<DebouncedButton> buttons;
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

//    button1 = DebouncedButton(SW_1_DOWN, LED1); 
  buttons.push_back(DebouncedButton(SW_1_DOWN, LED1));
    
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
}

// the loop function runs over and over again forever
void loop() {
  buttons[0].loop();
}

