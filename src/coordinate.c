/**
 * @file coordinate.c
 * <b> Implemantation of function: </b>
 * <ul>
 * <li> Conversion from radians to degrees </li>
 * <li> From degrees to radians </li>
 * <li> From cartesian to polar system coordinate </li>
 * <li> From polar to cartesian </li>
 * <li> Parse line and conversion to structure </li>
 * </ul>
 * 
 * @author Kushch A.E.
*/

#include "coordinate.h"

/// Angle which will use in formulas
#define ANGLE 180
/// Size string which I use in function
#define SIZE_STR 255

double radians_to_degrees(double radians)
{
	return (radians * ANGLE) / PI;
}

double degrees_to_radians(double degrees)
{
	return (degrees * PI) / ANGLE;
}

struct point_polar cartesian_to_polar(struct point_cartesian p)
{
	struct point_polar r; // result

	r.r = sqrt(
		pow(p.x, 2) +
		pow(p.y,
		    2)); // The square length equal the sum of square coordinates

	if (p.x == 0 &&
	    p.y == 0) { // If x,y = 0 than we can't do conversion to polar, because we write r,a = 0
		r.r = 0;
		r.a = 0;
	} else if (p.x >
		   0) { // Formulas and conditions you can find in wikipedia.
		r.a = atan(
			p.y /
			p.x); // From condition i may to use range from [-pi, pi]
	} else if (p.x < 0 && p.y >= 0) {
		r.a = atan(p.y / p.x) + PI;
	} else if (p.x < 0 && p.y < 0) {
		r.a = atan(p.y / p.x) - PI;
	} else if (p.x == 0 && p.y > 0) {
		r.a = PI / 2;
	} else if (p.x == 0 && p.y < 0) {
		r.a = -PI / 2;
	}

	r.a = radians_to_degrees(r.a);

	return r;
}

struct point_cartesian polar_to_cartesian(struct point_polar p)
{
	struct point_cartesian r; // result

	r.x = p.r * cos(degrees_to_radians(p.a)); // Coordinate x
	r.y = p.r * sin(degrees_to_radians(p.a)); // Coordinate y

	return r;
}

struct point_cartesian parse_point(char *str)
{
	struct point_cartesian r; // result
	char *buf = (char *)malloc(
		SIZE_STR); // Accepts an input string for output to the
	// stderr, because the input string
	strcpy(buf, str); // will be divided

	char *part; // Variable will takes a symbols of x*/
	char *part2; // Variable will takes a symbols of y*/
	char *end;

	if (strchr(str,
		   '&')) { // If string doesn't have '&' we return 'Cant parse
		// this string'
		strtok(str, "&"); // Divide string to 2

		char *null = strtok(
			NULL,
			"\0"); // Buffer. This variable take the right side of string. Now it take y=12. If it take "" than print error.

		if (strchr(str, '=') && null != NULL) {
			// PART 1

			part = strtok(str, "="); // Divide PART to 2
			part = strtok(
				NULL,
				"\0"); // Variable take the right side (x=25)

			if (part !=
			    NULL) { // If in part1 nothing we tell what can't parse this string
				int i = 0;
				while (part[i] !=
				       '\0') { // Go to end of string.
					if (part[i] > '9' ||
					    part[i] <
						    '0') { // If in string find another symbols(25x), we tell what "Can't parse" (48..57 in ASCII it's numbers)
						fprintf(stderr,
							"Can't parse following line: '%s'",
							buf);
						r.x = 0;
						r.y = 0;

						free(buf);
						return r;
					}
					i++;
				}
			} else {
				fprintf(stderr,
					"Can't parse following line: '%s'",
					buf);
				r.x = 0;
				r.y = 0;

				free(buf);
				return r;
			}

			if (strchr(buf, 'x') <
			    strchr(buf,
				   'y')) { // If user first writes x after y
				r.x = strtod(part, &end);
			} else { // If user first writes y after x
				r.y = strtod(part, &end);
			}

			// PART 2 Y
			part2 = strtok(null, "=");
			part2 = strtok(NULL, "\0");

			if (part2 != NULL) {
				int i = 0;
				while (part2[i] != '\0') {
					if (part2[i] > '9' || part2[i] < '0') {
						fprintf(stderr,
							"Can't parse following line: '%s'",
							buf);
						r.x = 0;
						r.y = 0;

						free(buf);
						return r;
					}
					i++;
				}
			} else {
				fprintf(stderr,
					"Can't parse following line: '%s'",
					buf);
				r.x = 0;
				r.y = 0;

				free(buf);
				return r;
			}

			if (strchr(buf, 'x') < strchr(buf, 'y')) {
				r.y = strtod(part2, &end);
			} else {
				r.x = strtod(part2, &end);
			}

			free(buf);
			return r;
		} else {
			fprintf(stderr, "Can't parse following line: '%s'",
				buf);
			r.x = 0;
			r.y = 0;

			free(buf);
			return r;
		}
	} else {
		fprintf(stderr, "Can't parse following line: '%s'", buf);
		r.x = 0;
		r.y = 0;

		free(buf);
		return r;
	}
}

#undef SIZE_STR
#undef ANGLE
