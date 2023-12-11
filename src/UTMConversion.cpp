/*
UTMConsersion.cpp - Library to convert in UTM coordenates.
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

#include "UTMConversion.h"

void GPS_UTM::UTM(double lati, double longi) {
	/*
	* Transformación de las coordenadas geográficas a UTM
	*/

	/*// Sobre la geometría del delipsoide WGS84
	double a = 6378137.0;
	double b = 6356752.3142;

  	float e1 = sqrt((a*a) - (b*b))/a; ///< Excentricidad.
	double e = sqrt(sq(a) - sq(b))/b; ///< Segunda excentricidad.
    double e2 = sq(e); ///< al cuadrado. Usaremos esta directamente.
    double c = sq(a) / b; ///< Radio Polar de Curvatura.
	*/

	// Se realiza las declaraciones para agilizar el calculo a UTM de X e Y.
	double e2 = 673949675659e-14; ///< Segunda excentricidad al cuadrado.
	double e2_2 = 336974837829e-14; // (e2 / 2.0)
	double c = 639959362580397e-8; ///< Radio Polar de Curvatura.
	double PI_180 = 1745329251994e-14;// (PI / 180.0)
	double alf = 505462256744e-14; // (0.75 * e2)
	double bet = 425820155e-13; // ((5.0 / 3.0) * alf * alf)
	double gam = 16740579e-14; // ((35.0 / 27.0) * alf * alf * alf)

    /// Sobre la longitud y latitud. Conversión de grados decimales a radianes.

    /*
    * Cálculo del signo de la longitud:
    *      - Si la longitud está referida al Oeste del meridiano de Greenwich,
    *        entonces la longitud es negativa (-).
    *      - Si la longitud está referida al Este del meridiano de Greenwich,
    *        entonces la longitud es positiva (+).
    */

    double latRad = lati * PI_180; ///< Latitud en Radianes.
    double lonRad = longi * PI_180; ///< Longitud en Radianes.

    /// Sobre el huso.
    float huso = ((longi + 180.0) / 6.0) + 1.0;  ///< Nos interesa quedarnos solo con la parte entera.
    _h = (int)huso;
	//_h = (int)((longi + 180.0) / 6.0) + 1; // Este calculo falla entre -1 y 0.


	// Calculamos la parte entera de latitud y longitud para ralizar calculos más rápidos.
	int lati_n = (int)lati;
	int longi_n = (int)longi;

	// Handle special case of west coast of Norway
	if ( lati_n >= 56 && lati_n < 64 && longi_n >= 3 && longi_n < 12 ) {
		_h = 32;
	}

	// Special zones for Svalbard
	if ( lati_n >= 72 && lati_n < 84 ) {
		if ( longi_n >= 0  && longi_n <  9 ) _h = 31;
		else if ( longi_n >= 9  && longi_n < 21 ) _h = 33;
		else if ( longi_n >= 21 && longi_n < 33 ) _h = 35;
		else if ( longi_n >= 33 && longi_n < 42 ) _h = 37;
	}

    int landa0 = _h * 6 - 183; ///< Cálculo del meridiano central del huso en grados.
    double Dlanda = lonRad - ((double)landa0 * PI_180);  ///< Desplazamiento del punto a calcular con respecto al meridiano central del huso.

	// Calculamos la zona.
	const char L[] = {'C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Z'};
	lati_n += 80;
	if ((lati_n >= 0) && (lati_n <= 151))
		_letter = L[(lati_n >> 3)];
	else if ((lati_n >= 152) && (lati_n <= 164))
		_letter = L[19];
	else
	    _letter = L[20]; // This is here as an error flag to show that the latitude is outside the UTM limits

	/*  Primera version de obtener la zona.
	if ((84 >= lati) && (lati >= 72))
		_letter = 'X';
	else if ((72 > lati) && (lati >= 64))
		_letter = 'W';
	else if ((64 > lati) && (lati >= 56))
		_letter = 'V';
	else if ((56 > lati) && (lati >= 48))
		_letter = 'U';
	else if ((48 > lati) && (lati >= 40))
		_letter = 'T';
	else if ((40 > lati) && (lati >= 32))
		_letter = 'S';
	else if ((32 > lati) && (lati >= 24))
		_letter = 'R';
	else if ((24 > lati) && (lati >= 16))
		_letter = 'Q';
	else if ((16 > lati) && (lati >= 8))
		_letter = 'P';
	else if (( 8 > lati) && (lati >= 0))
		_letter = 'N';
	else if (( 0 > lati) && (lati >= -8))
		_letter = 'M';
	else if ((-8> lati) && (lati >= -16))
		_letter = 'L';
	else if ((-16 > lati) && (lati >= -24))
		_letter = 'K';
	else if ((-24 > lati) && (lati >= -32))
		_letter = 'J';
	else if ((-32 > lati) && (lati >= -40))
		_letter = 'H';
	else if ((-40 > lati) && (lati >= -48))
		_letter = 'G';
	else if ((-48 > lati) && (lati >= -56))
		_letter = 'F';
	else if ((-56 > lati) && (lati >= -64))
		_letter = 'E';
	else if ((-64 > lati) && (lati >= -72))
		_letter = 'D';
	else if ((-72 > lati) && (lati >= -80))
		_letter = 'C';
	else
	    _letter = 'Z'; // This is here as an error flag to show that the latitude is outside the UTM limits
	*/

	/*!
    * Ecuaciones de Coticchia-Surace para el paso de Geográficas a UTM (Problema directo);
    */

    /// Cálculo de Parámetros.
    double coslatRad = cos(latRad);
    double coslatRad2 = sq(coslatRad);

    double A = coslatRad * sin(Dlanda);
    double xi = 0.5 * log((1 + A) / (1 - A));
    double n = atan(tan(latRad) / cos(Dlanda)) - latRad;
    double v = (c / sqrt(1 + e2 * coslatRad2)) * 0.9996;
    double z = e2_2 * sq(xi) * coslatRad2;
    double A1 = sin(2 * latRad);
    double A2 = A1 * coslatRad2;
    double J2 = latRad + (A1 / 2.0);
    double J4 = (3.0 * J2 + A2) / 4.0;
    double J6 = (5.0 * J4 + A2 * coslatRad2) / 3.0;
    double Bfi = 0.9996 * c * (latRad - alf * J2 + bet * J4 - gam * J6);

    /*!
    * Cálculo final de coordenadas UTM
    */
	/*
    Serial.println (" Las coordenadas GPS que se van a transformar son: ");
    Serial.print (" Latitud: "); Serial.println (lati,6);
    Serial.print (" Longitud: "); Serial.println (longi,6);

    Serial.println (" Coordenadas UTM actuales: ");
	Serial.print("UTM: "); Serial.print(_h); Serial.print(" ");Serial.println(_letter);
	*/
	_x = round(xi * v * (1 + (z / 3.0)) + 500000);
	/*!< 500.000 es el retranqueo que se realiza en cada huso sobre el origen de
    coordenadas en el eje X con el objeto de que no existan coordenadas negativas. */

    _y = round(n * v * (1 + z) + Bfi);
	if (lati < 0.0) _y += 10000000L;
	/*!< En el caso de latitudes al sur del ecuador, se sumará al valor de Y 10.000.000
    para evitar coordenadas negativas. */
	
	/*
    Serial.print (" X = "); Serial.print (_x); Serial.println (" (m)");
    Serial.print (" Y = "); Serial.print (_y); Serial.println (" (m)");
	*/
};

