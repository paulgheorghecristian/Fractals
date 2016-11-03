#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>

class Texture
{
    public:
        Texture(std::string);
        virtual ~Texture();
        void use(unsigned int);
    protected:
    private:
        GLuint texture_id;
        GLuint get_texture_id();
};

#endif // TEXTURE_H
