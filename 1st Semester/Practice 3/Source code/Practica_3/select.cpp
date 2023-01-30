#include "select.h"
#include "ui_select.h"

select::select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::select)
{
    ui->setupUi(this);
}

select::~select()
{
    delete ui;
}

int select::get_data()
{
    return ui->num->text().toInt();
}

void select::change_label()
{
    ui->label->setText("Ingrese el número de la persona que deseas eliminar");
}

void select::on_ok_cancel_accepted()
{
    QMessageBox alert;
    alert.setWindowTitle("Error");
    alert.setIcon(QMessageBox::Critical);

    if (ui->num->text().toInt() <= 0 || ui->num->text().toInt() > size)
    {
        alert.setText("Seleccion fuera de rango");
        alert.exec();
    }
    else
    {
        accept();
    }
}
