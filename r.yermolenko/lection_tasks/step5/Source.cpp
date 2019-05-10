#include <string>
#include <iostream>
#include "ParticleDefinition.h"
#include <limits>

int main()
{
	ParticleDefinition<double> p;
	p.setMass(1.007276466879);
	p.setName("proton");
	std::cout.precision(std::numeric_limits< double >::max_digits10);
	std::cout << "mass = " << p.getMass() << std::endl;
	std::cout << "Name: " << p.getName() << std::endl;
	return 0;
}