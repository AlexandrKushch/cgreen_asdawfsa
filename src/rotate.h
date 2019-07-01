#pragma once

#include "coordinate.h"
#include "segmentSize.h"
#include "matrix.h"

/**
 * <b>Function rotate point around start of coordinate </b>
 * 
 * Using convertion from cartesian to polar
 * Take away angle, because we rotate by clockwise
 * Using convertations from polar to cartesian
 * 
 * @return result
 * 
*/
struct point_cartesian point_rotate_polar(struct point_cartesian source,
					  double angle);
/**
 * <b> Function rotate point around start of coordinate using matrix </b>
 * 
 * Create const matrix, which size = 2*2 because we rotate in 2d system coordinate, and fill this matrix sin and cos, like in formula
 * With input coordinate (x, y) create matrix, which size = 2*1, like in formula
 * And multiply this matrixes
 * Result write in struct point_cartesian
 * 
 * @return result
 * 
*/
struct point_cartesian point_rotate_matrix(struct point_cartesian source,
					   double angle);
/**
 * <b> Function rotate point around point </b>
 * 
 * Create 3 const matrix, which need us for formula.
 * Fill matrices with values.
 * Create result matrix, which contains the result of the multiplication of these matrices.
 * When multiply matrices, using <i> copy_matrix </i> to avoid memory leaks. Every time free memory of result and copy in new variable.
 * 
 * @return result
 * 
*/
struct point_cartesian
point_rotate_matrix_center(struct point_cartesian source, double angle,
			   struct point_cartesian center_point);

/**
 * <b> The function scales the segment </b>
 * 
 * Create 3 const matrix, which need us for formula.
 * Fill matrices with values.
 * Create new matrix, which contains result of two multiplys, result of first point by angels, result of second point by angels.
 * Convert from matrix to line segment.
 * Clear memory
 * @return result_segment
 * 
*/
struct line_segment zoom(struct line_segment origin,
			 struct point_cartesian center, double zoom_value);
