#include "mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    //vao care retine starea meshei
    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    glGenBuffers(NUM_VBOS, vbo_handles);

    //trimit GPU-ului vertecsii
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handles[VERTEX]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    //trimit GPU-ului indecsii
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_handles[INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

    no_triangles = indices.size();

    //ii descriu shader-ului datele trimise

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (void*)(sizeof(glm::vec3)*2));
}

Mesh::~Mesh()
{
    glDeleteBuffers(NUM_VBOS, vbo_handles);
    glDeleteVertexArrays(1, &vao_handle);
}

GLuint Mesh::get_vao(){
    return vao_handle;
}

GLsizei Mesh::get_no_triangles(){
    return no_triangles;
}

void Mesh::draw(){
    glBindVertexArray(vao_handle);
    glDrawElements(GL_TRIANGLES, no_triangles, GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);
}

Mesh* Mesh::get_circle_mesh(float x, float y, float radius, const int number_triangles){

    std::vector<Vertex> vertices;

    //incep cu o linie pe care o rotesc cu 360/number_triangles pentru a crea triunghiurile aferente cercului

    vertices.push_back(Vertex(glm::vec3(x, y, 0.0f)));
    vertices.push_back(Vertex(glm::vec3(x, y+radius, 0.0f)));

    for(int i = 2; i < number_triangles+1; i++){
        float pos_x = vertices[i-1].position_coords.x * glm::cos(-(360/number_triangles)*PI/180) - vertices[i-1].position_coords.y * glm::sin(-(360/number_triangles)*PI/180);
        float pos_y = vertices[i-1].position_coords.x * glm::sin(-(360/number_triangles)*PI/180) + vertices[i-1].position_coords.y * glm::cos(-(360/number_triangles)*PI/180);
        vertices.push_back(Vertex(glm::vec3(pos_x, pos_y, 0.0f)));
    }

    std::vector<unsigned int> indices;

    for(int i = 0; i < number_triangles*3; i+=3){
        indices.push_back((i/3)+1);
        indices.push_back(0);
        indices.push_back((i/3)+2);
    }
    indices[number_triangles*3] = number_triangles+1;
    indices[number_triangles*3+1] = number_triangles+2;
    indices[number_triangles*3+2] = number_triangles+3;

    indices[number_triangles*3-1] = 1;

    return new Mesh(vertices, indices);
}
Mesh* Mesh::get_rectangle_mesh(float x, float y, float width, float height){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(Vertex(glm::vec3(x, y, 0.0f)));
    vertices.push_back(Vertex(glm::vec3(x+width, y, 0.0f)));
    vertices.push_back(Vertex(glm::vec3(x+width, y+height, 0.0f)));
    vertices.push_back(Vertex(glm::vec3(x, y+height, 0.0f)));

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    return new Mesh(vertices, indices);
}
