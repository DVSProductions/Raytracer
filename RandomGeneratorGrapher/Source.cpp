#include "Ziggurat.hpp"
#include "ziggurat2.hpp"
#include "cggRandom.h"
#include "Randfast_c.h"
#include "randfast.h"
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
using namespace std;
size_t samples = 500000000;
double resolution = 0.1;
clock_t start_t, end_t;
vector<int> ret;
#define doPrint true
size_t retsize = 0;

void prepareVector() {
	ret.clear();
	for (double n = -1; n <= 1; n += resolution)
		ret.push_back(0);
	retsize = ret.size();
}
void addToVector(double d) {
	const double idx = (1 + d) / resolution;
	if (idx<0 || idx>retsize)return;
	ret[idx]++;
}
#define customTest(name,preamble,generator,cleanup){cout<<"Testing "<<name;preamble prepareVector();start_t = clock(); for(size_t n = 0; n != samples; n++) addToVector(generator);end_t= clock(); cleanup}printresults(name)
#define runBench(type,params) {cout<<"Testing "#type;auto g=type params;prepareVector();start_t = clock(); for(size_t n = 0; n != samples; n++) {addToVector(g(generator));}end_t= clock();}printresults(#type)
void printresults(const char* name) {
	cout << " Completed in " << end_t - start_t << endl;
#if doPrint
	size_t maxv = 0;
	const auto max = ret.size();
	for (size_t n = 0; n < max; n++)if (ret[n] > maxv)maxv = ret[n];
	for (size_t n = 0; n < max; n++) {

		const double v = ((double)ret[n]) / ((double)maxv);
		std::string s = "";
		for (double d = 0; d < v; d += 0.01)
			s += "=";
		if (ret[n] == 0)
			s += "\bX";
		else if (n == 0) {
			if (ret[n + 1] > ret[n])
				s += "\b\\";
			else if (ret[n + 1] < ret[n])
				s += "\b/";
			else
				s += "\b|";
		}
		else if (n == max - 1) {
			if (ret[n - 1] > ret[n])
				s += "\b/";
			else s += "\b|";
		}
		else {
			if (ret[n + 1] > ret[n])
				s += "\b\\";
			else if (ret[n - 1] > ret[n])
				s += "\b/";
			else s += "\b|";
		}
		printf("%+.2lf |%s\n", resolution * n - 1, s.c_str());
		//cout << "\b>" << endl;
	}
	cout << endl;
#endif
}
int main() {
	auto generator = std::mt19937_64(random_device()());
	cout << "Random Tester" << endl;
	cout << "We are testing between -1 and 1" << endl;
	//customTest("cgg Random", auto c = cggRandom(generator());,c.nextDouble(), );
	customTest("Randfast_C", seed_fast(generator()); , rand_fast(), );
	customTest("Randfast_dist_C", seed_fast(generator()); , rand_dist(-1, 1), );
	customTest("Randfast_C++",randfast c(generator()); , c(), );
	customTest("Randfast_dist_C++",randfast c(generator());, c(-1, 1), );
	runBench(uniform_real_distribution<double>, (-1.0, 1.0));
	/*runBench(normal_distribution<double>, (0, 0.25));
	runBench(lognormal_distribution<double>, (-1, 0.25));
	runBench(chi_squared_distribution<double>, (1));
	runBench(cauchy_distribution<double>, (0, 0.1));
	runBench(fisher_f_distribution<double>, (0.1, 0.1));
	runBench(student_t_distribution<double>, (10000000));
	runBench(piecewise_constant_distribution<double>, ());
	runBench(piecewise_linear_distribution<double>, ());
	runBench(cxx::ziggurat_normal_distribution<double>, (0, 0.25));*/
	customTest("Zigguat(2) Origin", auto c = static_cast<uint32_t>(generator()); , r4_uni(c) * 2.0 - 1.0, );
	system("pause");
}