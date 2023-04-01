#include <iostream>
#include <vector>
#include <tuple>
#include <bits/stdc++.h>
#include <boost/algorithm/string/trim.hpp>

#include "point.hpp"
#include "polynomial.hpp"
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <sstream>
#include <GL/glut.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

GLfloat bound_x = 5;
GLfloat bound_y = 5;
GLfloat resolution = 1;

float ImGuiWidth = WINDOW_WIDTH;
float ImGuiHeight = 80.0f;

Polynomial currentPolynomial = Polynomial({{1, 2}, {2, 3}});

std::unordered_map<int, float> parseFunctionText(char *text)
{
    std::unordered_map<int, float> map = {};

    std::stringstream ss(text);
    std::string term;

    while (getline(ss, term, '+'))
    {
        std::stringstream ts(term);
        int coef, power = 0;
        char var;
        ts >> coef;
        if (ts.peek() == 'x')
        {
            ts >> var;
            if (ts.peek() == '^')
            {
                ts.ignore();
                ts >> power;
            }
            else
            {
                power = 1;
            }
        }
        else
        {
            power = 0;
        }
        map.insert({power, coef});
    }

    return map;
}

void draw_plane()
{
    glColor4f(0.0, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
    for (GLfloat i = -bound_x; i <= bound_x; i += resolution)
    {
        glVertex3f(i, bound_x, 0);
        glVertex3f(i, -bound_x, 0);

        glVertex3f(bound_x, i, 0);
        glVertex3f(-bound_x, i, 0);
    }

    glEnd();

    glColor4f(255.0, 0.0, 0.0, 0.2);
    glBegin(GL_LINES);

    // x-axis
    glVertex3f(bound_x, 0, 0);
    glVertex3f(-bound_x, 0, 0);
    // y-axis
    glVertex3f(0, bound_y, 0);
    glVertex3f(0, -bound_y, 0);

    glEnd();
}

void draw_plot(Polynomial polynomial)
{
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glPointSize(2.0f);
    glBegin(GL_LINE_STRIP);

    // Draw a bunch of points on the function
    for (GLfloat x = -bound_x; x <= bound_x; x += 0.01)
    {
        glVertex3f(x, polynomial.evaluate(x), 0);
    }

    glEnd();
}

void draw()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    {

        static char functionTextInput[128] = "3x^2 + 2x";

        ImGui::Begin("Function");
        ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHeight));
        ImGui::SetWindowPos(ImVec2(0, (float)(WINDOW_HEIGHT - ImGuiHeight)));

        ImGui::Text("f(x) = ");
        ImGui::SameLine();
        ImGui::InputText("##Name", functionTextInput, sizeof(functionTextInput));
        ImGui::SameLine();

        if (ImGui::Button("Plot"))
        {
            currentPolynomial.terms = parseFunctionText(functionTextInput);
            currentPolynomial.print();
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGuiIO &io = ImGui::GetIO();

    glClear(GL_COLOR_BUFFER_BIT);

    draw_plane();
    draw_plot(currentPolynomial);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
    glutPostRedisplay();
}

void init()
{

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(0.8, 0.83, 0.9, 1.0);

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGLUT_InstallFuncs();

    ImGui::StyleColorsDark();

    init();
    glutMainLoop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}