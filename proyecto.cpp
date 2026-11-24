#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// structs fuera del main para que las funciones puedan usarlos globalmente
struct libro{
    int ID=0;
    string Titulo;
    string autor;
    int unidades_disponible=0;
};
struct usuario {
    int carnet;
    string nombre;
    string Facultad;
    string contrasena;
};
struct prestamo{
    int id;
    int carnet;
    int libro;
    bool activo;
};

// Declaración de funciones
void registrarLibro(libro inventarioLibros[], int &totalLibros, int max_libros);
void mostrarInventario(libro inventarioLibros[], int totalLibros);
void buscarLibro(libro inventarioLibros[], int totalLibros);
void registrarUsuario(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios);
void prestarLibro(libro inventarioLibros[], int totalLibros, prestamo prestamosActivos[],int &totalPrestamos);
void devolverLibro(libro inventarioLibros[], int totalLibros, prestamo PrestamosActivos[], int totalPrestamos);
void mostrarUsuarios(usuario listaUsuarios[], int totalUsuarios);
void mostrarIntegrantes();
int iniciarSesion(usuario listaUsuarios[], int totalUsuarios);
void cargarUsuarios(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios);
void guardarUsuarios(usuario listaUsuarios[], int totalUsuarios);
void cargarLibros(libro inventarioLibros[], int &totalLibros, int max_libros);
void guardarLibros(libro inventarioLibros[], int totalLibros);
int leerEntero(string mensaje);

