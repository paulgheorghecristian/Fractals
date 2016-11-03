#include <iostream>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "entity.h"
#include <vector>
#include "input.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "physics.h"
#include <math.h>
#include "texture.h"
#include "framebuffer.h"
#include "camera.h"

#define DIM_X 1920.0f
#define DIM_Y 1080.0f

int main()
{
    const float WIDTH = 1080.0f;
    const float HEIGHT = 720.0f;

    Display display((int)WIDTH, (int)HEIGHT,"OpenGL");
    Shader fractalShader("res/shaders/julia");
    Shader shader("res/shaders");
    Camera cam(glm::vec3(0, 100, 0), 0, -45, 0);
    Input input;
    Framebuffer fractalFramebuffer(DIM_X, DIM_Y);
    Texture fractal(fractalFramebuffer.get_texture_id());

    display.set_viewport(0.0f, 0.0f, WIDTH, HEIGHT);

    Mesh* mesh = Mesh::get_rectangle_mesh(0.0f, 0.0f, 1.0f, 1.0f);
    Mesh* hillMesh = Mesh::get_surface(500, 500);

    Entity* rectangle = new Entity("rectangle",
                                    mesh,
                                    glm::vec4(1.0f, 0.0f, 0.0, 1.0f),
                                    glm::vec3(0,0,0),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(DIM_X, DIM_Y, 1.0f));

    Entity* hill = new Entity("hill",
                                hillMesh,
                                glm::vec4(1.0f, 0.0f, 0.0, 1.0f),
                                glm::vec3(0,0,0),
                                glm::vec3(0.0f, 0.0f, 0.0f),
                                glm::vec3(DIM_X, 50.0f, DIM_Y));
    shader.bind();
    shader.loadProjectionMatrix(glm::perspective(75.0f, WIDTH/HEIGHT, 1.0f, 2000.0f));
    shader.loadViewMatrix(cam.get_view_matrix());

    fractalShader.bind();
    fractalShader.loadProjectionMatrix(glm::ortho(0.0f, DIM_X, 0.0f, DIM_Y));

    glm::vec2 c(0, 0);

    int max_iter = 1000;
    fractalShader.loadMaxIter(max_iter);

    while(!display.isClosed()){
        display.clear(1.0f, 1.0f, 1.0f, 1.0f);
        display.set_viewport(0, 0, DIM_X, DIM_Y);
        input.update(display.getWindow());

        fractalFramebuffer.bind();
        fractalShader.bind();
        if(input.GetKeyDown(SDLK_1)){
            c.x += 0.001;
        }
        if(input.GetKeyDown(SDLK_2)){
            c.x -= 0.001;
        }
        if(input.GetKeyDown(SDLK_3)){
            c.y += 0.001;
        }
        if(input.GetKeyDown(SDLK_4)){
            c.y -= 0.001;
        }
        if(input.GetKeyDown(SDLK_5)){
            max_iter += 50;
        }
        if(input.GetKeyDown(SDLK_6)){
            max_iter -= 50;
        }
        fractalShader.loadMaxIter(max_iter);
        fractalShader.loadC(c);
        rectangle->draw(&fractalShader);
        fractalFramebuffer.unbind();

        display.clear(1.0f, 1.0f, 1.0f, 1.0f);
        display.set_viewport(0, 0, WIDTH, HEIGHT);

        if(input.GetKey(SDLK_w)){
            cam.move_forward(400.0f * Display::get_delta());
        }else if(input.GetKey(SDLK_s)){
            cam.move_forward(-400.0f * Display::get_delta());
        }

        if(input.GetKey(SDLK_a)){
            cam.move_sideways(-400.0f * Display::get_delta());
        }else if(input.GetKey(SDLK_d)){
            cam.move_sideways(400.0f * Display::get_delta());
        }

        if(glm::abs(glm::length(input.GetMouseDelta())) > 0.3f){
            cam.rotate_x(input.GetMouseDelta().y * 0.1f);
            cam.rotate_y(input.GetMouseDelta().x * 0.1f);
        }

        shader.bind();
        fractal.use(0);
        shader.loadProjectionMatrix(glm::perspective(75.0f, WIDTH/HEIGHT, 1.0f, 2000.0f));
        shader.loadViewMatrix(cam.get_view_matrix());
        hill->draw(&shader);

        display.update();
    }
    return 0;
}

