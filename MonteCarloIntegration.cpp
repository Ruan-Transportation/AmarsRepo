// Problem Statement:
// 
// 
//Write a program that compares Monte Carlo and one or more alternative numerical integration techniques.
//Structure this program so that it is easy to replace the particular function being integrated.
//Verify that the different techniques compute the same result(given a sufficient number of samples for each of them).


// General Steps of Monte Carlo Int:
// 1. Define the function to be integrated.
// 2. Define the domain of integration.
// 3. Generate random points in the domain.
// 4. Evaluate the function at each point.
// 5. Compute the average of the function values.
// 6. Multiply the average by the volume of the domain.


#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <functional>

using namespace std;


// Define lower bound of Domain
#ifndef a
#define a 0
#endif 

// Define upper bound of Domain
#ifndef b
#define b 50
#endif 



// Placeholder for function we are testing
double static exampleFunction (double x)
	{
		return x * x;
	}

// Generate Random Numbers
vector<double> generateRandomNumbers(int n, int lowerBound, int upperBound) {
	vector<double> randomNumbers;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(lowerBound, upperBound);
	//normal_distribution<> dis(mean, stddev);
	for (int i = 0; i < n; ++i) {
		randomNumbers.push_back(dis(gen));
	}

	return randomNumbers;
}

// Monte Carlo Integration using process described above
double MonteCarloIntegrator(function<double(double)> func, double lowerBound, double upperBound, int n) {

	vector<double> randPoints = generateRandomNumbers(n, lowerBound, upperBound);
	double result = 0.0;

	for (double num : randPoints) {
		result += func(num);
	}

	return ((upperBound - lowerBound) * result) / n;
}


// Trapezoidal Integration
double TrapezoidalIntegrator(function<double(double)> func, double lowerBound, double upperBound, int n) {
	
	double h = (upperBound - lowerBound) / n;
	double f_a = func(lowerBound);
	double f_b = func(upperBound);
	double result = 0.0;

	// Integral = h/2 * (f(a) + 2*sum(f(xi)) + f(b))

	for (int i = 0; i < n - 1; ++i) {
		
		double x_i = lowerBound + i * h;
		result += func(x_i);
	}

	return (h / 2) * (f_a + (2 * result) + f_b);

}



//int main() {
//	function<double(double)> func = exampleFunction;
//	double integrationresult = MonteCarloIntegrator(func, a, b, 10000);
//	double integrationresult2 = TrapezoidalIntegrator(func, a, b, 10000);
//
//	cout << "Monte Carlo Integration Result: " << integrationresult << "." << endl;
//	cout << "Trapezoidal Integration Result: " << integrationresult2 << "." << endl;
//
//	return 0;
//}