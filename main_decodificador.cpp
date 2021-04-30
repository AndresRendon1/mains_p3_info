#include <iostream>
#include<fstream>
#include<math.h>
using namespace std;
//VARIABLES GLOBALES
fstream archivo_lectura,archivo_escritura;
int semilla;//valor en el que se va a dividir el binario para ser codificado
int numfilas;//numero de filas del archivo
int i;//variable que nos servira para capturar los caracteres del archivo
int numcaracteres;//variable que nos ayudara a identificar el numero de caracteres en el archivo
int ascii[3000]={};//arreglo para convertir las letras a ascii
int binario[3000]={};//arreglo para convertir los valores ascii a binario
string nombre,texto,contenido;
//PROTOTIPO DE FUNCIONES
void convertir_binario(int a, int b[]);
int contador_0s_1s(string a);
string igual_cantidad_0s_1s(string a, string b);
string mayor_cantidad1s(string a,string b);
string mayor_cantidad0s(string a, string b);
void decodificacion_metodo1();
int valor_ascii(string a);
void convertir_a_caracter();
int main()
{
    cout << "Bienvenido al decodificador" << endl;
    cout<<"Ingrese el nombre del archivo codificado que desea abrir:  ";cin>>nombre;
    archivo_lectura.open(nombre+".txt",ios::in);//abrir en modo lectura

    if(archivo_lectura.is_open()){
        cout<<" ->El archivo '"<<nombre<<".txt' ha sido cargado correctamente."<<endl<<endl;
        while (!archivo_lectura.eof()){
           getline(archivo_lectura,texto);
           cout<<"El contenido del archivo '"<<nombre<<".txt' es: "<<endl<<texto<<endl<<endl;
        }
        archivo_lectura.close();
        decodificacion_metodo1();
        convertir_a_caracter();
    }
    return 0;
}

void convertir_binario(int a, int b[]){  //listo
    int i=0;
    int binario[8]={0,0,0,0,0,0,0,0};
    while(a!=1){
        binario[i]=a%2;
        a=a/2;
        i++;
    }
    binario[i]=a;               // a siempre va a ser igual a 1
    for(int j=7,i=0;j>=0;j--,i++){
        b[i]=binario[j];

    }

}

int contador_0s_1s(string a){ //listo
    int tam,cont1=0,cont0=0;
    tam=a.length();
    for(int i=0;i<tam;i++){
        if(a[i]=='1'){
            cont1++;
        }
        else if(a[i]=='0'){
            cont0++;
        }
    }
    if(cont1>cont0){
        return 1;
    }
    else if(cont0>cont1){
        return 0;
    }
    else {
        return 4;
    }
}

string igual_cantidad_0s_1s(string a, string b){ //listo
    int tam=0;
    tam=a.length();
    for(int i=0;i<tam;i++){
        if(a[i]=='1'){b[i]='0';}
        else if(a[i]=='0'){b[i]='1';}

    }
    return b;
}

string mayor_cantidad1s(string a, string b){ //listo
    int tam=0;
    tam=a.length();
    for(int i=2;i<tam;i+=2){
        if(a[i]=='0'){b[i]='1';}
        else{b[i]='0';}
    }

    return b;
}

string mayor_cantidad0s(string a, string b){ //listo
    int tam=0;
    tam=a.length();
    for(int i=1;i<tam;i+=2){
        if(a[i]=='0'){b[i]='1';}
        else{b[i]='0';}
    }
    return b;


}

void decodificacion_metodo1(){

    string cadena,bin_modificado,bloque1,bloque2,nombre;

    cout<<"Ingrese el nombre del archivo codificado que desea decodificar: ";
    cin>>nombre;

    archivo_lectura.open(nombre+".txt",ios::in);

    if(archivo_lectura.is_open()){
        cout<<" ->El archivo '"<<nombre<<".txt' ha sido cargado correctamente."<<endl<<endl;
        while (!(archivo_lectura.eof())) {
            archivo_lectura>>cadena;
        }

        cout<<"Ingrese nombre de salida para el archivo binario decodificado: ";cin>>nombre;
        cout<<"Ingrese el valor de la semilla: ";cin>> semilla;
        cout<<endl;

        archivo_escritura.open(nombre+".txt",ios::out);

        int tam=cadena.length();

        bloque1=cadena.substr(0,semilla);
        bin_modificado=igual_cantidad_0s_1s(bloque1,bloque1);
        archivo_escritura<<bin_modificado;


        for(int i=0;i<tam;i+=semilla){
            if(contador_0s_1s(bin_modificado)==1){
                bloque2=cadena.substr((i+semilla),semilla);
                bin_modificado=mayor_cantidad1s(bloque2,bloque2);
                archivo_escritura<<bin_modificado;
                bloque1=bloque2;
            }
            else if(contador_0s_1s(bin_modificado)==0){
                bloque2=cadena.substr((i+semilla),semilla);
                bin_modificado=mayor_cantidad0s(bloque2,bloque2);
                archivo_escritura<<bin_modificado;
                bloque1=bloque2;
            }
            else if(contador_0s_1s(bin_modificado)==4){
                bloque2=cadena.substr((i+semilla),semilla);
                bin_modificado=igual_cantidad_0s_1s(bloque2,bloque2);
                archivo_escritura<<bin_modificado;
                bloque1=bloque2;
            }
    }

    }
    else{
        cout<<"Lo siento,el archivo '"<<nombre<<"' no se pudo decodificar."<<endl;
    }
    archivo_escritura.close();
    archivo_lectura.close();
}

void convertir_a_caracter(){

    string nombre, subcadena,cadena,final;
    int letras;

    cout<<"Ingrese el nombre del archivo binario que desea abrir: ";cin>>nombre;

    archivo_lectura.open(nombre+".txt",ios::in);

    if(archivo_lectura.is_open()){
        cout<<" ->El archivo '"<<nombre<<".txt' ha sido cargado correctamente."<<endl<<endl;

        cout<<"Ingrese el nombre para el archivo de salida con el texto decodificado: ";cin>>nombre;

        while (!(archivo_lectura.eof())) {
            archivo_lectura>>cadena;

        }
        archivo_escritura.open(nombre+".txt",ios::out);
        int tam=cadena.length();
        for(int j=0; j<tam; j+=8){
            subcadena=cadena.substr(j,8);
            letras=valor_ascii(subcadena);
            archivo_escritura<<(char)letras;
        }cout<<"    ->EL archivo '"<<nombre<<"' ha sido creado correctamente\n"<<endl;

    }
    else{
        cout<<"Hubo un problema al cargar el archivo."<<endl;
    }
    archivo_lectura.close();
    archivo_escritura.close();

}

int valor_ascii (string a){
    int ascii=0;
    for (int i=0,j=7; i<8; i++, j--){
        ascii+=(((int)a[i])-48)*(pow(2,j));
    }
    return ascii;
}
