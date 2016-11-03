#include "display.h"

float Display::delta = 0;
bool Display::isWindowClosed;
Display::Display(int width, int height, std::string title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    glContext = SDL_GL_CreateContext(window);

    GLenum status = glewInit();

    if(status != GLEW_OK){
        std::cerr << "Glew failed to initialize !" << std::endl;
    }
    isWindowClosed = false;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);

     last_frame_time = SDL_GetTicks();
}

Display::~Display()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::clear(float r, float g, float b, float a){
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glScissor(viewport[0], viewport[1], viewport[2], viewport[3]);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::set_viewport(float x, float y, float width, float height){
    glViewport(x, y, width, height);
}

bool Display::isClosed(){
    return isWindowClosed;
}
void Display::update(){
    last_frame_time = SDL_GetTicks();

    SDL_GL_SwapWindow(window);

    long current_frame_time = SDL_GetTicks();
    //limit FPS
    if(1000.0f/MAX_FPS > current_frame_time - last_frame_time){
        SDL_Delay(1000.0f/MAX_FPS - (current_frame_time - last_frame_time));
    }

    delta = SDL_GetTicks() - last_frame_time;

}

glm::mat2 Display::get_2D_transform_matrix(float ferx, float fery, float widthfer, float heightfer,
		float viewx, float viewy, float widthview, float heightview){
		//transformarea fereastra-poarta
		float sx, sy, tx, ty;
		sx = (widthview-viewx) / (widthfer-ferx);
		sy = (heightview-viewy) / (heightfer-fery);
		tx = viewx - sx*ferx;
        ty = viewy - sy*fery;
		return glm::mat2(sx, tx,
                        sy, ty);
	}

float Display::get_delta(){
    return delta/1000.0f;
}
