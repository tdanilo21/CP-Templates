#pragma once
#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std;

// ************ class Layer ************ //

class Layer {
	
private:
	int size;
	// Bias represent values of bias that go into next layer
	Matrix values, weights, bias;

public:
	Layer(int size = 0, int next_size = 0);
	Layer(const vector<double>& values, int next_size = 0);
	Layer(const vector<double>& values, const Matrix& weights, int next_size = 0);

	void Resize(int size, int next_size);
	int Size() const;
	void SetValues(const vector<double>& values);
	Matrix GetValues() const;
	void SetWeights(const Matrix& weights);
	Matrix GetWeights() const;
	void SetWeight(int i, int j, double w);
	double GetWeight(int i, int j) const;
	void SetBias(const vector<double>& bias);
	Matrix GetBias() const;

	Matrix Propagate();
	void Reset();
};

// ************ class Net ************ //

class Net
{
private:
	static constexpr double learning_rate = 0.15f;
	int size;
	vector<Layer> layers;

public:
	Net(int size = 0);
	Net(const vector<int>& layout);

	void Resize(int size);
	void SetLayout(const vector<int>& layout);

	void Run(const vector<double>& inputData, vector<double>& outputData);
	void Train(const vector<double>& inputData, vector<double>& outputData, const vector<double>& answer);

private:
	void Reset();
	void FeedForward(const vector<double>& input);
	void GetOutput(vector<double>& output) const;
	void BackPropagate(const vector<double>& answer);
};



#include "NeuralNetwork.h"

// ******************** Lambda Functions ******************** //

// Activation function is Sigmoid:
double ActivationFunction(double x) { return tanh(x); }
double ActivationFunctionDerivative(double x) { return 1.0f - x * x; }

double Multiply(double a, double b) { return a * b; }
double Add(double a, double b) { return a + b; }


// ******************** class Layer ******************** //

Layer::Layer(int size, int next_size) { Resize(size, next_size); }
Layer::Layer(const vector<double>& values, int next_size) { Resize(values.size(), next_size); SetValues(values); }
Layer::Layer(const vector<double>& values, const Matrix& weights, int next_size) {
	Resize(values.size(), next_size);
	SetValues(values);
	SetWeights(weights);
}


void Layer::Resize(int size, int next_size) {
	this->size = size;
	this->values = Matrix(size);
	this->weights = Matrix(size, next_size, 1);
	this->bias = Matrix(next_size, 1, 1);
}
int Layer::Size() const { return size; }
void Layer::SetValues(const vector<double>& values) {
	this->values = Matrix::FromArray(values);
	this->size = values.size();
}
Matrix Layer::GetValues() const { return this->values; }
void Layer::SetWeights(const Matrix& weights) { this->weights.Copy(weights); }
Matrix Layer::GetWeights() const { return this->weights; }
void Layer::SetWeight(int i, int j, double w) {
	this->weights.Valid(i, j);

	this->weights.data[i][j] = w;
}
double Layer::GetWeight(int i, int j) const {
	this->weights.Valid(i, j);

	return this->weights.data[i][j];
}
void Layer::SetBias(const vector<double>& bias) { this->bias = Matrix::FromArray(bias); }
Matrix Layer::GetBias() const { return this->bias; }


Matrix Layer::Propagate() {
	Matrix weights_T = Matrix::Transpose(this->weights);
	Matrix values_next = Matrix::Product(weights_T, this->values);
	values_next = Matrix::ElementWise(values_next, this->bias, [](double a, double b) { return a + b; });
	values_next.Scale(ActivationFunction);
	return values_next;
}
void Layer::Reset() { this->values = Matrix(size); }


// ******************** class Net ******************** //

Net::Net(int size) { Resize(size); }
Net::Net(const vector<int>& layout) { SetLayout(layout); }


void Net::Resize(int size) { this->size = size; this->layers = vector<Layer>(size); }
void Net::SetLayout(const vector<int>& layout) {
	Resize(layout.size());
	for (int i = 0; i < this->size; i++) {
		int next_size = (i == this->size - 1 ? 0 : layout[i + 1]);
		this->layers[i] = Layer(layout[i], next_size);
	}
}


void Net::Run(const vector<double>& inputData, vector<double>& outputData) {
	Reset();
	FeedForward(inputData);
	GetOutput(outputData);
}
void Net::Train(const vector<double>& inputData, vector<double>& outputData, const vector<double>& answer) {
	Run(inputData, outputData);
	BackPropagate(answer);
}


void Net::Reset() { for (auto& l : layers) l.Reset(); }
void Net::FeedForward(const vector<double>& input) {
	this->layers[0].SetValues(input);
	for (int i = 0; i < size - 1; i++) {
		Matrix next_values = this->layers[i].Propagate();
		layers[i + 1].SetValues(Matrix::ToArray(next_values));
	}
}
void Net::GetOutput(vector<double>& output) const { output = Matrix::ToArray(this->layers.back().GetValues()); }
void Net::BackPropagate(const vector<double>& answer){
	// Calculating errors for the last layer:
	vector<Matrix> errors(this->size);
	errors.back() = Matrix::ElementWise(Matrix::FromArray(answer), this->layers.back().GetValues(),
		[](double a, double b) { return (a - b) * (a - b); });

	// Calculating derivatives for the last layer:
	vector<Matrix> derivatives = vector<Matrix>(this->size);
	derivatives.back() = Matrix::ElementWise(Matrix::FromArray(answer), this->layers.back().GetValues(),
		[](double a, double b) { return 2 * (a - b); });

	// Back propagating:
	for (int i = this->size - 2; i >= 0; i--) {
		Matrix weights = this->layers[i].GetWeights();
		Matrix bias = this->layers[i].GetBias();
		Matrix previous_values_T = Matrix::Transpose(this->layers[i].GetValues());
		Matrix next_values = this->layers[i + 1].GetValues();

		// Calculating gradient descent:
		// (this formula is for activation function sigmoid)
		Matrix gradient = next_values;
		gradient.Scale(ActivationFunctionDerivative);


		// Calculating delta weights:
		Matrix delta_weights = Matrix::ElementWise(errors[i + 1], gradient, Multiply);
		delta_weights = Matrix::ElementWise(delta_weights, derivatives[i + 1], Multiply);
		delta_weights = Matrix::Product(delta_weights, previous_values_T);
		delta_weights.Scale([](double x) { return Net::learning_rate * x; });
		delta_weights = Matrix::Transpose(delta_weights);

		// Adjusting weights:
		this->layers[i].SetWeights(Matrix::ElementWise(weights, delta_weights, Add));


		// Calculating delta biases:
		Matrix delta_bias = Matrix::ElementWise(errors[i + 1], gradient, Multiply);
		delta_bias = Matrix::ElementWise(delta_bias, derivatives[i + 1], Multiply);
		delta_bias.Scale([](double x) { return Net::learning_rate * x; });

		// Adjusting biases:
		this->layers[i].SetBias(Matrix::ToArray(Matrix::ElementWise(bias, delta_bias, Add)));


		// Calculating derivatives for this layer:
		derivatives[i] = Matrix::ElementWise(derivatives[i + 1], gradient, Multiply);
		derivatives[i] = Matrix::Product(weights, derivatives[i]);

		// Calculating errors for this layer:
		errors[i] = Matrix::Product(weights, errors[i + 1]);
	}
}
