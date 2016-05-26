#include "stdafx.h"
#include "Data.h"

bool ReadFile(std::vector<Planet> & fuelPlanet)
{
	try
	{
		std::ifstream inputFile("input.txt");
		size_t countPlanet;
		inputFile >> countPlanet;
		if (!(countPlanet >= MIN_COUNT_PLANETS && countPlanet <= MAX_COUNT_PLANETS))
			throw std::out_of_range("");
		fuelPlanet.resize(countPlanet);
		for (int i = 0; i < countPlanet; i++)
		{
			inputFile >> fuelPlanet[i].typeFuel;
		}
		return true;
	}
	catch (...)
	{
		std::cout << "File not exist or wrong file format." << std::endl;
		return false;
	}
}

int TreatmentPlanet(std::vector<Planet> & planets, int numberOfPlanet , int startStep)
{
	bool isNextPlanetTrue = true;
	if (startStep <= planets[numberOfPlanet].nextPlanetWithSameFuel)
	{
		while (isNextPlanetTrue && startStep < planets.size())
		{
			if (planets[numberOfPlanet].typeFuel == planets[startStep].typeFuel)
			{
				isNextPlanetTrue = false;
			}
			if (planets[startStep].countFlight == 0 || planets[startStep].countFlight < planets[numberOfPlanet].countFlight)
			{
				planets[startStep].previousPlanet = numberOfPlanet;
				planets[startStep].countFlight = planets[numberOfPlanet].countFlight + 1;
			}
			startStep++;
		}
	}
	return startStep;
}

void FindWay(std::vector<Planet> & planets)
{
	int nextStep = 1;
	for (int i = 0; i < planets.size() - 1; i++)
	{
		if (planets[i].isGoodPlanet)
		{
			nextStep = TreatmentPlanet(planets, i, nextStep);
		}
	}
}

void MarksPlanets(std::vector<Planet> & planets)
{
	planets[planets.size() - 1].isGoodPlanet = false;
	std::map<int, int> discoveredPlanet;
	bool isLastPlanetOnes = true;
	discoveredPlanet[planets[planets.size() - 1].typeFuel] = planets.size() - 1;
	for (int i = planets.size() - 2; i >= 0; i--)
	{
		auto planetItr = discoveredPlanet.find(planets[i].typeFuel);
		if (planetItr != discoveredPlanet.end())
		{
			planets[i].nextPlanetWithSameFuel = planetItr->second;
			planetItr->second = i;
		}
		
		if (isLastPlanetOnes || planetItr == discoveredPlanet.end() || planets[i].typeFuel == planets[i + 1].typeFuel)
		{
			if (planets[i].typeFuel != planets[planets.size() - 1].typeFuel)
			{
				planets[i].isGoodPlanet = false;
			}
			else
			{
				isLastPlanetOnes = false;
			}
			discoveredPlanet[planets[i].typeFuel] = i;
		}

	}
}


void OutputResult(std::vector<Planet> & planets)
{
	std::ofstream outputFile("output.txt");
	if (planets[planets.size() - 1].countFlight == 0)
	{
		outputFile << 0;
	}
	else
	{
		std::vector<int> way;
		outputFile << planets[planets.size() - 1].countFlight <<std::endl;
		int i = planets[planets.size() - 1].previousPlanet;
		while (i != -1)
		{
			way.insert(way.begin(), i);
			i = planets[i].previousPlanet;
		}
		for (auto k : way)
		{
			outputFile << k + 1 << " ";
		}
	}
}

void StarWay()
{
	std::vector<Planet> planets;
	if (ReadFile(planets))
	{
		MarksPlanets(planets);
		FindWay(planets);
		OutputResult(planets);
	}
}

int main()
{
	StarWay();
    return 0;
}

