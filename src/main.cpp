#include "Engine.h"
#include "Test.h"
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

const int I = 10;
const vector<double> M = { 20,75,100,105,75,0 };
const vector<double> V = { 0,75,150,200,250,300 };
const double T = 110;
const double Hm = 0.01;
const double Hv = 0.0001;
const double C = 0.1;


int main()
{
	double environmental_temperature;
	cout << "Enter environmental temperature: ";
	cin >> environmental_temperature;
	shared_ptr<Engine> engine = make_shared<InternalCombustionEngine>(I, M, V,T, Hm, Hv, C,environmental_temperature);
	TestOverHeat overheat;
	overheat.RunTest(engine);
	overheat.PrintResult();
	TestMaxPower maxpower;
	maxpower.RunTest(engine);
	maxpower.PrintResult();

	return 0;
}
