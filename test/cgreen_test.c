#include <cgreen/cgreen.h>

#include "../src/coordinate.h"
#include "../src/segmentSize.h"
#include "../src/matrix.h"
#include "../src/rotate.h"
#include "../src/star.h"

#define ROTATE_CENTER 4
#define NUM_AFTER_POINT 2
#define ZOOM_SIZE 6

Describe(Rotate);
BeforeEach(Rotate)
{
}
AfterEach(Rotate)
{
}

void assert_that_point(struct point_cartesian first,
		       struct point_cartesian second)
{
	significant_figures_for_assert_double_are(NUM_AFTER_POINT);

	assert_that_double(first.x, is_equal_to_double(second.x));
	assert_that_double(first.y, is_equal_to_double(second.y));
}

void assert_that_segment(struct line_segment first, struct line_segment second)
{
	significant_figures_for_assert_double_are(NUM_AFTER_POINT);

	assert_that_double(first.x1, is_equal_to_double(second.x1));
	assert_that_double(first.y1, is_equal_to_double(second.y1));
	assert_that_double(first.x2, is_equal_to_double(second.x2));
	assert_that_double(first.y2, is_equal_to_double(second.y2));
}

Ensure(Rotate, point_rotate_polar)
{
	struct point_cartesian input_source[ROTATE_CENTER] = {
		{ 3, 3 }, { 3, 3 }, { 10, 3 }, { 0, 0 }
	};
	double input_angle[ROTATE_CENTER] = { -90, 0, 35, 25 };

	struct point_cartesian expect[ROTATE_CENTER] = {
		{ -3, 3 }, { 3, 3 }, { 9.91, -3.28 }, { 0, 0 }
	};

	struct point_cartesian rotate_result;

	for (int i = 0; i < ROTATE_CENTER; i++) {
		rotate_result =
			point_rotate_polar(input_source[i], input_angle[i]);

		assert_that_point(rotate_result, expect[i]);
	}
}

Ensure(Rotate, point_rotate_matrix)
{
	struct point_cartesian input_source[ROTATE_CENTER] = {
		{ 3, 3 }, { 3, 3 }, { 10, 3 }, { 0, 0 }
	};
	double input_angle[ROTATE_CENTER] = { -90, 0, 35, 25 };

	struct point_cartesian expect[ROTATE_CENTER] = {
		{ -3, 3 }, { 3, 3 }, { 9.91, -3.28 }, { 0, 0 }
	};

	struct point_cartesian rotate_result;

	for (int i = 0; i < ROTATE_CENTER; i++) {
		rotate_result =
			point_rotate_matrix(input_source[i], input_angle[i]);
		assert_that_point(rotate_result, expect[i]);
	}
}

Ensure(Rotate, point_rotate_matrix_center)
{
	struct point_cartesian input_point[ROTATE_CENTER] = {
		{ 3, 3 }, { 3, 3 }, { 10, 3 }, { 0, 0 }
	};
	struct point_cartesian input_center[ROTATE_CENTER] = {
		{ 3, 3 }, { 3, 3 }, { 3, 3 }, { 3, 3 }
	};
	double input_angle[ROTATE_CENTER] = { -90, 25, 35, -25 };

	struct point_cartesian expect_point[ROTATE_CENTER] = {
		{ 3, 3 }, { 3, 3 }, { 8.73, -1.02 }, { 1.55, -0.98 }
	};

	struct point_cartesian rotate_result;

	for (int i = 0; i < ROTATE_CENTER; i++) {
		rotate_result = point_rotate_matrix_center(
			input_point[i], input_angle[i], input_center[i]);

		assert_that_point(rotate_result, expect_point[i]);
	}
}

Ensure(Rotate, zoom)
{
	struct line_segment input_origin[ZOOM_SIZE] = {
		{ 3, 3, 5, 3 }, { 3, 3, 3, 5 }, { 3, 3, 5, 5 },
		{ 3, 3, 1, 5 }, { 3, 3, 5, 5 }, { 3, 3, 5, 5 },
	};

	struct point_cartesian input_center[ZOOM_SIZE] = { { 4, 3 }, { 3, 4 },
							   { 4, 4 }, { 2, 4 },
							   { 0, 0 }, { 5, 5 } };

	double input_zoom[ZOOM_SIZE] = { 2, 3.5, -2, 0, 1, 0.5 };

	struct line_segment expect[ZOOM_SIZE] = {
		{ 2, 3, 6, 3 }, { 3, 0.5, 3, 7.5 }, { 6, 6, 2, 2 },
		{ 2, 4, 2, 4 }, { 3, 3, 5, 5 },     { 4, 4, 5, 5 },
	};

	struct line_segment result;

	for (int i = 0; i < ZOOM_SIZE; i++) {
		result = zoom(input_origin[i], input_center[i], input_zoom[i]);

		assert_that_segment(result, expect[i]);
	}
}

Ensure(Rotate, generate_sky_random){
	size_t N = 10;
	struct star stars[N];
	size_t max_x = N;
	size_t max_y = N;
	int count_center = 0;

	generate_sky_random(stars, N, max_x, max_y);

	for(size_t i = 0; i < N; i++){
		// Center is only one ?
		// if(stars[i].is_center){
		// 	count_center++;
		// }
		assert_that(stars[i].location.x, is_less_than(max_x));
		assert_that(stars[i].location.y, is_less_than(max_y));

		for(size_t j = i + 1; j < N; j++){
			assert_that(stars[i].location.x != stars[j].location.x || stars[i].location.y != stars[j].location.y);
		}
	}
	for(int i = 0; i < N; i=i+1){
		if(stars[i].is_center){
			count_center++;
		}
	}
	printf("Is center %i\n", stars[2].is_center);
	assert_that(count_center, is_equal_to(1));
}

int main()
{
	TestSuite *suite = create_test_suite();

	add_test_with_context(suite, Rotate, point_rotate_polar);
	add_test_with_context(suite, Rotate, point_rotate_matrix);
	add_test_with_context(suite, Rotate, point_rotate_matrix_center);
	add_test_with_context(suite, Rotate, zoom);

	add_test_with_context(suite, Rotate, generate_sky_random);

	return run_test_suite(suite, create_text_reporter());
}
