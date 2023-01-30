#ifndef WIN_H
#define WIN_H

#include <QWidget>

namespace Ui {
class Win;
}

class Win : public QWidget
{
	Q_OBJECT
	
public:
	explicit Win(QWidget *parent = nullptr);
	~Win();
	
	void set_text(QString text);
	
private slots:
	void on_Play_clicked();
	
private:
	Ui::Win *ui;
	
};

#endif // WIN_H
