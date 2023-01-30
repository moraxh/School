#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_Exit_clicked()
{
    // Salir de la aplicacion
    QApplication::exit();
}


void Menu::on_Play_clicked()
{
    // Crear un nuevo objeto donde estara el juego
    Game *g = new Game;
    // Mostrarlo
    g->show();
    // Ocultarlo
    this->hide();

}

