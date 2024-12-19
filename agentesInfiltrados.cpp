#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
using namespace std;

//Variables

//Crear clase

// Struct de las personas registradas
struct personas
{
    string nombre;
    string especie;
    float altura;
    bool capacidadMagica;
    float profundidadOjos;
    float distanciaEntreOjos;
    float distanciaFrenteYNariz;
    float distanciaNarizYLabioSuperior;
}persona;

const int  error=0.05;
int contadorcambiaformas=0;


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

/*detectar cambiaforma: no pueden alterar todo su estructura facial,no pueden alterar su altura mas de
1 unidad de medida hacia arriba o abajo,cada 3 personas comparten como maximo 2 medidas faciales,

*/


int numpersonas,i=1,j=2;

int  validacion( personas personai, personas personaj, int numpersonas, int contador=0,int contadorfacial=0,int i,int j ){
    if(j==numpersonas){


    }
    
    if(personai.especie==personaj.especie){
        contador++;
    }
    if(personai.altura==personaj.altura || fabsf(personai.altura-personaj.altura)<=1.05){
        contador++;
    }
    if(personai.profundidadOjos==personaj.profundidadOjos ||
     fabsf(personai.profundidadOjos-personaj.profundidadOjos)<=1.05){
        contador++;
        contadorfacial++;
    }
    if(personai.distanciaEntreOjos==personaj.distanciaEntreOjos || 
    fabsf(personai.distanciaEntreOjos-personaj.distanciaEntreOjos)<=1.05){
        contador++;
        contadorfacial++;
    }
    if(personai.distanciaFrenteYNariz==personaj.distanciaFrenteYNariz || 
    fabs(personai.distanciaFrenteYNariz-personaj.distanciaFrenteYNariz)<=1.05){
        contador++;
    }
    if(personai.distanciaNarizYLabioSuperior==personaj.distanciaNarizYLabioSuperior || 
    fabsf(personai.distanciaNarizYLabioSuperior-personaj.distanciaNarizYLabioSuperior)<=1.05){
        contador++;
        contadorfacial++;
    }

    
    
}

bool posiblecambiaforma(int contador, personas personai,int contadorfacial,int contadorposible=0){
    if((contador == 6 || contador<2)&& contadorfacial==4){
        return false;
    }
    if((contador==2 || (contador>2 && contador<6))&& contadorfacial<4 ){
        contadorposible+=1;
        return true;
        
    }


}

bool escambiaforma(personas personai,int i,int j,int numpersonas,int contador,int contadorfacial,int contadorposible){
    
    if(j==numpersonas && contadorposible>=1){
    contadorcambiaformas+=1;
    cout<<personai.nombre<<endl;
    return validacion(persona,persona,numpersonas, i+1,j);
    return true;
    }
    else{
       if(posiblecambiaforma(contador,personai,contadorfacial)==true){
         validacion(persona,persona,numpersonas,contador=0,i,j+1);

    }
    }
   
};



int main()
{

    leerBaseDeDatos();
    return 0;
}