int main() {
    int max_usuarios = 100;
    int max_libros = 100;

    usuario listaUsuarios[100];
    int totalUsuarios = 0;

    libro inventarioLibros[100];
    int totalLibros=0;
    
    prestamo prestamosActivos[100];
    int totalPrestamos = 0;

    cargarUsuarios(listaUsuarios, totalUsuarios, max_usuarios);
    cargarLibros(inventarioLibros, totalLibros, max_libros);

    bool sistemaActivo = true; // Variable maestra para mantener el programa encendido
    
    // Bucle principal del sistema
    while (sistemaActivo) {
        
        int rolActual = 0; // 0 = No logueado, 1 = Admin, 2 = Usuario normal
        
        // Bucle de Login: elegir iniciar sesion o registrarse
        while (rolActual == 0) {
            cout << "\n========================================" << endl;
            cout << "     BIBLIOTECA - ACCESO AL SISTEMA" << endl;
            cout << "========================================" << endl;
            cout << "  1. Iniciar sesion" << endl;
            cout << "  2. Registrarse" << endl;
            cout << "  0. Salir del programa" << endl;
            cout << "----------------------------------------" << endl;
            int opcionAcceso = leerEntero("Opcion: ");

            if (opcionAcceso == 1) {
                rolActual = iniciarSesion(listaUsuarios, totalUsuarios);

                if (rolActual == -1) {
                    rolActual = 0;
                } else if (rolActual == 0) {
                    cout << "Error: Credenciales incorrectas. Intente nuevamente." << endl;
                }
            } else if (opcionAcceso == 2) {
                registrarUsuario(listaUsuarios, totalUsuarios, max_usuarios);
            } else if (opcionAcceso == 0) {
                cout << "Apagando el sistema..." << endl;
                sistemaActivo = false;
                break;
            } else {
                cout << "Opcion invalida. Intente nuevamente." << endl;
            }
        }
    // Si se apaga el sistema desde el login, evitamos entrar al menú
    if (!sistemaActivo) {
        break; 
    }

    // Bucle del menú
        int opcion = -1;
    while (rolActual != 0 && sistemaActivo) {
            cout << "\n========================================" << endl;
            cout << "  SISTEMA DE BIBLIOTECA Y PRESTAMOS" << endl;
            cout << "========================================" << endl;
            if (rolActual == 1) {
                cout << "Sesion: Administrador" << endl;
            } else {
                cout << "Sesion: Estudiante" << endl;
            }
            cout << "----------------------------------------" << endl;
            if (rolActual == 1) {
                cout << "  1. Registrar libro" << endl;
                cout << "  2. Mostrar inventario" << endl;
                cout << "  3. Buscar libro (titulo o ID)" << endl;
                cout << "  4. Registrar usuario" << endl;
                cout << "  5. Prestar libro" << endl;
                cout << "  6. Devolver libro" << endl;
                cout << "  7. Mostrar usuarios" << endl;
                cout << "  8. Mostrar integrantes" << endl;
            } else {
                cout << "  3. Buscar libro (titulo o ID)" << endl;
                cout << "  5. Prestar libro" << endl;
                cout << "  6. Devolver libro" << endl;
                cout << "  8. Mostrar integrantes" << endl;
            }
            cout << "  9. Cerrar sesion (volver al acceso)" << endl;
            cout << "  0. Salir del programa" << endl;
            cout << "----------------------------------------" << endl;
            opcion = leerEntero("Opcion: ");

            switch(opcion){
                case 1:
                    if (rolActual == 1) {
                        registrarLibro(inventarioLibros, totalLibros, max_libros);
                    } else {
                        cout << "Error: solo el administrador puede registrar libros." << endl;
                    }
                    break;
                case 2:
                    if (rolActual == 1) {
                        mostrarInventario(inventarioLibros, totalLibros);
                    } else {
                        cout << "Error: solo el administrador puede ver el inventario." << endl;
                    }
                    break;
                case 4:
                    if (rolActual == 1) {
                        registrarUsuario(listaUsuarios, totalUsuarios, max_usuarios);
                    } else {
                        cout << "Error: solo el administrador puede registrar usuarios." << endl;
                    }
                    break;
                case 5: prestarLibro(inventarioLibros, totalLibros, prestamosActivos, totalPrestamos); break;
                case 6: devolverLibro(inventarioLibros, totalLibros, prestamosActivos, totalPrestamos); break;
                case 7:
                    if (rolActual == 1) {
                        mostrarUsuarios(listaUsuarios, totalUsuarios);
                    } else {
                        cout << "Error: solo el administrador puede ver la lista de usuarios." << endl;
                    }
                    break;
                case 8: mostrarIntegrantes(); break;
                case 9:
                    cout << "Cerrando sesion..." <<endl;
                    rolActual = 0; // Al ponerlo en 0, rompe este while interno y vuelve al login
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    sistemaActivo = false; // Rompe todos los bucles y apaga el programa
                    break;
                default:
                    cout << "Opcion invalida. " << endl;
                    break;
            }
        }
    }

    return 0;
}
/* ======================================================================
   DECLARACIÓN DE USO DE IA (Apoyo parcial)
   1. Herramienta utilizada: Gemini
   2. Parte del proyecto: Control de flujo general.
   3. Fragmento apoyado: Lógica de bucles anidados con variable booleana 
      ('sistemaActivo') para salir de forma limpia del programa.
   4. Modificaciones realizadas: Se adaptaron las opciones del menú switch.
====================================================================== */
// Módulo de Inicio de Sesión
// Retorna: 1 admin, 2 estudiante, 0 error, -2 volver al menu de acceso
int iniciarSesion(usuario listaUsuarios[], int totalUsuarios) {
    string pass;
    int carnetLogin;
    cout << "\n========================================" << endl;
    cout << "           INICIO DE SESION" << endl;
    cout << "========================================" << endl;
    cout << "  0. Volver al menu de acceso" << endl;
    cout << "  (admin: ingrese -1 como carnet)" << endl;
    cout << "----------------------------------------" << endl;
    carnetLogin = leerEntero("Carnet: ");

    if (carnetLogin == 0) {
        return -1;
    }

    if (carnetLogin == -1) {
        string user;
        cout << "Usuario admin: ";
        cin >> user;
        cout << "Contrasena: ";
        cin >> pass;
        if (user == "admin" && pass == "1234") {
            return 1;
        }
        return 0;
    }

    cout << "Contrasena: ";
    cin >> pass;

    for (int i = 0; i < totalUsuarios; i++) {
        if (listaUsuarios[i].carnet == carnetLogin && listaUsuarios[i].contrasena == pass) {
            return 2;
        }
    }
    return 0;
}

