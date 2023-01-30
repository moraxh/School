#include "win.h"
#include "ui_win.h"

#include "menu.h"

Win::Win(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::Win)
{
	ui->setupUi(this);
}

Win::~Win()
{
	delete ui;
}

void Win::on_Play_clicked()
{
	// Crear un nuevo objeto donde estara el menu
   Menu *g = new Menu;
   // Mostrarlo
   g->show();
   // Ocultarlo
	this->hide();
}

void Win::set_text(QString text)
{
	ui->won->setText("Gano " + text + "!!!");	
}

