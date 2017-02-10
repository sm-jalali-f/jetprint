#include "widget.h"
#include <QApplication>
#include <editorwidget.h>
#include <neweditorwidget.h>
#include <printwindow.h>
#include "printsettingdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    PrintSettingDialog *dialog =new PrintSettingDialog();
//    dialog->exec();

//    EditorWidget w;
    NewEditorWidget w;
    w.setWindowIcon(QIcon(":/res/icons/ic_app.png"));
    w.show();
//    PrintWindow window;
//    window.show();


    return a.exec();
}
