/*
UTMConsersion_example.cpp - Example to use this library to convert in UTM coordenates.
UTMConsersion v1.1

Copyright © 2019-2021 Francisco Rafael Reyes Carmona.
All rights reserved.

rafael.reyes.carmona@gmail.com

  This file is part of UTMConsersion.

  UTMConsersion is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  UTMConsersion is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with UTMConsersion.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <UTMConversion.h>

float flat[] = {37.8959210,40.033223,40.774997,66.077490,33.406994,-11.551785,7.333418,-41.266792,-21.643807,-37.463226};
float flon[] = {-4.7478210,-2.567744,15.582325,-45.853359,-84.482198,-45.151016,-69.030662,-67.625977,18.059812,146.629184};

GPS_UTM utm;

void setup() {
    char utmstr[] = "30S 123456 1234567";

    Serial.begin(9600);  

    for(int i = 0; i < 10;i++){
        char line[50];
        char strlat[12];
        char strlon[12];
        dtostrf(flat[i],8,6,strlat);
        dtostrf(flon[i],8,6,strlon);
        sprintf(line, "Coordenates %s, %s -> UTM: ", strlat, strlon);
        Serial.print(line);
        utm.UTM(flat[i], flon[i]);
        sprintf(utmstr, "%02d%c %ld %ld", utm.zone(), utm.band(), utm.X(), utm.Y());
        Serial.println(utmstr);
    }
}

void loop() {

}