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
};

// Variables globales
const float error = 0.1;        // esto es un porcentaje de error
int cantidadDeCambiaformas = 0; // cantidad de grupos de cambiaformas que hay
Personas **matriz = nullptr;    // Matriz dinámica para almacenar los cambiaformas y sus formas
int *tamanioGrupos = nullptr;   // Mantiene el tamaño de cada grupo de la matriz
int capacidadMatriz = 0;        // Capacidad actual de la matriz en grupos (asignada dinámicamente)

// Función para convertir una cadena "Si" o "No" a un booleano
bool convertirBool(const string &str)
{
    return str == "Si" || str == "si";
}

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
    cout << "Datos escritos en el archivo con éxito";
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

// Función para eliminar una persona del arreglo
void eliminarpersona(Personas *registro, int &numeroPersonas, int indice)
{
    for (int i = indice; i < numeroPersonas - 1; i++)
    {
        registro[i] = registro[i + 1];
    }
    numeroPersonas--;
}

// Función para filtrar el registro
Personas *filtrarRegistro(Personas *&registro, int &numeroPersonas)
{
    int j = 0;
    for (int i = 0; i < numeroPersonas; i++)
    {
        if (registro[i].especie != "kripsan" && registro[i].especie != "Kripsan" && registro[i].capacidadMagica == false)
        {

            j++;
        }
        else
        {
            eliminarpersona(registro, numeroPersonas, i);
            i--;
        }
    }
    return registro;
}

// Validar similitudes en atributos entre tres personas (verifica si forman un grupo sospechoso)
bool validacionCada3Personas(Personas persona1, Personas persona2, Personas persona3)
{
    int contadorFacial = 0;

    if (fabsf(persona1.profundidadOjos - persona2.profundidadOjos) <= error &&
        fabsf(persona1.profundidadOjos - persona3.profundidadOjos) <= error &&
        fabsf(persona2.profundidadOjos - persona3.profundidadOjos) <= error)
    {
        contadorFacial++;
    }
    if (fabsf(persona1.distanciaEntreOjos - persona2.distanciaEntreOjos) <= error &&
        fabsf(persona1.distanciaEntreOjos - persona3.distanciaEntreOjos) <= error &&
        fabsf(persona2.distanciaEntreOjos - persona3.distanciaEntreOjos) <= error)
    {
        contadorFacial++;
    }
    if (fabsf(persona1.distanciaFrenteYNariz - persona2.distanciaFrenteYNariz) <= error &&
        fabsf(persona1.distanciaFrenteYNariz - persona3.distanciaFrenteYNariz) <= error &&
        fabsf(persona2.distanciaFrenteYNariz - persona3.distanciaFrenteYNariz) <= error)
    {
        contadorFacial++;
    }
    if (fabsf(persona1.distanciaNarizYLabioSuperior - persona2.distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona1.distanciaNarizYLabioSuperior - persona3.distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona2.distanciaNarizYLabioSuperior - persona3.distanciaNarizYLabioSuperior) <= error)
    {
        contadorFacial++;
    }

    return contadorFacial > 2 && contadorFacial < 4;
}

// Verifica si un valor ya está en un grupo
bool contieneValor(Personas *grupo, int tamanioGrupo, const Personas &valor)
{
    for (int i = 0; i < tamanioGrupo; i++)
    {
        if (grupo[i].nombre == valor.nombre)
        {
            return true;
        }
    }
    return false;
}

void redimensionarMatriz()
{
    // Aumentar la capacidad de la matriz si es necesario
    if (cantidadDeCambiaformas >= capacidadMatriz)
    {
        int nuevaCapacidad = (capacidadMatriz == 0) ? 1 : capacidadMatriz++;
        Personas **nuevaMatriz = new Personas *[nuevaCapacidad];
        int *nuevoTamanioGrupos = new int[nuevaCapacidad];

        // Copiar los datos existentes
        for (int i = 0; i < cantidadDeCambiaformas; i++)
        {
            nuevaMatriz[i] = matriz[i];
            nuevoTamanioGrupos[i] = tamanioGrupos[i];
        }

        // Liberar la memoria anterior
        delete[] matriz;
        delete[] tamanioGrupos;

        matriz = nuevaMatriz;
        tamanioGrupos = nuevoTamanioGrupos;
        capacidadMatriz = nuevaCapacidad;
    }
}

