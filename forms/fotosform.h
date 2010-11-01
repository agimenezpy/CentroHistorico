#ifndef FOTOSFORM_H
#define FOTOSFORM_H

#include <QGroupBox>

namespace Ui {
    class FotosForm;
}

class FotosForm : public QGroupBox {
    Q_OBJECT
public:
    FotosForm(QWidget *parent = 0);
    ~FotosForm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FotosForm *ui;
};

#endif // FOTOSFORM_H
