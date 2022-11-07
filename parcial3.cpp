#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;

const char *nombre_archivo = "archivo.dat";
struct Venta {
	int codigo;
	char nombres[50];
	char apellidos[50];
	char formaPago[50];
	char fecha[50];
	int total;
};

void Leer();
void Crear();
void Actualizar();
void Borrar();
void menu();
void buscar_codigo();
void buscar_indice();

void Leer(){
	system("cls");
	ifstream archivo;
	archivo.open(nombre_archivo, ios::in | ios::binary);
	if (archivo.fail()){
		cout << "no se pudo abrir el archivo.";
		exit(1);
	}
	Venta venta;
	int id=0; // indice o pocision del registro(fila) dentro del archivo
	archivo.read((char *)&venta,sizeof(Venta));
	cout<<"___________________________________________________"<<endl;
	cout<<"ID"<<"|"<<" Fecha"<<"|"<<"Codigo"<<"|"<<"   Nombres  "<<"|"<<"   Apellidos   "<<"|"<<" Forma de pago "<<"|"<<" Total"<<endl;
	do{
		cout<<id<<"|"<<venta.fecha<<"|"<<venta.codigo<<"|"<<venta.nombres<<"|"<<venta.apellidos<<"|"<<venta.formaPago<<"|"<<venta.total<<endl;
		archivo.read((char *)&venta,sizeof(Venta));
		id+=1;
	}while(!archivo.eof());
	archivo.close();

}
void Crear(){
	
	ofstream archivo;
	archivo.open(nombre_archivo, ios::out | ios::binary);
	char res;
	Venta venta;
	do{
		fflush(stdin);
		cout<<"Ingrese Codigo:";
		cin>>venta.codigo;
		cin.ignore();
		
		cout<<"Ingrese Nombres:";
		cin.getline(venta.nombres,50);
		
		cout<<"Ingrese Apellidos:";
		cin.getline(venta.apellidos,50);

		cout<<"Ingrese Fecha:";
		cin.getline(venta.fecha,50);

		cout<<"Ingrese Metodo de pago:";
		cin.getline(venta.formaPago,50);
		
		cout<<"Ingrese total:";
		cin>>venta.total;
		
		archivo.write((char *)&venta,sizeof(Venta));
		cout<<"Desea ingresar otra venta (s/n):";
		cin>>res;
	}while(res=='s' || res=='S');
	archivo.close();
	Leer();

}
void Actualizar(){
	
	FILE* archivo = fopen(nombre_archivo,"r+b"); 
	Venta venta;
	int id=0;
	cout<<"Ingrese el ID que desea Modificar:";
	cin>>id;

	fseek(archivo,id * sizeof(Venta),SEEK_SET);
		cout<<"Ingrese Codigo:";
		cin>>venta.codigo;
		cin.ignore();
		
		cout<<"Ingrese Nombres:";
		cin.getline(venta.nombres,50);
		
		cout<<"Ingrese Apellidos:";
		cin.getline(venta.apellidos,50);

		cout<<"Ingrese Fecha:";
		cin.getline(venta.fecha,50);

		cout<<"Ingrese Metodo de pago:";
		cin.getline(venta.formaPago,50);
		
		cout<<"Ingrese total:";
		cin>>venta.total;
		
		fwrite(&venta,sizeof(Venta),1,archivo);
	
	
	fclose(archivo);
	Leer();
}
void Borrar(){


	const char *nombre_archivo_temp = "archivo_temp.dat";

	fstream archivo_temp;
	fstream archivo;
	archivo_temp.open(nombre_archivo_temp, ios::in | ios::out | ios::binary);
	archivo.open(nombre_archivo, ios::in | ios::binary);
	Venta venta;
	int id=0,id_n=0;
	cout<<"Ingrese el ID a eliminar:";
	cin>>id;
	while(archivo.read((char *)&venta,sizeof(Venta))){
		if (id_n !=id ){
			archivo_temp.write((char *)&venta,sizeof(Venta));
		}
		id_n++;
	}
	archivo.close();
	archivo_temp.close();
	
	archivo_temp.open(nombre_archivo_temp, ios::in | ios::binary);
	archivo.open(nombre_archivo, ios::out | ios::binary);

	while(archivo_temp.read((char *)&venta,sizeof(Venta))){
		archivo.write((char *)&venta,sizeof(Venta));
		
	}
	archivo.close();
	archivo_temp.close();
	Leer();
}

void buscar_codigo(){
	ifstream archivo;
	archivo.open(nombre_archivo, ios::in | ios::binary);
	int pos=0,indice=0,cod=0;
	cout<<"Que codigo desea ver: ";
	cin>>cod;
	
	Venta venta;

	archivo.read((char *)&venta,sizeof(Venta));

	do {
	   if(venta.codigo == cod)	{
	   	cout<<"Codigo: "<<venta.codigo<<endl;
	   	cout<<"Fecha: "<<venta.fecha<<endl;
	   	cout<<"Nombres: "<<venta.nombres<<endl;
	   	cout<<"Apellidos: "<<venta.apellidos<<endl;
	   	cout<<"Metodo de pago: "<<venta.formaPago<<endl;
	   	cout<<"Total: "<<venta.total<<endl;
	   }
	   archivo.read((char *)&venta,sizeof(Venta));	
	} while(!archivo.eof());
	
	
	archivo.close();
	menu();
}


void buscar_indice(){
	FILE* archivo = fopen(nombre_archivo, "rb");
	
	int pos=0;
	cout<<"Que registro desea ver: ";
	cin>>pos;
	system("cls");
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Venta), SEEK_SET );
	
	Venta venta;
	
    fread ( &venta, sizeof( Venta ), 1, archivo );

    	cout<<"Codigo: "<<venta.codigo<<endl;
	   	cout<<"Fecha: "<<venta.fecha<<endl;
	   	cout<<"Nombres: "<<venta.nombres<<endl;
	   	cout<<"Apellidos: "<<venta.apellidos<<endl;
	   	cout<<"Metodo de pago: "<<venta.formaPago<<endl;
	   	cout<<"Total: "<<venta.total<<endl;
        cout << endl;
	
	fclose(archivo);

	menu();
	
}

int main() {
	menu();
	return 0;
}

 void menu() {
	system("cls");
  int op ;

  do {

	cout << "|----------------------------------------|" << endl;
	cout << "| Bienvenido al sistema de Supermercado! |" << endl;
	cout << "|----------------------------------------|" << endl << endl;

    cout << "1. Cargar informacion de ventas" << endl;
    cout << "2. Leer informacion de ventas" << endl;
    cout << "3. Actualizar informacion de ventas" << endl;
    cout << "4. Borrar informacion de ventas" << endl;
    cout << "5. Buscar Codigo" << endl;
    cout << "6. Buscar Indice" << endl;
    cout << "7. Salir" << endl;
    cin >> op;

    switch(op) {
      case 1:
        Crear();
        break;
      case 2:
        Leer();
        break;
      case 3:
        Actualizar();
        break;
      case 4:
        Borrar();
        break;
      case 5:
        buscar_codigo();
	  case 6:
	  	buscar_indice();
	  case 7:
	  	exit(1);
      default:
        cout << "Por favor, escoja una opcion correcta." << endl;
    }

    system("pause");
    system("cls");
  } while(op!=7);
  
}



