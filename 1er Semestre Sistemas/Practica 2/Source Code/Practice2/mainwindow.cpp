/*
    Created by: Jorge Mora
    Practica 2
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load Fonts
    QFontDatabase::addApplicationFont(":/fonts/Assets/SF-Pro-Text-Bold.otf");
    QFontDatabase::addApplicationFont(":/fonts/Assets/SF-Pro-Text-Regular.otf");

    // Set default values
    ui->history->setText("");
    ui->input->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Return:
            ui->equal->animateClick();
            break;
        case Qt::Key_Enter:
            ui->equal->animateClick();
            break;
        case Qt::Key_Backspace:
            ui->input->backspace();
            break;
        case Qt::Key_0:
            ui->num_0->animateClick();
            break;
        case Qt::Key_1:
            ui->num_1->animateClick();
            break;
        case Qt::Key_2:
            ui->num_2->animateClick();
            break;
        case Qt::Key_3:
            ui->num_3->animateClick();
            break;
        case Qt::Key_4:
            ui->num_4->animateClick();
            break;
        case Qt::Key_5:
            ui->num_5->animateClick();
            break;
        case Qt::Key_6:
            ui->num_6->animateClick();
            break;
        case Qt::Key_7:
            ui->num_7->animateClick();
            break;
        case Qt::Key_8:
            ui->num_8->animateClick();
            break;
        case Qt::Key_9:
            ui->num_9->animateClick();
            break;
        case Qt::Key_Period:
            ui->dot->animateClick();
            break;
        case Qt::Key_Plus:
            ui->plus->animateClick();
            break;
        case Qt::Key_Minus:
            ui->minus->animateClick();
            break;
        case Qt::Key_Asterisk:
            ui->multiplication->animateClick();
            break;
        case Qt::Key_Slash:
            ui->division->animateClick();
            break;
    }
}


void MainWindow::translator(QString _input)
{
    std::vector<QString> result;
    int length = _input.length();
    bool error = false;

    for (int i = 0; i < length; i++)
    {
        // ======== Posible Errors ========

        // Other errors
        if (error)
            break;

        // Last character invalid
        if (_input[length - 1] == '+' ||_input[length - 1] == '-' || _input[length - 1] == 'x' || _input[length - 1] == '*' || _input[length - 1] == '/' || _input[length - 1] == '.')
        {
            setError("ERROR: Last char invalid");
            error = true;
            break;
        }

        // Multiple signs
        if ((_input[i] == '*' || _input[i] == 'x' || _input[i] == '/' || _input[i] == '.') && (_input[i + 1] == '*' || _input[i + 1] == 'x' || _input[i + 1] == '/' || _input[i + 1] == '.'))
        {
            setError("ERROR: Multiple Sig+ns");
            error = true;
            break;
        }
        else if((_input[i] == '+' || _input[i] == '-') && (_input[i + 1] == '*' || _input[i + 1] == 'x' || _input[i + 1] == '/' || _input[i + 1] == '.'))
        {
            setError("ERROR: Multiple Signs");
            error = true;
            break;
        }
        else if((_input[i] == '.') && (_input[i + 1] == '+' || _input[i + 1] == '-'))
        {
            setError("ERROR: Multiple Signs");
            error = true;
            break;
        }

        // Unvalid char
        if (!(_input[i].isDigit() || _input[i] == '+' || _input[i] == '-' || _input[i] == '*' || _input[i] == 'x' || _input[i] == '/' || _input[i] == '.'))
        {
            setError("ERROR: Unvalid char");
            error = true;
            break;
        }

        // ======== Interpeter ========

        if ((_input[0] == '+' || _input[0] == '-' || _input[0] == 'x' || _input[0] == '/') && (i == 0))
        {
            result.push_back("0");
            result.push_back(_input[0]);
            i++;
        }

        if (_input[i].isDigit()) // Is a number
        {
            QString num = "";
            bool isdecimal = false;
            num.append(_input[i]);

            if (i + 1 != length) // Out of index size
            {
                while ((_input[i + 1].isDigit()) || (_input[i + 1] == '.'))
                {
                    num.append(_input[i + 1]);
                    i++;

                    if (i + 1 == length) // Next char is last?
                        break;

                    if (isdecimal)
                    {
                        if (_input[i + 1] == '.')
                        {
                            setError("ERROR: Muliple Periods");
                            error = true;
                        }
                    }
                    else
                    {
                        if (_input[i] == '.')
                            isdecimal = true;
                    }
                }
            }
            result.push_back(num);
        }

        if (_input[i] == '.') // Zero Decimal Place without zero
        {
            QString num = "0.";

            if (i + 1 != length) // Out of index size
            {
                while ((_input[i + 1].isDigit()))
                {
                    num.append(_input[i + 1]);
                    i++;

                    if (_input[i + 1] == '.')
                    {
                        setError("ERROR: Muliple Periods");
                        error = true;
                    }

                    if (i + 1 == length) // Next char is the last?
                        break;
                }
            }
            result.push_back(num);
        }

        if (_input[i] == '*' || _input[i] == 'x' || _input[i] == '/') // Is a math sign
        {
            if (i + 1 != length)
            {
                if (_input[i + 1] == '+' || _input[i + 1] == '-')
                {
                    result.push_back(_input[i]);
                    i++;
                    QString num = "";
                    num.append(_input[i]);


                    if (i + 1 != length) // Triple Signs
                    {
                        if(_input[i + 1] == '+' || _input[i + 1] == '-' || _input[i + 1] == 'x' || _input[i + 1] == '*' || _input[i + 1] == '/')
                        {
                            setError("ERROR: Multiple Signs");
                            error = true;
                        }
                    }

                    i++;

                    // == Recycled code from above ==
                    if (_input[i].isDigit()) // Is a number
                    {
                        bool isdecimal = false;
                        num.append(_input[i]);;

                        if (i + 1 != length) // Out of index size
                        {
                            while ((_input[i + 1].isDigit()) || (_input[i + 1] == '.'))
                            {
                                num.append(_input[i + 1]);
                                i++;

                                if (i + 1 == length) // Next char is the last?
                                    break;

                                if (isdecimal)
                                {
                                    if (_input[i + 1] == '.')
                                    {
                                        setError("ERROR: Muliple Periods");
                                        error = true;
                                    }
                                }
                                else
                                {
                                    if (_input[i] == '.')
                                        isdecimal = true;
                                }
                            }
                        }
                        result.push_back(num);
                    }
                }
                else
                {
                    result.push_back(_input[i]);
                }
            }
        }
        else if(_input[i] == '+' || _input[i] == '-')
        {
            if (i + 1 != length)
            {
                if (_input[i + 1] == '+' || _input[i + 1] == '-') // Rule ef signs
                {
                    if (_input[i] == '+' && _input[i + 1] == '+')
                    {
                        result.push_back("+");
                        i++;
                    }
                    else if (_input[i] == '-' && _input[i + 1] == '-')
                    {
                        result.push_back("+");
                        i++;
                    }
                    else if (_input[i] == '+' && _input[i + 1] == '-')
                    {
                        result.push_back("-");
                        i++;
                    }
                    else if (_input[i] == '-' && _input[i + 1] == '+')
                    {
                        result.push_back("-");
                        i++;
                    }

                    if (i + 1 != length) // Triple Signs
                    {
                        if(_input[i + 1] == '+' || _input[i + 1] == '-' || _input[i + 1] == 'x' || _input[i + 1] == '*' || _input[i + 1] == '/')
                        {
                            setError("ERROR: Multiple Signs");
                            error = true;
                        }
                    }

                }
                else
                {
                    result.push_back(_input[i]);
                }
            }
        }


    }

    if (!error)
    {
        // Divide by zero
        length = result.size();
        for(int i = 0; i < length; i++)
        {
            if ((result[i] == "/") && (result[i + 1].toDouble() == 0))
            {
                setError("ERROR: Dividing by zero");
                error = true;
                break;
            }
        }
    }

    if (!error)
        solver(result);
}

void MainWindow::solver(std::vector<QString> _operation) // ("56", "*" , "3")
{
     std::vector<QString> aux_vector;
     text_rich_generator(_operation);
     int size       = _operation.size();
     double result  = 0;

     qDebug() << _operation;
     // ========== Multiplication ==========
     for (int i = 1; i < size; i +=2)
     {
         if (_operation[i] == "*" || _operation[i] == "x")
         {
             result = _operation[i - 1].toDouble() * _operation[i + 1].toDouble();
             aux_vector.push_back(QString::number(result, 'f', 3));

             if (i + 2 < size) // Check if i char isnt the last
             {
                 i+=2;
                 for (int a = i; a < size; a++)
                     aux_vector.push_back(_operation[a]);

             }
             _operation = aux_vector;
             aux_vector.clear();
             i = -1;
             size = _operation.size();

         }
         else if(_operation[i] == "+" || _operation[i] == "-" || _operation[i] == "/")
         {
             if (i - 2 > 0) // Check if i char isnt the first
             {
                 if ((_operation[i - 2] != "x") && (_operation[i - 2] != "*"))
                 {
                    aux_vector.push_back(_operation[i - 1]);
                 }
             }
             else
             {
                 aux_vector.push_back(_operation[i - 1]);
             }

             aux_vector.push_back(_operation[i]);

         }
     }

     aux_vector.clear();
     size   = _operation.size();
     result = 0;

     qDebug() << _operation;
     // ========== Division ==========
     for (int i = 1; i < size; i +=2)
     {
         if (_operation[i] == "/")
         {
             result = _operation[i - 1].toDouble() / _operation[i + 1].toDouble();
             aux_vector.push_back(QString::number(result, 'f', 3));

             if (i + 2 < size) // Check if i char isnt the last
             {
                 i+=2;
                 for (int a = i; a < size; a++)
                     aux_vector.push_back(_operation[a]);

             }
             _operation = aux_vector;
             aux_vector.clear();
             i = -1;
             size = _operation.size();

         }
         else if(_operation[i] == "+" || _operation[i] == "-")
         {
             if (i - 2 > 0) // Check if i char isnt the first
             {
                 if ((_operation[i - 2] != "x") && (_operation[i - 2] != "*"))
                 {
                    aux_vector.push_back(_operation[i - 1]);
                 }
             }
             else
             {
                 aux_vector.push_back(_operation[i - 1]);
             }

             aux_vector.push_back(_operation[i]);

         }
     }

     aux_vector.clear();
     size   = _operation.size();
     result = 0;

     qDebug() << _operation;
     // ========== Minus ==========
     for (int i = 1; i < size; i +=2)
     {
         if (_operation[i] == "-")
         {
             result = _operation[i - 1].toDouble() - _operation[i + 1].toDouble();
             aux_vector.push_back(QString::number(result, 'f', 3));

             if (i + 2 < size) // Check if i char isnt the last
             {
                 i+=2;
                 for (int a = i; a < size; a++)
                     aux_vector.push_back(_operation[a]);

             }
             _operation = aux_vector;
             aux_vector.clear();
             i = -1;
             size = _operation.size();

         }
         else if(_operation[i] == "+")
         {
             if (i - 2 > 0) // Check if i char isnt the first
             {
                 if ((_operation[i - 2] != "x") && (_operation[i - 2] != "*"))
                 {
                    aux_vector.push_back(_operation[i - 1]);
                 }
             }
             else
             {
                 aux_vector.push_back(_operation[i - 1]);
             }

             aux_vector.push_back(_operation[i]);

         }
     }

     aux_vector.clear();
     size   = _operation.size();
     result = 0;

     qDebug() << _operation;

     // ========== Plus ==========
     for (int i = 1; i < size; i +=2)
     {
         if (_operation[i] == "+")
         {
             result = _operation[i - 1].toDouble() + _operation[i + 1].toDouble();
             aux_vector.push_back(QString::number(result, 'f', 3));

             if (i + 2 < size) // Check if i char isnt the last
             {
                 i+=2;
                 for (int a = i; a < size; a++)
                     aux_vector.push_back(_operation[a]);

             }
             _operation = aux_vector;
             aux_vector.clear();
             i = -1;
             size = _operation.size();

         }
     }

    // Display values
    // Remove Zeros
    QString ans = _operation[0];

    if (ans.endsWith("0"))
    {
        while(ans.endsWith("0"))
            ans.remove(ans.length()-1, 1);

        if (ans.endsWith("."))
            ans.remove(ans.length()-1, 1);
    }
    ui->input->setText(ans);
}

void MainWindow::text_rich_generator(std::vector<QString> raw)
{
    ui->history->setText("");
    QString rich_text   = "";
    int size            = raw.size();

    // Generate richtext
    for (int i = 0; i < size; i++)
    {
        if (raw[i] == "*" || raw[i] == "x" ||  raw[i] == "+" || raw[i] == "-" || raw[i] == "/")
        {
            rich_text.append("<span style='color:#df7a79;'> " + raw[i] + " </span>");
        }
        else
        {
            rich_text.append("<span style='color:#ffffff;'>" + raw[i] + "</span>");
        }
    }

    ui->history->setText(rich_text);
}

void MainWindow::setError(QString _error)
{
    ui->input->setText("");
    ui->input->setPlaceholderText(_error);
    ui->history->setText("");
}


/*
 ____        _   _
| __ ) _   _| |_| |_ ___  _ __  ___
|  _ \| | | | __| __/ _ \| '_ \/ __|
| |_) | |_| | |_| || (_) | | | \__ \
|____/ \__,_|\__|\__\___/|_| |_|___/

*/

