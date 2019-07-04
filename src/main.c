/**
 * @file main.c
 * <b> Using functions from Task02/day03 </b>
*/

#include "coordinate.h"
#include "segmentSize.h"
#include "matrix.h"
#include "rotate.h"
#include "star.h"

#define TEN 10

/**
 * Function call functions from Task02/day03 </i>
 * @return 0
*/
int main()
{
	print_sin();

	int size = 20;
	print_diagram("helloworld", size, 'x');

	int array[] = { 11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34 };
	int rows = 3;
	int cols = 4;

	printf("Print 2d array:\n");
	print_2d_array(array, rows, cols);

	struct matrix source;
	struct matrix for_mul;
	struct matrix for_det;
	for_mul.rows = 4;
	for_mul.cols = 3;

	source.rows = 3;
	source.cols = 4;

	for_det.rows = for_det.cols = 3;

	source = alloc_matrix(source);
	for_mul = alloc_matrix(for_mul);
	for_det = alloc_matrix(for_det);

	float fraction = 0;
	for (size_t i = 0; i < source.rows; i++) {
		for (size_t j = 0; j < source.cols; j++) {
			fraction = rand() % TEN * TEN;
			fraction /= TEN * TEN;
			source.data[i][j] = rand() % TEN + fraction;
		}
	}
	for (size_t i = 0; i < for_mul.rows; i++) {
		for (size_t j = 0; j < for_mul.cols; j++) {
			fraction = rand() % TEN * TEN;
			fraction /= TEN * TEN;
			for_mul.data[i][j] = rand() % TEN + fraction;
		}
	}
	for (size_t i = 0; i < for_det.rows; i++) {
		for (size_t j = 0; j < for_det.cols; j++) {
			fraction = rand() % TEN * TEN;
			fraction /= TEN * TEN;
			for_det.data[i][j] = rand() % TEN + fraction;
		}
	}

	printf("Print matrix:\n");
	print_matrix(source);
	printf("Matrix for multiply:\n");
	print_matrix(for_mul);
	printf("Copy matrix:\n");
	struct matrix copy = copy_matrix(source);
	print_matrix(copy);
	printf("Mul matrix by -2:\n");
	struct matrix mul = mul_matrix_by_value(source, -2);
	print_matrix(mul);
	printf("Sum matrixes:\n");
	struct matrix sum = sum_matrix(source, source);
	print_matrix(sum);
	printf("Mul matrix1 by matrix2:\n");
	struct matrix mul_mat = mul_matrix(source, for_mul);
	print_matrix(mul_mat);
	printf("Trans matrix:\n");
	struct matrix trans_mat = transpose_matrix(source);
	print_matrix(trans_mat);
	printf("Matrix for get determinant:\n");
	print_matrix(for_det);
	double det = get_matrix_determinant(for_det);
	printf("Determinant of mul_mat %7.2f:\n", det);
	struct matrix inverse = get_inverse_matrix(for_det);
	printf("Inverse:\n");
	print_matrix(inverse);

	source = free_matrix(source);
	sum = free_matrix(sum);
	mul = free_matrix(mul);
	copy = free_matrix(copy);
	mul_mat = free_matrix(mul_mat);
	for_mul = free_matrix(for_mul);
	trans_mat = free_matrix(trans_mat);
	for_det = free_matrix(for_det);
	inverse = free_matrix(inverse);

	// DAY 04
	struct point_cartesian point = { 10, 3 };
	struct point_cartesian center = { 0, 0 };
	double angle = 35;

	struct point_cartesian rotate_point = point_rotate_polar(point, angle);
	struct point_cartesian rotate_matrix =
		point_rotate_matrix(point, angle);
	struct point_cartesian rotate_center =
		point_rotate_matrix_center(point, angle, center);

	printf("Result rotate using convertation from cartesian to polar: X = %f, Y = %f\n",
	       rotate_point.x, rotate_point.y);
	printf("Result rotate using matrix: X = %f, Y = %f\n", rotate_matrix.x,
	       rotate_matrix.y);
	printf("Result rotate using point_rotate_center: X = %f, Y = %f\n",
	       rotate_center.x, rotate_center.y);

	struct line_segment origin = { 3, 3, 3, 5 };
	double _zoom = 3.5;
	struct point_cartesian _center = { 3, 4 };

	struct line_segment result_segment = zoom(origin, _center, _zoom);

	printf("X1: %f, Y1: %f, X2: %f, Y2: %f\n", result_segment.x1,
	       result_segment.y1, result_segment.x2, result_segment.y2);

	printf("---------------------------------day05------------------------------------\n");
	// size_t N = 10;
	// struct star stars[N];
	// size_t max_x = N + N;
	// size_t max_y = N + N;
	// int count_center = 0;

	return 0;
}
