#include <cstdlib>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

sf::RenderWindow window;
sf::VideoMode videoMode = sf::VideoMode(800, 600);
sf::String title = "Shader display";
sf::Shader shader;

sf::Clock globalClock;

bool running = true;

void handle_input();
void render();

int main(int argc, char* argv[])
{
    window.create(videoMode, title);
    globalClock.restart();

    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    window.resetGLStates();

    glClearColor(0.2, 0.2, 0.2, 0.0);

    if (!sf::Shader::isAvailable())
    {
        cout << "Shaders are not available." << endl;
        exit(EXIT_FAILURE);
    } 

    if (!shader.loadFromFile("./shaders/vert.glsl", "./shaders/frag.glsl"))
    {
        cout << "Failed to load shaders." << endl;
        exit(EXIT_FAILURE);
    }

    sf::Vector2f res(videoMode.width, videoMode.height);
    sf::Time gt = globalClock.getElapsedTime();
    shader.setParameter("iResolution", res);
    shader.setParameter("iGlobalTime", gt.asSeconds());

    sf::Shader::bind(&shader);

    while (running)
    {
        handle_input();
        render();
    }

    sf::Shader::bind(NULL);
    window.close();

    exit(EXIT_SUCCESS);
}

void handle_input()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    running = false;
                }

                break;

            case sf::Event::Closed:
                running = false;

                break;

            case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);

                break;

            default:
                break;
        }
    }
}

void render()
{
    window.clear();

    float ratio = videoMode.width / videoMode.height;

    sf::Vector2f res(videoMode.width, videoMode.height);
    sf::Time gt = globalClock.getElapsedTime();
    shader.setParameter("iResolution", res);
    shader.setParameter("iGlobalTime", gt.asSeconds());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f( 1.0f, -1.0f, 0.0f);
            glVertex3f( 1.0f,  1.0f, 0.0f);
            glVertex3f(-1.0f,  1.0f, 0.0f);
        glEnd();
    glPopMatrix();

    window.display();
}
