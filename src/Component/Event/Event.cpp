#include <iostream>
#include "Component/Event/Event.hpp"
#include "Component/Event/EventType.hpp"
#include "Component/Object/ObjectType.hpp"

Event::Event(EventType type, ObjectType objType, float timer) : type(type), objType(objType), timer(timer) {}

void Event::apply(GameContext *gameContext) {
    switch(type) {
        case EventType::SpawnObject:
            spawnObject(objType);
    }
}

void Event::spawnObject(ObjectType type, float timeInterval) {
    std::cout << "spawning" << std::endl;
}
