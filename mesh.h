#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#define PI 3.1415926535

struct Vertex{
    glm::vec3 position_coords;
    glm::vec3 normal_coords;
    glm::vec2 texture_coords;

    Vertex() : position_coords(0.0f), normal_coords(0.0f), texture_coords(0.0f){}

    Vertex(glm::vec3 position_coords, glm::vec3 normal_coords, glm::vec2 texture_coords){
        this->position_coords = position_coords;
        this->normal_coords = normal_coords;
        this->texture_coords = texture_coords;
    }
    Vertex(glm::vec3 position_coords) : Vertex(position_coords, glm::vec3(0.0f), glm::vec2(0.0f)){}
    Vertex(glm::vec3 position_coords, glm::vec3 normal_coords) : Vertex(position_coords, normal_coords, glm::vec2(0.0f)){}
};

class Mesh
{
    public:
        Mesh(std::vector<Vertex>&, std::vector<unsigned int>&);
        GLuint get_vao();
        void draw();
        GLsizei get_no_triangles();
        static Mesh* get_circle_mesh(float, float, float, const int);
        static Mesh* get_rectangle_mesh(float, float, float, float);
        static Mesh* get_surface(int width, int height);
        virtual ~Mesh();
    protected:
    private:
            enum VBOs{
                VERTEX, INDEX, NUM_VBOS
            };
            GLuint vao_handle;
            GLuint vbo_handles[NUM_VBOS];
            GLsizei no_triangles;
};

#endif // MESH_H
