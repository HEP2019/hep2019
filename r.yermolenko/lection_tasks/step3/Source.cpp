#include <string>
#include <iostream>
#include "ParticleDefinition.h"



int main()
{
	ParticleDefinition p;
	p.mass = 1;
	p.E = 2;
	std::cout << p.getEnergy();
	return 0;
}