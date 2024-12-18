#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

//Variables

//Crear clase

// Struct de las personas registradas
struct personas
{
    string nombre;
    string especie;
    int altura;
    string capacidadMagica;
    float profundidadOjos;
    float distanciaEntreOjos;
    int distanciaFrenteYNariz;
    float distanciaNarizYLabioSuperior;
}persona;

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

/*detectar cambiaforma: no pueden alterar todo su estructura facial,no pueden alterar su altura mas de
1 unidad de medida hacia arriba o abajo,cada 3 personas comparten como maximo 2 medidas faciales,

*/


int numpersonas;

int  validacion( personas persona1, personas persona2, int numpersonas, int contador=0){
    if(persona1.especie==persona2.especie){
        contador++;
    }
    if(persona1.altura==persona2.altura || persona1.altura<=persona1.altura+1 || persona1.altura>=persona2.altura-1){
        contador++;
    }
    if(persona1.profundidadOjos==persona2.profundidadOjos){
        contador++;
    }
    if(persona1.distanciaEntreOjos==persona2.distanciaEntreOjos){
        contador++;
    }
    if(persona1.distanciaFrenteYNariz==persona2.distanciaFrenteYNariz){
        contador++;
    }
    if(persona1.distanciaNarizYLabioSuperior==persona2.distanciaNarizYLabioSuperior){
        contador++;
    }
    
}

bool posiblecambiaforma(int contador, personas persona1){
    if(contador == 6 || contador<2){
        return false;
    }
    if(contador==2 || (contador>2 && contador<6) ){
        return true;
    }


}

