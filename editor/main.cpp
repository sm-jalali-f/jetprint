#include "widget.h"
#include <QApplication>
#include <editorwidget.h>
#include <printwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    EditorWidget w;
    EditorWidget w;
    w.setWindowIcon(QIcon(":/res/icons/ic_app.png"));
    w.show();
//    PrintWindow window;
//    window.show();


    return a.exec();
}
