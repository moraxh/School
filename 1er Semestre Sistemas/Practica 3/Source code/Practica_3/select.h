#ifndef SELECT_H
#define SELECT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class select;
}

class select : public QDialog
{
    Q_OBJECT

public:
    explicit select(QWidget *parent = nullptr);
    ~select();

    int size;

    int get_data();

    void change_label();

private slots:
    void on_ok_cancel_accepted();

private:
    Ui::select *ui;
};

#endif // SELECT_H
