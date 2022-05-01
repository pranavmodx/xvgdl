#pragma once

#include <unordered_map>

class Controls {
	std::unordered_map<std::string, std::string> umap;
public:
	int getControls(std::string);
	void setControls(const std::string& key, const std::string& value);
};