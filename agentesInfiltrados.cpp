#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Struct de las personas registradas
struct Personas {
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
const float error = 0.1;        // esto es global porque es el porcentaje de error
int cantidadDeCambiaformas = 0; // esto es global porque es la cantidad de cambiaformas que hay
Personas **matriz = nullptr;    // Matriz dinámica para almacenar los cambiaformas y sus formas
int *formas = nullptr;          // Arreglo para almacenar la cantidad de formas de cada cambiaforma

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

bool validacion(Personas *persona, int &numeroPersonas, int i)
{

 
    int contadorFacial = 0;
    Personas *posiblescambiaformas = new Personas[numeroPersonas];

    // Comparar profundidad de ojos
    if (fabsf(persona[i].profundidadOjos - persona[i + 1].profundidadOjos) <= error &&
        fabsf(persona[i].profundidadOjos - persona[i + 2].profundidadOjos) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia entre ojos
    if (fabsf(persona[i].distanciaEntreOjos - persona[i + 1].distanciaEntreOjos) <= error &&
        fabsf(persona[i].distanciaEntreOjos - persona[i + 2].distanciaEntreOjos) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia frente y nariz
    if (fabsf(persona[i].distanciaFrenteYNariz - persona[i + 1].distanciaFrenteYNariz) <= error &&
        fabsf(persona[i].distanciaFrenteYNariz - persona[i + 2].distanciaFrenteYNariz) <= error)
    {
        contadorFacial++;
    }

    // Comparar distancia nariz y labio superior
    if (fabsf(persona[i].distanciaNarizYLabioSuperior - persona[i + 1].distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona[i].distanciaNarizYLabioSuperior - persona[i + 2].distanciaNarizYLabioSuperior) <= error)
    {
        contadorFacial++;
    }
    return contadorFacial > 2;
}

bool hayCambiaforma(Personas *persona, int numeroPersonas, int i)
{
    if (i >= numeroPersonas - 2)
    {
        return false;
    }

    if (validacion(persona, numeroPersonas, i) &&
        fabsf(persona[i].altura - persona[i + 1].altura) > 0 && fabsf(persona[i].altura - persona[i + 1].altura) <= 1.05 &&
        fabsf(persona[i].altura - persona[i + 2].altura) > 0 && fabsf(persona[i].altura - persona[i + 2].altura) <= 1.05 &&
        fabsf(persona[i + 1].altura - persona[i + 2].altura) > 0 && fabsf(persona[i + 1].altura - persona[i + 2].altura) <= 1.05 &&
        persona[i].profundidadOjos < persona[i + 1].profundidadOjos < persona[i + 2].profundidadOjos)
    {

        cout << persona[i].nombre << " es cambiaforma" << endl;
   return true;
    }
    return hayCambiaforma(persona, numeroPersonas, i + 1);
}

// Función para convertir una cadena "Si" o "No" a un booleano
bool convertirBool(const string &str) {
    return str == "Si" || str == "si";
}

// Función para leer datos desde un archivo
Personas *obtenerData(int &numeroPersonas) {
    ifstream archivo("dataBase.in");

    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return nullptr;
    }

    string linea;
    getline(archivo, linea);
    numeroPersonas = stoi(linea);

    Personas *registro = new Personas[numeroPersonas];

    for (int i = 0; i < numeroPersonas; i++) {
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
void eliminarpersona(Personas *registro, int &numeroPersonas, int indice) {
    for (int i = indice; i < numeroPersonas - 1; i++) {
        registro[i] = registro[i + 1];
    }
    numeroPersonas--;
}

// Función para filtrar el registro
Personas *filtrarRegistro(Personas *registro, int &numeroPersonas) {
    Personas *persona = new Personas[numeroPersonas];
    int j = 0;
    for (int i = 0; i < numeroPersonas; i++) {
        if (registro[i].especie != "kripsan" && registro[i].especie != "Kripsan" && registro[i].capacidadMagica == false) {
            persona[j] = registro[i];
            j++;
        } else {
            eliminarpersona(registro, numeroPersonas, i);
            i--;
        }
    }
    return persona;
}

// Función para validar si tres personas son sospechosas
bool validacionCada3Personas(Personas persona1, Personas persona2, Personas persona3) {
    int contadorFacial = 0;
    // Comparar profundidad de ojos
    if (fabsf(persona1.profundidadOjos - persona2.profundidadOjos) <= error &&
        fabsf(persona1.profundidadOjos - persona3.profundidadOjos) <= error &&
        fabsf(persona2.profundidadOjos - persona3.profundidadOjos) <= error) {
        contadorFacial++;
    }

    // Comparar distancia entre ojos
    if (fabsf(persona1.distanciaEntreOjos - persona2.distanciaEntreOjos) <= error &&
        fabsf(persona1.distanciaEntreOjos - persona3.distanciaEntreOjos) <= error &&
        fabsf(persona2.distanciaEntreOjos - persona3.distanciaEntreOjos) <= error) {
        contadorFacial++;
    }

    // Comparar distancia frente y nariz
    if (fabsf(persona1.distanciaFrenteYNariz - persona2.distanciaFrenteYNariz) <= error &&
        fabsf(persona1.distanciaFrenteYNariz - persona3.distanciaFrenteYNariz) <= error &&
        fabsf(persona2.distanciaFrenteYNariz - persona3.distanciaFrenteYNariz) <= error) {
        contadorFacial++;
    }

    // Comparar distancia nariz y labio superior
    if (fabsf(persona1.distanciaNarizYLabioSuperior - persona2.distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona1.distanciaNarizYLabioSuperior - persona3.distanciaNarizYLabioSuperior) <= error &&
        fabsf(persona2.distanciaNarizYLabioSuperior - persona3.distanciaNarizYLabioSuperior) <= error) {
        contadorFacial++;
    }

    return contadorFacial > 2 && contadorFacial < 4;
}

// Función para verificar si un arreglo contiene un valor
bool contieneValor(Personas **matriz, int indice, Personas valor) {
    for (int i = 0; i < cantidadDeCambiaformas; ++i) {
        for (int j = 0; j < formas[i]; j++) {
            if (matriz[i][j].nombre == valor.nombre) {
                return true;
            }
        }
    }
    return false;
}
// Reasignar dinámicamente una fila de la matriz
Personas* reasignarFila(Personas* fila, int &capacidadActual, int nuevaCapacidad) {
    Personas* nuevaFila = new Personas[nuevaCapacidad];
    for (int i = 0; i < capacidadActual; ++i) {
        nuevaFila[i] = fila[i];
    }
    delete[] fila; // Libera la memoria anterior
    capacidadActual = nuevaCapacidad;
    return nuevaFila;
}

// Modificación en la función agregarCambiaformas para manejar dinámicamente el tamaño de las filas
void agregarCambiaformas(Personas sospechoso1, Personas sospechoso2, Personas sospechoso3, int &indice, Personas **&matriz, int &numeroPersonas) {
    // Aumenta fila si es necesario
    if (formas[indice] >= numeroPersonas) {
        matriz[indice] = reasignarFila(matriz[indice], formas[indice], formas[indice] * 2);
    }
    if (!contieneValor(matriz, indice, sospechoso1)) {
        matriz[indice][formas[indice]++] = sospechoso1;
    }
    if (!contieneValor(matriz, indice, sospechoso2)) {
        matriz[indice][formas[indice]++] = sospechoso2;
    }
    if (!contieneValor(matriz, indice, sospechoso3)) {
        matriz[indice][formas[indice]++] = sospechoso3;
    }
}
// Función para agregar cambiaformas a la matriz
void agregarCambiaformas(Personas sospechoso1, Personas sospechoso2, Personas sospechoso3, int &indice, Personas **&matriz, int &numeroPersonas) {
    bool validarSospechoso1 = contieneValor(matriz, indice, sospechoso1);

    if (!validarSospechoso1) {
        matriz[indice][formas[indice]] = sospechoso1;
        formas[indice]++;
    }

    bool validarSospechoso2 = contieneValor(matriz, indice, sospechoso2);

    if (!validarSospechoso2) {
        matriz[indice][formas[indice]] = sospechoso2;
        formas[indice]++;
    }
    bool validarSospechoso3 = contieneValor(matriz, indice, sospechoso3);
    if (!validarSospechoso3) {
        matriz[indice][formas[indice]] = sospechoso3;
        formas[indice]++;
    }

    cantidadDeCambiaformas++;
}

// Función para crear una matriz
Personas **crearmatriz(int numeroPersonas, int *formas) {
    Personas **matriz = new Personas *[numeroPersonas];
    for (int i = 0; i < numeroPersonas; i++) {
        matriz[i] = new Personas[formas[i]];
    }
    return matriz;
}

// Función de salida
void salida(Personas **persona, int cantidadDeCambiaformas, int *formas) {
    cout << cantidadDeCambiaformas << endl;

    for (int i = 0; i < cantidadDeCambiaformas; i++) {
        for (int j = 0; j < formas[i]; j++) {
            cout << i + 1 << " - " << persona[i][j].nombre;
            if (j == 0) {
                cout << " (O)";
            }
            cout << endl;
        }
        cout << endl;
    }
}

// Función para ordenar tres personas según la profundidad de los ojos
void ordenarPorProfundidadOjos(Personas &persona1, Personas &persona2, Personas &persona3, Personas **matriz, int i) {
    if (persona1.profundidadOjos < persona2.profundidadOjos && persona1.profundidadOjos < persona3.profundidadOjos) {
        matriz[i][0] = persona1;
        if (persona2.profundidadOjos < persona3.profundidadOjos) {
            matriz[i][1] = persona2;
            matriz[i][2] = persona3;
        } else {
            matriz[i][1] = persona3;
            matriz[i][2] = persona2;
        }
    } else if (persona2.profundidadOjos < persona1.profundidadOjos && persona2.profundidadOjos < persona3.profundidadOjos) {
        matriz[i][0] = persona2;
        if (persona1.profundidadOjos < persona3.profundidadOjos) {
            matriz[i][1] = persona1;
            matriz[i][2] = persona3;
        } else {
            matriz[i][1] = persona3;
            matriz[i][2] = persona1;
        }
    } else {
        matriz[i][0] = persona3;
        if (persona1.profundidadOjos < persona2.profundidadOjos) {
            matriz[i][1] = persona1;
            matriz[i][2] = persona2;
        } else {
            matriz[i][1] = persona2;
            matriz[i][2] = persona1;
        }
    }
}

// Función para analizar si tres personas son sospechosas de ser cambiaformas
bool analizarSospechosos(Personas persona1, Personas persona2, Personas persona3) {
    // Verificar si son el mismo cambiaforma entre personas distintas
    if (fabsf(persona1.altura - persona2.altura) <= 1 + error &&
        fabsf(persona1.altura - persona3.altura) <= 1 + error &&
        fabsf(persona2.altura - persona3.altura) <= 1 + error &&
        persona1.nombre != persona2.nombre &&
        persona1.nombre != persona3.nombre &&
        persona2.nombre != persona3.nombre) {
        return true;
    }
    return false;
}

// Función para detectar cambiaformas
void detectarCambiaformas(Personas *registro, int &numeroPersonas, int i, Personas **&matriz) {
    // 1 Sola persona en el registro
    if (numeroPersonas == 1) {
        salida(matriz, 0, nullptr);
    }
    // 2 Personas en el registro
    else if (numeroPersonas == 2) {
        if (fabsf(registro[0].altura - registro[1].altura) <= 1 + error && fabsf(registro[0].profundidadOjos - registro[1].profundidadOjos) <= error) {
            cantidadDeCambiaformas++;
            if (registro[0].profundidadOjos < registro[1].profundidadOjos) {
                matriz[0][0] = registro[0];
                matriz[0][1] = registro[1];
            } else {
                matriz[0][0] = registro[1];
                matriz[0][1] = registro[0];
            }
            formas = new int[1];
            formas[0] = 2;
        }
    }
    // Más de 2 personas en el registro
    else {
        if (i >= numeroPersonas / 3) {
            return;
        }
        for (int j = 0; j < numeroPersonas; j++) {
            for (int k = 0; k < numeroPersonas; k++) {
                if (analizarSospechosos(registro[i], registro[j], registro[k])) {
                    cout << registro[i].nombre << " " << registro[j].nombre << " " << registro[k].nombre << endl;
                    agregarCambiaformas(registro[i], registro[j], registro[k], i, matriz, numeroPersonas);
                    detectarCambiaformas(registro, numeroPersonas, i + 1, matriz);
                }
            }
        }
    }
}

int main() {
    int numeroPersonas;
    Personas *registro = obtenerData(numeroPersonas);
    Personas *registroFiltrado = filtrarRegistro(registro, numeroPersonas);
    formas = new int[numeroPersonas]; // Inicializar el arreglo formas
    for (int i = 0; i < numeroPersonas; ++i) {
        formas[i] = 3; // Asignar un valor por defecto
    }
    matriz = crearmatriz(numeroPersonas, formas);
    detectarCambiaformas(registroFiltrado, numeroPersonas, 0, matriz);
    salida(matriz, cantidadDeCambiaformas, formas);
//imprimir matriz
    for (int i = 0; i < cantidadDeCambiaformas; i++) {
        for (int j = 0; j < formas[i]; j++) {
            cout << matriz[i][j].nombre << " ";
        }
        cout << endl;
    }

    // Liberar la memoria asignada
    for (int i = 0; i < numeroPersonas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] registro;
    delete[] registroFiltrado;
    delete[] formas;

    return 0;
}