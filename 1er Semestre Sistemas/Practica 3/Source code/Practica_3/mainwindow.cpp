#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    update_buttons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_data()
{
    update_buttons();

    int size = data.names.size();

    ui->display->clear();

    for (int i = 0; i < size; i++)
    {
        ui->display->setPlainText(ui->display->toPlainText() + "Persona " + QString::number(i + 1) + "\n");
        ui->display->setPlainText(ui->display->toPlainText() + data.names[i] + "\n");
        ui->display->setPlainText(ui->display->toPlainText() + QString::number(data.ages[i]) + "\n");
        ui->display->setPlainText(ui->display->toPlainText() + QString::number(data.weights[i], 'f', 1) + "\n\n");
    }
}

void MainWindow::update_buttons()
{
    if (data.names.size() == 0)
    {
        ui->edit->setEnabled(false);
        ui->erase->setEnabled(false);
        ui->clean->setEnabled(false);
        ui->save->setEnabled(false);
    }
    else
    {
        ui->edit->setEnabled(true);
        ui->erase->setEnabled(true);
        ui->clean->setEnabled(true);
        ui->save->setEnabled(true);
    }

}

void MainWindow::reader(QString _path)
{
    this->on_clean_clicked();

    QFile file(_path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Cant open file";

    QTextStream a(&file);
    for (int i = 0; !a.atEnd(); i++)
    {
        QString line = a.readLine();
        QString value = "";
        int which_data = 0;

        for (int e = 0; e < line.length(); e++)
        {
            if (line[e] != ',')
                value.append(line[e]);
            else
            {
                if (which_data == 0)
                    data.names.push_back(value);
                else if(which_data == 1)
                    data.ages.push_back(value.toInt());
                value.clear();
                which_data++;
            }

            if (e == line.length() - 1)
                data.weights.push_back(value.toDouble());
        }
    }

    display_data();
}

void MainWindow::saver(QString _path)
{
    QFile file(_path);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        qDebug("Cant open file");

    int size = data.names.size();

    QTextStream a(&file);
    for (int i = 0; i < size; i++)
    {
        QString value = data.names[i] + "," + QString::number(data.ages[i]) + "," + QString::number(data.weights[i], 'f', 1);
        a << value;
        if(i + 1 < size)
            a << "\n";
    }

    file.close();

}

void MainWindow::on_add_clicked()
{
    std::vector <QString> aux_vector;

    add_edit add_edit;
    if (add_edit.exec() == 1)
    {
        aux_vector = add_edit.get_data();

        data.names.push_back(aux_vector[0]);
        data.ages.push_back(aux_vector[1].toInt());
        data.weights.push_back(aux_vector[2].toDouble());

        display_data();
    }
}


void MainWindow::on_clean_clicked()
{
    data.names.clear();
    data.ages.clear();
    data.weights.clear();

    ui->display->clear();
    update_buttons();
}


void MainWindow::on_edit_clicked()
{
    std::vector <QString> aux_vector;

    select select;
    select.size = data.names.size();

    if (data.names.size() == 1)
    {
        int nperson = 0;

        add_edit add_edit;
        aux_vector.push_back(data.names[nperson]);
        aux_vector.push_back(QString::number(data.ages[nperson]));
        aux_vector.push_back(QString::number(data.weights[nperson], 'f', 1));

        add_edit.set_data(aux_vector);

        if (add_edit.exec() == 1)
        {
            aux_vector = add_edit.get_data();
            data.names[nperson] = aux_vector[0];
            data.ages[nperson] = aux_vector[1].toInt();
            data.weights[nperson] = aux_vector[2].toDouble();

            display_data();
        }
    }
    else if (select.exec() == 1)
    {
        int nperson = select.get_data() - 1;

        add_edit add_edit;
        aux_vector.push_back(data.names[nperson]);
        aux_vector.push_back(QString::number(data.ages[nperson]));
        aux_vector.push_back(QString::number(data.weights[nperson], 'f', 1));

        add_edit.set_data(aux_vector);

        if (add_edit.exec() == 1)
        {
            aux_vector = add_edit.get_data();
            data.names[nperson] = aux_vector[0];
            data.ages[nperson] = aux_vector[1].toInt();
            data.weights[nperson] = aux_vector[2].toDouble();

            display_data();
        }
    }
}


void MainWindow::on_erase_clicked()
{
    select select;
    select.size = data.names.size();
    select.change_label();

    if (data.names.size() == 1)
    {
        data.names.erase(data.names.begin());
        data.ages.erase(data.ages.begin());
        data.weights.erase(data.weights.begin());

        display_data();
    }
    else if (select.exec() == 1)
    {
        int nperson = select.get_data() - 1;
        data.names.erase(data.names.begin() + nperson);
        data.ages.erase(data.ages.begin() + nperson);
        data.weights.erase(data.weights.begin() + nperson);

        display_data();
    }
}


void MainWindow::on_open_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) , tr("CSV Files(*.csv)"));
    if (path != "")
        reader(path);
}


void MainWindow::on_save_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Guardar Archivo"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("CSV Files(*.csv)"));
    if (path != "")
        saver(path);
}
