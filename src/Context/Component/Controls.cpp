#include "Component/Controls.hpp"

int Controls::getControls(std::string key) {
	return umap[key];
}

void Controls::setControls(std::string key, std::string value) {
	umap[key] = value;
}