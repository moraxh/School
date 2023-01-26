#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) : QMainWindow(parent), ui(new Ui::Game) {
	ui->setupUi(this);
	
	// Un poco de CSS para que se vea chido
	QString stylesheet = ".QPushButton{border: none; border-radius: 2px;} .QPushButton:hover{border: 1px solid black;}";
	QString white = "#e0cdad";
	QString black = "#7a4f23";
	
	// Crear tablero en un tipo de "arreglo" para botones
	QButtonGroup board;
	
	// Crear 64 casillas
	for (int i = 0; i < 64; i++) {
		// Añadir boton dandole un id y siendo este hijo del QFrame board
		board.addButton(new QPushButton(ui->board), i);
		// Establecer el nombre del boton
		board.button(i)->setObjectName(QString::number(i));
		// Darle tamaño
		board.button(i)->resize(49, 49);
		// Posicionar el boton en el eje x, y
		int x = ((i % 8) * 49) + 4;
		int y = (int(i / 8) * 49) + 4;
		board.button(i)->move(x, y);
		// Conectar todas las señales de los botones a un mismo metodo
		connect(board.button(i), SIGNAL(clicked()), this, SLOT(OnButtonClicked()));
		
		// Ponerle su estilo mmalon
		if (((i + int(i / 8)) % 2) == 0)
			board.button(i)->setStyleSheet(stylesheet + ".QPushButton{background-color:" + white + ";}");
		else
			board.button(i)->setStyleSheet(stylesheet + ".QPushButton{background-color:" + black + ";}");
		
		// Cursor
		board.button(i)->setCursor(Qt::PointingHandCursor);
	}
	
	// Depende de grid este mueve las piezas
//	for (int i = 0; i < 8; i++) {
//		for (int j = 0; j < 8; j++) {
//			// Buscar el que tiene el mismo nombre
//			refresh(grid[i][j], ui->board->findChild<QPushButton *>(QString::number((i * 8) + j)));
//		}
//	}
	
	updater();.
	
	turn_of();
}

Game::~Game() { delete ui; }

void Game::move(int from, int to) {
	// Guardar el caracter de las posiciones elegidas
	int from_x = from % 8;
	int from_y = int(from / 8);
	int to_x = to % 8;
	int to_y = int(to / 8);
	
	char to_char = grid[to_y][to_x];
	char from_char =  grid[from_y][from_x];
	
	// Convertir en dama
	if(from_char == 'x' && to_y == 7)
		from_char = 'X';
	else if(from_char == 'o' && to_y == 0)
		from_char = 'O';
		
	// Cambiar tabla 
	grid[to_y][to_x] = from_char;
	grid[from_y][from_x] = to_char;
	
	// Checar si comio a alguien 
	if(from_y + 2 == to_y){
		if(from_x + 2 == to_x){
			grid[from_y + 1][from_x + 1] == 'x' || grid[from_y + 1][from_x + 1] == 'X' ? f_blancas--: f_rojas--;
			grid[from_y + 1][from_x + 1] = '-';
//			refresh('-', ui->board->findChild<QPushButton*>(QString::number( ((from_y + 1) * 8) + from_x + 1)));
		}
		if(from_x - 2 == to_x) {
			grid[from_y + 1][from_x - 1] == 'x' || grid[from_y + 1][from_x - 1] == 'X' ? f_blancas--: f_rojas--;
			grid[from_y + 1][from_x - 1] = '-';
//			refresh('-', ui->board->findChild<QPushButton*>(QString::number( ((from_y + 1) * 8) + from_x - 1)));
		}
	}
	else if(from_y - 2 == to_y){
		if(from_x + 2 == to_x){
			grid[from_y - 1][from_x + 1] == 'x' || grid[from_y - 1][from_x + 1] == 'X' ? f_blancas--: f_rojas--;
			grid[from_y - 1][from_x + 1] = '-';
//			refresh('-', ui->board->findChild<QPushButton*>(QString::number( ((from_y - 1) * 8) + from_x + 1)));
		}
		if(from_x - 2 == to_x){
			grid[from_y - 1][from_x - 1] == 'x' || grid[from_y - 1][from_x - 1] == 'X' ? f_blancas--: f_rojas--;
			grid[from_y - 1][from_x - 1] = '-';
//			refresh('-', ui->board->findChild<QPushButton*>(QString::number( ((from_y - 1) * 8) + from_x - 1)));
		}
	}
	
	// Actualizar cambios de forma visual
//	refresh(grid[int(to_y)][to_x], ui->board->findChild<QPushButton*>(QString::number(to)));
//	refresh(grid[int(from_y)][from_x], ui->board->findChild<QPushButton*>(QString::number(from)));
	
	std::thread hola(&Game::updater, this);
	
}

