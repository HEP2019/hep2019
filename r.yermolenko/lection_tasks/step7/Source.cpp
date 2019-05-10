#include <string>
#include <iostream>
#include "electron.h"
#include <limits>

int main()
{
	Electron<double> e;
	std::cout.precision(std::numeric_limits< double >::max_digits10);
	std::cout << "mass = " << e.getMass() << std::endl;
	std::cout << "Name: " << e.getName() << std::endl;
	std::cout << "Family: " << e.getFamily() << std::endl;
	std::cout << "Spin: " << e.getSpin() << std::endl;
	std::cout << "ElectricCharge: " << e.getElectricCharge() << std::endl;
	//e.~Electron();
	return 0;
}