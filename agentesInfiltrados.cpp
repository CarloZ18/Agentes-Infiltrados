#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
using namespace std;

// Variables

const float error = 0.1;      // esto es global poque es el porcentaje de error
int contadorCambiaformas = 0; // y este tambien global porque en la cantidad en general
// char *arr=new char [numpersonas];//segun yo arreglo donde se va a guardar los nombres a los que cambia
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
    archivo.close();
    return registro;
}

void eliminarpersona(Personas *registro, int &numeroPersonas, int indice)
{
    for (int i = indice; i < numeroPersonas - 1; i++)
    {
        registro[i] = registro[i + 1];
    }
    numeroPersonas--;
}

Personas *filtrarRegistro(Personas *registro, int &numeroPersonas)
{
    Personas *persona = new Personas[numeroPersonas];
    int j = 0;
    for (int i = 0; i < numeroPersonas; i++)
    {
        if (registro[i].especie != "kripsan" && registro[i].especie != "Kripsan" && registro[i].capacidadMagica == false)
        {
            persona[j] = registro[i];
            j++;
        }

        else
        {
            eliminarpersona(registro, numeroPersonas, i);
            i--;
        }
    }

    return persona;
}

bool validacionCada3Personas(Personas *persona, int &numeroPersonas, int i)
{

    int contadorFacial = 0;

    // Comparar profundidad de ojos
    if (fabsf(persona[i].profundidadOjos - persona[i + 1].profundidadOjos) <= error &&
        fabsf(persona[i].profundidadOjos - persona[i + 2].profundidadOjos) <= error &&
        fabsf(persona[i + 1].profundidadOjos - persona[i + 2].profundidadOjos) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia entre ojos
    if (fabsf(persona[i].distanciaEntreOjos - persona[i + 1].distanciaEntreOjos) <= error &&
        fabsf(persona[i].distanciaEntreOjos - persona[i + 2].distanciaEntreOjos) <= error &&
        fabsf(persona[i + 1].distanciaEntreOjos - persona[i + 2].distanciaEntreOjos) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia frente y nariz
    if (fabsf(persona[i].distanciaFrenteYNariz - persona[i + 1].distanciaFrenteYNariz) <= error &&
        fabsf(persona[i].distanciaFrenteYNariz - persona[i + 2].distanciaFrenteYNariz) <= error &&
        fabsf(persona[i + 1].distanciaFrenteYNariz - persona[i + 2].distanciaFrenteYNariz) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia nariz y labio superior
    if (fabsf(persona[i].distanciaNarizYLabioSuperior - persona[i + 1].distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona[i].distanciaNarizYLabioSuperior - persona[i + 2].distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona[i + 1].distanciaNarizYLabioSuperior - persona[i + 2].distanciaNarizYLabioSuperior) <= error)
    {
        contadorFacial++;
    }

    return contadorFacial > 2;
}

// La funcion será llamada en el backtracking
bool analizarSospechosos(Personas *persona, int numeroPersonas, int i, int j, int k)
{
    // Verificar si son el mismo cambiaforma
    if (validacionCada3Personas(persona, numeroPersonas, i) &&
        fabsf(persona[i].altura - persona[i + j].altura) <= 1 + error &&
        fabsf(persona[i].altura - persona[i + k].altura) <= 1 + error &&
        fabsf(persona[i + j].altura - persona[i + k].altura) <= 1 + error

    )
    {
        return true;
    }
    return false;
}

Personas **detectarCambiaformas(Personas *persona, int numeroPersonas, int i)
{
    for (int i = 0; i < numeroPersonas - 3; i++)
    {
        for (int j = 1; j < numeroPersonas - 2; j++)
        {
            for (int k = 2; k < numeroPersonas - 1; k++)
            {
                analizarSospechosos(persona, numeroPersonas, i, j, k);
            }
        }
    }
}

// Funcion salida

/*Su primer parametro es una matriz con la siguiente estructura

registro={
{
{"Hectin Nabal", "Humana", 10.55, false, 0.12, 0.2, 1.25, 0.238},
{"Geostren Mandos", "Elfo", 10.2, false, 0.13, 0.2, 2.1, 0.239},
{"Urma Dian", "Humana", 10.55, true, 0.12, 0.2, 1.25, 0.238}
},

{
{"Helga Untrima", "Ubarikiwe", 10.78, false, 0.14, 0.2, 2.5, 0.238},
{"Chin Xilan", "Humana", 12.55, false, 0.12, 0.2, 2, 0.48}
}

}
*/
void salida(Personas **persona, int cantidadDeCambiaformas, int *formas)
{
    cout << cantidadDeCambiaformas << endl;

    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        for (int j = 0; j < formas[i]; j++)
        {
            cout << i + 1 << " - " << persona[i][j].nombre;
            if (j == 0)
            {
                cout << " (O)";
            }
            cout << endl;
        }
        cout << endl;
    }
}

// se supone que este es el backtracking que define si es cambiaforma o no

/*void backtracking(Personas personai, int i, int j, int numpersonas, int contador, int contadorfacial, int contadorposible)
{
    if (i == numpersonas)
    {
        cout << contadorCambiaformas << endl;
        return;
    }

    /*for(int k=j; k<=numpersonas; k++){
        if(posibleCambiaforma(contador,personai,contadorfacial,contadorposible)==true){
            validacionCada3Personas(persona,persona,numpersonas,contador=0,contadorfacial=0,i,j+1);
            contadorCambiaformas+=1;
            imprimircambiaforma(persona,persona,i,j,arr);
            escambiaforma(persona,i+1,j,numpersonas,contador=0,contadorfacial=0,contadorposible=0);
        }
        else{
            validacionCada3Personas(persona,persona,numpersonas,contador=0,contadorfacial=0,i,j+1);
        }

        }
};*/

int main()
{
    int numeroPersonas;
    Personas *registro = obtenerData(numeroPersonas);
    Personas *registroFiltrado = filtrarRegistro(registro, numeroPersonas);
    detectarCambiaformas(registroFiltrado, numeroPersonas, 0);
    // IMPRIMIR REGISTRO

    /* if (personas)
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
  }*/

    // IMPRIMIR COUT DE LA FUNCION SALIDA

    /*
        // Crear un arreglo de arreglos de Personas
        int filas = 2;
        int columnasPorFila[] = {3, 2};
        Personas **arr = new Personas *[filas];
        for (int i = 0; i < filas; ++i)
        {
            arr[i] = new Personas[columnasPorFila[i]];
        }

        // Asignar valores a los arreglos de Personas
        arr[0][0] = {"Hectin Nabal", "Humana", 10.55, false, 0.12, 0.2, 1.25, 0.238};
        arr[0][1] = {"Geostren Mandos", "Elfo", 10.2, false, 0.13, 0.2, 2.1, 0.239};
        arr[0][2] = {"Urma Dian", "Humana", 10.55, true, 0.12, 0.2, 1.25, 0.238};
        arr[1][0] = {"Helga Untrima", "Ubarikiwe", 10.78, false, 0.14, 0.2, 2.5, 0.238};
        arr[1][1] = {"Chin Xilan", "Humana", 12.55, false, 0.12, 0.2, 2, 0.48};


        // Llamar a la función salida
        salida(arr, filas, columnasPorFila);

        // Liberar la memoria asignada
        for (int i = 0; i < filas; ++i)
        {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] personas;*/

    return 0;
}