void Game::history(int from, int to)
{
	// Diccionario para acceder a la letra segun posicion en x
	char dict[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	char from_x = dict[from % 8];
	int from_y = int(from / 8) + 1;
	char to_x = dict[to % 8];
	int to_y = int(to / 8) + 1;
	
	// Concantenar a historial
		ui->history->append((turn_red ? "Rebeca(" : "Hadassah(") + QString(from_x) + QString::number(from_y) + " → " + QString(to_x) + QString::number(to_y) + ")");
}

void Game::highlighter(int id, bool clean)
{
	int x = id % 8;
	int y = int(id / 8);
	QPushButton *btn;
	
	if (clean){
		/*
		 * BLANCAS
		 */ 
		if(grid[y][x] == 'x') {
			// Abajo
			if (y < 7){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y + 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x - 1) ));
						refresh(grid[y + 1][x - 1], btn);
					}
					// Comer a un jugador 
					else if(grid[y + 1][x - 1] == 'o' || grid[y + 1][x - 1] == 'O'){
						if((y + 1) < 7 && (x - 1) > 0) {
							if(grid[y + 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x - 2) ));
								refresh(grid[y + 2][x - 2], btn);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y + 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x + 1) ));
						refresh(grid[y + 1][x + 1], btn);
					}
					else if(grid[y + 1][x + 1] == 'o' || grid[y + 1][x + 1] == 'O'){
						if((y + 1) < 7 && (x + 1) < 7) {
							if(grid[y + 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x + 2) ));
								refresh(grid[y + 2][x + 2], btn);
							}
						}
					}
				}	
			}
		}
		/*
		 * NEGRAS
		 */ 
		else if (grid[y][x] == 'o'){
			// Arriba
			if (y > 0){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y - 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x - 1) ));
						refresh(grid[y - 1][x - 1], btn);
					}
					// Comer a un jugador 
					else if(grid[y - 1][x - 1] == 'x' || grid[y - 1][x - 1] == 'X'){
						if((y - 1) > 0 && (x - 1) > 0) {
							if(grid[y - 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x - 2) ));
								refresh(grid[y - 2][x - 2], btn);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y - 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x + 1) ));
						refresh(grid[y - 1][x + 1], btn);
					}
					else if(grid[y - 1][x + 1] == 'x' || grid[y - 1][x + 1] == 'X'){
						if((y - 1) > 0 && (x + 1) < 7) {
							if(grid[y - 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x + 2) ));
								refresh(grid[y - 2][x + 2], btn);
							}
						}
					}
				}
			}
		}
		/*
		 * DAMAS
		 */ 
		else if (grid[y][x] == 'X' || grid[y][x] == 'O'){
			char enemy, enemy_d;
			if (grid[y][x] == 'X'){
				enemy = 'o';
			   enemy_d = 'O';
			}
			else {
				enemy = 'x';
				enemy_d = 'X';
			}
			// Arriba
			if (y > 0){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y - 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x - 1) ));
						refresh(grid[y - 1][x - 1], btn);
					}
					// Comer a un jugador 
					else if(grid[y - 1][x - 1] == enemy || grid[y - 1][x - 1] == enemy_d){
						if((y - 1) > 0 && (x - 1) > 0) {
							if(grid[y - 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x - 2) ));
								refresh(grid[y - 2][x - 2], btn);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y - 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x + 1) ));
						refresh(grid[y - 1][x + 1], btn);
					}
					else if(grid[y - 1][x + 1] == enemy || grid[y - 1][x + 1] == enemy_d){
						if((y - 1) > 0 && (x + 1) < 7) {
							if(grid[y - 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x + 2) ));
								refresh(grid[y - 2][x + 2], btn);
							}
						}
					}
				}
			}
			
			// Abajo
			if (y < 7){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y + 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x - 1) ));
						refresh(grid[y + 1][x - 1], btn);;
					}
					// Comer a un jugador 
					else if(grid[y + 1][x - 1] == enemy || grid[y + 1][x - 1] == enemy_d){
						if((y + 1) < 7 && (x - 1) > 0) {
							if(grid[y + 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x - 2) ));
								refresh(grid[y + 2][x - 2], btn);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y + 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x + 1) ));
						refresh(grid[y + 2][x + 1], btn);
					}
					else if(grid[y + 1][x + 1] == enemy || grid[y + 1][x + 1] == enemy_d){
						if((y + 1) < 7 && (x + 1) < 7) {
							if(grid[y + 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x + 2) ));
								refresh(grid[y + 2][x + 2], btn);
							}
						}
					}
				}	
			}
		}
	}
	
	/*
	 * 
	 * 
	 * 
	 * 
	 * 
	 */
	else {
		/*
		 * BLANCAS
		 */ 
		if(grid[y][x] == 'x') {
			// Abajo
			if (y < 7){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y + 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x - 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					// Comer a un jugador 
					else if(grid[y + 1][x - 1] == 'o' || grid[y + 1][x - 1] == 'O'){
						if((y + 1) < 7 && (x - 1) > 0) {
							if(grid[y + 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x - 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y + 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x + 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					else if(grid[y + 1][x + 1] == 'o' || grid[y + 1][x + 1] == 'O'){
						if((y + 1) < 7 && (x + 1) < 7) {
							if(grid[y + 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x + 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}	
			}
		}
		/*
		 * NEGRAS
		 */ 
		else if (grid[y][x] == 'o'){
			// Arriba
			if (y > 0){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y - 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x - 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					// Comer a un jugador 
					else if(grid[y - 1][x - 1] == 'x' || grid[y - 1][x - 1] == 'X'){
						if((y - 1) > 0 && (x - 1) > 0) {
							if(grid[y - 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x - 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y - 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x + 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					else if(grid[y - 1][x + 1] == 'x' || grid[y - 1][x + 1] == 'X'){
						if((y - 1) > 0 && (x + 1) < 7) {
							if(grid[y - 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x + 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}
			}
		}
		/*
		 * DAMAS
		 */ 
		else if (grid[y][x] == 'X' || grid[y][x] == 'O'){
			char enemy, enemy_d;
			if (grid[y][x] == 'X'){
				enemy = 'o';
			   enemy_d = 'O';
			}
			else {
				enemy = 'x';
				enemy_d = 'X';
			}
			// Arriba
			if (y > 0){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y - 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x - 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					// Comer a un jugador 
					else if(grid[y - 1][x - 1] == enemy || grid[y - 1][x - 1] == enemy_d){
						if((y - 1) > 0 && (x - 1) > 0) {
							if(grid[y - 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x - 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y - 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 1) * 8) + (x + 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					else if(grid[y - 1][x + 1] == enemy || grid[y - 1][x + 1] == enemy_d){
						if((y - 1) > 0 && (x + 1) < 7) {
							if(grid[y - 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y - 2) * 8) + (x + 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}
			}
			
			// Abajo
			if (y < 7){
				// Izquierda
				if (x > 0){
					// Posible movimiento
					if(grid[y + 1][x - 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x - 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					// Comer a un jugador 
					else if(grid[y + 1][x - 1] == enemy || grid[y + 1][x - 1] == enemy_d){
						if((y + 1) < 7 && (x - 1) > 0) {
							if(grid[y + 2][x - 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x - 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}
				// Derecha
				if (x < 7){
					// Posible movimiento
					if(grid[y + 1][x + 1] == '-') {
						btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 1) * 8) + (x + 1) ));
						btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
						btn->setEnabled(true);
					}
					else if(grid[y + 1][x + 1] == enemy || grid[y + 1][x + 1] == enemy_d){
						if((y + 1) < 7 && (x + 1) < 7) {
							if(grid[y + 2][x + 2] == '-') {
								btn = ui->board->findChild<QPushButton*>(QString::number( ((y + 2) * 8) + (x + 2) ));
								btn->setStyleSheet(btn->styleSheet() + ".QPushButton{image:" + holder + ";}");
								btn->setEnabled(true);
							}
						}
					}
				}	
			}
		}
	}
}

void Game::refresh(char ch, QPushButton *button) {	
	// Depende del simbolo la imagen cambiara
	switch (ch) {
		case 'x':
			button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + blancas + ";}");
			break;
		case 'X':
			button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + blancas_d + ";}");
			break;
		case 'o':
			button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + rojas + ";}");
			break;
		case 'O': 
			button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + rojas_d + ";}");
			break;
		default:
			button->setStyleSheet(button->styleSheet() + ".QPushButton{image: none;}");
	}
}

void Game::turn_of() 
{
	// Cambiar el marcador de turno
	if(turn_red){
		ui->turn->setText("Turno de Rebeca");
	}	
	else {
		ui->turn->setText("Turno de Hadassah");
	}
	
	// Recorre los botones y los activa o desactiva segun el turno
	for(int i = 0; i < 64; i++) {
		QPushButton *btn = ui->board->findChild<QPushButton*>(QString::number(i));
		int id = btn->objectName().toInt();
		
		switch(grid[int(id / 8)][id % 8]){
		case 'x':
			// Operador ternario segun el turno
			btn->setEnabled(turn_red ? false : true);
			break;
		case 'X':
			btn->setEnabled(turn_red ? false : true);
			break;
		case 'o':
			btn->setEnabled(turn_red ? true : false);
			break;
		case 'O':
			btn->setEnabled(turn_red ? true : false);
			break;
		default:
			btn->setEnabled(false);
		}
	}
}

void Game::OnButtonClicked() {
	if (from == -1) {
		from = this->sender()->objectName().toInt();
		highlighter(from, false);
	} 
	else {
		to = this->sender()->objectName().toInt();
		highlighter(from, true);
		
		// Si has seleccionado una ficha del mismo grupo
		if (grid[int(to / 8)][to % 8] == grid[int(from / 8)][from % 8]) {
			from = this->sender()->objectName().toInt();
			highlighter(from, false);
		}
		else {
			history(from, to);
			move(from, to);
			turn_red = !turn_red;
			turn_of();
			from = -1;
			// Checar si se gano
			if (f_blancas == 0){
				Win *w = new Win;
				w->show();
				w->set_text("Rebeca");
				this->hide();
			}
			else if(f_rojas == 0){
				Win *w = new Win;
				w->show();
				w->set_text("Hadassah");
				this->hide();				
			}
		}
	}
}

void Game::updater()
{
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			QPushButton *button = ui->board->findChild<QPushButton*>(QString::number((i * 8) + j));
			switch(grid[i][j]){
			case 'x':
				button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + blancas + ";}");
				break;
			case 'X':
				button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + blancas_d + ";}");
				break;
			case 'o':
				button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + rojas + ";}");
				break;
			case 'O': 
				button->setStyleSheet(button->styleSheet() + ".QPushButton{image:" + rojas_d + ";}");
				break;
			default:
				button->setStyleSheet(button->styleSheet() + ".QPushButton{image: none;}");
			}
		}
	}
}
