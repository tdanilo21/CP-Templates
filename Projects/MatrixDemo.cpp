#pragma once
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class Matrix
{
public:
	int rows, cols;
	vector<vector<double> > data;

	Matrix(int rows = 1, int cols = 1, bool flag = 0);
	Matrix(int rows, int cols, const vector<vector<double> >& data);
	Matrix(const Matrix& m);

	void SetDimensions(int rows, int cols);
	void SetData(const vector<vector<double> >& data);
	void Randomize();
	void Copy(const Matrix& m);
	void Valid(int i, int j) const;

	static vector<double> ToArray(const Matrix& m);
	static Matrix FromArray(const vector<double>& arr);
		
	static Matrix Product(const Matrix& a, const Matrix& b);
	static Matrix Transpose(const Matrix& m);
	static Matrix ElementWise(const Matrix& a, const Matrix& b, double func(double, double));
	void Scale(double func(double));

	void Print() const;
};


#include "Matrix.h"

double Random() { return ((double)rand() / (double)RAND_MAX) * 2 - 1; }

Matrix::Matrix(int rows, int cols, bool flag) { SetDimensions(rows, cols); if (flag) Randomize(); }
Matrix::Matrix(int rows, int cols, const vector<vector<double> >& data) { SetDimensions(rows, cols); SetData(data); }
Matrix::Matrix(const Matrix& m) { this->Copy(m); }


void Matrix::SetDimensions(int rows, int cols) {
	this->rows = rows;
	this->data.resize(rows);
	this->cols = cols;
	for (auto& v : this->data) v = vector<double>(cols, 0.0f);
}
void Matrix::SetData(const vector<vector<double> >& data) {
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->data[i][j] = data[i][j];
}
void Matrix::Randomize() {
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->data[i][j] = Random();
}
void Matrix::Copy(const Matrix& m) {
	SetDimensions(m.rows, m.cols);
	SetData(m.data);
}
void Matrix::Valid(int i, int j) const { assert(i >= 0 && i < this->rows && j >= 0 && j < this->cols); }


vector<double> Matrix::ToArray(const Matrix& m) {
	vector<double> result;
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; j++)
			result.push_back(m.data[i][0]);
	return result;
}
Matrix Matrix::FromArray(const vector<double>& arr) {
	Matrix result = Matrix(arr.size());
	for (int i = 0; i < arr.size(); i++)
		result.data[i][0] = arr[i];
	return result;
}


Matrix Matrix::Product(const Matrix& a, const Matrix& b) {
	assert(a.cols == b.rows);

	Matrix result = Matrix(a.rows, b.cols);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			double sum = 0.0f;
			for (int k = 0; k < a.cols; k++)
				sum += a.data[i][k] * b.data[k][j];
			result.data[i][j] = sum;
		}
	}
	return result;
}
Matrix Matrix::Transpose(const Matrix& m) {
	Matrix result = Matrix(m.cols, m.rows);
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; j++)
			result.data[j][i] = m.data[i][j];
	return result;
}
Matrix Matrix::ElementWise(const Matrix& a, const Matrix& b, double func(double, double)) {
	assert(a.rows == b.rows && a.cols == b.cols);

	Matrix result = Matrix(a.rows, a.cols);
	for (int i = 0; i < a.rows; i++)
		for (int j = 0; j < a.cols; j++)
			result.data[i][j] = func(a.data[i][j], b.data[i][j]);
	return result;
}
void Matrix::Scale(double func(double)) {
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->data[i][j] = func(this->data[i][j]);
}


void Matrix::Print() const {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++)
			cout << this->data[i][j] << " ";
		cout << '\n';
	}
}
