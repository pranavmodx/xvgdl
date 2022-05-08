#pragma once

#include <unordered_map>
#include <string>

class Controls {
	std::unordered_map<std::string, std::string> umap;
public:
	std::string getControls(std::string);
	void setControls(std::string key, std::string value);
};