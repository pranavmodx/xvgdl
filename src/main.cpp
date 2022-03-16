#include <iostream>

#include "pugixml/pugixml.hpp"
#include "SFML/Graphics.hpp"

int main() {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::cout << desktop.height << std::endl;

	std::string my_xml = "<Person>XYZ</Person>";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(my_xml.data());
	if (!result)
        return -1;

	std::cout << doc.first_child().name() << std::endl;

	return 0;
}