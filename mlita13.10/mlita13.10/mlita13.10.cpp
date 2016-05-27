#include "stdafx.h"
#include "Data.h"

bool ReadFile(std::vector<std::string> & words, std::vector<std::string> & superfiks, const std::string & inFile)
{
	try
	{
		std::ifstream inputFile(inFile);
		size_t wordsVectorSize;
		inputFile >> wordsVectorSize;
		if (!(wordsVectorSize >= MIN_COUNT_WORD && wordsVectorSize <= MAX_COUNT_WORD))
			throw std::out_of_range("");
		words.resize(wordsVectorSize);
		std::string str;
		for (size_t i = 0; i < wordsVectorSize; i++)
		{
			inputFile >> str;
			if (!(str.size() >= MIN_SIZE_WORD && str.size() <= MAX_SIZE_WORD))
				throw std::out_of_range("");
			words[i] = str;
		}

		size_t superfiksVectorSize;
		inputFile >> superfiksVectorSize;
		if (!(superfiksVectorSize >= MIN_COUNT_WORD && superfiksVectorSize <= MAX_COUNT_WORD))
			throw std::out_of_range("");
		superfiks.resize(superfiksVectorSize);
		for (size_t i = 0; i < superfiksVectorSize; i++)
		{
			inputFile >> str;
			if (!(str.size() >= MIN_SIZE_WORD && str.size() <= MAX_SIZE_WORD))
				throw std::out_of_range("");
			superfiks[i] = str;
		}
		return true;
	}
	catch (...)
	{
		std::cout << "File not exist or wrong file format." << std::endl;
		return false;
	}
}


size_t CountSuperfikWord(const std::vector<Word> & allWord, size_t startPosition, std::vector<size_t> & superfiks)
{
	size_t countSuperfik = 0;
	while (startPosition + countSuperfik + 1 < allWord.size() && allWord[startPosition].word == allWord[startPosition + countSuperfik + 1].word.substr(0, allWord[startPosition].word.size()))
	{
		countSuperfik++;
		if (allWord[startPosition + countSuperfik].numberSuperfik >= 0)
		{
			countSuperfik += CountSuperfikWord(allWord, startPosition + countSuperfik, superfiks);
		}
	}
	superfiks[allWord[startPosition].numberSuperfik] = countSuperfik;
	return countSuperfik;
}

void OutputResult(const std::vector<Word> & allWord, size_t countSuprefiks, const std::string & outFile)
{
	std::vector<size_t> suprefiks(countSuprefiks, 0);
	size_t i = 0;
	while (i < allWord.size())
	{
		if (allWord[i].numberSuperfik >= 0) 
		{
			i += CountSuperfikWord(allWord, i, suprefiks) + 1;
		}
		else
		{
			i++;
		}
	}
	std::ofstream outputFile(outFile);
	for (size_t i = 0; i < suprefiks.size(); i++)
	{
		outputFile << suprefiks[i] << std::endl;
	}
}

void CreateWord(const std::vector<std::string> & words, std::vector<Word> & allWord, size_t & counterAllWord, bool isSupref)
{
	for (size_t i = 0; i < words.size(); i++) {
		size_t sizeWord = words[i].size();
		std::string newWord = "";
		for (size_t n = 0; n < sizeWord; n++) {
			newWord += words[i].substr(n,1) + words[i].substr(sizeWord - 1 - n, 1);
		}
		allWord[counterAllWord].numberSuperfik = (isSupref) ? i : -1 ;
		allWord[counterAllWord].word = newWord;
		counterAllWord++;
	}
}

void MergerWordsAndSuprefiks(const std::vector<std::string> & words, const std::vector<std::string> & suprefiks, std::vector<Word> & allWord)
{
	allWord.resize(words.size() + suprefiks.size());
	size_t counterAllWord = 0;
	CreateWord(words, allWord, counterAllWord, false);
	CreateWord(suprefiks, allWord, counterAllWord, true);
}

void SortWords(std::vector<Word> & allWord) 
{
	size_t sizeUnsortVector = allWord.size();
	bool isSorted = false;
	while (!isSorted)
	{
		isSorted = true;
		for (size_t i = 0; i < sizeUnsortVector - 1; i++) 
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

void FindeSuprefiks(const std::string & inFile, const std::string & outFile) {
	std::vector<std::string> allWords;
	std::vector<std::string> allSuperfiks;
	std::vector<Word> mergedWordsAndSuperfiks;
	if (ReadFile(allWords, allSuperfiks, inFile))
	{
		MergerWordsAndSuprefiks(allWords, allSuperfiks, mergedWordsAndSuperfiks);
		SortWords(mergedWordsAndSuperfiks);
		OutputResult(mergedWordsAndSuperfiks, allSuperfiks.size(), outFile);
	}
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return 1;
	}

	FindeSuprefiks(argv[1], argv[2]);
    return 0;
}

