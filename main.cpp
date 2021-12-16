#include <iostream>
#include <vector>

#include <QApplication>
#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif
#include <QOpenGLFunctions_3_3_Core>
#include "my_app.cpp"



////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //!Utworzenie i wyswietlenie okna aplikacji
    Window w;
    std::cout << (const char*)glGetString(GL_VERSION) << std::endl;

    w.show();

    return a.exec();
}
