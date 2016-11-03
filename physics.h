#ifndef PHYSICS_H
#define PHYSICS_H

#include "entity.h"

class Physics
{
    public:
        Physics();
        static bool entities_overlap(Entity*, Entity*);
        static glm::vec2 beam_entity_overlap(Entity*, Entity*);
        virtual ~Physics();
    protected:
    private:
};

#endif // PHYSICS_H
