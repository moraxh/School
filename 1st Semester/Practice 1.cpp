/* 
    Practica 1 
    Jorge Emiliano Mora Herrera
    Nua: 393872
*/

#include <iostream>
#include <string>

using namespace std; 

string names[10]    = {"", "", "", "", "", "", "", "", "", ""};
int ages[10]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int weights[10]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool main_run = true;
int opt, aux1, aux3;
string aux2;

void main_menu();
void input_data();
void print_data(int a);
void search_data(int a, int b, int c,string d);
void search(int a);

int main () 
{
    main_menu();
}

void main_menu() 
{
    while (main_run) 
    {
        cout << "\n---Agenda---\nMenu\n0 - Salir\n1 - Ingresar datos\n2 - Buscar por edad\n3 - Buscar por nombre\n4 - Buscar por peso\n5 - Imprimir agenda\n\nIngrese una opcion: ";
        cin >> opt;

        switch (opt)
        {
            case 0:
                main_run = false;
                break;
            case 1: 
                input_data();
                break;
            case 2: 
                search(1);
                break;
            case 3: 
                search(2);
                break;
            case 4: 
                search(3);
                break;
            case 5: 
                if (names[0] != "")
                {
                    for(int i = 0; i < 10; i++)
                    {
                        print_data(i);
                    }
                }
                else
                {
                    cout << "\n-> ERROR: No existe informacion guardada <-\n";
                }
                break;
            default:
                cout << "\n-> ERROR: Opcion no valida <-\n"; 
                break;
        }
    }
}

void input_data() 
{
    for (int i = 0; i < 10; i++)
    {
        cout << "\nPersona (" << i + 1 << ")";
        cout << "\nIngrese el nombre: ";
        cin.ignore(10000, '\n');
        cin.clear();
        getline(cin, names[i]);

        while (ages[i] <= 0) 
        {
            cout << "Ingrese la edad(mayor que 0): ";
            cin >> ages[i];
        }

        while (weights[i] <= 0)
        {
            cout << "Ingrese el peso(mayor que 0): ";
            cin >> weights[i];
        }
    }
}

void print_data(int a) 
{
    cout << "\nPersona (" << a + 1 << ")\nNombre: " << names[a] << "\nEdad: " << ages[a] << "\nPeso: " << weights[a] << endl;
    aux1 = 1;
}

/* 
a = al arreglo que queremos consultar 1 = edad, 2 = nombre, 3 = peso
b = a la edad o peso que queremos buscar
c = 1 si es un dato especifico, 2 si es menor que y 3 si es mayor que
d = al nombre que queremos buscar 
*/
void search_data(int a, int b, int c,string d)
{
    aux1 = 0;
    if (a == 1)
    {   
        for(int i = 0; i < 10; i++)
        {   
            if (c == 1)
            {
                if (ages[i] == b)
                {
                    print_data(i);
                }
            }
            else if (c == 2) 
            {
                if (ages[i] < b)
                {
                    print_data(i);
                }
            }
            else if (c == 3)
            {
                if (ages[i] > b)
                {
                    print_data(i);
                }
            }
            if (i == 9 && aux1 == 0)
            {
                cout << "\nNo hay nadie que coincida\n";
            }
        }
    }
    else if (a == 2)
    {
        for (int i = 0; i < 10; i++)
        {
            if (names[i] == d)
            {
                print_data(i);   
            }
            if (i == 9 && aux1 == 0)
            {
                cout << "\nNo hay nadie que se llame asi\n";
            }
        }
    }
    else if (a == 3)
    {
        for(int i = 0; i < 10; i++)
        {   
            if (c == 1)
            {
                if (weights[i] == b)
                {
                    print_data(i);
                }
            }
            else if (c == 2) 
            {
                if (weights[i] < b)
                {
                    print_data(i);
                }
            }
            else if (c == 3)
            {
                if (weights[i] > b)
                {
                    print_data(i);
                }
            }
            if (i == 9 && aux1 == 0)
            {
                cout << "\nNo hay nadie que coincida\n";
            }
        }
    }
}

/* 
a = 1 Buscar edad
a = 2 Buscar nombres
a = 3 Buscar peso
*/
void search(int a) 
{
    // Checa si existen datos
    if (names[0] != "")
    {
        switch (a) 
        {
            case 1:
                cout << "\nSubmenu\n0 - Regresar\n1 - Edad Especifica\n2 - Menor a X edad\n3 - Mayor a X edad\nIngrese una opcion: ";
                aux2 = "\nIngrese la edad especifica: ";
                aux1 = 1;
                break;
            case 2:
                cout << "\nIngrese un nombre: ";
                cin.ignore(10000, '\n');
                cin.clear();
                getline(cin, aux2);
                search_data(2, 0, 0, aux2);
                break;
            case 3:
                cout << "\nSubmenu\n0 - Regresar\n1 - Peso Especifica\n2 - Menor a X peso\n3 - Mayor a X peso\nIngrese una opcion: ";
                aux2 = "\nIngrese el peso especifico: ";
                aux1 = 3;
                break;
        }

        if (a == 1 || a == 3)
        {   cin >> opt;

            switch (opt)
            {
                case 1:
                    cout << aux2;
                    cin >> aux3;
                    search_data(aux1, aux3, 1, "");
                    break;
                case 2:
                    cout << (aux1 == 1?"\nIngrese la edad menor que: ":"\nIngrese el peso menor que: " );
                    cin >> aux3;
                    search_data(aux1, aux3, 2, "");
                    break;
                case 3:
                    cout << (aux1 == 1?"\nIngrese la edad mayor que: ":"\nIngrese el peso mayor que: " );
                    cin >> aux3;
                    search_data(aux1, aux3, 3, "");
                    break;
            }
        }
    }
    else {
        cout << "\n-> ERROR: No existe informacion guardada <-\n";
    }
}