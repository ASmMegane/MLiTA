#include "stdafx.h"
#include "Data.h"

void InitializationMatrix(std::vector<std::vector<Pole>> & area, int h, int w)
{
	area.resize(h);
	for (size_t i = 0; i < area.size(); i++)
	{
		area[i].resize(w);
	}	
}

bool ReadFile(std::vector<std::vector<Pole>> & area) 
{
	try
	{
		std::ifstream inputFile("input.txt");
		unsigned short height, width;
		inputFile >> height;
		inputFile >> width;
		if (!(height >= MIN_NUM && height <= MAX_NUM))
			throw std::out_of_range("");
		if (!(width >= MIN_NUM && width <= MAX_NUM))
			throw std::out_of_range("");
		InitializationMatrix(area, height, width);
		std::string str;
		for (size_t n = 0; n < height; n++)
		{
			inputFile >> str;
			for (size_t m = 0; m < width; m++)
			{
				if (str[m] == '.')
				{
					area[n][m].size = WEIGHT_LAND;
				}
				else if (str[m] == '@')
				{
					area[n][m].size = WEIGHT_WATER;
				}
			}
		}
		return true;
	}
	catch (...)
	{
		std::cout << "File not exist or wrong file format." << std::endl;
		return false;
	}
}

void CheckNeighborItem(std::list<std::pair<int, int>>::iterator topToProcessItr, int iNextTop, int jNextTop, std::vector<std::vector<Pole>> & area, std::list<std::pair<int, int>> & availableTops)
{
	//проверка на вхождение точки в границы матрицы
	if (!(iNextTop >= 0 && iNextTop < area.size() && jNextTop >= 0 && jNextTop < area[iNextTop].size()))
	{
		return;
	}
	//выершина должна быть еще не пройдена
	if (area[iNextTop][jNextTop].isVisited)
	{
		return;
	}
	//заполнение веса для вершины
	if (area[iNextTop][jNextTop].allWay == 0 || area[iNextTop][jNextTop].allWay > area[topToProcessItr->first][topToProcessItr->second].allWay + area[iNextTop][jNextTop].size)
	{
		if (area[iNextTop][jNextTop].allWay == 0)
		{
			availableTops.push_back(std::make_pair(iNextTop, jNextTop));
		}
		area[iNextTop][jNextTop].allWay = area[topToProcessItr->first][topToProcessItr->second].allWay + area[iNextTop][jNextTop].size;
	}
}

void ProcessItem(std::list<std::pair<int, int>>::iterator topToProcessItr, std::vector<std::vector<Pole>> & area, std::list<std::pair<int, int>> & availableTops)
{
	CheckNeighborItem(topToProcessItr, topToProcessItr->first, topToProcessItr->second + 1, area, availableTops);
	CheckNeighborItem(topToProcessItr, topToProcessItr->first, topToProcessItr->second - 1, area, availableTops);
	CheckNeighborItem(topToProcessItr, topToProcessItr->first + 1, topToProcessItr->second, area, availableTops);
	CheckNeighborItem(topToProcessItr, topToProcessItr->first - 1, topToProcessItr->second, area, availableTops);
	area[topToProcessItr->first][topToProcessItr->second].isVisited = true;
	availableTops.erase(topToProcessItr);	
}

std::list<std::pair<int, int>>::iterator FindeNextItem(std::list<std::pair<int, int>> & availableTops, std::vector<std::vector<Pole>> & area)
{
	auto nextTopItr = availableTops.begin();
	auto currentTopItr = availableTops.begin();
	while (currentTopItr != availableTops.end())
	{
		if (area[currentTopItr->first][currentTopItr->second].allWay < area[nextTopItr->first][nextTopItr->second].allWay)
		{
			nextTopItr = currentTopItr;
		}
		currentTopItr++;
	}
	return nextTopItr;
}

void FindWay() 
{
	std::vector<std::vector<Pole>> area;
	if (ReadFile(area))
	{
		area[0][0].allWay = area[0][0].size;
		std::list<std::pair<int, int>> availableTops;
		availableTops.push_back(std::make_pair(0, 0));
		auto nextTopItr = availableTops.begin();
		while (nextTopItr != availableTops.end() )
		{
			ProcessItem(nextTopItr, area, availableTops);		
			nextTopItr = FindeNextItem(availableTops, area);
		}
		std::ofstream outputFile("output.txt");
		int height = area.size();
		int width = area[0].size();
		int countLand = round((area[height - 1][width - 1].allWay - (double)((int)area[height - 1][width - 1].allWay)) * (1 / WEIGHT_LAND));
		outputFile << (int)area[height - 1][width - 1].allWay << " " << countLand;
	}
}


int main()
{
	FindWay();
    return 0;
}

