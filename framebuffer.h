#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <iostream>

class Framebuffer
{
    public:
        Framebuffer(int, int);
        void bind();
        void unbind();
        GLuint get_texture_id();
        virtual ~Framebuffer();
    protected:
    private:
        int width, height;
        GLuint framebuffer_id;
        GLuint depthbuffer_id;
        GLuint texture_id;
        const int TEXTURE_WIDTH, TEXTURE_HEIGHT;
};

#endif // FRAMEBUFFER_H
