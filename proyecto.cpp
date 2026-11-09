#include<iostream>
#include<string>
using namespace std;


    struct libro{
        int ID=0;
        string Titulo;
        string autor;
        int unidades_disponible=0;
    
    };
    struct usuario{
        int id=0;
        string nombre;

       
    };
    libro lista_Libros[100];
    int total_libros = 0;

    usuario lista_usuarios[100];
    int total_usuarios =0;

    int opcion= 0;


    
    
    











// Definimos un límite máximo para nuestros arreglos
const int MAX_USUARIOS = 100;
// structs fuera del main para que las funciones puedan usarlos
struct libro {
    int ID = 0;
    int Titulo = 0;
    int autor = 0;
    int unidades_disponible = 0;
};
struct usuario {
    string carnet;
    string nombre;
    string Facultad;
};

// Arreglo y contador para el registro de usuarios (variables globales)
usuario listaUsuarios[MAX_USUARIOS];
int totalUsuarios = 0;

// Módulo de Registro de Usuarios
void registrarUsuario() {
    // if-else para controlar que no se exceda el límite de usuarios
    if (totalUsuarios < MAX_USUARIOS) {
        cout << "\n--- Registro de Nuevo Estudiante ---" << endl;
        
        string carnetIngresado;
        cout << "Ingrese el carnet (Ej. 00024026): ";
        cin >> carnetIngresado;

        // Control de duplicados
        bool duplicado = false;
        for (int i = 0; i < totalUsuarios; i++) {
            if (listaUsuarios[i].carnet == carnetIngresado) {
                duplicado = true;
            }
        }
        // if-else para decidir si se registra o se rechaza
        if (duplicado == true) {
            cout << "Error: El carnet ingresado ya se encuentra registrado." << endl;
        } else {
            listaUsuarios[totalUsuarios].carnet = carnetIngresado;

        cout << "Ingrese el primer nombre: ";
        cin >> listaUsuarios[totalUsuarios].nombre;
        
        cout << "Ingrese la facultad (Sin espacios): ";
        cin >> listaUsuarios[totalUsuarios].Facultad;
        
        totalUsuarios++;
        cout << "¡Usuario registrado exitosamente!" << endl;
        }} else {
        cout << "\nError: No se pueden registrar mas usuarios, limite alcanzado." << endl;
        }
    }

int main() {
    

    return 0;
}