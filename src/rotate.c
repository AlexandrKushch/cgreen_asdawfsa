/**
 * @file matrix.c
 * <b> Implemantation of function for Task02/day04 </b>
 * 
 * @author Kushch A.E.
*/
#include "rotate.h"

struct point_cartesian point_rotate_polar(struct point_cartesian source,
					  double angle)
{
	struct point_polar pp = cartesian_to_polar(source);
	pp.a -= angle;
	struct point_cartesian result = polar_to_cartesian(pp);
	return result;
}

struct point_cartesian point_rotate_matrix(struct point_cartesian source,
					   double angle)
{
	struct point_cartesian result;

	struct matrix mul_mat;
	mul_mat.rows = mul_mat.cols = 2;

	mul_mat = alloc_matrix(mul_mat);

	mul_mat.data[0][0] = cos(degrees_to_radians(angle));
	mul_mat.data[0][1] = sin(degrees_to_radians(angle));
	mul_mat.data[1][0] = -sin(degrees_to_radians(angle));
	mul_mat.data[1][1] = cos(degrees_to_radians(angle));

	struct matrix mul_mat_source;
	mul_mat_source.rows = 2;
	mul_mat_source.cols = 1;
	mul_mat_source = alloc_matrix(mul_mat_source);

	mul_mat_source.data[0][0] = source.x;
	mul_mat_source.data[1][0] = source.y;

	struct matrix result_mat = mul_matrix(mul_mat, mul_mat_source);

	result.x = result_mat.data[0][0];
	result.y = result_mat.data[1][0];

	mul_mat = free_matrix(mul_mat);
	result_mat = free_matrix(result_mat);
	mul_mat_source = free_matrix(mul_mat_source);

	return result;
}

struct point_cartesian
point_rotate_matrix_center(struct point_cartesian source, double angle,
			   struct point_cartesian center_point)
{
	angle = -angle;
	struct matrix rotate_mines;
	struct matrix rotate_plus;
	struct matrix sin_cos;

	struct matrix result_matrix;
	struct matrix source_matrix;

	rotate_mines.rows = rotate_mines.cols = 3;
	rotate_plus.rows = rotate_plus.cols = 3;
	sin_cos.rows = sin_cos.cols = 3;
	source_matrix.rows = 1;
	source_matrix.cols = 3;

	rotate_mines = alloc_matrix(rotate_mines);
	rotate_plus = alloc_matrix(rotate_plus);
	sin_cos = alloc_matrix(sin_cos);
	source_matrix = alloc_matrix(source_matrix);

	for (size_t i = 0; i < rotate_mines.rows; i++) {
		for (size_t j = 0; j < rotate_mines.cols; j++) {
			rotate_mines.data[i][j] = 0;
			rotate_plus.data[i][j] = 0;
			sin_cos.data[i][j] = 0;
		}
	}

	for (size_t i = 0, j = 0; i < rotate_mines.rows; i++, j++) {
		rotate_mines.data[i][j] = 1;
		rotate_plus.data[i][j] = 1;
	}

	source_matrix.data[0][0] = source.x;
	source_matrix.data[0][1] = source.y;
	source_matrix.data[0][2] = 1;

	rotate_mines.data[2][0] = -center_point.x;
	rotate_mines.data[2][1] = -center_point.y;

	rotate_plus.data[2][0] = center_point.x;
	rotate_plus.data[2][1] = center_point.y;

	sin_cos.data[0][0] = cos(degrees_to_radians(angle));
	sin_cos.data[0][1] = sin(degrees_to_radians(angle));
	sin_cos.data[1][0] = -sin(degrees_to_radians(angle));
	sin_cos.data[1][1] = cos(degrees_to_radians(angle));
	sin_cos.data[2][2] = 1;

	result_matrix = mul_matrix(source_matrix, rotate_mines);
	struct matrix copy_result_matrix = copy_matrix(result_matrix);
	result_matrix = free_matrix(result_matrix);

	result_matrix = mul_matrix(copy_result_matrix, sin_cos);
	copy_result_matrix = free_matrix(copy_result_matrix);
	copy_result_matrix = copy_matrix(result_matrix);
	result_matrix = free_matrix(result_matrix);

	result_matrix = mul_matrix(copy_result_matrix, rotate_plus);
	copy_result_matrix = free_matrix(copy_result_matrix);

	struct point_cartesian result;
	result.x = result_matrix.data[0][0];
	result.y = result_matrix.data[0][1];

	rotate_mines = free_matrix(rotate_mines);
	rotate_plus = free_matrix(rotate_plus);
	sin_cos = free_matrix(sin_cos);
	source_matrix = free_matrix(source_matrix);
	result_matrix = free_matrix(result_matrix);

	return result;
}

#define ROWS_MATRIX 2
#define COLS_MATRIX 3
#define SIZE_ANGELS 3

struct line_segment zoom(struct line_segment origin,
			 struct point_cartesian center, double zoom_value)
{
	struct matrix first_point;
	struct matrix second_point;
	struct matrix angles;

	first_point.rows = second_point.rows = ROWS_MATRIX;
	first_point.cols = second_point.cols = COLS_MATRIX;
	angles.rows = angles.cols = SIZE_ANGELS;

	first_point = alloc_matrix(first_point);
	second_point = alloc_matrix(second_point);
	angles = alloc_matrix(angles);

	for (int i = 0; i < ROWS_MATRIX; i++) {
		for (int j = 0; j < COLS_MATRIX; j++) {
			first_point.data[i][j] = 0;
			second_point.data[i][j] = 0;
		}
	}
	for (int i = 0; i < SIZE_ANGELS; i++) {
		for (int j = 0; j < SIZE_ANGELS; j++) {
			angles.data[i][j] = 0;
		}
	}

	first_point.data[0][0] = origin.x1;
	first_point.data[0][1] = origin.y1;
	first_point.data[0][2] = 1;

	second_point.data[1][0] = origin.x2;
	second_point.data[1][1] = origin.y2;
	second_point.data[1][2] = 1;

	angles.data[0][0] = zoom_value;
	angles.data[1][1] = zoom_value;
	angles.data[2][0] = -center.x * zoom_value + center.x;
	angles.data[2][1] = -center.y * zoom_value + center.y;
	angles.data[2][2] = 1;

	struct matrix result[ROWS_MATRIX];

	result[0] = mul_matrix(first_point, angles);
	result[1] = mul_matrix(second_point, angles);

	struct line_segment result_segment;

	result_segment.x1 = result[0].data[0][0];
	result_segment.y1 = result[0].data[0][1];
	result_segment.x2 = result[1].data[1][0];
	result_segment.y2 = result[1].data[1][1];

	first_point = free_matrix(first_point);
	second_point = free_matrix(second_point);
	angles = free_matrix(angles);
	result[0] = free_matrix(result[0]);
	result[1] = free_matrix(result[1]);

	return result_segment;
}
