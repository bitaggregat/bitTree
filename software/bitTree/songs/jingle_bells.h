/**
BSD 3-Clause License

Copyright (c) 2024, bitaggregat GmbH

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

// Note frequencies in Hz
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587

#define NOTE_NONE     0
#define NOTE_PAUSE    1
#define NOTE_QUARTER  4
#define NOTE_EIGHTH   8

struct note {
  int frequency;
  int duration;
};

note song[] = {
    {NOTE_E4, NOTE_EIGHTH}, {NOTE_E4, NOTE_EIGHTH}, {NOTE_E4, NOTE_QUARTER}, // Jingle Bells
    {NOTE_E4, NOTE_EIGHTH}, {NOTE_E4, NOTE_EIGHTH}, {NOTE_E4, NOTE_QUARTER}, // Jingle Bells
    {NOTE_E4, NOTE_EIGHTH}, {NOTE_G4, NOTE_EIGHTH}, {NOTE_C4, NOTE_EIGHTH}, {NOTE_D4, NOTE_EIGHTH}, {NOTE_E4, NOTE_QUARTER}, // Jingle all the way
    {NOTE_F4, NOTE_EIGHTH}, {NOTE_F4, NOTE_EIGHTH}, {NOTE_F4, NOTE_EIGHTH}, {NOTE_F4, NOTE_EIGHTH}, // Oh what fun
    {NOTE_F4, NOTE_EIGHTH}, {NOTE_E4, NOTE_EIGHTH}, {NOTE_E4, NOTE_EIGHTH}, {NOTE_E4, NOTE_EIGHTH}, // It is to ride in a one horse open sleigh
    {NOTE_G4, NOTE_EIGHTH}, {NOTE_G4, NOTE_EIGHTH}, {NOTE_F4, NOTE_EIGHTH}, {NOTE_D4, NOTE_EIGHTH}, {NOTE_C4, NOTE_EIGHTH}, // Hey!
    {NOTE_NONE, NOTE_PAUSE} // Pause
};
