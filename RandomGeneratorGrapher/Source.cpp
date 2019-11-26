#include "Ziggurat.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
using namespace std;
size_t samples = 10000000;
double resolution = 0.03;
clock_t start_t, end_t;
vector<int> ret;
#define doPrint true


void prepareVector() {
	ret.clear();
	for (double n = -1; n <= 1; n += resolution)
		ret.push_back(0);
}
void addToVector(double d) {
	double idx = (1 + d) / resolution;
	if (idx<0 || idx>ret.size())return;
	ret[idx]++;
}
#define runBench(type,params) {cout<<"Testing "#type;auto g=type params;prepareVector();start_t = clock(); for(size_t n = 0; n != samples; n++) {addToVector(g(generator));}end_t= clock();}printresults(#type)
void printresults(const char* name) {
	cout <<" Completed in " << end_t - start_t << endl;
#if doPrint
	size_t maxv = 0;
	auto max = ret.size();
	for (size_t n = 0; n < max; n++)if (ret[n] > maxv)maxv = ret[n];
	for (size_t n = 0; n < max; n++) {
		printf("%+.2lf |", resolution * n - 1);
		double v = ((double)ret[n]) / ((double)maxv);
		for (double d = 0; d < v; d += 0.01)
			cout << "=";
		if (ret[n] == 0)
			cout << "\bX" << endl;
		else if (n == 0) {
			if (ret[n + 1] > ret[n])
				cout << "\b\\" << endl;
			else if (ret[n + 1] < ret[n])
				cout << "\b/" << endl;
			else
				cout << "\b|" << endl;
		}
		else if (n == max - 1) {
			if (ret[n - 1] > ret[n])
				cout << "\b/" << endl;
			else cout << "\b|" << endl;
		}
		else {
			if (ret[n + 1] > ret[n])
				cout << "\b\\" << endl;
			else if (ret[n - 1] > ret[n])
				cout << "\b/" << endl;
			else cout << "\b|" << endl;
		}
		//cout << "\b>" << endl;
	}
	cout << endl;
#endif
}
int main() {
	auto generator = std::ranlux48_base(random_device()());
	cout << "Random Tester" << endl;
	cout << "We are testing between -1 and 1" << endl;
	runBench(uniform_real_distribution<double>, (-1.0, 1.0));
	runBench(normal_distribution<double>, (0, 0.25));
	runBench(lognormal_distribution<double>, (-1, 0.25));
	runBench(chi_squared_distribution<double>, (1));
	runBench(cauchy_distribution<double>, (0, 0.1));
	runBench(fisher_f_distribution<double>, (0.1, 0.1));
	runBench(student_t_distribution<double>, (10000000));
	runBench(piecewise_constant_distribution<double>, ());
	runBench(piecewise_linear_distribution<double>, ());
	runBench(cxx::ziggurat_normal_distribution<double>, ( 0,0.25 ));
	system("pause");
}