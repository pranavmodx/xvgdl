#pragma once

#include <unordered_map>
#include <string>

class Properties {
	std::unordered_map<std::string, int> umap;
public:
	int getProperty(std::string);
	void setProperty(std::string, int value);
};