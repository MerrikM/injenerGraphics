#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Math3D.h"

GLuint VBO;

/*
Описываю функцию рендеринга с одним изменением: в функции glDrawArrays 
мы теперь отрисовываем треугольник (GL_TRIANGLES) вместо точек (GL_POINTS) 
и принимаем 3 вершины вместо 1
*/
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}


/*
Описываю функции создания фигуры с небольшими изменениями:
массив увеличивается с 1 вершины до 3, а также описываются 
эти вершины с их координатами
*/
static void CreateVertexBuffer()
{
    
    //Создаем массив из одного экземпляра стуктуры Vector3f, описанный в Header.h, и задаем XYZ на нулевые координаты.
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO); // Добавление функции генерации элемента
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2.6.3.	Добавление функции, которая связывается с массивом вершин и указателем 
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); // 2.6.4.	Добавление функции, которая наполняет данными наш объект
}


int main(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 03");

    InitializeGlutCallbacks();

    // Инициализируем GLEW
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Установка цвета

    CreateVertexBuffer();

    glutMainLoop(); // Передача управления GLUT

    return 0;
}
