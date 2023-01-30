#include "add_edit.h"
#include "ui_add_edit.h"

add_edit::add_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_edit)
{
    ui->setupUi(this);
}

add_edit::~add_edit()
{
    delete ui;

}

std::vector<QString> add_edit::get_data()
{
    std::vector <QString> data;
    data.clear();
    data.push_back(ui->name->text());
    data.push_back(ui->age->text());
    data.push_back(ui->weight->text());

    return data;
}

void add_edit::set_data(std::vector<QString> _data)
{
    ui->name->setText(_data[0]);
    ui->age->setValue(_data[1].toInt());
    ui->weight->setValue(_data[2].toDouble());
}

void add_edit::on_ok_cancel_accepted()
{
    QMessageBox alert;
    alert.setWindowTitle("Error");
    alert.setIcon(QMessageBox::Critical);

    if (ui->name->text() != "")
    {
        if (ui->age->text() != "0")
        {
            if (ui->weight->text() == "0.0")
            {
                alert.setText("El peso no puede ser 0");
                alert.exec();
            }
            else
            {
                if (ui->name->text().contains(','))
                {
                    alert.setText("El nombre no puede contener comas");
                    alert.exec();
                }
                else
                    accept();
            }
        }
        else
        {
            alert.setText("La edad no puede ser 0");
            alert.exec();
        }
    }
    else
    {
        alert.setText("El nombre no puede estar vacio");
        alert.exec();
    }
}
