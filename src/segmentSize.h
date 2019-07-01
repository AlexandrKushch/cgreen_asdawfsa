#pragma once

#include <stdbool.h>
#include "coordinate.h"

/**
 * <b> Contains coordinate points A and B </b>
 * <ul>
 * <li> x1 - abscissa axis of point A </li>
 * <li> y1 - ordinate axis of point A </li>
 * <li> x2 - abscissa axis of point B </li>
 * <li> y2 - ordinate axis of point B </li>
 * </ul>
*/
struct line_segment {
	/// Coordinate x of point A
	double x1;
	/// Coordinate y of point A
	double y1;

	/// Coordinate x of point B
	double x2;
	/// Coordinate y of point B
	double y2;
};

/**
 * <b> Function find distance length between two points </b>
 * Using formula from Internet for find length
 * 
 * @param r - result(length)
 * @return r
*/
double get_length(struct line_segment segment);

/**
 * <b> Function determine whether a segment point belongs </b>
 * Using formula from Internet for find length
 * 
 * @param r - result(true or false)
 * @return r
*/
bool is_point_on_line(struct point_cartesian point,
		      struct line_segment segment);

/**
 * <b> Function displays the beginning and end points of the segment on the screen </b>
 * <ul>
 * <li> In array write the ' ' </li>
 * <li> If position in array equal with coordinates the beginnig and end of the segment we write in array '*' </li>
 * <li> In end of 2nd loop we display on screen element of array (cartesian[i][j]) </li>
 * <li> In end of 1st loop print on screen new line('\n') </li>
 * </ul>
 * 
 * @param cartesian - array which we displayed on the screen
*/
void print_segment_points(struct line_segment segment);

/**
 * <b> Function displays the segment on the screen </b>
 * <ul>
 * <li> In array write the ' ' </li>
 * <li> If position in array equal with coordinates in segment we write in array '*' </li>
 * <li> In end of 2nd loop we display on screen element of array (cartesian[i][j]) </li>
 * <li> In end of 1st loop print on screen new line('\n') </li>
 * </ul>
 * 
 * @param cartesian - array which we displayed on the screen
*/
void print_segment(struct line_segment segment);

/**
 * <b> Function displays the sine way on the screen </b>
 * <ul>
 * <li> In array write the ' ' </li>
 * <li> Using formula <b>y = sin(x)</b> </li>
 * <li> Result multiplyed by 5, in order to increase graph. And add 5, in order to lower the graph </li>
 * <li> Displayed x and y, if previos point by abscis not in array. </li>
 * </ul>
 * 
 * @param cartesian - array which we displayed on the screen
 * @param previos_point_abscis - The previous point, need to compare, if this point is already in the array, we do nothing
 * @param point - point in cartesian system 
*/
void print_sin();

/**
 * <b> Function displays which displays a bar chart of how often characters appear in a word </b>
 * <ul>
 * <li> First of all, we will find out if the character is already counted, then we skip it since its quantity has already been found. </li>
 * <li> Secondly, If a character is not counted, then we write it into an array <b> sym[i] </b> </li>
 * <li> We count how many times a character repeats in a word. </li>
 * <li> Find the character that repeats most often in the word </li>
 * <li> Character with "max_count" take 100% "diagram_size" </li>
 * <li> Take charecter which != character with "max_count" </li>
 * <li> Than we learn how many times less the number of repetitions from the maximum number of repetitions. </li>
 * <li> Take a piece of the entire size and write to the array with the number of "x" </li>
 * <li> We display the result </li>
 * </ul>
 * 
 * @param count - Number of different characters per line
 * @param count_sym[diagram_size] - Number of times a character is repeated in a string
 * @param sym[diagram_size] - The symbol itself which corresponds to its number of repetitions.
 * @param count_fill_sym[diagram_size] - How many "x" fill out the diagram
 * @param max_value - The symbol that repeats most often, the number of repetitions is written into this variable.
 * @param max_key - The key of the character that repeats more often
 * @param how_many_times_less
*/
void print_diagram(const char *word, const int diagram_size, char fill_symbol);

/**
 * <b> Function sorts a part of an integer array </b>
 * <ul>
 * <li> We create 2 conditions that check whether the ranges are outside the limits </li>
 * <li> Next condition if low range < high range than we do nothing </li>
 * <li> Make loop which sorting in range from <b>low_range</b> to <b>high_range</b> </li>
 * </ul>
 * 
 * @param cartesian - array which we displayed on the screen
 * @param previos_point_abscis - The previous point, need to compare, if this point is already in the array, we do nothing
 * @param point - point in cartesian system 
*/

void sort_array_desc_ranged(int data[], int size, int low_range,
			    int high_range);
