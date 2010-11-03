#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QFile>

bool createConnections();
bool openDb(const QString &filename, const QString &dsn = "");

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    if (!createConnections())
        return 1;
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

bool createConnections() {
    return openDb("centro_historico.db");
}

bool openDb(const QString &filename, const QString &dsn) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        if (QString::fromUtf8(file.read(16).constData()) != "SQLite format 3") {
            QMessageBox::critical(0, "Error al abrir la base de datos",
                                  QString("Archivo no válido: %1").arg(filename));
            return false;
        }
        file.close();
        QSqlDatabase db;
        if (dsn.size() > 0)
            db = QSqlDatabase::addDatabase("QSQLITE",dsn);
        else
            db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(filename);
        if (!db.open()) {
            QMessageBox::critical(0, "Error al abrir la base de datos",
                               db.lastError().text());
            return false;
        }
        db.close();
        return true;
    }
    else {
        QMessageBox::critical(0, "Error al abrir la base de datos",
                              QString("Archivo no encontrado: %1").arg(filename));
        return false;
    }
}
