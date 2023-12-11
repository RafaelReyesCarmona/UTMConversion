/*
UTMConsersion.h - Library to convert in UTM coordenates. Headers file.
UTMConsersion v1.3

Copyright © 2019-2022 Francisco Rafael Reyes Carmona.
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

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef UTMConversion_h
#define UTMConversion_h

class GPS_UTM {
	private:
		int _h;
		char _letter;
		long _x;
		long _y;

	public:
    GPS_UTM(){
			_h = 0;
			_letter = 'Z';
			_x = 0L;
			_y = 0L;
		};

	void UTM(double, double);
	void UTM(long,long);

	int zone(){
		return _h;
	};

	char band(){
		return _letter;
	};

	long X(){
		return _x;
	};

	long Y(){
		return _y;
	};
};

#endif
