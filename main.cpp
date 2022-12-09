#include "window.h"
#include "qcustomplot.h"
int main(int argc, char *argv[]) {
    QApplication app( argc, argv );
    Window window;

    window.showMaximized();
    return app.exec();
}
