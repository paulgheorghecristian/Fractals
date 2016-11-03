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

int main()
{
    const float WIDTH = 1920.0f;
    const float HEIGHT = 1080.0f;

    Display display((int)WIDTH, (int)HEIGHT,"OpenGL");
    Shader shader("res/shaders/julia");
    Input input;

    display.set_viewport(0.0f, 0.0f, WIDTH, HEIGHT);

    Mesh* mesh = Mesh::get_rectangle_mesh(0.0f, 0.0f, 1.0f, 1.0f);

    Entity* rectangle = new Entity("rectangle",
                                    mesh,
                                    glm::vec4(1.0f, 0.0f, 0.0, 1.0f),
                                    glm::vec3(0,0,0),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(WIDTH, HEIGHT, 1.0f));

    shader.bind();
    glm::mat4 projMat = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    shader.loadProjectionMatrix(projMat);

    glm::vec2 c(0, 0);

    glm::vec2 min_coords(0, 0);
    glm::vec2 max_coords(2, 2);

    glm::vec2 center;

    glm::vec2 focus(-0.743, 0.1);

    glm::vec2 real_min_coords;
    glm::vec2 real_max_coords;

    int max_iter = 1000;
    shader.loadMaxIter(max_iter);

    Texture t("res/textures/pal.bmp");

    while(!display.isClosed()){
        display.clear(1.0f, 1.0f, 1.0f, 1.0f);
        input.update();

        shader.bind();
        t.use(0);
        center = glm::vec2((max_coords.x + min_coords.x) / 2.0f, (max_coords.y + min_coords.y) / 2.0f);
        real_min_coords = glm::vec2(min_coords.x + (focus.x - center.x), min_coords.y + (focus.y - center.y));
        real_max_coords = glm::vec2(max_coords.x + (focus.x - center.x), max_coords.y + (focus.y - center.y));
        shader.loadCoords(real_min_coords.x, real_min_coords.y, real_max_coords.x, real_max_coords.y);
        if(input.GetKeyDown(SDLK_w)){
            max_coords /= 1.05f;
        }
        if(input.GetKeyDown(SDLK_s)){
            max_coords *= 1.05f;
        }
        if(input.GetKeyDown(SDLK_a)){
            focus.x -= 0.01f;
        }
        if(input.GetKeyDown(SDLK_d)){
            focus.x += 0.01f;
        }

        if(input.GetKeyDown(SDLK_z)){
            max_iter += 10;
            shader.loadMaxIter(max_iter);
        }
        if(input.GetKeyDown(SDLK_x)){
            max_iter -= 10;
            shader.loadMaxIter(max_iter);
        }

        if(input.GetKeyDown(SDLK_1)){
            c.x += 0.01;
        }
        if(input.GetKeyDown(SDLK_2)){
            c.x -= 0.01;
        }
        if(input.GetKeyDown(SDLK_3)){
            c.y += 0.01;
        }
        if(input.GetKeyDown(SDLK_4)){
            c.y -= 0.01;
        }

        std::cout << c.x << " " << c.y << std::endl;

        shader.loadC(c);

        rectangle->draw(&shader);

        display.update();
    }
    return 0;
}