void GPS_UTM::UTM(long lati_L, long longi_L) {
	/*
	* Transformación de las coordenadas geográficas a UTM
	*/

	// Se realiza las declaraciones para agilizar el calculo a UTM de X e Y.
	double e2 = 673949675659e-14; ///< Segunda excentricidad al cuadrado.
	double e2_2 = 336974837829e-14; // (e2 / 2.0)
	double c = 639959362580397e-8; ///< Radio Polar de Curvatura.
	double PI_180 = 1745329251994e-14;// (PI / 180.0)
	double PI_180_L = 1745329251994e-21;// (PI / 180.0/ 10000000)
	double alf = 505462256744e-14; // (0.75 * e2)
	double bet = 425820155e-13; // ((5.0 / 3.0) * alf * alf)
	double gam = 16740579e-14; // ((35.0 / 27.0) * alf * alf * alf)

    /// Sobre la longitud y latitud. Conversión de grados decimales a radianes.

    /*
    * Cálculo del signo de la longitud:
    *      - Si la longitud está referida al Oeste del meridiano de Greenwich,
    *        entonces la longitud es negativa (-).
    *      - Si la longitud está referida al Este del meridiano de Greenwich,
    *        entonces la longitud es positiva (+).
    */

    double latRad = lati_L * PI_180_L; ///< Latitud en Radianes.
    double lonRad = longi_L * PI_180_L; ///< Longitud en Radianes.

	// Calculamos la parte entera de latitud y longitud para ralizar calculos más rápidos.
	int lati_n = (int)(lati_L / 10000000L);
	int longi_n = (int)(longi_L / 10000000L);

    /// Sobre el huso.
	float huso = ((float)(longi_L + 1800000000L) / 6e7) + 1.0;  ///< Nos interesa quedarnos solo con la parte entera.
    _h = (int)huso;

	//_h = (int)((longi_n + 180) / 6) + 1; // Este calculo falla entre -1 y 0.

	// Handle special case of west coast of Norway
	if ( lati_n >= 56 && lati_n < 64 && longi_n >= 3 && longi_n < 12 ) {
		_h = 32;
	}

	// Special zones for Svalbard
	if ( lati_n >= 72 && lati_n < 84 ) {
		if ( longi_n >= 0  && longi_n <  9 ) _h = 31;
		else if ( longi_n >= 9  && longi_n < 21 ) _h = 33;
		else if ( longi_n >= 21 && longi_n < 33 ) _h = 35;
		else if ( longi_n >= 33 && longi_n < 42 ) _h = 37;
	}

    int landa0 = _h * 6 - 183; ///< Cálculo del meridiano central del huso en grados.
    double Dlanda = lonRad - ((double)landa0 * PI_180);  ///< Desplazamiento del punto a calcular con respecto al meridiano central del huso.

	// Calculamos la zona.
	const char L[] = {'C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Z'};
	lati_n += 80;
	if ((lati_n >= 0) && (lati_n <= 151))
		_letter = L[(lati_n >> 3)];
	else if ((lati_n >= 152) && (lati_n <= 164))
		_letter = L[19];
	else
	    _letter = L[20]; // This is here as an error flag to show that the latitude is outside the UTM limits

	/*!
    * Ecuaciones de Coticchia-Surace para el paso de Geográficas a UTM (Problema directo);
    */

    /// Cálculo de Parámetros.
    double coslatRad = cos(latRad);
    double coslatRad2 = sq(coslatRad);

    double A = coslatRad * sin(Dlanda);
    double xi = 0.5 * log((1 + A) / (1 - A));
    double n = atan(tan(latRad) / cos(Dlanda)) - latRad;
    double v = (c / sqrt(1 + e2 * coslatRad2)) * 0.9996;
    double z = e2_2 * sq(xi) * coslatRad2;
    double A1 = sin(2 * latRad);
    double A2 = A1 * coslatRad2;
    double J2 = latRad + (A1 / 2.0);
    double J4 = (3.0 * J2 + A2) / 4.0;
    double J6 = (5.0 * J4 + A2 * coslatRad2) / 3.0;
    double Bfi_L = 9996.0 * c * (latRad - alf * J2 + bet * J4 - gam * J6) / 100.0;

    /*!
    * Cálculo final de coordenadas UTM
    */
	/*
    Serial.println (" Las coordenadas GPS que se van a transformar son: ");
    Serial.print (" Latitud: "); Serial.println (lati_L);
    Serial.print (" Longitud: "); Serial.println (longi_L);

    Serial.println (" Coordenadas UTM actuales: ");
	Serial.print("UTM: "); Serial.print(_h); Serial.print(" ");Serial.println(_letter);
	*/
	_x = (long)(xi * v * (1.0 + (z / 3.0)) * 1e2);
	_x += 50000000L;
	/*!< 500.000 * 100 es el retranqueo que se realiza en cada huso sobre el origen de
    coordenadas en el eje X con el objeto de que no existan coordenadas negativas. */

    _y = (long)(n * v * (1 + z) * 1e2 + Bfi_L);
	if (lati_L < 0) _y += 1000000000L;
	/*!< En el caso de latitudes al sur del ecuador, se sumará al valor de Y 10.000.000 * 100
    para evitar coordenadas negativas. */
	
	/*
    Serial.print (" X = "); Serial.print (_x); Serial.println (" (cm)");
    Serial.print (" Y = "); Serial.print (_y); Serial.println (" (cm)");
	*/
};