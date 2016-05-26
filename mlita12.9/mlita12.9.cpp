#include "stdafx.h"
#include "Data.h"

void InitializationMatrix(std::vector<std::vector<Pole>> & area, int h, int w)
{
	area.resize(h);
	for (int i = 0; i < h; i++)
	{
		area[i].resize(w);
	}	
}

void ReadFile(std::vector<std::vector<Pole>> & area) 
{
	std::ifstream inputFile("input.txt");
	int height, width;
	inputFile >> height;
	inputFile >> width;
	InitializationMatrix(area, height, width);
	std::string str;
	for (int n = 0; n < height; n++)
	{
		inputFile >> str;
		for (int m = 0; m < width; m++)
		{
			if (str[m] == '.')
			{
				area[n][m].size = 0.0001;
			}
			else if (str[m] == '@')
			{
				area[n][m].size = 1.0;
			}
		}
	}

}

void CheckNeighborItem(int n, int m, int nNext, int mNext, std::vector<std::vector<Pole>> & area)
{
	if (!(nNext >= 0 && nNext < area.size() && mNext >= 0 && mNext < area[nNext].size()))
	{
		return;
	}
	if (area[nNext][mNext].isSteped)
	{
		return;
	}
	if (area[nNext][mNext].allWay == 0 || area[nNext][mNext].allWay > area[n][m].allWay + area[nNext][mNext].size)
	{
		area[nNext][mNext].allWay = area[n][m].allWay + area[nNext][mNext].size;
	}
}

void ProcessItem(int n, int m, std::vector<std::vector<Pole>> & area)
{
	CheckNeighborItem(n, m, n, m + 1, area);
	CheckNeighborItem(n, m, n, m - 1, area);
	CheckNeighborItem(n, m, n + 1, m, area);
	CheckNeighborItem(n, m, n - 1, m, area);
	area[n][m].isSteped = true;
	
}

bool FindeNextItem(std::vector<std::vector<Pole>> & area, int & n, int & m)
{
	n = -1;
	for (int i = 0; i < area.size(); i++)
	{
		for (int k = 0; k < area[i].size(); k++)
		{
			if (!area[i][k].isSteped && (n == -1 || area[i][k].allWay < area[n][m].allWay) && area[i][k].allWay != 0)
			{
				n = i;
				m = k;
			}
		}
	}
	if (n == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void FindWay() 
{
	std::vector<std::vector<Pole>> area;
	ReadFile(area);
	area[0][0].allWay = area[0][0].size;
	ProcessItem(0, 0, area);
	int nNext, mNext;
	while (FindeNextItem(area, nNext, mNext) && !(nNext == area.size() - 1 && mNext == area[nNext].size() - 1))
	{
		ProcessItem(nNext, mNext, area);
	}
	std::ofstream outputFile("output.txt");
	int countLand = round((area[nNext][mNext].allWay - (double)((int)area[nNext][mNext].allWay)) * 10000);
	outputFile << (int)area[nNext][mNext].allWay << " " << countLand;
}


int main()
{
	FindWay();
    return 0;
}

