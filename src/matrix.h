#pragma once

#include "coordinate.h"

/**
 * <b> Contains value of matrix and rows, columns </b>
 * <ul>
 * <li> data - 2d array which contains value </li>
 * <li> rows - count of rows in matrix </li>
 * <li> cols - count of columns in matrix </li>
 * </ul>
*/
struct matrix {
	/// 2d array which contains value
	double **data;
	/// count of rows in matrix
	size_t rows;
	/// count of columns in matrix
	size_t cols;
};

/**
 * <b> Memory fill function </b>
 * 
 * @param source - struct matrix
 * @return source
*/
struct matrix alloc_matrix(struct matrix source);

/**
 * <b> Free memory function </b>
 * 
 * @param source - struct matrix
 * @return source
*/
struct matrix free_matrix(struct matrix source);

/**
 * <b> Function displayed 2d array </b>
 * 
 * @param array - which we need to display
 * @param rows
 * @param cols
*/
void print_2d_array(int *array, int rows, int cols);

/**
 * <b> Function displayed matrix </b>
 * 
 * @param source - struct matrix
*/
void print_matrix(struct matrix source);

/**
 * <b> Function copy matrix in new matrix </b>
 * 
 * First of all, create new matrix with rows and columns which equal old matrix
 * Second, in loop in loop copy old array in new
 * 
 * @param source - struct matrix
 * @return r - result
*/
struct matrix copy_matrix(struct matrix source);

/**
 * <b> Function multiplyed matrix by value </b>
 * 
 * Make new matrix, which size = size source matrix
 * Make loop in loop, where everyone elemnt multiplyed by value
 * 
 * @param source - struct matrix
 * @param lamda - value
 * @return r - result
*/
struct matrix mul_matrix_by_value(struct matrix source, double lamda);

/**
 * <b> Function to matrix1 add matrix2 </b>
 * 
 * Make variable which will be result of sum
 * Make condition, if size of matrix1 != size of matrix2, than displayed what we can't sum this matrixes
 * Else make loop in loop, and everyone element of matrix1 add to element matrix2
 * 
 * @param source1 - struct matrix1
 * @param source2 - struct matrix2
 * 
 * @return r - result
*/
struct matrix sum_matrix(struct matrix source1, struct matrix source2);

/**
 * <b> Multiplication function of two matrices </b>
 * 
 * 
 * Make new matrix (result)
 * Make compare, if (ROW1 == COLS2 && ROW2 == COL1), this is the main compare where we want to multiply the matrixes
 * Fill new matrix by
 * Make loop in loop in loop, which write in new matrix result multiply of two matrix
 * 
 * 
 * @param source1 - struct matrix1
 * @param source2 - struct matrix2
 * 
 * @return r - result
*/
struct matrix mul_matrix(struct matrix source1, struct matrix source2);

/**
 * <b> Matrix transpose function  </b>
 * 
 * 
 * Make new matrix (result)
 * Make loop in loop, which write result in new matrix
 * 
 * @param source1 - struct matrix1
 * @param source2 - struct matrix2
 * 
 * @return r - result
*/
struct matrix transpose_matrix(struct matrix source);

/**
 * <b> Find matrix determinant  </b>
 * 
 * 
 * Make compare, if rows != cols, we can't find determinant
 * Make compare if rows and columns == 1, then determinant equal first element in matrix
 * Make compare if rows and columns == 2, then find determinant using formula
 * Make compare if rows nad columns > 2, then make loop in loop in loop, which make part of matrix and find determinant this part of matrix, after that det of new matrix we multiplyed by 'ij' element of origin matrix.
 * After we add or take away from det what we take in previos paragraph
 * 
 * @param source1 - struct matrix
 * 
 * @return det - determinant
*/
double get_matrix_determinant(struct matrix source);

/**
 * <b> Function make with input matrix inverse matrix  </b>
 * 
 * Make compare, if determinant of input matrix == 0 then displayed about this, and return function
 * In compare make matrixes which help to find inverse matrix: transpose matrix, union matrix based on transpose, and algorithmic addition matrix.
 * For algorithmic addition matrix make size (rows, columns) less by 1
 * Make loop in loop which create algorithmic addition from transpose matrix, after get matrix determinant from algorithmic addition and write this det to element of union matrix
 * After loop in loop find inverse matrix, just divide union matrix by determinant of input matrix.
 * 
 * @param source - input matrix
 * 
 * @return inverse - inverse matrix
*/
struct matrix get_inverse_matrix(struct matrix source);
