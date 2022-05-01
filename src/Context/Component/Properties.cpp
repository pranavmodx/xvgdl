#include "Component/Properties.hpp"

int Properties::getProperty(std::string key) {
	return umap[key];
}

void Properties::setProperty(std::string key, int value) {
	umap[key] = value;
}