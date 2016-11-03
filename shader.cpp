#include "shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& path)
{
    GLint compile_result = 0, link_result = 0;
    char info_log_message[1024];

    std::string vertex_shader_source = load_shader(path + "/vertex");
    std::string fragment_shader_source = load_shader(path + "/fragment");

    const GLchar* vertexSS[1];
    const GLchar* fragmentSS[1];

    vertexSS[0] = vertex_shader_source.c_str();
    fragmentSS[0] = fragment_shader_source.c_str();

    GLint vertex_length[1];
    GLint fragment_length[1];

    vertex_length[0] = strlen(vertexSS[0]);
    fragment_length[0] = strlen(fragmentSS[0]);


    vertex_handle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_handle, 1, vertexSS, vertex_length);
    glCompileShader(vertex_handle);

    glGetShaderiv(vertex_handle, GL_COMPILE_STATUS, &compile_result);
	if(compile_result == GL_FALSE) {
        glGetShaderInfoLog(vertex_handle, 1024, NULL, info_log_message);
        std::cout << "EROARE COMPILARE vertex shader" << std::endl << "LOG=" << info_log_message << std::endl;
        exit(-1);
	}

	fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_handle, 1, fragmentSS, fragment_length);
    glCompileShader(fragment_handle);

    glGetShaderiv(fragment_handle, GL_COMPILE_STATUS, &compile_result);
	if(compile_result == GL_FALSE) {
        glGetShaderInfoLog(fragment_handle, 1024, NULL, info_log_message);
        std::cout << "EROARE COMPILARE fragment shader" << std::endl << "LOG=" << info_log_message << std::endl;
        exit(-1);
	}

    program = glCreateProgram();
    glAttachShader(program, vertex_handle);
    glAttachShader(program, fragment_handle);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &link_result);
    if(link_result == GL_FALSE) {
		glGetProgramInfoLog(program, 1024, NULL, info_log_message);
        std::cout << "EROARE LINK program shader" << std::endl << "LOG=" << info_log_message << std::endl;
        exit(-2);
	}

    getAllUniformLocations();

}

void Shader::getAllUniformLocations(){
    //caut in shader-e uniformele respective
    projMat_location = glGetUniformLocation(program, "projection_matrix");
    viewMat_location = glGetUniformLocation(program, "view_matrix");
    modelMat_location = glGetUniformLocation(program, "model_matrix");
    colorVector_location = glGetUniformLocation(program, "color_vector");
    max_iter_location = glGetUniformLocation(program, "max_iter");
    c_location = glGetUniformLocation(program, "c");
    glUniform1i(glGetUniformLocation(program, "fractalHeightmap"), 0);
}

void Shader::loadMaxIter(int iter){
    glUniform1i(max_iter_location, iter);
}

void Shader::loadCoords(float xmin, float ymin, float xmax, float ymax){
    glUniform2f(min_coords_location, xmin, ymin);
    glUniform2f(max_coords_location, xmax, ymax);
}

void Shader::loadColor(glm::vec4 color){
    loadVector(colorVector_location, color);
}

void Shader::loadVector(GLuint location, glm::vec4 vect){
    glUniform4f(location, vect.x, vect.y, vect.z, vect.w);
}

void Shader::loadProjectionMatrix(glm::mat4 matrix){
    loadMatrix(projMat_location, matrix);
}

void Shader::loadModelMatrix(glm::mat4 matrix){
    loadMatrix(modelMat_location, matrix);
}

void Shader::loadViewMatrix(glm::mat4 matrix){
    loadMatrix(viewMat_location, matrix);
}

void Shader::loadMatrix(GLuint location, glm::mat4 matrix){
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void Shader::loadC(glm::vec2 c){
    glUniform2f(c_location, c.x, c.y);
}

std::string Shader::load_shader(const std::string& fileName){
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if(file.is_open()){
        while(file.good()){
            getline(file, line);
            output.append(line + "\n");
        }

    }else{
        std::cerr << "Unable to load shader: " << fileName << std::endl;

    }
    return output;
}

Shader::~Shader()
{
    glUseProgram(0);

    glDetachShader(program, vertex_handle);
    glDetachShader(program, fragment_handle);

    glDeleteShader(vertex_handle);
	glDeleteShader(fragment_handle);

    glDeleteProgram(program);
}

void Shader::bind(){
    glUseProgram(program);
}
