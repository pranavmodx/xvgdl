#include "Component/Controls.hpp"

std::string Controls::getControls(std::string key) {
	return umap[key];
}

void Controls::setControls(std::string key, std::string value) {
	umap[key] = value;
}