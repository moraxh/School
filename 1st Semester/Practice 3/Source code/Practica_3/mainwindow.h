#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <QDebug>
#include <vector>

#include "add_edit.h"
#include "select.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct var
    {
        std::vector <QString> names;
        std::vector <int> ages;
        std::vector <double> weights;
    };

    struct var data;

    void display_data();

    void update_buttons();

    void reader(QString _path);

    void saver(QString _path);

private slots:

    void on_add_clicked();

    void on_clean_clicked();

    void on_edit_clicked();

    void on_erase_clicked();

    void on_open_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
