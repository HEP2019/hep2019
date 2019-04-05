#include <string>
#include <iostream>
#include "ParticleDefinition.h"

int main()
{
	ParticleDefinition p;
	p.setMass(1.f);
	p.setName("proton");
	std::cout << "mass = " << p.getMass() << std::endl;
	std::cout << "Name: " << p.getName() << std::endl;
	return 0;
}