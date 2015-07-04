
#include "StringHelper.h"

std::vector<std::string> StringHelper::Split(const std::string& value, char rep)
{
	std::vector<std::string> splits;
	std::string::const_iterator start = value.begin();
	std::string::const_iterator end = start;
	while (end != value.end())
	{
		if (*end == rep)
		{
			splits.push_back(std::string(start, end));
			start = end + 1;
		}

		++end;
	}
	splits.push_back(std::string(start, end));

	return splits;
}

std::vector<int> StringHelper::SplitInt(const std::string& value, char rep)
{
	std::vector<int> splits;
	std::string::const_iterator start = value.begin();
	std::string::const_iterator end = start;
	while (end != value.end())
	{
		if (*end == rep)
		{
			splits.push_back(atoi(std::string(start, end).c_str()));
			start = end + 1;
		}

		++end;
	}
	splits.push_back(atoi(std::string(start, end).c_str()));

	return splits;
}

std::string StringHelper::Trim(const std::string& value)
{
	size_t start = value.find_first_not_of(" \n\r\t");
	size_t end = value.find_last_not_of(" \n\r\t");
	return std::string(value, start, end - start + 1);
}
