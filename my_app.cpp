#include <iostream>
#include <vector>

#include <QApplication>
#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif
#include <QOpenGLFunctions_3_3_Core>
#include <GL/glu.h>


const char* vshader =
        "#version 330 \n"
        "uniform vec3 Kolor; \n"
        "in vec3 pos; \n"
        "out vec4 fColor; \n"
        "void main() { "
        "    gl_Position = vec4(pos, 1);"
        "    fColor = vec4(Kolor, 1.0);"
        "}";

std::string vertexShader =
        "#version 330 core \n"
        "layout(location = 0) in vec4 position; \n"
        "void main() \n"
        "{\n"
        "	gl_Position = position;\n"
        "}";

std::string fragmentShader =
        "#version 330 core \n"
        "layout(location = 0) out vec4 color; \n"
        "void main() \n"
        "{\n"
        "	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}";

const char* fshader =
        "#version 330 \n"
        "in vec4 fColor; \n"
        "out vec4 FragColor; \n"
        "void main() { "
        "    FragColor = fColor;"
        "}";


void PRINT_GL_ERRORS(const char* mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR)
        std::cout << "ERROR in: " << mess <<(const char*)gluErrorString(err) << std::endl;
}


struct vec3 {float x,y,z;};
struct vec4 {float x,y,z,w;};

class Window : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    std::vector<vec3> positions;
    GLuint buffer;
protected:


    GLuint compileShader(GLuint type, const std::string& source){
        GLuint id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // TODO: error handling ;)
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            std::cout<< "Failed to compile"<<(type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<"shader "<< std::endl;
            std::cout<< message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader){
        GLuint program = glCreateProgram();
        GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }


    void initializeGL() override
    {
        initializeOpenGLFunctions();


        GLuint shader = createShader(vertexShader, fragmentShader);
        glUseProgram(shader);


        positions = {
            {-0.5f, 0.0f, 0.0f},
            {0.0f, -0.5f, 0.0f},
            {0.5f, 0.0f, 0.0f},
        };

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(vec3), positions.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

     }


    void paintGL() override
    {
       glClear(GL_COLOR_BUFFER_BIT);
       glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void resizeGL(int w, int h) override
    {
        glViewport(0,0, w, h);
    }
};





