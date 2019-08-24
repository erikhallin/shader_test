#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/gl.h>

#include <string>

//vertex shader ok, men inte fragment shader. Kan inte sätta rätt färg från glColor()

using namespace std;

class shader
{
    public:
        shader(const string& fileName);

        void bind();
        //void update(const Transform& transform, const Camera& camera);

        virtual ~shader();

    private:

        static const unsigned int NUM_SHADERS = 2;
        static const unsigned int NUM_UNIFORMS = 3;
        void operator=(const shader& _shader) {}
        shader(const shader& _shader) {}

        string load_shader(const string& fileName);
        void   check_shader_error(GLuint shader_id, GLuint flag, bool isProgram, const string& errorMessage);
        GLuint create_shader(const string& text, unsigned int type);

        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
