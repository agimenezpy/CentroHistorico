#ifndef ABOUT_H
#define ABOUT_H

#include "ui_about.h"

class About : public QDialog, private Ui::About {
    Q_OBJECT
public:
    About(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // ABOUT_H
