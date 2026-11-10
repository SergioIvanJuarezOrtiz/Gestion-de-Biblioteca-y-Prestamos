#include<iostream>
#include<string>
using namespace std;

// Definimos un límite máximo para nuestros arreglos
const int MAX_USUARIOS = 100;
const int MAX_LIBROS = 100;
// structs fuera del main para que las funciones puedan usarlos
struct libro {
    int ID = 0;
    int Titulo = 0;// Nota para Sergio: Cambiar a string luego
    int autor = 0;// Nota para Sergio: Cambiar a string luego
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

libro inventarioLibros[MAX_LIBROS];
int totalLibros = 0; // Sergio, usa esta variable en tu función de agregar libros

// Declaración de funciones
void registrarUsuario();
void prestarLibro();

int main() {
    
    return 0;
}

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

// Módulo de Préstamos y Devoluciones
void prestarLibro() {
    cout << "\n--- Modulo de Prestamos ---" << endl;
    int idBuscar;
    cout << "Ingrese el ID del libro que desea prestar: ";
    cin >> idBuscar;

    bool libroEncontrado = false;
    
    // for para buscar el libro en el inventario
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idBuscar) {
            libroEncontrado = true;
            
            // if-else para verificar estrictamente si hay stock disponible antes de prestar
            if (inventarioLibros[i].unidades_disponible > 0) {
                inventarioLibros[i].unidades_disponible--; // Descontamos 1 unidad del inventario
                cout << "Prestamo realizado con exito. Disfrute su lectura." << endl;
            } else {
                cout << "Error: No hay unidades disponibles para prestar de este libro en este momento." << endl;
            }
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El libro con el ID ingresado no existe." << endl;
    }
}