#include <QApplication>
#include "PokedexWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PokedexWindow w;
    w.show();
    return app.exec();
}
