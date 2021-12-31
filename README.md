<img src="img/location.png" width=48 height=48 align=right>

# UTMConversion #

[![GPS NMEA: UTMConversion](https://img.shields.io/badge/GPS_NMEA-UTMConversion-red?style=for-the-badge&logo=googlemaps)](README.md)
[![Version: v1.0.1](https://img.shields.io/badge/Version-v1.0.1-blue?style=for-the-badge&logo=v)]()

Library for conversion GPS location info to UTM coordinates (WG86). It has been implemented From library UTMconversion.h (TinyTrackGPS V0.7)

## Installation ##

### Arduino IDE ###

For a tutorial on how to install new libraries for use with the Arduino
development environment please refer to the following website:
http://www.arduino.cc/en/Reference/Libraries

--- or ---

1. Download the ZIP file from the page [releases](https://github.com/RafaelReyesCarmona/UTMConversion/releases) to your machine.
<p align=center>
<img src="img/Download_latest.png" alt="Download latest version of library" width=600>
</p>

2. In the Arduino IDE, choose Sketch/Include Library/Add Zip Library.
<p align=center>
<img src="img/Add_library.png" alt="Add library Arduino IDE" width=600>
</p>

3. Navigate to the ZIP file, and click Open.

### PlatformIO ###

How to use the library in PlatformIO see [documentation](https://docs.platformio.org/en/latest/librarymanager/index.html) of Library Manager.

The only one simple step is to define dependencies in “platformio.ini” (Project Configuration File). For example,

```
[env:pro16MHzatmega328]
platform = atmelavr
board = pro16MHzatmega328
framework = arduino
lib_deps = rafaelreyescarmona/UTMConversion

[env:LGT8F328]
board = LGT8F328P
board_build.f_cpu = 32000000
platform = lgt8f
framework = arduino
lib_deps = rafaelreyescarmona/UTMConversion@^1.0.0
```

For Manual installation in PlatformIO Core:

1. Run a terminal and type for search the library: 
```
pio lib search UTMConversion
```
<p align=center>
<img src="img/PlatformIO_3.png" alt="PlatformIO Search command" width=600>
</p>

2. Type for install:
```
pio lib install 12973
```

--- or ---

1. Search "UTMConversion" in search box of _Libraries_ of panel.
<p align=center>
<img src="img/PlatformIO_1.png" alt="PlatformIO Search screen" width=600>
</p>

2. Click _Add to project_ button. Library will be included in the project and "platformio.ini" updated.
<p align=center>
<img src="img/PlatformIO_2.png" alt="PlatformIO Add library" width=600>
</p>

## How to use the library ##

In Arduino IDE, Choose Sketch/Include Library/Scroll and select "UTMConversion".
<p align=center>
<img src="img/Using_library_1.png" alt="Using ThermistorNTC library in Arduino IDE" width=600>
</p>

There are a two examples files with the library. In the Arduino IDE, choose File/Examples/UTMConversion, and you can see "UTMConversion_example".

<p align=center>
<img src="img/Arduino_examples.png" alt="Examples files" width=600>
</p>

--- or ---

Example of use:

```C++
#include "UTMconversion.h"

float flat = 37.8959210;
float flon = -4.7478210;

GPS_UTM utm;

void setup() {
  char utmstr[] = "30S 123456 1234567";

  Serial.begin(9600);  

  utm.UTM(flat, flon);
  sprintf(utmstr, "%02d%c %ld %ld", utm.zone(), utm.band(), utm.X(), utm.Y());
  Serial.println(utmstr);
}

void loop() {

}
```

## License ##

This file is part of UTMConversion.

UTMConversion is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

UTMConversion is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with UTMConversion.  If not, see <https://www.gnu.org/licenses/>.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)

## Authors ##

Copyright © 2019-2021 Francisco Rafael Reyes Carmona.
Contact me: rafael.reyes.carmona@gmail.com

## Credits ##

Location icon at the beginning is from [Flaticon.es](https://www.flaticon.es) designed by [Good Ware](https://www.flaticon.com/authors/good-ware)
and licensed by [free license](img/license.pdf).
