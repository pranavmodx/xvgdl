#include <utility>

class Object {
	std::string name;
	std::string type;
	int height;
	int width;
	std::pair<int, int> position;

public:
	std::string getName() = 0;
	std::string getType() = 0;
};