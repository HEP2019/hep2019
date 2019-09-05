#pragma once
#include <string>
class ParticleDefinition
{
public:
	std::string name;
	float mass;
	float Px;
	float Py;
	float Pz;
	float E;
	float getEnergy();
};