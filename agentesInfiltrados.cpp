#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
using namespace std;

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

// Variables

const float error = 0.1;        // esto es global poque es el porcentaje de error
int cantidadDeCambiaformas = 0; // esto es global porque es la cantidad de cambiaformas que hay
Personas *arregloSospechosos;   // esto es global porque es el arreglo de los sospechosos
int *formas;                    // esto es global porque es el arreglo de la cantidad de formas que tiene cada cambiaformas
int numeroDeSospechozos = 0;

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

bool validacionCada3Personas(Personas persona1, Personas persona2, Personas persona3)
{

    int contadorFacial = 0;
    // Comparar profundidad de ojos
    if (fabsf(persona1.profundidadOjos - persona2.profundidadOjos) <= error &&
        fabsf(persona1.profundidadOjos - persona3.profundidadOjos) <= error &&
        fabsf(persona2.profundidadOjos - persona3.profundidadOjos) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia entre ojos
    if (fabsf(persona1.distanciaEntreOjos - persona2.distanciaEntreOjos) <= error &&
        fabsf(persona1.distanciaEntreOjos - persona3.distanciaEntreOjos) <= error &&
        fabsf(persona2.distanciaEntreOjos - persona3.distanciaEntreOjos) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia frente y nariz
    if (fabsf(persona1.distanciaFrenteYNariz - persona2.distanciaFrenteYNariz) <= error &&
        fabsf(persona1.distanciaFrenteYNariz - persona3.distanciaFrenteYNariz) <= error &&
        fabsf(persona2.distanciaFrenteYNariz - persona3.distanciaFrenteYNariz) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia nariz y labio superior
    if (fabsf(persona1.distanciaNarizYLabioSuperior - persona2.distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona1.distanciaNarizYLabioSuperior - persona3.distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona2.distanciaNarizYLabioSuperior - persona3.distanciaNarizYLabioSuperior) <= error)
    {
        contadorFacial++;
    }

    return contadorFacial > 2 && contadorFacial < 4;
}

bool contieneValor(Personas *arr, int tam, Personas valor)
{
    for (int i = 0; i < tam; ++i)
    {
        if (arr[i].nombre == valor.nombre)
        {
            return true;
        }
    }
    return false;
}

void agregarCambiaformas(Personas sospechoso1, Personas sospechoso2, Personas sospechoso3, int &indice, Personas **&matriz, int numeroPersonas)

{

    bool validarSospechoso1 = contieneValor(arregloSospechosos, numeroDeSospechozos, sospechoso1);
    bool validarSospechoso2 = contieneValor(arregloSospechosos, numeroDeSospechozos, sospechoso2);
    bool validarSospechoso3 = contieneValor(arregloSospechosos, numeroDeSospechozos, sospechoso3);
    if (!validarSospechoso1)
    {
        formas[indice]++;
        arregloSospechosos[numeroDeSospechozos] = sospechoso1;
        matriz[indice][0] = sospechoso1;
        numeroDeSospechozos++;
    }
    if (!validarSospechoso2)
    {
        formas[indice]++;
        arregloSospechosos[numeroDeSospechozos] = sospechoso2;
        matriz[indice][1] = sospechoso2;
        numeroDeSospechozos++;
    }
    if (!validarSospechoso3)
    {
        formas[indice]++;
        arregloSospechosos[numeroDeSospechozos] = sospechoso3;
        matriz[indice][2] = sospechoso3;
        numeroDeSospechozos++;
    }
    cantidadDeCambiaformas += indice;
}

void eliminarCambiaforma(Personas **matriz, int indice, int &numeroPersonas)
{
    for (int i = indice; i < cantidadDeCambiaformas - 1; i++)
    {
        matriz[i] = matriz[i + 1];
    }
    cantidadDeCambiaformas--;
}
// La funcion será llamada en el backtracking
bool analizarSospechosos(Personas persona1, Personas persona2, Personas persona3)
{

    // Verificar si el grupo es sospechozo
    if (validacionCada3Personas(persona1, persona2, persona3) &&
        fabsf(persona1.altura - persona2.altura) <= 1 + error &&
        fabsf(persona1.altura - persona3.altura) <= 1 + error &&
        fabsf(persona2.altura - persona3.altura) <= 1 + error &&
        persona1.nombre != persona2.nombre &&
        persona1.nombre != persona3.nombre &&
        persona2.nombre != persona3.nombre

    )
    {
        return true;
    }
    return false;
}

Personas **crearmatriz(int &cantidadDeCambiaformas, int *&formas)
{
    Personas **matriz = new Personas *[cantidadDeCambiaformas];
    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        matriz[i] = new Personas[formas[i]];
    }
    return matriz;
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
    cout << "entro" << endl;

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

void ordenarPorProfundidadOjos(Personas &persona1, Personas &persona2, Personas &persona3, Personas **matriz, int i)
{
    if (persona1.profundidadOjos < persona2.profundidadOjos && persona1.profundidadOjos < persona3.profundidadOjos)
    {
        matriz[i][0] = persona1;
        if (persona2.profundidadOjos < persona3.profundidadOjos)
        {
            matriz[i][1] = persona2;
            matriz[i][2] = persona3;
        }
        else
        {
            matriz[i][1] = persona3;
            matriz[i][2] = persona2;
        }
    }
    else if (persona2.profundidadOjos < persona1.profundidadOjos && persona2.profundidadOjos < persona3.profundidadOjos)
    {
        matriz[i][0] = persona2;
        if (persona1.profundidadOjos < persona3.profundidadOjos)
        {
            matriz[i][1] = persona1;
            matriz[i][2] = persona3;
        }
        else
        {
            matriz[i][1] = persona3;
            matriz[i][2] = persona1;
        }
    }
    else
    {
        matriz[i][0] = persona3;
        if (persona1.profundidadOjos < persona2.profundidadOjos)
        {
            matriz[i][1] = persona1;
            matriz[i][2] = persona2;
        }
        else
        {
            matriz[i][1] = persona2;
            matriz[i][2] = persona1;
        }
    }
}

void detectarCambiaformas(Personas *persona, int &numeroPersonas, int i, Personas **&matriz)
{

    // 1 Sola persona en el registro
    if (numeroPersonas == 1)
    {
        salida(matriz, 0, nullptr);
    }
    // 2 Personas en el registro
    else if (numeroPersonas == 2)
    {
        if (fabsf(persona[0].altura - persona[1].altura) <= 1 + error && fabsf(persona[0].profundidadOjos - persona[1].profundidadOjos) <= error)
        {
            cantidadDeCambiaformas++;
            if (persona[0].profundidadOjos < persona[1].profundidadOjos)
            {
                matriz[0][0] = persona[0];
                matriz[0][1] = persona[1];
            }
            else
            {
                matriz[0][0] = persona[1];
                matriz[0][1] = persona[0];
            }
            formas = new int[1];
            formas[0] = 2;
            salida(matriz, 1, formas);
        }
        else
        {
            salida(matriz, 0, nullptr);
        }
    }
    // Más de 2 personas en el registro
    else
    {

        if (i >= numeroPersonas / 3)
        {
            return;
        }
        for (int j = 0; j < numeroPersonas; j++)
        {
            for (int k = 0; k < numeroPersonas; k++)
            {
                if (analizarSospechosos(persona[i], persona[j], persona[k]))
                {
                    cout << persona[i].nombre << " " << persona[j].nombre << " " << persona[k].nombre << endl;
                    // ordenarPorProfundidadOjos(persona[i], persona[j], persona[k], matriz, cantidadDeCambiaformas - 1);
                    agregarCambiaformas(persona[i], persona[j], persona[k], cantidadDeCambiaformas, matriz, numeroPersonas);
                    detectarCambiaformas(persona, numeroPersonas, i + 1, matriz);
                    // eliminarCambiaforma(matriz, cantidadDeCambiaformas - 1, numeroPersonas);
                }
            }
        }
    }
}
int main()
{
    int numeroPersonas;
    Personas *registro = obtenerData(numeroPersonas);
    Personas *registroFiltrado = filtrarRegistro(registro, numeroPersonas);
    formas = new int[numeroPersonas]; // Inicializar el arreglo formas
    for (int i = 0; i < numeroPersonas; ++i)
    {
        formas[i] = numeroPersonas; // Asignar un valor por defecto
    }
    arregloSospechosos = new Personas[numeroPersonas];

    Personas **matriz = crearmatriz(numeroPersonas, formas);
    detectarCambiaformas(registroFiltrado, numeroPersonas, 0, matriz);
    salida(matriz, cantidadDeCambiaformas, formas);

    Personas **matrizRedimensionada = new Personas *[cantidadDeCambiaformas];

    // Liberar la memoria asignada
    for (int i = 0; i < numeroPersonas; ++i)
    {
        delete[] matriz[i];
    }
    // Liberar la memoria asignada
    for (int i = 0; i < cantidadDeCambiaformas; ++i)
    {
        delete[] matrizRedimensionada[i];
    }
    delete[] matriz;
    delete[] arregloSospechosos;
    delete[] registro;
    delete[] registroFiltrado;
    delete[] formas;

    return 0;
}
