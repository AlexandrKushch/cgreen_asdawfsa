#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PI 3.141592

/**
 * <b> Contains coordinate: </b>
 * <ul>
 * <li> x - abscissa axis </li>
 * <li> y - ordinate axis </li>
 * </ul>
*/
struct point_cartesian {
	/// Coordinate x
	double x;
	/// Coordinate y
	double y;
};

/**
 * <b> Contains coordinate: </b>
 * <ul>
 * <li> r - length of line </li>
 * <li> a - angle </li>
 * </ul>
*/
struct point_polar {
	/// Length
	double r;
	/// Angle
	double a;
};

/**
   * <b> Function performs conversion from radians to degrees </b>
   * <ul>
   * <li> Incoming degrees multiply to 180 and divide to PI  </li>
   * </ul>
   * 
   * @return (radians * ANGLE) / PI
   */
double radians_to_degrees(double radians);

/**
   * <b> Function performs conversion from degrees to radians </b>
   * <ul>
   * <li> Incoming radians multiply to 180 and divide to PI  </li>
   * </ul>
   * 
   * @return (degrees * PI) / ANGLE
   */
double degrees_to_radians(double degrees);

/**
   * <b> Function performs conversion from cartesian coordinate system to polar
   * </b> <ul> <li> The square length equal the sum of square coordinates </li>
   * <li> For calculation angle we need to make 6 conditions and use formulas
   * with wikipedia </li>
   * </ul>
   *
   * @param r result which we will return
   * @return r
   */
struct point_polar cartesian_to_polar(struct point_cartesian p);

/**
   * <b> Function performs conversion from polar coordinate system to cartesian
   * </b> <ul> <li> For coordinate x we need length multiply to COS(angle) </li>
   * <li> For coordinate y we need length multiply to SIN(angle)  </li>
   * </ul>
   *
   * @param r result which we will return
   * @return r
   */
struct point_cartesian polar_to_cartesian(struct point_polar p);
/**
   * <b> Function makes of string -> cartesian coordinate system </b>
   * <ul>
   * <li> Make variables </li>
   * <li> First condition: if string have '&' </li>
   * <li> Than we divide <i>str</i> to <i>&</i> </li>
   * <li> Second condition: if in part where the numbers should be nothing we
   * tell <i>error</i> </li> <li> Else make condition: if in string with numbers
   * have other symbols we tell <i>error</i> </li> <li> Next condition: if user
   * write before x after y OR before y after x. We write this data correct in
   * structure</li> <li> For <i>PART2</i> we doing same </li>
   * </ul>
   *
   * @param r - it's struct point_cartesian, result which we will return
   * @param buf - it's char*, take input string, will use if input line can't to parse. We can't print input str, because it will be divided
   * @param part - Variable will takes a symbols of x. Will convarsion to numbers.
   * @param part1 - Variable will takes a symbols of y. Will be conversion to numbers.
   * 
   * @return r
   */
struct point_cartesian parse_point(char *str);
