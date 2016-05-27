#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

const unsigned int MIN_COUNT_WORD = 1;
const unsigned int MAX_COUNT_WORD = 200000;
const unsigned short MIN_SIZE_WORD = 1;
const unsigned short MAX_SIZE_WORD = 50;

struct Word {
	std::string word;
	int numberSuperfik;
};
