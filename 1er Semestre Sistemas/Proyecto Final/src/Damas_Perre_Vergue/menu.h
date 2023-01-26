#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_Exit_clicked();

    void on_Play_clicked();

private:
    Ui::Menu *ui;
};
#endif // MENU_H
