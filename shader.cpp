#include "shader.h"
#include <iostream>
#include <fstream>

shader::shader(const string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = create_shader(load_shader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = create_shader(load_shader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
	 glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	check_shader_error(m_program, GL_LINK_STATUS, true, "ERROR: Could not link shader program");

	glValidateProgram(m_program);
	check_shader_error(m_program, GL_LINK_STATUS, true, "ERROR: Invalid shader program");

	m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
}

shader::~shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

	glDeleteProgram(m_program);
}

void shader::bind()
{
	glUseProgram(m_program);
}

/*void shader::update(const Transform& transform, const Camera& camera)
{
	glm::mat4 MVP = transform.GetMVP(camera);
	glm::mat4 Normal = transform.GetModel();

	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[2], 0.0f, 0.0f, 1.0f);
}*/

string shader::load_shader(const string& fileName)
{
    ifstream file;
    file.open((fileName).c_str());

    string output;
    string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		cout << "ERROR: Unable to load shader: " << fileName << endl;
    }

    return output;
}

void shader::check_shader_error(GLuint shader_id, GLuint flag, bool isProgram, const string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader_id, flag, &success);
    else
        glGetShaderiv(shader_id, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader_id, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader_id, sizeof(error), NULL, error);

        cout << errorMessage << ": '" << error << "'" << endl;
    }
}

GLuint shader::create_shader(const string& text, unsigned int type)
{
    GLuint shader_id=glCreateShader(type);

    if(shader_id == 0)
		cout << "Error compiling shader type " << type << endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader_id, 1, p, lengths);
    glCompileShader(shader_id);

    check_shader_error(shader_id, GL_COMPILE_STATUS, false, "ERROR: Could not compile shader");

    return shader_id;
}
