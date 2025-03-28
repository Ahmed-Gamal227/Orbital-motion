#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Orbital parameters
struct Planet {
    float distance; // Distance from the center (e.g., the sun)
    float radius;   // Radius of the planet
    float speed;    // Orbital speed
    float angle;    // Current angle in radians
    float r, g, b;  // Color of the planet
};

// Define planets
std::vector<Planet> planets = {
    {0.2f, 0.02f, 0.02f, 0.0f, 1.0f, 0.0f, 0.0f}, // Red planet
    {0.4f, 0.03f, 0.015f, 0.0f, 0.0f, 1.0f, 0.0f}, // Green planet
    {0.6f, 0.04f, 0.01f, 0.0f, 0.0f, 0.0f, 1.0f}  // Blue planet
};

// Function to draw a circle
void drawCircle(float x, float y, float radius, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle

    for (int i = 0; i <= 100; ++i) {
        float angle = i * 2.0f * 3.14 / 100;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }

    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Orbital Motion Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1); // Set coordinate system

    // Set background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the sun
        drawCircle(0.0f, 0.0f, 0.1f, 1.0f, 1.0f, 0.0f); // Yellow sun

        // Update and draw each planet
        for (auto& planet : planets) {
            planet.angle += planet.speed; // Update angle
            if (planet.angle > 2.0f * 3.14) {
                planet.angle -= 2.0f * 3.14;
            }

            float x = planet.distance * cos(planet.angle);
            float y = planet.distance * sin(planet.angle);
            drawCircle(x, y, planet.radius, planet.r, planet.g, planet.b);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}