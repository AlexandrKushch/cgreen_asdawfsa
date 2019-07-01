/**
 * @file segmentSize.c
 * <b> Implemantation of function <i>get_length</i> </b>
 * 
 * @author Kushch A.E.
*/

#include "segmentSize.h"
#include "coordinate.h"

#define DELTA 0.05
#define SPACE 32
#define STAR 42
#define POINT 46
#define N 11
#define M 40

#define CIRCLE 360
#define SIZE_GRAPH 5
#define AMPLITUDE 1

double get_length(struct line_segment segment)
{
	double r; // result

	r = sqrt(pow(segment.x2 - segment.x1, 2) +
		 pow(segment.y2 - segment.y1, 2));

	return r;
}

bool is_point_on_line(struct point_cartesian point, struct line_segment segment)
{
	struct line_segment atoc = { point.x, point.y, segment.x1, segment.y1 };
	struct line_segment ctob = { point.x, point.y, segment.x2, segment.y2 };

	double ab = get_length(segment); // AB = AC + BC
	double ac = get_length(atoc);
	double cb = get_length(ctob);

	return fabs(ab - (ac + cb)) < DELTA;
}

void print_segment_points(struct line_segment segment)
{
	char cartesian[N][M];
	struct point_cartesian point;
	for (int y = 0; y < N; y++) {
		point.y = y;
		for (int x = 0; x < M; x++) {
			point.x = x;

			if (x == segment.x1 && y == segment.y1) {
				cartesian[x][y] = STAR;
			} else if (x == segment.x2 && y == segment.y2) {
				cartesian[x][y] = STAR;
			} else {
				cartesian[x][y] = SPACE;
			}
			printf("%c", cartesian[x][y]);
		}
		printf("\n");
	}
}

void print_segment(struct line_segment segment)
{
	char cartesian[N][M];
	struct point_cartesian point;
	for (int y = 0; y < N; y++) {
		point.y = y;
		for (int x = 0; x < M; x++) {
			point.x = x;

			if (x == segment.x1 && y == segment.y1) {
				cartesian[x][y] = STAR;
			} else if (x == segment.x2 && y == segment.y2) {
				cartesian[x][y] = STAR;
			} else if (is_point_on_line(point, segment)) {
				cartesian[x][y] = STAR;
			} else {
				cartesian[x][y] = SPACE;
			}
			printf("%c", cartesian[x][y]);
		}
		printf("\n");
	}
}

void print_sin()
{
	struct point_cartesian point = { 0, 0 };
	char cartesian[N][M];
	double previos_point_abscis =
		-1; // The previous point, need to compare, if this point is already in the array, we do nothing

	for (int i = 0; i < N; i++) { // Fill cartesian coordinate with spaces
		for (int j = 0; j < M; j++) {
			cartesian[i][j] = SPACE;
		}
	}

	for (; point.x < CIRCLE; point.x++) { // From 0 to 360 in abscissa axis
		point.x = degrees_to_radians(point.x);
		point.y =
			AMPLITUDE *
			((sin(point.x) * SIZE_GRAPH) +
			 SIZE_GRAPH); // Using formula for find 'y'. Multiply by 5 because point will be very small (=0). Add 5 because 'y' will be in point(0, 0), but need in point (0, 5)
		point.x *=
			SIZE_GRAPH; // Multiply by 5 because point will be very small (=0).

		if ((int)point.x !=
		    (int)previos_point_abscis) { // If previos point by abscis is alredy in array. We do nothing
			cartesian[(int)(point.y)][(int)(point.x)] = STAR;
		}

		previos_point_abscis =
			point.x; // After changes in abscis and compare, we previos point assign new point
		point.x /=
			SIZE_GRAPH; // Return value for abscis back, because after that we adding 1 in normal value
		point.x = radians_to_degrees(
			point.x); // And return in normal system.
	}

	for (int i = 0; i < N; i++) { // We show our graph on the display.
		for (int j = 0; j < M; j++) {
			printf("%c", cartesian[i][j]);
		}
		printf("\n");
	}
}

