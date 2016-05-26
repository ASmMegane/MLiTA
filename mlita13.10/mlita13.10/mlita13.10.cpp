#include "stdafx.h"
#include "Data.h"

bool ReadFile(std::vector<std::string> & words, std::vector<std::string> & suprefiks)
{
	try
	{
		std::ifstream inputFile("input.txt");
		int wordsVectorSize;
		inputFile >> wordsVectorSize;
		if (!(wordsVectorSize >= MIN_COUNT_WORD && wordsVectorSize <= MAX_COUNT_WORD))
			throw std::out_of_range("");
		words.resize(wordsVectorSize);
		std::string str;
		for (int i = 0; i < wordsVectorSize; i++)
		{
			inputFile >> str;
			if (!(str.size() >= MIN_SIZE_WORD && str.size() <= MAX_SIZE_WORD))
				throw std::out_of_range("");
			words[i] = str;
		}

		int suprefiksVectorSize;
		inputFile >> suprefiksVectorSize;
		if (!(suprefiksVectorSize >= MIN_COUNT_WORD && suprefiksVectorSize <= MAX_COUNT_WORD))
			throw std::out_of_range("");
		suprefiks.resize(suprefiksVectorSize);
		for (int i = 0; i < suprefiksVectorSize; i++)
		{
			inputFile >> str;
			if (!(str.size() >= MIN_SIZE_WORD && str.size() <= MAX_SIZE_WORD))
				throw std::out_of_range("");
			suprefiks[i] = str;
		}
		return true;
	}
	catch (...)
	{
		std::cout << "File not exist or wrong file format." << std::endl;
		return false;
	}
}


int CountSuprefikWord(const std::vector<Word> & allWord, int startPosition, std::vector<int> & suprefiks)
{
	int countSupref = 0;
	while (startPosition + countSupref + 1 < allWord.size() && allWord[startPosition].word == allWord[startPosition + countSupref + 1].word.substr(0, allWord[startPosition].word.size()))
	{
		countSupref++;
		if (allWord[startPosition + countSupref].numberSuprefik >= 0)
		{
			countSupref += CountSuprefikWord(allWord, startPosition + countSupref, suprefiks);
		}
	}
	suprefiks[allWord[startPosition].numberSuprefik] = countSupref;
	return countSupref;
}

void OutputResult(const std::vector<Word> & allWord, int countSuprefiks)
{
	std::vector<int> suprefiks(countSuprefiks, 0);
	int i = 0;
	while (i < allWord.size())
	{
		if (allWord[i].numberSuprefik >= 0) 
		{
			i += CountSuprefikWord(allWord, i, suprefiks);
		}
		else
		{
			i++;
		}
	}
	std::ofstream outputFile("output.txt");
	for (auto suprefik : suprefiks)
	{
		outputFile << suprefik << std::endl;
	}
}

void CreateWord(const std::vector<std::string> & words, std::vector<Word> & allWord, int & counterAllWord, bool isSupref)
{
	for (int i = 0; i < words.size(); i++) {
		int sizeWord = words[i].size();
		std::string newWord = "";
		for (int n = 0; n < sizeWord; n++) {
			newWord += words[i].substr(n,1) + words[i].substr(sizeWord - 1 - n, 1);
		}
		allWord[counterAllWord].numberSuprefik = (isSupref) ? i : -1 ;
		allWord[counterAllWord].word = newWord;
		counterAllWord++;
	}
}

void MergerWordsAndSuprefiks(const std::vector<std::string> & words, const std::vector<std::string> & suprefiks, std::vector<Word> & allWord)
{
	allWord.resize(words.size() + suprefiks.size());
	int counterAllWord = 0;
	CreateWord(words, allWord, counterAllWord, false);
	CreateWord(suprefiks, allWord, counterAllWord, true);
}

void SortWords(std::vector<Word> & allWord) 
{
	int sizeUnsortVector = allWord.size();
	bool isSorted = false;
	while (!isSorted)
	{
		isSorted = true;
		for (int i = 0; i < sizeUnsortVector - 1; i++) 
		{
			if (allWord[i].word > allWord[i + 1].word) 
			{
				Word providing;
				providing = allWord[i];
				allWord[i] = allWord[i + 1];
				allWord[i + 1] = providing;				
				isSorted = false;
			}
		}
		sizeUnsortVector--;
	}
}

void FindeSuprefiks() {
	std::vector<std::string> allWords;
	std::vector<std::string> allSuprefiks;
	std::vector<Word> mergedWordsAndSuprefiks;
	std::map<std::string, int> countSuprefiks;
	if (ReadFile(allWords, allSuprefiks))
	{
		MergerWordsAndSuprefiks(allWords, allSuprefiks, mergedWordsAndSuprefiks);
		SortWords(mergedWordsAndSuprefiks);
		OutputResult(mergedWordsAndSuprefiks, allSuprefiks.size());
	}
}


int main()
{
	FindeSuprefiks();
    return 0;
}

