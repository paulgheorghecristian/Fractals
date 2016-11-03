#include "physics.h"

Physics::Physics()
{
    //ctor
}

Physics::~Physics()
{
    //dtor
}

bool Physics::entities_overlap(Entity *e1, Entity *e2){

    //intersectie intre dreptunghiuri

    float e1_x1 = e1->get_position().x;
    float e1_y1 = e1->get_position().y;
    float e1_x2 = e1->get_position().x + e1->get_scale().x;
    float e1_y2 = e1->get_position().y + e1->get_scale().y;

    float e2_x1 = e2->get_position().x;
    float e2_y1 = e2->get_position().y;
    float e2_x2 = e2->get_position().x + e2->get_scale().x;
    float e2_y2 = e2->get_position().y + e2->get_scale().y;

    return e1_x1 < e2_x2 && e1_x2 > e2_x1 &&
            e1_y1 < e2_y2 && e1_y2 > e2_y1;
}

glm::vec2 Physics::beam_entity_overlap(Entity *beam, Entity *e){

    //intersectie intre raza si obiectele scenei

    float x = beam->get_position().x + (glm::cos(glm::radians(beam->get_rotation().z)))*beam->get_scale().x;
    float y = beam->get_position().y + (glm::sin(glm::radians(beam->get_rotation().z)))*beam->get_scale().x;

    if(e->get_name() == "rectangle"){

        //daca capatul razei se afla in dreptunghi
        if(x >= e->get_position().x && x <= e->get_position().x + e->get_scale().x &&
            y >= e->get_position().y && y <= e->get_position().y + e->get_scale().y){
            return glm::vec2(x, y);
        }else{
            return glm::vec2(-1.0f, -1.0f);
        }
    }else if(e->get_name() == "circle"){
        glm::vec2 beam_position(x, y);
        glm::vec2 circle_position(e->get_position().x, e->get_position().y);

        //daca distanta dintre capatul razei si centrul cercului este mai mica
        //decat raza cercului

        if(glm::distance(beam_position, circle_position) <= e->get_scale().x){
            return glm::vec2(x, y);
        }else{
            return glm::vec2(-1.0f, -1.0f);
        }
    }else if(e->get_name() == "camera"){

        float WIDTH = e->get_scale().x / 2.0f + e->get_position().x;
        float HEIGHT = e->get_scale().y / 2.0f + e->get_position().y;

        float diagonal_length = (e->get_scale().x * sqrt(2.0f)) / 2.0f;
        float x_camera_bound = WIDTH - diagonal_length;
        float y_camera_bound = HEIGHT - diagonal_length;

        float ec = x+y-(WIDTH+HEIGHT)+diagonal_length;

        //intersectia cu ipotenuza camerei
        //daca distanta de la capatul razei la ipotenuza este intre 0 si 10, inseamna
        //ca am intersectat-o
        if(ec < 10.0f && ec > 0.0f){
            return glm::vec2(1.0f, 1.0f);
        }
        return glm::vec2(-1.0f, -1.0f);
    }
}
