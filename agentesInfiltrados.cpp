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

const int  error=0.05;//esto es global poque es el porcentaje de error
int contadorcambiaformas=0;//y este tambien global porque en la cantidad en general

char *arr=new char [numpersonas];//segun yo arreglo donde se va a guardar los nombres a los que cambia 


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


int numpersonas,i=1,j=2;//aqui esto son globales porque deben empezar ahi
//funcion que valida que tantas cosas iguales tienen 2 personas

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
//funcion que depende de que tantas cosas iguales tenga descarta si puede se un  cambiaformas o no 

bool posiblecambiaforma(int contador, personas personai,int contadorfacial,int contadorposible=0){
    if(contador<2 && contadorfacial==4){
        return false;
    }
    if((contador==2 || (contador>2 && contador<6))&& contadorfacial<4 ){
        contadorposible+=1;
        return true;
        
    }


}
//funcion que imprime el cambiaformas original y en que se convierte (solo los parametros)
void imprimircambiaforma(personas personai,personas personaj,int i ,int j,char*arr){
    cout<<personai.nombre<<endl;
    for(int k=0;k<j;k++){
        cout<<"hola"<<endl;
    }
}

//se supone que este es el backtracking que define si es cambiaforma o no

void escambiaforma(personas personai,int i,int j,int numpersonas,int contador,int contadorfacial,int contadorposible){
    if(i==numpersonas){
        cout<< contadorcambiaformas<<endl;
        return;
    }

    for(int k=j; k<=numpersonas; k++){
        if(posiblecambiaforma(contador,personai,contadorfacial,contadorposible)==true){
            validacion(persona,persona,numpersonas,contador=0,contadorfacial=0,i,j+1);
            contadorcambiaformas+=1;
            imprimircambiaforma(persona,persona,i,j,arr);
            escambiaforma(persona,i+1,j,numpersonas,contador=0,contadorfacial=0,contadorposible=0);
        }
        else{
            validacion(persona,persona,numpersonas,contador=0,contadorfacial=0,i,j+1);
        }
        
        }
        
    
    
    
   
};



int main()
{

    leerBaseDeDatos();
    return 0;
}