void print_diagram(const char *word, const int diagram_size, char fill_symbol)
{
	if ((int)strlen(word) > diagram_size) {
		printf("Length bigger than diagram size\n");
		return;
	}

	int count = 0; // Количество разных символов в строке
	int count_sym[diagram_size]; // Количество раз символ повторяется в строке
	char sym[diagram_size]; // Сам символ которому соответствует его количеству повторений
	double count_fill_sym
		[diagram_size]; // Каким количеством "х" заполнить диаграму
	int max_value =
		0; // Символ который повторяется чаще всего, количество повторений запишется в эту переменную
	int max_key = 0; // Ключ символа который повторяется чаще вссего

	for (int i = 0; i < diagram_size; i++) // Заполняем массив -1
		count_sym[i] = -1;

	for (unsigned int i = 0, k = 0; i < strlen(word);
	     i++, k++) { // В этом цикле проверяем
		for (unsigned int j = 0; j < strlen(word);
		     j++) { // Если символ уже посчитан, то мы его пропускаем так как его количество уже найдено
			if (word[i] == sym[j]) {
				i++;
				j = -1;
			}
		}
		if (i < strlen(word)) {
			sym[k] =
				word[i]; // Если символ не посчитан то мы его записываем в массив
			count++; // Узнаем количество разных символов в строке
		} else {
			break;
		}

		count_sym[k] =
			1; // Даный символ уже есть в строке значит он количество повторений точно равно 1
		for (unsigned int j = i + 1; j < strlen(word);
		     j++) { // Ищем есть ли еще такие символы
			if (sym[k] == word[j]) {
				count_sym[k]++;
			}
		}
	}

	for (int i = 0; i < count;
	     i++) { // Узнаем какой символ повторяется чаще всего
		if (count_sym[i] > max_value) {
			max_value =
				count_sym[i]; // Запоминаем количество повторений
			max_key = i; // Запоминаем его ключ
		}
	}

	count_fill_sym[max_key] = diagram_size;
	double how_many_times_less = 0;

	for (int i = 0; i < count; i++) {
		if (i != max_key) { // Проходимся по всем елементам
			how_many_times_less =
				(double)count_sym[max_key] /
				count_sym[i]; // Узнаем во сколько раз меньше даное количество повторений от максимального количества повторений
			count_fill_sym[i] =
				diagram_size /
				how_many_times_less; // Берем часть от всего размера и записываем в массив с количеством "х"
		}
	}

	// SORTING
	int swap = 0;
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1; j++) {
			if (count_fill_sym[j] < count_fill_sym[j + 1]) {
				swap = count_fill_sym[j];
				count_fill_sym[j] = count_fill_sym[j + 1];
				count_fill_sym[j + 1] = swap;

				swap = sym[j];
				sym[j] = sym[j + 1];
				sym[j + 1] = swap;
			}
		}
	}

	for (int i = 0; i < count; i++) { // Виводим на экран результат
		printf("%c => ", sym[i]);
		for (int j = 0; j < (int)count_fill_sym[i]; j++) {
			printf("%c", fill_symbol);
		}
		printf("\n");
	}
}

void sort_array_desc_ranged(int data[], int size, int low_range, int high_range)
{
	if (low_range >= size || low_range < 0) {
		low_range = 0;
	}
	if (high_range >= size || high_range < 0) {
		high_range = size - 1;
	}
	if (low_range > high_range) {
		return;
	}

	for (int i = low_range; i < high_range; i++) {
		for (int j = low_range; j < high_range; j++) {
			if (data[j] > data[j + 1]) {
				data[j] = data[j] + data[j + 1];
				data[j + 1] = data[j] - data[j + 1];
				data[j] = data[j] - data[j + 1];
			}
		}
	}
}

#undef DELTA
