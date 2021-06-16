#pragma once
#include <vector>
#include <assert.h>

using namespace std;

template<typename T>
class Matrix {
public:
	int rows, cols;
	vector<vector<T> > data;

	Matrix(int rows = 1, int cols = 1, T defaultData = T());
	Matrix(const vector<vector<T> >& data);
	Matrix(const Matrix<T>& m);

	void SetDimensions(int rows, int cols);
	void SetData(const vector<vector<T> >& data);
	void SetData(const T& data);
	vector<T> GetRow(int index) const;
	vector<T> GetCol(int index) const;
	void Randomize();

	static vector<T> ToArray(const Matrix<T>& m);
	static Matrix<T> FromArray(const vector<T>& arr);

	static Matrix<T> Product(const Matrix<T>& a, const Matrix<T>& b);
	static Matrix<T> Transpose(const Matrix<T>& m);
	static Matrix<T> ElementWise(const Matrix<T>& a, const Matrix<T>& b, T func(const T&, const T&));
	void Scale(T func(const T&));
};


// **************  Implementation  ************** //

template<typename T> Matrix<T>::Matrix(int rows, int cols, T defaultData) {
	SetDimensions(rows, cols);
	SetData(defaultData);
}
template<typename T> Matrix<T>::Matrix(const vector<vector<T> >& data) {
	for (int i = 1; i < data.size(); i++)
		assert(data[0].size() == data[i].size());

	SetDimensions(data.size(), data[0].size());
	SetData(data);
}
template<typename T> Matrix<T>::Matrix(const Matrix<T>& m) {
	SetDimensions(m.rows, m.cols);
	SetData(m.data);
}


template<typename T> void Matrix<T>::SetDimensions(int rows, int cols) {
	this->rows = rows;
	this->data.resize(rows);
	this->cols = cols;
	for (auto& v : this->data) v = vector<T>(cols, T());
}
template<typename T> void Matrix<T>::SetData(const vector<vector<T> >& data) {
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->data[i][j] = T(data[i][j]);
}
template<typename T> void Matrix<T>::SetData(const T& data) {
	for (int i = 0; i < this->rows; i++)
		this->data[i] = vector<T>(this->cols, data);
}
template<typename T> vector<T> Matrix<T>::GetRow(int index) const {
	assert(index >= 0 && index < this->rows);

	vector<T> result = vector<T>(this->cols);
	for (int i = 0; i < this->cols; i++)
		result[i] = T(this->data[index][i]);
	return result;
}
template<typename T> vector<T> Matrix<T>::GetCol(int index) const {
	assert(index >= 0 && index < this->cols);

	vector<T> result = vector<T>(this->rows);
	for (int i = 0; i < this->rows; i++) result[i] = T(this->data[i][index]);
	return result;
}
template<typename T> void Matrix<T>::Randomize() {
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->data[i][j] = T::Random();
}


template<typename T> vector<T> Matrix<T>::ToArray(const Matrix<T>& m) {
	vector<T> result = vector<T>(this->rows * this->cols);
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; j++)
			result[i] = T(m.data[i][j]);
	return result;
}
template<typename T> Matrix<T> Matrix<T>::FromArray(const vector<T>& arr) {
	Matrix<T> result = Matrix<T>(arr.size());
	for (int i = 0; i < arr.size(); i++)
		result.data[i][0] = T(arr[i]);
	return result;
}


template<typename T> Matrix<T> Matrix<T>::Product(const Matrix<T>& a, const Matrix<T>& b) {
	assert(a.cols == b.rows);

	Matrix<T> result = Matrix<T>(a.rows, b.cols);
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			result.data[i][j] = T::DotProduct(a.GetRow(i), b.GetCol(j));
	return result;
}
template<typename T> Matrix<T> Matrix<T>::Transpose(const Matrix<T>& m) {
	Matrix<T> result = Matrix<T>(m.cols, m.rows);
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; j++)
			result.data[j][i] = T(m.data[i][j]);
	return result;
}
template<typename T> Matrix<T> Matrix<T>::ElementWise(const Matrix<T>& a, const Matrix<T>& b, T func(const T&, const T&)) {
	assert(a.rows == b.rows && a.cols == b.cols);

	Matrix<T> result = Matrix<T>(a.rows, a.cols);
	for (int i = 0; i < a.rows; i++)
		for (int j = 0; j < a.cols; j++)
			result.data[i][j] = func(a.data[i][j], b.data[i][j]);
	return result;
}
template<typename T> void Matrix<T>::Scale(T func(const T&)) {
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			this->data[i][j] = func(this->data[i][j]);
}
