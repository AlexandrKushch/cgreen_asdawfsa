/**
 * @file test.c
 * Testing all functions
 * @author Kushch A.E.
 * @version 1.1.1
 * @date 2019.05.25
*/

#include "fct.h"
#include "../src/coordinate.h"
#include "../src/segmentSize.h"
#include "../src/matrix.h"

#undef DBL_EPSILON // I'm doing this because DBL_Epsilon = very small value, and test don't working
#define DBL_EPSILON 0.01 // Assign another value

/// Size for test functions: radians_to_degrees/degrees_to_radians && This value i can use for test parse_point in loop 'for'
#define SIZE_RTOD 6
/// Size for test functions: cartesian_to_polar/polar_to_cartesian
#define SIZE_CTOP 9
/// Size lines in test parse_point
#define SIZE_STR 50
/// Size for test function: get_length && This value i can use for test is_point_on_line
#define SIZE_INPUT_POINT 4
/// Size for test function: sort_array_desc_ranged
#define SIZE_ARRAY 5
/// Size for array
#define SIZE_SUB_ARRAY 10

FCT_BGN()
{
	FCT_QTEST_BGN(radians_to_degrees)
	{
		double input[] = { 1, 0, 10, 0.17, 6.28, 4.89 };
		double expect[] = { 57.29, 0, 572.95, 9.74, 359.81, 280.17 };

		for (int i = 0; i < SIZE_RTOD; i++) {
			if (fct_chk_eq_dbl(radians_to_degrees(input[i]),
					   expect[i]) == 0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(degrees_to_radians)
	{
		double input[] = { 57.29, 0, 572.95, 9.74, 359.81, 280.17 };
		double expect[] = { 1, 0, 10, 0.17, 6.28, 4.89 };
		for (int i = 0; i < SIZE_RTOD; i++) {
			if (fct_chk_eq_dbl(degrees_to_radians(input[i]),
					   expect[i]) == 0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(cartesian_to_polar)
	{
		struct point_cartesian input[] = { { 0, 0 },   { 25, 0 },
						   { -25, 0 }, { 0, -25 },
						   { 10, 10 }, { -25, -25 },
						   { 0, 25 },  { 10, -10 },
						   { -10, 10 } };
		struct point_polar expected[] = {
			{ 0, 0 },    { 25, 0 },      { 25, 180 },
			{ 25, -90 }, { 14.14, 45 },  { 35.36, -135 },
			{ 25, 90 },  { 14.14, -45 }, { 14.14, 135 }
		};

		for (int i = 0; i < SIZE_CTOP; i++) {
			if (fct_chk_eq_dbl(cartesian_to_polar(input[i]).r,
					   expected[i].r) == 0) {
				FCT_FINAL();
			}
			if (fct_chk_eq_dbl(cartesian_to_polar(input[i]).a,
					   expected[i].a) == 0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(polar_to_cartesian)
	{
		struct point_polar input[] = { { 0, 0 },      { 25, 0 },
					       { 25, 180 },   { 25, -90 },
					       { 14.14, 45 }, { 35.36, -135 },
					       { 25, 90 },    { 14.14, -45 },
					       { 14.14, 135 } };
		struct point_cartesian expected[] = { { 0, 0 },   { 25, 0 },
						      { -25, 0 }, { 0, -25 },
						      { 10, 10 }, { -25, -25 },
						      { 0, 25 },  { 10, -10 },
						      { -10, 10 } };

		for (int i = 0; i < SIZE_CTOP; i++) {
			if (fct_chk_eq_dbl(polar_to_cartesian(input[i]).x,
					   expected[i].x) == 0) {
				FCT_FINAL();
			}
			if (fct_chk_eq_dbl(polar_to_cartesian(input[i]).y,
					   expected[i].y) == 0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(polar_to_cartesian)
	{
		struct point_polar input[] = { { 0, 0 },      { 25, 0 },
					       { 25, 180 },   { 25, -90 },
					       { 14.14, 45 }, { 35.36, -135 },
					       { 25, 90 },    { 14.14, -45 },
					       { 14.14, 135 } };
		struct point_cartesian expected[] = { { 0, 0 },   { 25, 0 },
						      { -25, 0 }, { 0, -25 },
						      { 10, 10 }, { -25, -25 },
						      { 0, 25 },  { 10, -10 },
						      { -10, 10 } };

		for (int i = 0; i < SIZE_CTOP; i++) {
			if (fct_chk_eq_dbl(polar_to_cartesian(input[i]).x,
					   expected[i].x) == 0) {
				FCT_FINAL();
			}
			if (fct_chk_eq_dbl(polar_to_cartesian(input[i]).y,
					   expected[i].y) == 0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(parse_point)
	{
		char *name_file = (char *)malloc(sizeof(char) * SIZE_STR);
		strcpy(name_file, "Errors.txt");
		FILE *file_error = freopen(name_file, "w", stderr);
		char *str = (char *)malloc(sizeof(char) * SIZE_STR);

		char input[SIZE_RTOD][SIZE_STR] = {
			"point:x=12&y=25", "point:y=12&x=25", "point:y=&x=25",
			"point:y=10",      "point:y=10&",     "point:y=10&x=5x"
		};
		struct point_cartesian expected[SIZE_RTOD] = {
			{ 12, 25 }, { 25, 12 }, { 0, 0 },
			{ 0, 0 },   { 0, 0 },   { 0, 0 }
		};
		char expected_file[SIZE_INPUT_POINT][SIZE_STR] = {
			"Can't parse following line: 'point:y=&x=25'",
			"Can't parse following line: 'point:y=10'",
			"Can't parse following line: 'point:y=10&'",
			"Can't parse following line: 'point:y=10&x=5x'"
		};

		struct point_cartesian tmp;
		fclose(file_error);

		for (int i = 0, j = 0; i < SIZE_RTOD; i++) {
			file_error = freopen(name_file, "w", stderr);
			tmp = parse_point(input[i]);
			fclose(file_error);

			if (!fct_chk(tmp.x == expected[i].x &&
				     tmp.y == expected[i].y)) {
				FCT_FINAL();
			}

			if (expected[i].x == 0 && expected[i].y == 0) {
				file_error = fopen(name_file, "r");
				fgets(str, SIZE_STR, file_error);
				if (fct_chk_eq_str(str, expected_file[j]) ==
				    0) {
					FCT_FINAL();
				}
				j++;
				fclose(file_error);
			}
		}

		free(name_file);
		free(str);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(get_length)
	{
		struct line_segment input[SIZE_INPUT_POINT] = { { 2, 1, 23, 4 },
								{ -2, 1, 0, 4 },
								{ 1, 1, 1, 1 },
								{ 6, -6, -6,
								  6 } };
		double expected[SIZE_INPUT_POINT] = { 21.21, 3.6, 0, 16.97 };

		for (int i = 0; i < SIZE_INPUT_POINT; i++) {
			if (fct_chk_eq_dbl(get_length(input[i]), expected[i]) ==
			    0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(is_point_on_line)
	{
		struct point_cartesian input_point[SIZE_INPUT_POINT] = {
			{ 0, 0 }, { 0, 0 }, { -0.4, 1.76 }, { 1.5, 1.5 }
		};
		struct line_segment input_segment[SIZE_INPUT_POINT] = {
			{ 1, 1, 23, 4 },
			{ 2, 1, -2, -1 },
			{ -1, -1.52, 0.4, 6.2 },
			{ 1, 1, -2, -1 }
		};
		bool expect[SIZE_INPUT_POINT] = { 0, 1, 1, 0 };
		bool returned;

		for (int i = 0; i < SIZE_INPUT_POINT; i++) {
			returned = is_point_on_line(input_point[i],
						    input_segment[i]);
			if (fct_chk_eq_int(expect[i], returned) == 0) {
				FCT_FINAL();
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(sort_array_desc_ranged)
	{
		int input_array[SIZE_ARRAY][SIZE_SUB_ARRAY] = {
			{ 1, -4, -5, -3, 2, 5, 10, 3, 6, 5 },
			{ 1, -4, -5, -3, 2, 5, 10, 3, 6, 5 },
			{ 1, -4, -5, -3, 2, 5, 10, 3, 6, 5 },
			{ 1, -4, -5, -3, 2, 5, 10, 3, 6, 5 },
			{ 1, -4, -5, -3, 2, 5, 10, 3, 6, 5 }
		};

		int input_low_range[SIZE_ARRAY] = { 5, 100, 5, 0, 4 };
		int input_high_range[SIZE_ARRAY] = { 1, 4, -1, 9, 7 };

		int expected[SIZE_ARRAY][SIZE_SUB_ARRAY] = {
			{ 1, -4, -5, -3, 2, 5, 10, 3, 6, 5 },
			{ -5, -4, -3, 1, 2, 5, 10, 3, 6, 5 },
			{ 1, -4, -5, -3, 2, 3, 5, 5, 6, 10 },
			{ -5, -4, -3, 1, 2, 3, 5, 5, 6, 10 },
			{ 1, -4, -5, -3, 2, 3, 5, 10, 6, 5 }
		};

		for (int i = 0; i < SIZE_ARRAY; i++) {
			sort_array_desc_ranged(input_array[i], SIZE_SUB_ARRAY,
					       input_low_range[i],
					       input_high_range[i]);

			for (int j = 0; j < SIZE_SUB_ARRAY; j++) {
				if (fct_chk_eq_int(input_array[i][j],
						   expected[i][j]) == 0) {
					FCT_FINAL();
				}
			}
		}
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(copy_matrix)
	{
		struct matrix input;
		struct matrix copy;
		float fraction = 0;

		input.rows = 3;
		input.cols = 5;
		input = alloc_matrix(input);
		for (unsigned int i = 0; i < input.rows; i++) {
			for (unsigned int j = 0; j < input.cols; j++) {
				fraction = rand() % SIZE_SUB_ARRAY *
					   SIZE_SUB_ARRAY;
				fraction /= SIZE_SUB_ARRAY * SIZE_SUB_ARRAY;
				input.data[i][j] =
					rand() % SIZE_SUB_ARRAY + fraction;
			}
		}

		copy = copy_matrix(input);

		for (unsigned int i = 0; i < input.rows; i++) {
			for (unsigned int j = 0; j < input.cols; j++) {
				fct_chk_eq_dbl(input.data[i][j],
					       copy.data[i][j]);
				fct_chk(&input.data[i][j] != &copy.data[i][j]);
			}
		}

		input = free_matrix(input);
		copy = free_matrix(copy);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(mul_matrix_by_value)
	{
		double input_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, -1, 0, -2, -3 };
		double expect_arr[] = { -2,  -4,  -6, -8, -10, -12,
					-14, -16, 2,  0,  4,   6 };
		int k = 0;

		struct matrix input;
		struct matrix expect;

		input.rows = expect.rows = 3;
		input.cols = expect.cols = 4;

		input = alloc_matrix(input);
		expect = alloc_matrix(expect);

		for (unsigned int i = 0; i < input.rows; i++) {
			for (unsigned int j = 0; j < input.cols; j++, k++) {
				input.data[i][j] = input_arr[k];
				expect.data[i][j] = expect_arr[k];
			}
		}

		struct matrix mul = mul_matrix_by_value(input, -2);

		for (unsigned int i = 0; i < mul.rows; i++) {
			for (unsigned int j = 0; j < mul.cols; j++) {
				fct_chk_eq_dbl(mul.data[i][j],
					       expect.data[i][j]);
			}
		}

		input = free_matrix(input);
		expect = free_matrix(expect);
		mul = free_matrix(mul);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(sum_matrix)
	{
		double input1_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		double input2_arr[] = { 1, 4, 7, 2, 5, 8, 3, 6, 9 };
		double expect_arr[] = { 2, 6, 10, 6, 10, 14, 10, 14, 18 };
		int k = 0;

		struct matrix input1;
		struct matrix input2;
		struct matrix expect;

		input1.rows = input2.rows = expect.rows = 3;
		input1.cols = input2.cols = expect.cols = 3;

		input1 = alloc_matrix(input1);
		input2 = alloc_matrix(input2);
		expect = alloc_matrix(expect);

		for (unsigned int i = 0; i < input1.rows; i++) {
			for (unsigned int j = 0; j < input1.cols; j++, k++) {
				input1.data[i][j] = input1_arr[k];
				input2.data[i][j] = input2_arr[k];
				expect.data[i][j] = expect_arr[k];
			}
		}

		struct matrix sum = sum_matrix(input1, input2);

		for (unsigned int i = 0; i < input1.rows; i++) {
			for (unsigned int j = 0; j < input1.cols; j++) {
				fct_chk_eq_dbl(sum.data[i][j],
					       expect.data[i][j]);
			}
		}

		input1 = free_matrix(input1);
		input2 = free_matrix(input2);
		expect = free_matrix(expect);
		sum = free_matrix(sum);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(mul_matrix)
	{
		double input_arr[] = { 1, 2, 3, 4, 5, 6 };
		double expect_arr[] = { 9, 12, 15, 19, 26, 33, 29, 40, 51 };
		int k = 0;

		struct matrix input1;
		struct matrix input2;
		struct matrix expect;

		input1.rows = input2.cols = 3;
		input1.cols = input2.rows = 2;
		expect.rows = expect.cols = 3;

		input1 = alloc_matrix(input1);
		input2 = alloc_matrix(input2);
		expect = alloc_matrix(expect);

		for (unsigned int i = 0; i < input1.rows; i++) {
			for (unsigned int j = 0; j < input1.cols; j++, k++) {
				input1.data[i][j] = input_arr[k];
			}
		}
		k = 0;
		for (unsigned int i = 0; i < input2.rows; i++) {
			for (unsigned int j = 0; j < input2.cols; j++, k++) {
				input2.data[i][j] = input_arr[k];
			}
		}
		k = 0;
		for (unsigned int i = 0; i < expect.rows; i++) {
			for (unsigned int j = 0; j < expect.cols; j++, k++) {
				expect.data[i][j] = expect_arr[k];
			}
		}

		struct matrix mul_mat = mul_matrix(input1, input2);

		for (unsigned int i = 0; i < input1.rows; i++) {
			for (unsigned int j = 0; j < input1.cols; j++) {
				fct_chk_eq_dbl(mul_mat.data[i][j],
					       expect.data[i][j]);
			}
		}

		input1 = free_matrix(input1);
		input2 = free_matrix(input2);
		expect = free_matrix(expect);
		mul_mat = free_matrix(mul_mat);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(transpose_matrix)
	{
		double input_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		double expect_arr[] = { 1, 4, 7, 2, 5, 8, 3, 6, 9 };
		int k = 0;

		struct matrix input;
		struct matrix expect;

		input.rows = input.cols = 3;
		expect.rows = expect.cols = 3;

		input = alloc_matrix(input);
		expect = alloc_matrix(expect);

		for (unsigned int i = 0; i < input.rows; i++) {
			for (unsigned int j = 0; j < input.cols; j++, k++) {
				input.data[i][j] = input_arr[k];
				expect.data[i][j] = expect_arr[k];
			}
		}

		struct matrix trans_mat = transpose_matrix(input);

		for (unsigned int i = 0; i < trans_mat.rows; i++) {
			for (unsigned int j = 0; j < trans_mat.cols; j++) {
				fct_chk_eq_dbl(trans_mat.data[i][j],
					       expect.data[i][j]);
			}
		}

		input = free_matrix(input);
		expect = free_matrix(expect);
		trans_mat = free_matrix(trans_mat);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(get_matrix_determinant)
	{
		double input_arr[] = { 7, 8, 9, 1, 1, 2, 3, 4,
				       4, 5, 6, 7, 7, 9, 8, 2 };
		double expect_det = 81;
		int k = 0;

		struct matrix input;

		input.rows = input.cols = 4;

		input = alloc_matrix(input);

		for (unsigned int i = 0; i < input.rows; i++) {
			for (unsigned int j = 0; j < input.cols; j++, k++) {
				input.data[i][j] = input_arr[k];
			}
		}

		double result_det = get_matrix_determinant(input);

		if (fct_chk_eq_dbl(result_det, expect_det) == 0) {
			FCT_FINAL();
		}

		input = free_matrix(input);
	}
	FCT_QTEST_END();

	FCT_QTEST_BGN(get_inverse_matrix)
	{
		double input_arr[] = { 7, 8, 9, 1, 1, 2, 3, 4,
				       4, 5, 6, 7, 7, 9, 8, 2 };
		double expect_arr[] = { 0.18,  -1.37, 0.85, -0.33, -0.48, 0.62,
					-0.48, 0.66,  0.40, 0.51,  -0.25, -0.33,
					-0.11, -0.11, 0.22, 0 };
		int k = 0;

		struct matrix input;
		struct matrix expect;

		input.rows = input.cols = 4;
		expect.rows = expect.cols = 4;

		input = alloc_matrix(input);
		expect = alloc_matrix(expect);

		for (unsigned int i = 0; i < input.rows; i++) {
			for (unsigned int j = 0; j < input.cols; j++, k++) {
				input.data[i][j] = input_arr[k];
				expect.data[i][j] = expect_arr[k];
			}
		}

		struct matrix result = get_inverse_matrix(input);

		for (size_t i = 0; i < result.rows; i++) {
			for (size_t j = 0; j < result.cols; j++) {
				fct_chk_eq_dbl(result.data[i][j],
					       expect.data[i][j]);
			}
		}

		input = free_matrix(input);
		expect = free_matrix(expect);
		result = free_matrix(result);
	}
	FCT_QTEST_END();
}
FCT_END()
