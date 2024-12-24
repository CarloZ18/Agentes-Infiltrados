#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
using namespace std;

// Variables

const int error = 0.05;       // esto es global poque es el porcentaje de error
int contadorCambiaformas = 0; // y este tambien global porque en la cantidad en general
// char *arr=new char [numpersonas];//segun yo arreglo donde se va a guardar los nombres a los que cambia
int numpersonas, i = 1, j = 2; // aqui esto son globales porque deben empezar ahi
// funcion que valida que tantas cosas iguales tienen 2 personas

// Struct de las personas registradas
struct Personas
{
    string nombre;
    string especie;
    float altura;
    bool capacidadMagica;
    float profundidadOjos;
    float distanciaEntreOjos;
    float distanciaFrenteYNariz;
    float distanciaNarizYLabioSuperior;
} persona;

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

int validacion(Personas *persona, int numeroPersonas)
{
    int contador = 0;
    int contadorfacial = 0;

    for (int i = 0; i < numeroPersonas; i++)
    {
        if (persona[i].especie == persona[i + 1].especie)
        {
            contador++;
        }
        if (persona[i].altura == persona[i + 1].altura || fabsf(persona[i].altura - persona[i + 1].altura) <= 1.05)
        {
            contador++;
        }
        if (persona[i].profundidadOjos == persona[i + 1].profundidadOjos ||
            fabsf(persona[i].profundidadOjos - persona[i + 1].profundidadOjos) <= 1.05)
        {
            contador++;
            contadorfacial++;
        }
        if (persona[i].distanciaEntreOjos == persona[i + 1].distanciaEntreOjos ||
            fabsf(persona[i].distanciaEntreOjos - persona[i + 1].distanciaEntreOjos) <= 1.05)
        {
            contador++;
            contadorfacial++;
        }
        if (persona[i].distanciaFrenteYNariz == persona[i + 1].distanciaFrenteYNariz ||
            fabs(persona[i].distanciaFrenteYNariz - persona[i + 1].distanciaFrenteYNariz) <= 1.05)
        {
            contador++;
        }
        if (persona[i].distanciaNarizYLabioSuperior == persona[i + 1].distanciaNarizYLabioSuperior ||
            fabsf(persona[i].distanciaNarizYLabioSuperior - persona[i + 1].distanciaNarizYLabioSuperior) <= 1.05)
        {
            contador++;
            contadorfacial++;
        }
    }
}

// Función para convertir una cadena "Si" o "No" a un booleano
bool convertirBool(const string &str)
{
    return str == "Si" || str == "si";
}

// Leer archivo y obtener data
Personas *obtenerData(int &numeroPersonas)
{
    ifstream archivo("dataBase.in");

    // Verificamos si el archivo se abrió correctamente
    if (!archivo)
    {
        cerr << "Error al abrir el archivo" << endl;
        return nullptr;
    }

    string linea;
    getline(archivo, linea);
    numeroPersonas = stoi(linea);

    Personas *registro = new Personas[numeroPersonas];

    for (int i = 0; i < numeroPersonas; i++)
    {
        getline(archivo, registro[i].nombre);
        getline(archivo, registro[i].especie);
        archivo >> registro[i].altura;
        string capacidadMagicaStr;
        archivo >> capacidadMagicaStr;
        registro[i].capacidadMagica = convertirBool(capacidadMagicaStr);
        archivo >> registro[i].profundidadOjos;
        archivo >> registro[i].distanciaEntreOjos;
        archivo >> registro[i].distanciaFrenteYNariz;
        archivo >> registro[i].distanciaNarizYLabioSuperior;
        archivo.ignore(); // Ignorar el salto de línea después de leer los datos
    }
    validacion(registro, numeroPersonas);
    archivo.close();
    return registro;
}

/*detectar cambiaforma: no pueden alterar todo su estructura facial,no pueden alterar su altura mas de
1 unidad de medida hacia arriba o abajo,cada 3 personas comparten como maximo 2 medidas faciales,

*/

// funcion que depende de que tantas cosas iguales tenga descarta si puede se un  cambiaformas o no

bool posibleCambiaforma(int contador, Personas personai, int contadorfacial)
{
int contadorposible = 0;
    if (contador < 2 && contadorfacial == 4)
    {
        return false;
    }
    if ((contador == 2 || (contador > 2 && contador < 6)) && contadorfacial < 4)
    {
        contadorposible += 1;
        return true;
    }
}
// funcion que imprime el cambiaformas original y en que se convierte (solo los parametros)
void imprimircambiaforma(Personas personai, Personas personaj, int i, int j, char *arr)
{
    cout << personai.nombre << endl;
    for (int k = 0; k < j; k++)
    {
        cout << "hola" << endl;
    }
}

// se supone que este es el backtracking que define si es cambiaforma o no

void escambiaforma(Personas personai, int i, int j, int numpersonas, int contador, int contadorfacial, int contadorposible)
{
    if (i == numpersonas)
    {
        cout << contadorCambiaformas << endl;
        return;
    }

    /*for(int k=j; k<=numpersonas; k++){
        if(posibleCambiaforma(contador,personai,contadorfacial,contadorposible)==true){
            validacion(persona,persona,numpersonas,contador=0,contadorfacial=0,i,j+1);
            contadorCambiaformas+=1;
            imprimircambiaforma(persona,persona,i,j,arr);
            escambiaforma(persona,i+1,j,numpersonas,contador=0,contadorfacial=0,contadorposible=0);
        }
        else{
            validacion(persona,persona,numpersonas,contador=0,contadorfacial=0,i,j+1);
        }

        }*/
};

int main()
{
    int numeroPersonas;
    Personas *personas = obtenerData(numeroPersonas);

    if (personas)
    {
        for (int i = 0; i < numeroPersonas; i++)
        {
            cout << "Nombre: " << personas[i].nombre << endl;
            cout << "Especie: " << personas[i].especie << endl;
            cout << "Altura: " << personas[i].altura << endl;
            cout << "Capacidad Magica: " << (personas[i].capacidadMagica ? "Si" : "No") << endl;
            cout << "Profundidad de Ojos: " << personas[i].profundidadOjos << endl;
            cout << "Distancia entre Ojos: " << personas[i].distanciaEntreOjos << endl;
            cout << "Distancia Frente y Nariz: " << personas[i].distanciaFrenteYNariz << endl;
            cout << "Distancia Nariz y Labio Superior: " << personas[i].distanciaNarizYLabioSuperior << endl;
        }

        delete[] personas;
    }

    return 0;
}
