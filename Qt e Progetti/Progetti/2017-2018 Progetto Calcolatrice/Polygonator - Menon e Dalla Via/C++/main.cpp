#include <QApplication>
#include "Controller/MainWindowController.h"

int main(int argc, char *argv[]) {
    QApplication qApplication(argc, argv);
    MainWindowController mainWindowController;

    return qApplication.exec();
}