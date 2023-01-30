#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>
#include <QThread>

#include "win.h"

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit Game(QWidget *parent = nullptr);
	~Game();
	
	// Imagenes de las fichas
	QString blancas = "url(:/images/Hada_White.png)";
	QString rojas = "url(:/images/Rebe_red.png)";
	QString blancas_d = "url(:/images/Hada_White_Dama.png)";
	QString rojas_d = "url(:/images/Rebe_red_Dama.png)";
	QString holder = "url(:/images/holder.png)";
	
	// Contador de fichas 
	int f_blancas = 12;
	int f_rojas = 12;
	
	// Movimientos
	int from = -1;
	int to = -1;
	 
	// Turno
	bool turn_red = true;
	
	/* Crear tablero
	 * - = Nada
	 * x = Blancas
	 * o = Rojas
	 * X = Dama blanca
	 * O = Dama roja
	 */
	char grid[8][8] = {{'x', '-', 'x', '-', 'x', '-', 'x', '-'},
							{'-', '-', '-', 'x', '-', 'x', '-', 'x'},
							{'x', '-', 'x', '-', 'x', '-', 'x', '-'},
							{'-', '-', '-', '-', '-', '-', '-', '-'},
							{'-', '-', '-', '-', '-', '-', '-', '-'},
							{'-', 'o', '-', 'o', '-', 'o', '-', 'o'},
							{'o', '-', 'o', '-', 'o', '-', 'o', '-'},
							{'-', 'o', '-', 'o', '-', 'o', '-', 'o'}};
	
	
private slots:
	// Mueve  las fichas
	void move(int from, int to);
	// Establece el historial
	void history(int from, int to);
	// Ilumina los posibles movimientos
	void highlighter(int id, bool clean);
	// Actualiza una posicion
	void refresh(char ch, QPushButton *button);
	// Activa/Desactiva los botones segun el turno
	void turn_of();
	// Si un boton es presionado
	void OnButtonClicked();
	void updater();
private:
	Ui::Game *ui;
};

#endif // GAME_H
