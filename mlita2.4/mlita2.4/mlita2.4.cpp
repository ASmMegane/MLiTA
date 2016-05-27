#include "stdafx.h"
#include "Data.h"

bool ReadFile(std::vector<Planet> & fuelPlanet, const std::string & file)
{
	try
	{
		std::ifstream inputFile(file);
		size_t countPlanet;
		inputFile >> countPlanet;
		if (!(countPlanet >= MIN_COUNT_PLANETS && countPlanet <= MAX_COUNT_PLANETS))
			throw std::out_of_range("");
		fuelPlanet.resize(countPlanet);
		for (size_t i = 0; i < countPlanet; i++)
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

int TreatmentPlanet(std::vector<Planet> & planets, size_t numberOfPlanet , size_t startStep)
{
	bool isNextPlanetExist = true;
	if (startStep <= planets[numberOfPlanet].nextPlanetWithSameFuel)
	{
		while (isNextPlanetExist && startStep < planets.size())
		{
			if (planets[numberOfPlanet].typeFuel == planets[startStep].typeFuel)
			{
				isNextPlanetExist = false;
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
	size_t nextStep = 1;
	for (size_t i = 0; i < planets.size() - 1; i++)
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


void OutputResult(std::vector<Planet> & planets, const std::string & outFile)
{
	std::ofstream outputFile(outFile);
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
		for (auto numberPlanetForFuel : way)
		{
			outputFile << numberPlanetForFuel + 1 << " ";
		}
	}
}

void StarWay(const std::string & inFile, const std::string & outFile)
{
	std::vector<Planet> planets;
	if (ReadFile(planets, inFile))
	{
		MarksPlanets(planets);
		FindWay(planets);
		OutputResult(planets, outFile);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return 1;
	}
	StarWay(argv[1], argv[2]);
    return 0;
}

