/**
 * @file matrix.c
 * <b> Implemantation of function for Task02/day03 </b>
 * 
 * @author Kushch A.E.
*/

#include "matrix.h"

struct matrix alloc_matrix(struct matrix source)
{
	source.data = (double **)malloc(sizeof(double) * source.rows);
	for (size_t i = 0; i < source.rows; i++) {
		source.data[i] = (double *)malloc(sizeof(double) * source.cols);
	}

	return source;
}

struct matrix free_matrix(struct matrix source)
{
	for (size_t i = 0; i < source.rows; i++) {
		free(source.data[i]);
	}
	free(source.data);

	return source;
}

void print_2d_array(int *array, int rows, int cols)
{
	for (int i = 0, k = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++, k++) {
			printf("%5i", array[k]);
		}
		printf("\n");
	}
}

void print_matrix(struct matrix source)
{
	for (unsigned int i = 0; i < source.rows; i++) {
		for (unsigned int j = 0; j < source.cols; j++) {
			printf("%7.2f", source.data[i][j]);
		}
		printf("\n");
	}
}

struct matrix copy_matrix(struct matrix source)
{
	struct matrix r; // result
	r.rows = source.rows;
	r.cols = source.cols;

	r.data = (double **)malloc(sizeof(double) * r.rows);
	for (unsigned int i = 0; i < r.rows; i++) {
		r.data[i] = (double *)malloc(sizeof(double) * r.cols);
	}

	for (unsigned int i = 0; i < r.rows; i++) {
		for (unsigned int j = 0; j < r.cols; j++) {
			r.data[i][j] = source.data[i][j];
		}
	}

	return r;
}

struct matrix mul_matrix_by_value(struct matrix source, double lamda)
{
	struct matrix r; // result
	r.rows = source.rows;
	r.cols = source.cols;

	r.data = (double **)malloc(sizeof(double) * r.rows);
	for (unsigned int i = 0; i < r.rows; i++) {
		r.data[i] = (double *)malloc(sizeof(double) * r.cols);
	}

	for (unsigned int i = 0; i < source.rows; i++) {
		for (unsigned int j = 0; j < source.cols; j++) {
			r.data[i][j] = source.data[i][j] * lamda;
		}
	}
	return r;
}

struct matrix sum_matrix(struct matrix source1, struct matrix source2)
{
	struct matrix r;
	r.rows = source1.rows;
	r.cols = source1.cols;

	r.data = (double **)malloc(sizeof(double) * r.rows);
	for (unsigned int i = 0; i < r.rows; i++) {
		r.data[i] = (double *)malloc(sizeof(double) * r.cols);
	}

	if (source1.cols == source2.cols && source1.rows == source2.rows) {
		for (unsigned int i = 0; i < source1.rows; i++) {
			for (unsigned int j = 0; j < source1.cols; j++) {
				r.data[i][j] =
					source1.data[i][j] + source2.data[i][j];
			}
		}
	} else {
		printf("Size source1 must be equal size source2\n");
	}

	return r;
}

struct matrix mul_matrix(struct matrix source1, struct matrix source2)
{
	struct matrix r;
	r.rows = source1.rows;
	r.cols = source2.cols;

	r = alloc_matrix(r);

	if (source1.cols == source2.rows) {
		for (unsigned int i = 0; i < r.rows; i++) {
			for (unsigned int j = 0; j < r.cols; j++) {
				r.data[i][j] = 0;
			}
		}

		for (unsigned int i = 0; i < r.rows; i++) {
			for (unsigned int j = 0; j < r.cols; j++) {
				for (unsigned int k = 0; k < source1.cols;
				     k++) {
					r.data[i][j] += source1.data[i][k] *
							source2.data[k][j];
				}
			}
		}

		return r;
	} else {
		printf("Error, matrixes can't be multiplyed\n");
		return r;
	}
}

struct matrix transpose_matrix(struct matrix source)
{
	struct matrix r; //result
	r.rows = source.cols;
	r.cols = source.rows;