// Agrega un grupo de cambiaformas a la matriz dinámica
void agregarCambiaformas(Personas &sospechoso1, Personas &sospechoso2, Personas &sospechoso3)
{
    redimensionarMatriz();

    int j = 0;
    Personas *nuevoGrupo = new Personas[3];

    // Verificar si esta cada sospechozo y agregarlo en caso de no estar
    // Arreglo de enteror que tienen primer parametro si se encontro el sospechoso y el segundo parametro la posicion en la matriz

    int encontrado1[] = {0, 0};
    int encontrado2[] = {0, 0};
    int encontrado3[] = {0, 0};
    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        if (contieneValor(matriz[i], tamanioGrupos[i], sospechoso1))
        {
            encontrado1[0] = 1;
            encontrado1[1] = i;
            break;
        }
    }

    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        if (contieneValor(matriz[i], tamanioGrupos[i], sospechoso2))
        {
            encontrado2[0] = 1;
            encontrado2[1] = i;
            break;
        }
    }

    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        if (contieneValor(matriz[i], tamanioGrupos[i], sospechoso3))
        {
            encontrado3[0] = 1;
            encontrado3[1] = i;
            break;
        }
    }

    if (encontrado1[0] == 0)
    {
        if (j == 0)
        {
            nuevoGrupo[j] = sospechoso1;
        }
        else
        {

            if (nuevoGrupo[j - 1].profundidadOjos < sospechoso1.profundidadOjos)
            {
                nuevoGrupo[j] = sospechoso1;
            }
            else
            {
                nuevoGrupo[j] = nuevoGrupo[j - 1];
                nuevoGrupo[j - 1] = sospechoso1;
            }
        }

        j++;
    }

    if (encontrado2[0] == 0)
    {

        if (nuevoGrupo[j - 1].profundidadOjos < sospechoso2.profundidadOjos)
        {
            nuevoGrupo[j] = sospechoso2;
        }
        else
        {
            nuevoGrupo[j] = nuevoGrupo[j - 1];
            nuevoGrupo[j - 1] = sospechoso2;
        }
        j++;
    }

    if (encontrado3[0] == 0)
    {

        if (nuevoGrupo[j - 1].profundidadOjos < sospechoso3.profundidadOjos)
        {
            nuevoGrupo[j] = sospechoso3;
        }
        else
        {
            nuevoGrupo[j] = nuevoGrupo[j - 1];
            nuevoGrupo[j - 1] = sospechoso3;
        }
        j++;
    }

    // Crear un nuevo grupo
    matriz[cantidadDeCambiaformas] = nuevoGrupo;
    tamanioGrupos[cantidadDeCambiaformas] = 3;
    cantidadDeCambiaformas > 0 ? cantidadDeCambiaformas = encontrado3[1] : cantidadDeCambiaformas++;
}

// Analizar si tres personas son sospechosas
bool analizarSospechosos(const Personas &persona1, const Personas &persona2, const Personas &persona3)
{
    if (validacionCada3Personas(persona1, persona2, persona3) &&
        persona1.nombre != persona2.nombre &&
        persona1.nombre != persona3.nombre &&
        persona2.nombre != persona3.nombre)
    {
        return true;
    }
    return false;
}

// Detectar cambiaformas en el registro
void salida()
{
    cout << cantidadDeCambiaformas << endl;
    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        for (int j = 0; j < tamanioGrupos[i]; j++)
        {
            cout << i + 1 << " - " << matriz[i][j].nombre;
            if (j == 0)
            {
                cout << " (O)";
            }
            cout << endl;
        }
        cout << endl;
    }
}
void detectarCambiaformas(Personas *registro, int numeroPersonas, int i)
{
    // 2 Personas en el registro
    if (numeroPersonas == 2)
    {
        if (fabsf(registro[0].altura - registro[1].altura) <= 1 + error && fabsf(registro[0].profundidadOjos - registro[1].profundidadOjos) <= error)
        {

            redimensionarMatriz();
            Personas *nuevoGrupo = new Personas[2];
            if (registro[0].profundidadOjos < registro[1].profundidadOjos)
            {

                nuevoGrupo[0] = registro[0];
                nuevoGrupo[1] = registro[1];
            }
            else
            {
                nuevoGrupo[0] = registro[1];
                nuevoGrupo[1] = registro[0];
            }
            matriz[cantidadDeCambiaformas] = nuevoGrupo;
            cantidadDeCambiaformas++;
            tamanioGrupos[0] = 2;
        }
    }
    else
    {

        if (i >= numeroPersonas / 3)
        {
            return;
        }
        for (int j = 0; j < numeroPersonas; j++)
        {
            for (int k = j + 1; k < numeroPersonas; k++)
            {
                if (analizarSospechosos(registro[i], registro[j], registro[k]))
                {
                    agregarCambiaformas(registro[i], registro[j], registro[k]);
                    detectarCambiaformas(registro, numeroPersonas, i + 1);
                }
            }
        }
    }
}

// Imprimir los resultados

// Liberar la memoria dinámica usada por la matriz
void liberarMatriz()
{
    for (int i = 0; i < cantidadDeCambiaformas; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] tamanioGrupos;
}

// Función principal
int main()
{
    int numeroPersonas;
    Personas *registro = obtenerData(numeroPersonas);
    Personas *registroFiltrado = filtrarRegistro(registro, numeroPersonas);
    if (!registro)
    {
        return 1;
    }

    detectarCambiaformas(registroFiltrado, numeroPersonas, 0);
    salida();

    // Limpieza de memoria
    delete[] registro;
    liberarMatriz();

    return 0;
}