// Módulo de Registro de Usuarios
void registrarUsuario(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios ) {
    // if-else para controlar que no se exceda el límite de usuarios
    if (totalUsuarios < max_usuarios) {
        cout << "\n========================================" << endl;
        cout << "         REGISTRO DE USUARIO" << endl;
        cout << "========================================" << endl;
        cout << "  0. Volver al menu de acceso" << endl;
        cout << "----------------------------------------" << endl;

        int carnetIngresado = leerEntero("Carnet (ej. 24026, 0 cancelar): ");

        if (carnetIngresado == 0) {
            cout << "Registro cancelado." << endl;
            return;
        }

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

            cout << "Primer nombre: ";
            cin >> listaUsuarios[totalUsuarios].nombre;

            cin.ignore();

            cout << "Facultad: ";
            getline(cin, listaUsuarios[totalUsuarios].Facultad);
            cout << "Contrasena: ";
            cin >> listaUsuarios[totalUsuarios].contrasena;
            totalUsuarios++;
            guardarUsuarios(listaUsuarios, totalUsuarios);
            cout << "¡Usuario registrado exitosamente!" << endl;
        }
    } else {
        cout << "\nError: No se pueden registrar mas usuarios, limite alcanzado." << endl;
    }
}

//funcion para registrar libros utilizando if-else 
void registrarLibro(libro inventarioLibros[], int &totalLibros, int max_libros){
    //verifica si se puede agregar otro libro
    if(totalLibros >= max_libros){
        cout<<"El inventario esta completo" <<endl;

    }else{
        cout << "\n========================================" << endl;
        cout << "         REGISTRO DE LIBRO" << endl;
        cout << "========================================" << endl;
        
        cin.ignore();
    
        cout <<"Ingrese el Titulo del libro: ";
        getline(cin, inventarioLibros[totalLibros].Titulo); 

        cout <<"Ingrese el Autor del libro: ";
        getline(cin, inventarioLibros[totalLibros].autor);

        inventarioLibros[totalLibros].unidades_disponible =
            leerEntero("Ingrese las unidades disponibles: ");

        //validar los datos y asignar el ID
    
        if(inventarioLibros[totalLibros].Titulo == ""){
            cout <<"fallo titulo vacio" <<endl;
        }else if (inventarioLibros[totalLibros].autor == ""){
            cout <<"fallo autor vacio" <<endl;
        }else if (inventarioLibros[totalLibros].unidades_disponible < 0){
            cout <<" fallo unidades incorrectas" <<endl;
        }else{
            inventarioLibros[totalLibros].ID= totalLibros + 1;
            cout <<"ID asignado: " << inventarioLibros[totalLibros].ID << endl;

            totalLibros++;
            guardarLibros(inventarioLibros, totalLibros);
            cout <<"el Libro registrado correctamente" <<endl;
        }    
    }
}
//funcion para mostrar inventario
void mostrarInventario(libro inventarioLibros[], int totalLibros){
    // verificar si no hay libros registrados
    if(totalLibros ==0){

        cout<<"No hay libros registrados" <<endl;

    }else{

        cout << "\n========================================" << endl;
        cout << "           INVENTARIO DE LIBROS" << endl;
        cout << "========================================" << endl;

        for(int i = 0; i <totalLibros; i++){
            cout << "----------------------------------------" << endl;
            cout << "ID: " << inventarioLibros[i].ID << endl;
            cout << "Titulo: " << inventarioLibros[i].Titulo << endl;
            cout << "Autor: " << inventarioLibros[i].autor << endl;
            cout << "Unidades: " << inventarioLibros[i].unidades_disponible << endl;
        }
    }
}
//funcion para buscar libro
void buscarLibro(libro inventarioLibros[],int totalLibros){

    int opcion;
    int idBusqueda;
    string tituloBuscar;
    bool encontrado = false;

    //verificar si hay libros registrados
    if(totalLibros ==0){
        cout << "No hay libros registrados" <<endl;
        return;
    }

    cout << "====== Buscar libro =======" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por Titulo" << endl;
    cout <<" ingrese una opcion: ";
    cin >> opcion;

    //verificar si se ingreso un numero

    if(cin.fail()){           //si ocurrio error al introducir numero
        cin.clear();         //limpia estado de error
        cin.ignore(1000, '\n');
        cout << "Error: ingrese un numero" <<endl;
        return;
    }

    if(opcion ==1){

        cout <<"Ingrese el ID del libro: ";
        cin >>idBusqueda;

        //verificar si se ingreso un numero
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: ingrese un numero"<<endl;
            return;
        }

    
        // buscar por ID
        for(int i=0; i < totalLibros; i++){

            if(inventarioLibros[i].ID == idBusqueda){

                cout <<"Libro encontrado " <<endl;
                cout <<"ID : " << inventarioLibros[i].ID <<endl;
                cout <<"Titulo :  "<< inventarioLibros[i].Titulo <<endl;
                cout <<"Autor : " << inventarioLibros[i].autor << endl;
                cout <<"Unidades: " <<inventarioLibros[i].unidades_disponible << endl;

                encontrado = true;
                break;
            }
    }
    if(encontrado == false){
        cout<<"Libro no encontrado" <<endl;

    }
    }else if(opcion ==2){
        cin.ignore(1000, '\n');

        cout<<"Ingrese el titulo del libro: ";
        getline(cin, tituloBuscar);

        //busca por titulo
        for(int i = 0; i<totalLibros; i++){

            if(inventarioLibros[i].Titulo == tituloBuscar){

                cout <<"Libro encontrado" <<endl;
                cout <<"ID: " << inventarioLibros[i].ID << endl;
                cout <<"Titulo: " << inventarioLibros[i].Titulo <<endl;
                cout <<"Autor: " << inventarioLibros[i].autor <<endl;
                cout << "Unidades: " << inventarioLibros[i].unidades_disponible <<   endl;

                encontrado = true;
            }
        }
        if(encontrado == false){

            cout <<"Libro no encontrado" << endl;

        }

    } else{
        cout << " Opcion incorrecta" <<endl;
    }
}






