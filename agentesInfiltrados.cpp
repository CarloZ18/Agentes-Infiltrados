#include <iostream>
#include <fstream>
using namespace std;

//Variables

//Crear clase

// Struct de las personas registradas
struct personaRegistrada
{
    string nombre;
    string especia;
    int altura;
    string capacidadMagica;
    float profundidadOjos;
    float distanciaEntreOjos;
    int distaciaFrenteYNariz;
    float distanciaNarizYLabioSuperior;
};

// Crear archivo
void crearBaseDeDatos(string data)
{
    ofstream archivo("dataBase.in");

    // Verificamos si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al crear el archivo";
    }

    archivo.close();
    cout << "Datos escritos en el archivo con exito";
}

// Leer archivo
void leerBaseDeDatos()
{
    ifstream archivo("dataBase.in");

    // Verificamos si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al crear el archivo";
    }

    string linea;
    getline(archivo, linea);
    int cantidadPersonas=stoi(linea);
    // Leemos el archivo línea por línea
    while (getline(archivo, linea))
    {

        cout << linea << endl; // Mostramos cada línea en la consola
    }

    archivo.close();
    cout << cantidadPersonas;
}

string obtenerData(int personasRegistradas)
{
}

int main()
{

    leerBaseDeDatos();
    return 0;
}