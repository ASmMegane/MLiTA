#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

const unsigned int MIN_COUNT_PLANETS = 2;
const unsigned int MAX_COUNT_PLANETS = 300000;

struct Planet
{
	size_t countFlight = 0;
	size_t typeFuel;
	int previousPlanet = -1;
	bool isGoodPlanet = true;
	int nextPlanetWithSameFuel = -1;
};