// Módulo de Préstamos y Devoluciones
void prestarLibro(libro inventarioLibros[], int totalLibros, prestamo prestamosActivos[], int&totalPrestamos) {
    cout << "\n========================================" << endl;
    cout << "            PRESTAMO DE LIBRO" << endl;
    cout << "========================================" << endl;
    int idBuscar = leerEntero("Ingrese el ID del libro que desea prestar: ");

    bool libroEncontrado = false;
    
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idBuscar) {
            libroEncontrado = true;
            
            if (inventarioLibros[i].unidades_disponible > 0) {

                //verifica si hay espacio para otro prestamo
                if (totalPrestamos < 100){
                    int carnetEstudiante = leerEntero("Ingrese su carnet de estudiante:");

                    //guarda prestamo en el arreglo
                    prestamosActivos[totalPrestamos].id = totalPrestamos +1;
                    prestamosActivos[totalPrestamos].carnet = carnetEstudiante;
                    prestamosActivos[totalPrestamos].libro = idBuscar;
                    prestamosActivos[totalPrestamos].activo = true;

                    totalPrestamos++;
                    //restar  una unidad del libro
                    inventarioLibros[i].unidades_disponible--;
                    guardarLibros(inventarioLibros, totalLibros);

                   cout << "Prestamo realizado con exito. Disfrute su lectura." << endl;
                    
                }else{
                    cout <<"error: El historial de prestamos esta lleno" <<endl;
                }
                
            } else {
                cout << "Error: No hay unidades disponibles." << endl;
            }
            break;
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El libro no existe." << endl;
    }
}

// Módulo de Devoluciones
void devolverLibro(libro inventarioLibros[], int totalLibros, prestamo prestamosActivos[], int totalPrestamos){
    cout << "\n========================================" << endl;
    cout << "           DEVOLUCION DE LIBRO" << endl;
    cout << "========================================" << endl;
    int carnetEstudiante = leerEntero("Ingrese su carnet de estudiante: ");
    int idDevolver = leerEntero("Ingrese el ID del libro que desea devolver: ");

    bool libroEncontrado = false;
    bool prestamoEncontrado = false;

    // Busca el libro en el inventario
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idDevolver) {
            libroEncontrado = true;

            //buscar el prestamo registrado
            for(int j=0; j< totalPrestamos; j++){

                if(prestamosActivos[j].libro == idDevolver && prestamosActivos[j].carnet == carnetEstudiante && prestamosActivos[j].activo == true){

                    
                prestamosActivos[j].activo =false;

                    // reintegra unidades al invetario
                    inventarioLibros[i].unidades_disponible++;
                    guardarLibros(inventarioLibros,totalLibros);

                    prestamoEncontrado = true;
                    cout << "Gracias por su devolucion, estudiante " << carnetEstudiante << "." << endl;
                    cout << "Libro reintegrado al inventario con exito." << endl;  
                    break;
                } 
            }
            if(prestamoEncontrado == false){
                cout <<"Error: no existe un prestamo activo para este estudiante" <<endl;
                break;
            }
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El ID ingresado no corresponde a ningun libro de nuestra biblioteca." << endl;
    }
}

