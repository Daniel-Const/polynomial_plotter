#include <iostream>
#include <vector>
#include <tuple>
#include "point.hpp"
#include "polynomial.hpp"

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

GLfloat bound_x = 5;
GLfloat bound_y = 5;
GLfloat resolution = 1;

void example_poly()
{
    Polynomial p = Polynomial({{1, 2}, {2, 3}});

    p.print();
    float result = p.evaluate(3.0);
    std::cout << "P(3) = " << result << std::endl;

    Point point_a = Point(-1 / 3, -1 / 3);
    Point point_b = Point(-0.2, -1);

    std::cout << "-0.333, -0.333 is on P(x): " << (p.containsPoint(point_a) ? "Yes" : "No") << std::endl;
    std::cout << "-0.2, -1 is on P(x): " << (p.containsPoint(point_b) ? "Yes" : "No") << std::endl;
}

void draw_plane()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (GLfloat i = -bound_x; i <= bound_x; i += resolution)
    {
        glVertex3f(i, bound_x, 0);
        glVertex3f(i, -bound_x, 0);

        glVertex3f(bound_x, i, 0);
        glVertex3f(-bound_x, i, 0);
    }

    glEnd();

    glColor3f(255.0, 0.0, 0.0);
    glBegin(GL_LINES);

    // x-axis
    glVertex3f(bound_x, 0, 0);
    glVertex3f(-bound_x, 0, 0);

    // y-axis
    glVertex3f(0, bound_y, 0);
    glVertex3f(0, -bound_y, 0);

    glEnd();
}

void draw_plot()
{
    // P(x) = 2x + 3x^2
    // Polynomial p = Polynomial({{1, 2}, {2, 3}});
    Polynomial p = Polynomial({{1, 0.5}, {2, 2}, {3, 2}});

    glColor3f(0.0, 0.0, 255.0);
    glPointSize(2.0f);
    glBegin(GL_LINE_STRIP);

    // Draw a bunch of points on the function
    for (GLfloat x = -bound_x; x <= bound_x; x += 0.01)
    {
        glVertex3f(x, p.evaluate(x), 0);
    }

    glEnd();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_plane();
    draw_plot();
    glFlush();
}

void init()
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-bound_x, bound_x, -bound_x, bound_x, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Polynomial");
    glutDisplayFunc(draw);
    init();
    glutMainLoop();
}