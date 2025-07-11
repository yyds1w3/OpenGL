#include <func.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int main()
{
    Q_GLFWInit();
    GLFWwindow* window = Q_MakeContextCurrent(800, 600);
    Q_GladInit();
    Q_ShaderSources ShaderSouces;
    ShaderSouces = Q_PraseShaderFile("../res/shaders/Basic.shader");
    unsigned int ShaderProgram = Q_CreatShaderProgram(ShaderSouces.VertexSource, ShaderSouces.FragmentSource);
    
    // Start write data to the GL_ARRAY_BUFFER
    float vertices[] = {
        // positions       // colors         // texture coords
        1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 4.0f, 4.0f,  // top right
       -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom right
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f,  // bottom left
       -1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 4.0f   // top left
    };

    unsigned int indices[]{
        0, 1, 2,
        0, 1, 3
    };

    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glUseProgram(ShaderProgram);

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0); // Acitve the Texture unit 0 before binding (default 0 is actived)
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../res/texture/wood.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../res/texture/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glUniform1i(glGetUniformLocation(ShaderProgram, "ourTexture1"), GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(ShaderProgram, "ourTexture2"), 1);
    glBindVertexArray(vao);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // End write data to the GL_ARRAY_BUFFER
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true);
        glClearColor(0.2f, 0.2, 0.5, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // 3 -> indices numbers, when no GL_ELEMENT_ARRAY_BUFFER, we are spposed to set *indices, but we have so just set it nullptr
        glfwSwapBuffers(window); // Used for draw the buffer
        glfwPollEvents(); // Check if Events are triggered
    }

    glfwTerminate(); // Close the Window and release the resouces distributed
    return 0;
}