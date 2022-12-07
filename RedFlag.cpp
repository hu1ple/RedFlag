#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 900, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.870588f, 0.0f, 1.0f);\n"
"}\n\0";

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    // Build and compile our shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Set up vertex data (and buffer(s)) and attribute pointers
   
        GLfloat vertices[][33]{
                {
                    -0.666667f, 0.6f,		0.0f,

                    -0.666667f, 0.8f,		0.0f,
                    -0.856878f, 0.592705f,	0.0f,
                    -0.784224f, 0.257295f,	0.0f,
                    -0.54911f,  0.257295f,	0.0f,
                    -0.476455f, 0.592705f,	0.0f,

                    -0.711573f, 0.592713,	0.0f,
                    -0.739327f, 0.464587,	0.0f,
                    -0.666667f, 0.3854,		0.0f,
                    -0.594006f, 0.464587,	0.0f,
                    -0.62176f,  0.592713,	0.0f
                },
                {
                    -0.333f,	0.8f,		0.0f,

                    -0.3905f,	0.74855f,	0.0f,
                    -0.318378f,	0.702549f,	0.0f,
                    -0.266924f, 0.791221f,	0.0f,
                    -0.307246f, 0.892026f,	0.0f,
                    -0.38362f,	0.865654f,	0.0f,

                    -0.343299f, 0.764846f,	0.0f,
                    -0.314124f, 0.77492f,	0.0f,
                    -0.311496f,	0.819654f,	0.0f,
                    -0.339046f, 0.837226f,	0.0f,
                    -0.358702f, 0.803353f,	0.0f
                },
                {
                    -0.2f,		0.6f,		0.0f,

                    -0.265997f, 0.585858f,	0.0f,
                    -0.211427f, 0.50148f,	0.0f,
                    -0.141066f, 0.553253f,	0.0f,
                    -0.152149f, 0.669629f,	0.0f,
                    -0.229361f, 0.68978f,	0.0f,

                    -0.218279f, 0.573402f,	0.0f,
                    -0.188784f, 0.565704f,	0.0f,
                    -0.174789f, 0.605402f,	0.0f,
                    -0.195635f, 0.637635f,	0.0f,
                    -0.222513f, 0.617857f,	0.0f
                },
                {
                    -0.2f,		0.3f,		0.0f,

                    -0.264102f, 0.327472f,	0.0f,
                    -0.237227f, 0.217043f,	0.0f,
                    -0.158906f, 0.221258f,	0.0f,
                    -0.137376f, 0.334292f,	0.0f,
                    -0.20239f,  0.399936f,	0.0f,

                    -0.223923f, 0.286901f,	0.0f,
                    -0.199087f, 0.261825f,	0.0f,
                    -0.175513f, 0.289506f,	0.0f,
                    -0.185779f, 0.33169f,	0.0f,
                    -0.215698f, 0.33008f,	0.0f
                },
                {
                    -0.333f,	0.1f,		0.0f,

                    -0.385391f, 0.16247f,	0.0f,
                    -0.389028f, 0.0450391f,	0.0f,
                    -0.315697f, 0.00356278f,0.0f,
                    -0.266739f, 0.0953593f, 0.0f,
                    -0.309812f, 0.193569f,	0.0f,

                    -0.358773f, 0.101773f,	0.0f,
                    -0.342318f, 0.0642566f,	0.0f,
                    -0.313447f, 0.0761366f, 0.0f,
                    -0.312058f, 0.120995f,	0.0f,
                    -0.340071f, 0.136839f,	0.0f
                }

    };
        GLuint indices[] = {
            0, 6, 2,
            0, 2, 7,
            0, 1, 6,
            0, 1, 10,
            0, 5, 10,
            0, 5, 9,
            0, 4, 9,
            0, 4, 8,
            0, 3, 7,
            0, 3, 8
    };


    GLuint VBO[5], VAO[5], EBO[5];
    for (int i = 0; i < 5; i++)
    {
        glGenVertexArrays(1, &VAO[i]);
        glGenBuffers(1, &VBO[i]);
        glGenBuffers(1, &EBO[i]);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

        glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
    }
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
        glUseProgram(shaderProgram);

        for(int i=0;i<5;i++)
        { 
            glBindVertexArray(VAO[i]);
            // glDrawArrays(GL_TRIANGLES, 0, 6); // We set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
            glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