void MainWindow::on_ce_clicked() // Clear data
{
    ui->input->setText("");
    ui->history->setText("");
    ui->input->setPlaceholderText("0");
}

void MainWindow::on_equal_clicked()
{
    if (ui->input->text() != "")
        translator(ui->input->text());
}

void MainWindow::on_plus_clicked()
{
    ui->input->setText(ui->input->text() + "+");
}

void MainWindow::on_minus_clicked()
{
    ui->input->setText(ui->input->text() + "-");
}

void MainWindow::on_multiplication_clicked()
{
    ui->input->setText(ui->input->text() + "x");
}

void MainWindow::on_division_clicked()
{
    ui->input->setText(ui->input->text() + "/");
}


void MainWindow::on_dot_clicked()
{
    ui->input->setText(ui->input->text() + ".");
}

/*
 _   _                 _
| \ | |_   _ _ __ ___ | |__   ___ _ __ ___
|  \| | | | | '_ ` _ \| '_ \ / _ \ '__/ __|
| |\  | |_| | | | | | | |_) |  __/ |  \__ \
|_| \_|\__,_|_| |_| |_|_.__/ \___|_|  |___/

*/
void MainWindow::on_num_0_clicked()
{
    ui->input->setText(ui->input->text() + "0");
}

void MainWindow::on_num_1_clicked()
{
    ui->input->setText(ui->input->text() + "1");
}


void MainWindow::on_num_2_clicked()
{
    ui->input->setText(ui->input->text() + "2");
}


void MainWindow::on_num_3_clicked()
{
    ui->input->setText(ui->input->text() + "3");
}

void MainWindow::on_num_4_clicked()
{
    ui->input->setText(ui->input->text() + "4");
}


void MainWindow::on_num_5_clicked()
{
    ui->input->setText(ui->input->text() + "5");
}


void MainWindow::on_num_6_clicked()
{
    ui->input->setText(ui->input->text() + "6");
}


void MainWindow::on_num_7_clicked()
{
    ui->input->setText(ui->input->text() + "7");
}

void MainWindow::on_num_8_clicked()
{
    ui->input->setText(ui->input->text() + "8");
}

void MainWindow::on_num_9_clicked()
{
    ui->input->setText(ui->input->text() + "9");
}

void MainWindow::on_input_textChanged(const QString &arg1)
{
     ui->input->setPlaceholderText("0");
}
