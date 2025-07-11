#include <func.h>

void Q_GLFWInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Only support modern OpenGL
    // glfwWindoHint(GLFW_FORWARD_COMPAT, GL_TRUE); MacOS needs it !
}
GLFWwindow* Q_MakeContextCurrent(unsigned int width, unsigned int height, const char* WindowName)
{
    GLFWwindow *window = glfwCreateWindow(width, height, WindowName, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    return window;
}

void Q_GladInit()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

unsigned int Q_CreatShaderProgram(const std::string &vertex, const std::string &fragment)
{
    unsigned int ShaderProgram;
    ShaderProgram = glCreateProgram();
    unsigned int vertexshader, fragmentshader;
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *VertexSrc = vertex.c_str();
    const char *FragmentSrc = fragment.c_str();
    glShaderSource(vertexshader, 1, &VertexSrc, nullptr);
    glShaderSource(fragmentshader, 1, &FragmentSrc, nullptr);
    glCompileShader(GL_VERTEX_SHADER);
    glCompileShader(GL_FRAGMENT_SHADER);

    // Error Handling
    int success;
    glGetShaderiv(GL_VERTEX_SHADER, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(GL_VERTEX_SHADER, GL_INFO_LOG_LENGTH, &length);
        char *info = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(vertexshader, length, &length, info);
        std::cout << "Verter shader compiled failed: " << info << std::endl;
    }
    glGetShaderiv(GL_FRAGMENT_SHADER, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(GL_FRAGMENT_SHADER, GL_INFO_LOG_LENGTH, &length);
        char *info = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(fragmentshader, length, &length, info);
        std::cout << "Fragment shader compiled failed: " << info << std::endl;
    }

    glAttachShader(ShaderProgram, vertexshader);
    glAttachShader(ShaderProgram, fragmentshader);
    glLinkProgram(ShaderProgram);
    glValidateProgram(ShaderProgram);
    // glDeleteShader(vertexshader);
    // glDeleteShader(fragmentshader);
    return ShaderProgram;
}

Q_ShaderSources Q_PraseShaderFile(const char *filepath)
{
    std::stringstream ss[2];
    std::ifstream stream(filepath);
    std::string line;
    enum class Type
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    Type type = Type::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = Type::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = Type::FRAGMENT;
        }
        else
            ss[(int)type] << line << '\n';
    }

    return {ss[0].str(), ss[1].str()};
}