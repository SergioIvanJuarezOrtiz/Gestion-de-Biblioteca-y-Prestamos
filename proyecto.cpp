#include<iostream>
#include<string>
using namespace std;

// Límite máximo para nuestros arreglos
const int MAX_USUARIOS = 100;
const int MAX_LIBROS = 100;

// structs fuera del main para que las funciones puedan usarlos globalmente
struct libro{
    int ID=0;
    string Titulo;
    string autor;
    int unidades_disponible=0;
};
struct usuario {
    string carnet;
    string nombre;
    string Facultad;
};
struct prestamo{
    string carnet_usuario;
    string id_prestamo;
    string id_libro;
    bool activo;
};

// Arreglo y contador para el registro de usuarios (variables globales)
usuario listaUsuarios[MAX_USUARIOS];
int totalUsuarios = 0;
 libro inventarioLibros[MAX_LIBROS];
    int totalLibros=0;

// Declaración de funciones
void registrarLibro();
void mostrarInventario();
void buscarLibro();
void registrarUsuario();
void prestarLibro();
void devolverLibro();
void mostrarUsuarios();
void mostrarIntegrantes(); 

int main() {
    //variable para el menu principal
    int opcion=0;
    //bucle do-while para repetir el menu cuando no se seleccione una opcion del 1-9 
    //switch para seleccionar alguna de las opciones del menu

    do {
        cout << "=====Bienvenido al sistema de biblioteca y prestamos===== " << endl;
        cout << "Seleccione una opcion del menu del (1 al 9): " << endl;
        cout << "1. Registrar Libro "<<endl;
        cout << "2. Mostrar Inventario " <<endl;
        cout << "3. Buscar Libro (Titulo o ID) " <<endl;
        cout << "4. Registrar Usuario " <<endl;
        cout << "5. Prestar Libro " <<endl;
        cout << "6. Delvolver Libro " <<endl;
        cout << "7. Mostrar Usuarios " <<endl;
        cout << "8. Mostrar Integrantes "<<endl;
        cout << "9. Salir del programa "<<endl;
        cout <<" Ingrese su opcion: ";
        cin >> opcion;

        switch(opcion){

            case 1:
            registrarLibro();
            break;

            case 2:
            mostrarInventario();
            break;

            case 3:
            buscarLibro();
            break;

            case 4:
            registrarUsuario();
            break;

            case 5:
            prestarLibro();
            break;

            case 6:
            devolverLibro();
            break;

            case 7:
            mostrarUsuarios();
            break;

            case 8:
            mostrarIntegrantes();
            break;

            case 9:
            cout << "Salir del programa " <<endl;
            break;

            default:
            cout << "opcion invalida, seleccione un valor del (1-9) " << endl;
            break;
        }
    }while(opcion != 9);

    
    
    // Sergio agregará aquí el bucle while y el switch principal
    
    return 0;
}

/* ======================================================================
   DECLARACIÓN DE USO DE IA 
   1. Herramienta utilizada: Gemini
   2. Parte del proyecto: Módulo de Registro (registrarUsuario) y Búsquedas.
   3. Fragmento apoyado: La lógica de usar una variable booleana ("bandera") 
      dentro de un ciclo 'for' para detectar duplicados o encontrar IDs.
   4. Modificaciones realizadas: Se adaptó el código generado para que 
      utilice nuestros structs ('listaUsuarios' e 'inventarioLibros'), 
      y se personalizaron los mensajes de salida (cout) según la rúbrica.
====================================================================== */

// Módulo de Registro de Usuarios
void registrarUsuario() {
    // if-else para controlar que no se exceda el límite de usuarios
    if (totalUsuarios < MAX_USUARIOS) {
        cout << "\n--- Registro de Nuevo Estudiante ---" << endl;
        
        string carnetIngresado;
        cout << "Ingrese el carnet (Ej. 00024026): ";
        cin >> carnetIngresado;

        // Control de duplicados usando lógica de bandera booleana
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
        }
    } else {
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

// Módulo de Devoluciones
void devolverLibro() {
    cout << "\n--- Modulo de Devoluciones ---" << endl;
    string carnetEstudiante;
    cout << "Ingrese su carnet de estudiante: ";
    cin >> carnetEstudiante;

    int idDevolver;
    cout << "Ingrese el ID del libro que desea devolver: ";
    cin >> idDevolver;

    bool libroEncontrado = false;

    // Busca el libro en el inventario
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idDevolver) {
            libroEncontrado = true;
            
            // Reintegrar stock sumando 1 unidad
            inventarioLibros[i].unidades_disponible++;
            cout << "Gracias por su devolucion, estudiante " << carnetEstudiante << "." << endl;
            cout << "Libro reintegrado al inventario con exito." << endl;
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El ID ingresado no corresponde a ningun libro de nuestra biblioteca." << endl;
    }
}

// Función para listar los usuarios registrados
void mostrarUsuarios() {
    cout << "\n--- Listado de Estudiantes Registrados ---" << endl;
    if (totalUsuarios == 0) {
        cout << "No hay estudiantes registrados en el sistema actualmente." << endl;
    } else {
        for (int i = 0; i < totalUsuarios; i++) {
            cout << i + 1 << ". Carnet: " << listaUsuarios[i].carnet 
                 << " | Nombre: " << listaUsuarios[i].nombre 
                 << " | Facultad: " << listaUsuarios[i].Facultad << endl;
        }
    }
    cout << "------------------------------------------" << endl;
}

// Función para mostrar los integrantes del proyecto
void mostrarIntegrantes() {
    cout << "\n==========================================" << endl;
    cout << "       INTEGRANTES DEL PROYECTO" << endl;
    cout << "==========================================" << endl;
    cout << "1. Sergio Ivan Juarez Ortiz - 00011826" << endl;
    cout << "2. Christhian Eduardo Sanchez Lopez - 00024026" << endl;
    cout << "==========================================" << endl;
}
