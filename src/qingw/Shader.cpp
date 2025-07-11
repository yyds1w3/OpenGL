#include <Shader.h>

Shader::Shader(const char *filepath, unsigned int ShaderProgram)
{
    std::stringstream ss[2];
    std::ifstream stream(filepath);
    std::string line;
    enum class Type
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
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
    ShaderProgram = glCreateProgram();
    unsigned int vertexshader, fragmentshader;
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertex = ss[0].str();
    std::string fragment = ss[1].str();
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
    m_ShaderProgram = ShaderProgram;
}
