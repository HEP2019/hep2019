#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "electron.h"
#include "photon.h"
#include "I_ParticleDefinition.h"


int main()
{
	Electron<double> e(0.01);
	std::cout.precision(std::numeric_limits< double >::max_digits10);
	std::cout << "E: " << e.getE() << std::endl;
	Photon<double> p(0.02);
	std::cout << "E: " << p.getE() << std::endl;

	std::vector<std::unique_ptr<IParticleDefinition<double>>> particals;
	std::unique_ptr<IParticleDefinition<double>> pt;
	for (int num = 0; num < 100; ++num)
	{
		if (static_cast<float>(std::rand()) / RAND_MAX < 0.5)
		{
			pt = std::unique_ptr<IParticleDefinition<double>>(new Electron<double>(static_cast<float>(std::rand()) / RAND_MAX));
		}
		else
		{
			pt = std::unique_ptr<IParticleDefinition<double>>(new Photon<double>(static_cast<float>(std::rand()) / RAND_MAX));
		}
		particals.emplace_back(std::move(pt));
	}
	
	for (auto const& particle : particals)
	{
		double E = particle->getE();
		std::cout << "name: " << particle->getName() << "\tE:" << E << "\n";
	}
	return 0;
}