	r.data = (double **)malloc(sizeof(double) * r.rows);
	for (unsigned int i = 0; i < r.rows; i++) {
		r.data[i] = (double *)malloc(sizeof(double) * r.cols);
	}

	for (unsigned int i = 0; i < source.rows; i++) {
		for (unsigned int j = 0; j < source.cols; j++) {
			r.data[j][i] = source.data[i][j];
		}
	}

	return r;
}

double get_matrix_determinant(struct matrix source)
{
	double det = 0; // determinant
	if (source.rows != source.cols) {
		printf("Determinant of matrix can't be count\n");
		return 0;
	}
	if (source.rows == 1) {
		det = source.data[0][0];
		return det;
	}
	if (source.rows == 2) {
		for (unsigned int i = 0; i < source.rows - 1; i++) {
			for (unsigned int j = 0; j < source.cols; j++) {
				if (j % 2 == 0) {
					det += source.data[i][j] *
					       source.data[i + 1][j + 1];
				} else {
					det -= source.data[i][j] *
					       source.data[j][i];
				}
			}
		}
		return det;
	}
	if (source.rows > 2) {
		struct matrix new_source;
		new_source.rows = source.rows - 1;
		new_source.cols = source.cols - 1;

		new_source = alloc_matrix(new_source);

		unsigned int k = 0, l = 0, i = 0;

		for (unsigned int j = 0; j < source.cols; j++) {
			for (unsigned int ni = 0; ni < source.rows; ni++) {
				for (unsigned int nj = 0; nj < source.rows;
				     nj++) {
					if (ni != i && nj != j) {
						new_source.data[k][l] =
							source.data[ni][nj];
						l++;
						if (l >= new_source.rows) {
							l = 0;
							k++;
						}
					}
				}
			}
			l = 0;
			k = 0;

			if (j % 2 == 0) {
				det += source.data[i][j] *
				       get_matrix_determinant(new_source);
			} else {
				det -= source.data[i][j] *
				       get_matrix_determinant(new_source);
			}
		}

		new_source = free_matrix(new_source);

		return det;
	}
	return 0;
}

struct matrix get_inverse_matrix(struct matrix source)
{
	struct matrix inverse;
	inverse.rows =
		0; // In future, when I'll clean member, make copmare if rows == 0 then membernot clean.

	if (get_matrix_determinant(source) != 0) {
		struct matrix trans_mat = transpose_matrix(source);
		struct matrix union_mat;
		struct matrix alg_add;

		union_mat.rows = trans_mat.rows;
		union_mat.cols = trans_mat.cols;
		alg_add.rows = alg_add.cols = source.rows - 1;

		union_mat = alloc_matrix(union_mat);

		alg_add = alloc_matrix(alg_add);

		size_t k = 0, l = 0;

		for (size_t i = 0; i < union_mat.rows; i++) {
			for (size_t j = 0; j < union_mat.cols; j++) {
				for (size_t ni = 0; ni < union_mat.rows; ni++) {
					for (size_t nj = 0; nj < union_mat.cols;
					     nj++) {
						if (ni != i && nj != j) {
							alg_add.data[k][l] =
								trans_mat.data
									[ni][nj];
							l++;
							if (l >= alg_add.rows) {
								l = 0;
								k++;
							}
						}
					}
				}
				k = 0;
				l = 0;

				if ((i + j) % 2 == 0) {
					union_mat.data[i][j] =
						get_matrix_determinant(alg_add);
				} else {
					union_mat.data[i][j] =
						-get_matrix_determinant(
							alg_add);
				}
			}
		}

		inverse = mul_matrix_by_value(
			union_mat, 1 / get_matrix_determinant(source));

		trans_mat = free_matrix(trans_mat);
		union_mat = free_matrix(union_mat);
		alg_add = free_matrix(alg_add);

		return inverse;
	} else {
		printf("Determinant can't be equal 0\n");
		return inverse;
	}
}
