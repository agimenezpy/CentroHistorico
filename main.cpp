#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

bool createConnection();

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    if (!createConnection())
        return 1;
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("centro_historico.db");
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Error al abrir la base de datos"),
                               db.lastError().text());
        return false;
    }
    return true;
}
