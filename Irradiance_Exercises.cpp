//Compute the irradiance at a point due to a unit-radius disk h units directly above its normal with constant outgoing radiance of 10 W/m^2 sr. 
// Do the computation twice, once as an integral over solid angle and once as an integral over area. 

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <functional>


using namespace std;

// Define pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// Define h 
#ifndef h
#define h 7
#endif

// Define the constant outgoing radiance
#ifndef L
#define L 10
#endif

// Define the radius of the disk
#ifndef r
#define r 1
#endif



// The disk subtends a solid angle omega at the surface point. We can take the diffierential form of omega as 
// d_omega = r/(r^2 + h^2) * h * d_r * d_theta
// The irradiance at the point is the integral of the radiance over the solid angle subtended by the disk.

double static CalculateIrradiance(double rad, double dist)
{
	double d_I = (rad / (pow(pow(rad,2) + pow(dist,2),(5/2)))) * dist;
	return d_I;
}

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

double MonteCarloIntegrator(function<double(double, double)> func, double lowerBound, double upperBound, int n) {

	vector<double> randPoints = generateRandomNumbers(n, lowerBound, upperBound);
	double result = 0.0;
	double constant = h;

	for (double num : randPoints) {
		result += func(num, constant);
	}

	return ((upperBound - lowerBound) * result) / n;
}

int main() {}




}