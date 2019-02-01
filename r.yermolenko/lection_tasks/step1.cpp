#include <string>
#include <iostream>

class ParticleDefinition
{
public:
	std::string name;
	float mass;
	float Px;
	float Py;
	float Pz;
	float E;
	float getEnergy() {return E;}
};


int main()
{
	ParticleDefinition p;
	p.mass = 1;
	p.E = 2;
	std::cout << p.getEnergy();
	return 0;
}