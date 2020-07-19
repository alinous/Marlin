/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once


#define REVERSE_TEMP_SENSOR_RANGE

// Marlin temperature sensor type 22
//
// This was created to allow use of the E3D PT100 amplifier on the BigTreeTech and similar boards 
// without requiring any hardware mods (cutting resistors, etc.).
// The BigTreeTech boards have a 3.3V ADC reference and a 4.7K pullup resistor 
// connected to the Thermistor inputs so we can't use the standard Marlin temp sensor types.
//
// HARDWARE INSTALL:
//
// Since the BigTreeTech board is not 5V tolerant you need to operate the 
// E3D PT100 at 3.3V. Yes this board will operate at 3.3V but it won't report
// temperatures beyond approx 360C.
// 3.3V can be found on some BTT connectors (WIFI connector on the SKR 1.4)
// Connect the output of the PT100 amp to the standard thermistor input on the BTT board.
//
// SOFTWARE INSTALL:
//
// This table must be compiled into the Marlin 2.0.x firmware. Locate and open the 
// thermistors.h file and add the following text:
//
// #if ANY_THERMISTOR_IS(22) // Pt100 with E3D amp @ 3.3v w/4.7K pullup (BigTreeTech, etc.). Abbycus 2020
//   #include "thermistor_22.h"
// #endif
//
// In configuration.h:
//      #define TEMP_SENSOR_0 22       // use 0 or 1
//      #define HEATER_0_MAXTEMP 310   // set max temperature to less than 360
//
// CALCULATIONS:
//
// Array values below were derived from PT100 resistance vs temperature tables.
//
// Constants:
//    Vref = 3.30V
//    Rb = 4400 (resistance of two bridge resistors in the INA826 circuit)
//    Rpu = 4700 (pullup resistor on thermistor input)
//    Ramp = 100 (INA826 amp output resistor)
//    RTD = Resistance @ temperature. Example 111 ohms at 25C.
//      
// Calculate Vo : output of the INA826 amplifier in the E3D PCB
//    Vo = ((Vref / (RTD + Rb)) * RTD) * 10
// Next calculate Vadc : output voltage with a 4.7K pullup on the thermistor input.
//    Vadc = (((Vref - Vo) / Rpu) * Ramp) + Vo
// Lastly calculate ADC digital value for each point in the array below (10 bit ADC, 0 - 1023).
//    ADC = (Vadc / Vref) * 1024
//
// Abby@Abbycus 2020
//
const short temptable_22[][2] PROGMEM = {
  { OV(  0),    0 },
  { OV(245),    1 },
  { OV(253),   10 },
  { OV(261),   20 },
  { OV(270),   30 },
  { OV(278),   40 },
  { OV(287),   50 },
  { OV(295),   60 },
  { OV(303),   70 },
  { OV(311),   80 },
  { OV(319),   90 },
  { OV(328),  100 },
  { OV(336),  110 },
  { OV(344),  120 },
  { OV(352),  130 },
  { OV(360),  140 },
  { OV(368),  150 },
  { OV(376),  160 },
  { OV(384),  170 },
  { OV(391),  180 },
  { OV(399),  190 },
  { OV(407),  200 },
  { OV(415),  210 },
  { OV(422),  220 },
  { OV(430),  230 },
  { OV(438),  240 },
  { OV(445),  250 },
  { OV(453),  260 },
  { OV(460),  270 },
  { OV(468),  280 },
  { OV(475),  290 },
  { OV(483),  300 },
  { OV(490),  310 },
  { OV(497),  320 },
  { OV(505),  330 },
  { OV(512),  340 },
  { OV(519),  350 },
  { OV(526),  360 },
  { OV(533),  370 },
  { OV(541),  380 },
  { OV(548),  390 },
  { OV(554),  400 },
  { OV(623),  500 },
  { OV(689),  600 },
  { OV(751),  700 },
  { OV(810),  800 },
  { OV(850),  900 },
  { OV(910), 1000 },
  { OV(960), 1100 }
};
