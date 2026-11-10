#include<iostream>
#include<string>
using namespace std;


    const int MAX_USUARIOS = 100;
    const int MAX_LIBROS = 100;

    struct libro{

// Límite máximo para nuestros arreglos
const int MAX_USUARIOS = 100;
const int MAX_LIBROS = 100;
// structs fuera del main para que las funciones puedan usarlos
struct libro{

        int ID=0;
        string Titulo;
        string autor;
        int unidades_disponibles;
    
    };
    struct usuario{
        string carnet;
        string nombre;
        string facultad;
    };
    struct prestamo{
        string carnet_usuario;
        string id_prestamo;
        string id_libro;
        bool activo;

    };

    libro inventario_libro[MAX_LIBROS];
    int total_libros=0;

    usuario lista_usuarios[MAX_USUARIOS];
    int total_usuarios=0;

    void registrar_libro();
    void registar_inventario();
    
    
    int main(){



   










    };
struct usuario {
    string carnet;
    string nombre;
    string Facultad;
};




libro inventarioLibros[MAX_LIBROS];
int totalLibros = 0; // Sergio, usa esta variable en tu función de agregar libros

// Declaración de funciones
void registrarUsuario();
void prestarLibro();
void devolverLibro();

int main() {
    int opcion= 0;
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





    

    
    
    










    return 0;

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

// Módulo de Devoluciones
void devolverLibro() {
    cout << "\n--- Modulo de Devoluciones ---" << endl;
    int idDevolver;
    cout << "Ingrese el ID del libro que desea devolver: ";
    cin >> idDevolver;

    bool libroEncontrado = false;

    // Busca el libro en el inventario
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idDevolver) {
            //reintegrar stock
            inventarioLibros[i].unidades_disponible++;
            cout << "Gracias por su devolucion, estudiante " << carnetEstudiante << "." << endl;
            cout << "Libro reintegrado al inventario con exito." << endl;
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El ID ingresado no corresponde a ningun libro de nuestra biblioteca." << endl;
    }

}