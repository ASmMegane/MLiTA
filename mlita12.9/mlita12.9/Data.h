#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <io.h>
#include <list>

const unsigned short MIN_NUM = 1;
const unsigned short MAX_NUM = 50;
const double WEIGHT_WATER = 1.0;
const double WEIGHT_LAND = 0.0001;

struct Pole
{
	double size = 0;
	double allWay = 0;
	bool isVisited = false;
};