// Función para listar los usuarios registrados
void mostrarUsuarios(usuario listaUsuarios[], int totalUsuarios) {
    cout << "\n========================================" << endl;
    cout << "      ESTUDIANTES REGISTRADOS" << endl;
    cout << "========================================" << endl;
    if (totalUsuarios == 0) {
        cout << "No hay estudiantes registrados en el sistema actualmente." << endl;
    } else {
        for (int i = 0; i < totalUsuarios; i++) {
            cout << i + 1 << ". Carnet: " << listaUsuarios[i].carnet 
                 << " | Nombre: " << listaUsuarios[i].nombre 
                 << " | Facultad: " << listaUsuarios[i].Facultad << endl;
        }
    }
    cout << "----------------------------------------" << endl;
}

// Función para mostrar los integrantes del proyecto
void mostrarIntegrantes() {
    cout << "\n========================================" << endl;
    cout << "       INTEGRANTES DEL PROYECTO" << endl;
    cout << "========================================" << endl;
    cout << "1. Sergio Ivan Juarez Ortiz - 00011826" << endl;
    cout << "2. Christhian Eduardo Sanchez Lopez - 00024026" << endl;
    cout << "========================================" << endl;
}

// Pide un entero y vuelve a preguntar si escriben texto
int leerEntero(string mensaje) {
    int valor;
    bool entradaValida = false;

    while (entradaValida == false) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cout << "Error: debe ingresar solo numeros. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            entradaValida = true;
        }
    }

    return valor;
}

// Persistencia en archivos de texto
void cargarUsuarios(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios) {
    ifstream archivo("usuarios.txt");
    if (archivo.is_open() == false) {
        totalUsuarios = 0;
        return;
    }

    archivo >> totalUsuarios;
    if (totalUsuarios > max_usuarios) {
        totalUsuarios = max_usuarios;
    }

    archivo.ignore();
    for (int i = 0; i < totalUsuarios; i++) {
        archivo >> listaUsuarios[i].carnet;
        archivo.ignore();
        getline(archivo, listaUsuarios[i].nombre);
        getline(archivo, listaUsuarios[i].Facultad);
        getline(archivo, listaUsuarios[i].contrasena);
    }
    archivo.close();
}

void guardarUsuarios(usuario listaUsuarios[], int totalUsuarios) {
    ofstream archivo("usuarios.txt");
    if (archivo.is_open() == false) {
        cout << "Error: no se pudo guardar el archivo de usuarios." << endl;
        return;
    }

    archivo << totalUsuarios << endl;
    for (int i = 0; i < totalUsuarios; i++) {
        archivo << listaUsuarios[i].carnet << endl;
        archivo << listaUsuarios[i].nombre << endl;
        archivo << listaUsuarios[i].Facultad << endl;
        archivo << listaUsuarios[i].contrasena << endl;
    }
    archivo.close();
}

void cargarLibros(libro inventarioLibros[], int &totalLibros, int max_libros) {
    ifstream archivo("libros.txt");
    if (archivo.is_open() == false) {
        totalLibros = 0;
        return;
    }

    archivo >> totalLibros;
    if (totalLibros > max_libros) {
        totalLibros = max_libros;
    }

    archivo.ignore();
    for (int i = 0; i < totalLibros; i++) {
        archivo >> inventarioLibros[i].ID;
        archivo.ignore();
        getline(archivo, inventarioLibros[i].Titulo);
        getline(archivo, inventarioLibros[i].autor);
        archivo >> inventarioLibros[i].unidades_disponible;
        archivo.ignore();
    }
    archivo.close();
}

void guardarLibros(libro inventarioLibros[], int totalLibros) {
    ofstream archivo("libros.txt");
    if (archivo.is_open() == false) {
        cout << "Error: no se pudo guardar el archivo de libros." << endl;
        return;
    }

    archivo << totalLibros << endl;
    for (int i = 0; i < totalLibros; i++) {
        archivo << inventarioLibros[i].ID << endl;
        archivo << inventarioLibros[i].Titulo << endl;
        archivo << inventarioLibros[i].autor << endl;
        archivo << inventarioLibros[i].unidades_disponible << endl;
    }
    archivo.close();
}


