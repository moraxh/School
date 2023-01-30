#ifndef ADD_EDIT_H
#define ADD_EDIT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class add_edit;
}

class add_edit : public QDialog
{
    Q_OBJECT

public:
    explicit add_edit(QWidget *parent = nullptr);
    ~add_edit();

    std::vector <QString> get_data();

    void set_data(std::vector <QString> _data);

private slots:

    void on_ok_cancel_accepted();

private:
    Ui::add_edit *ui;
};

#endif // ADD_EDIT_H
