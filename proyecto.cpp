#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// structs fuera del main para que las funciones puedan usarlos globalmente
struct libro{
    int ID=0;
    string Titulo;
    string autor;
    int unidades_totales=0;
    int unidades_disponible=0;
};
struct usuario {
    string carnet;
    string nombre;
    string Facultad;
    string contrasena;
};
struct prestamo{
    int id;
    string carnet;
    int libro;
    bool activo;
};

// Declaración de funciones
void registrarLibro(libro inventarioLibros[], int &totalLibros, int max_libros);
void mostrarInventario(libro inventarioLibros[], int totalLibros);
void buscarLibro(libro inventarioLibros[], int totalLibros);
void registrarUsuario(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios);
void prestarLibro(libro inventarioLibros[], int totalLibros, prestamo prestamosActivos[], int &totalPrestamos,
                  usuario listaUsuarios[], int totalUsuarios);
void devolverLibro(libro inventarioLibros[], int totalLibros, prestamo PrestamosActivos[], int totalPrestamos);
void reportePrestamos(prestamo prestamoActivos[], int totalPrestamos);
void misPrestamos(string carnetUsuario, prestamo prestamosActivos[], int totalPrestamos,
                  libro inventarioLibros[], int totalLibros);
void mostrarUsuarios(usuario listaUsuarios[], int totalUsuarios);
void mostrarIntegrantes();
int iniciarSesion(usuario listaUsuarios[], int totalUsuarios, string &carnetSesion);
void cargarUsuarios(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios);
void guardarUsuarios(usuario listaUsuarios[], int totalUsuarios);
void cargarLibros(libro inventarioLibros[], int &totalLibros, int max_libros);
void guardarLibros(libro inventarioLibros[], int totalLibros);
void cargarPrestamos(prestamo prestamosActivos[], int &totalPrestamos, int max_prestamos);
void guardarPrestamos(prestamo prestamosActivos[], int totalPrestamos);
int leerEntero(string mensaje);
string leerLinea(string mensaje);
bool carnetSoloDigitos(string carnet);

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
    cargarPrestamos(prestamosActivos, totalPrestamos, 100);

    bool sistemaActivo = true; // Variable maestra para mantener el programa encendido
    
    // Bucle principal del sistema
    while (sistemaActivo) {
        
        int rolActual = 0; // 0 = No logueado, 1 = Admin, 2 = Usuario normal
        string carnetSesion = "";
        
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
                rolActual = iniciarSesion(listaUsuarios, totalUsuarios, carnetSesion);

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
                cout << " 10. Reporte de prestamos" << endl;
            } else {
                cout << "  3. Buscar libro (titulo o ID)" << endl;
                cout << "  5. Prestar libro" << endl;
                cout << "  6. Devolver libro" << endl;
                cout << "  7. Mis prestamos" << endl;
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
                case 3:
                    buscarLibro(inventarioLibros, totalLibros);
                    break;
                case 4:
                    if (rolActual == 1) {
                        registrarUsuario(listaUsuarios, totalUsuarios, max_usuarios);
                    } else {
                        cout << "Error: solo el administrador puede registrar usuarios." << endl;
                    }
                    break;
                case 5:
                    prestarLibro(inventarioLibros, totalLibros, prestamosActivos, totalPrestamos,
                                 listaUsuarios, totalUsuarios);
                    break;
                case 6: devolverLibro(inventarioLibros, totalLibros, prestamosActivos, totalPrestamos); break;
                case 7:
                    if (rolActual == 1) {
                        mostrarUsuarios(listaUsuarios, totalUsuarios);
                    } else {
                        misPrestamos(carnetSesion, prestamosActivos, totalPrestamos,
                                     inventarioLibros, totalLibros);
                    }
                    break;
                case 8: mostrarIntegrantes(); break;
                case 9:
                    cout << "Cerrando sesion..." <<endl;
                    carnetSesion = "";
                    rolActual = 0; // Al ponerlo en 0, rompe este while interno y vuelve al login
                    break;
                case 10:
                if(rolActual == 1){
                    reportePrestamos(prestamosActivos, totalPrestamos);
                }else{
                    cout <<"Error: solo administrador puede ver los reportes." <<endl;
                }
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
int iniciarSesion(usuario listaUsuarios[], int totalUsuarios, string &carnetSesion) {
    carnetSesion = "";
    string pass;
    string carnetLogin;
    cout << "\n========================================" << endl;
    cout << "           INICIO DE SESION" << endl;
    cout << "========================================" << endl;
    cout << "  0. Volver al menu de acceso" << endl;
    cout << "  (admin: ingrese -1 como carnet)" << endl;
    cout << "----------------------------------------" << endl;
    cin.ignore(1000, '\n');
    carnetLogin = leerLinea("Carnet: ");

    if (carnetLogin == "0") {
        return -1;
    }

    if (carnetLogin == "-1") {
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

    if (carnetSoloDigitos(carnetLogin) == false) {
        cout << "Error: el carnet solo puede contener digitos (puede incluir ceros a la izquierda)." << endl;
        return 0;
    }

    cout << "Contrasena: ";
    cin >> pass;

    for (int i = 0; i < totalUsuarios; i++) {
        if (listaUsuarios[i].carnet == carnetLogin && listaUsuarios[i].contrasena == pass) {
            carnetSesion = carnetLogin;
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

        cin.ignore(1000, '\n');
        string carnetIngresado = leerLinea("Carnet (ej. 00024026, 0 cancelar): ");

        if (carnetIngresado == "0") {
            cout << "Registro cancelado." << endl;
            return;
        }

        if (carnetIngresado == "-1") {
            cout << "Error: -1 esta reservado para el administrador." << endl;
            return;
        }

        if (carnetSoloDigitos(carnetIngresado) == false) {
            cout << "Error: el carnet solo puede contener digitos." << endl;
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

        inventarioLibros[totalLibros].unidades_totales =
            leerEntero("Ingrese las unidades totales en biblioteca: ");

        //validar los datos y asignar el ID
    
        if(inventarioLibros[totalLibros].Titulo == ""){
            cout <<"fallo titulo vacio" <<endl;
        }else if (inventarioLibros[totalLibros].autor == ""){
            cout <<"fallo autor vacio" <<endl;
        }else if (inventarioLibros[totalLibros].unidades_totales < 0){
            cout <<" fallo unidades incorrectas" <<endl;
        }else{
            inventarioLibros[totalLibros].unidades_disponible =
                inventarioLibros[totalLibros].unidades_totales;
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
            cout << "Unidades totales: " << inventarioLibros[i].unidades_totales << endl;
            cout << "Unidades disponibles: " << inventarioLibros[i].unidades_disponible << endl;
        }
    }
}
string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.length(); i++) {
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = texto[i] - 'A' + 'a';
        }
    }
    return texto;
}

bool tituloCoincideParcial(string titulo, string busqueda) {
    if (busqueda.empty()) {
        return false;
    }
    return aMinusculas(titulo).find(aMinusculas(busqueda)) != string::npos;
}

bool idCoincideParcial(int id, string busqueda) {
    if (busqueda.empty()) {
        return false;
    }
    return to_string(id).find(busqueda) != string::npos;
}

void mostrarLibroEncontrado(libro libroEncontrado) {
    cout << "----------------------------------------" << endl;
    cout << "ID: " << libroEncontrado.ID << endl;
    cout << "Titulo: " << libroEncontrado.Titulo << endl;
    cout << "Autor: " << libroEncontrado.autor << endl;
    cout << "Unidades totales: " << libroEncontrado.unidades_totales << endl;
    cout << "Unidades disponibles: " << libroEncontrado.unidades_disponible << endl;
}

//funcion para buscar libro
void buscarLibro(libro inventarioLibros[], int totalLibros) {

    int opcion;
    string textoBusqueda;
    int coincidencias = 0;

    if (totalLibros == 0) {
        cout << "No hay libros registrados" << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "            BUSCAR LIBRO" << endl;
    cout << "========================================" << endl;
    cout << "  1. Buscar por ID" << endl;
    cout << "  2. Buscar por Titulo" << endl;
    cout << "----------------------------------------" << endl;
    cout << " ingrese una opcion: ";
    cin >> opcion;

    //verificar si se ingreso un numero

    if(cin.fail()){           //si ocurrio error al introducir numero
        cin.clear();         //limpia estado de error
        cin.ignore(1000, '\n');
        cout << "Error: ingrese un numero" << endl;
        return;
    }

    cin.ignore(1000, '\n');

    if (opcion == 1) {
        cout << "Ingrese el ID: ";
        getline(cin, textoBusqueda);

        cout << "\n----------------------------------------" << endl;
        cout << "        LIBROS QUE COINCIDEN" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < totalLibros; i++) {
            if (idCoincideParcial(inventarioLibros[i].ID, textoBusqueda)) {
                mostrarLibroEncontrado(inventarioLibros[i]);
                coincidencias++;
            }
        }
    } else if (opcion == 2) {
        cout << "Ingrese el titulo: ";
        getline(cin, textoBusqueda);

        cout << "\n----------------------------------------" << endl;
        cout << "        LIBROS QUE COINCIDEN" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < totalLibros; i++) {
            if (tituloCoincideParcial(inventarioLibros[i].Titulo, textoBusqueda)) {
                mostrarLibroEncontrado(inventarioLibros[i]);
                coincidencias++;
            }
        }
    } else {
        cout << " Opcion incorrecta" << endl;
        return;
    }

    if (coincidencias == 0) {
        cout << "No se encontraron libros con esa busqueda." << endl;
    } else {
        cout << "----------------------------------------" << endl;
        cout << "Total encontrados: " << coincidencias << endl;
    }
}






bool carnetEstaRegistrado(usuario listaUsuarios[], int totalUsuarios, string carnet) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (listaUsuarios[i].carnet == carnet) {
            return true;
        }
    }
    return false;
}

// Módulo de Préstamos y Devoluciones
void prestarLibro(libro inventarioLibros[], int totalLibros, prestamo prestamosActivos[], int &totalPrestamos,
                  usuario listaUsuarios[], int totalUsuarios) {
    cout << "\n========================================" << endl;
    cout << "            PRESTAMO DE LIBRO" << endl;
    cout << "========================================" << endl;
    int idBuscar = leerEntero("Ingrese el ID del libro que desea prestar: ");

    int indiceLibro = -1;
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idBuscar) {
            indiceLibro = i;
            break;
        }
    }

    if (indiceLibro == -1) {
        cout << "Error: el libro con ese ID no existe." << endl;
        return;
    }

    if (inventarioLibros[indiceLibro].unidades_disponible <= 0) {
        cout << "Error: No hay unidades disponibles." << endl;
        return;
    }

    if (totalPrestamos >= 100) {
        cout << "error: El historial de prestamos esta lleno" << endl;
        return;
    }

    cin.ignore(1000, '\n');
    string carnetEstudiante = leerLinea("Ingrese su carnet de estudiante: ");

    if (carnetEstudiante == "-1") {
        cout << "Error: -1 es carnet reservado para el administrador, no se puede usar en un prestamo." << endl;
        return;
    }
    if (carnetSoloDigitos(carnetEstudiante) == false) {
        cout << "Error: el carnet solo puede contener digitos." << endl;
        return;
    }
    if (carnetEstaRegistrado(listaUsuarios, totalUsuarios, carnetEstudiante) == false) {
        cout << "Error: no existe un estudiante registrado con ese carnet." << endl;
        return;
    }

    prestamosActivos[totalPrestamos].id = totalPrestamos + 1;
    prestamosActivos[totalPrestamos].carnet = carnetEstudiante;
    prestamosActivos[totalPrestamos].libro = idBuscar;
    prestamosActivos[totalPrestamos].activo = true;

    totalPrestamos++;
    inventarioLibros[indiceLibro].unidades_disponible--;
    guardarLibros(inventarioLibros, totalLibros);
    guardarPrestamos(prestamosActivos, totalPrestamos);

    cout << "Prestamo realizado con exito. Disfrute su lectura." << endl;
}

// Módulo de Devoluciones
void devolverLibro(libro inventarioLibros[], int totalLibros, prestamo prestamosActivos[], int totalPrestamos){
    cout << "\n========================================" << endl;
    cout << "           DEVOLUCION DE LIBRO" << endl;
    cout << "========================================" << endl;
    cin.ignore(1000, '\n');
    string carnetEstudiante = leerLinea("Ingrese su carnet de estudiante: ");
    if (carnetSoloDigitos(carnetEstudiante) == false) {
        cout << "Error: el carnet solo puede contener digitos." << endl;
        return;
    }
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
                    if (inventarioLibros[i].unidades_disponible <
                        inventarioLibros[i].unidades_totales) {
                        inventarioLibros[i].unidades_disponible++;
                    }
                    guardarLibros(inventarioLibros,totalLibros);
                    guardarPrestamos(prestamosActivos, totalPrestamos);

                    prestamoEncontrado = true;
                    cout << "Gracias por su devolucion, estudiante " << carnetEstudiante << "." << endl;
                    cout << "Libro reintegrado al inventario con exito." << endl;  
                    break;
                } 
            }
            if(prestamoEncontrado == false){
                cout <<"Error: no existe un prestamo activo para este estudiante" <<endl;
                
            }
            break;
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El ID ingresado no corresponde a ningun libro de nuestra biblioteca." << endl;
    }
}
string tituloLibroPorId(libro inventarioLibros[], int totalLibros, int idLibro) {
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idLibro) {
            return inventarioLibros[i].Titulo;
        }
    }
    return "(libro no encontrado)";
}

void misPrestamos(string carnetUsuario, prestamo prestamosActivos[], int totalPrestamos,
                  libro inventarioLibros[], int totalLibros) {
    cout << "\n========================================" << endl;
    cout << "            MIS PRESTAMOS" << endl;
    cout << "========================================" << endl;
    cout << "Carnet: " << carnetUsuario << endl;
    cout << "----------------------------------------" << endl;

    if (totalPrestamos == 0) {
        cout << "No tienes prestamos registrados." << endl;
        return;
    }

    int misRegistros = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamosActivos[i].carnet != carnetUsuario) {
            continue;
        }
        misRegistros++;
        string titulo = tituloLibroPorId(inventarioLibros, totalLibros, prestamosActivos[i].libro);
        cout << "Prestamo #" << prestamosActivos[i].id << endl;
        cout << "Libro ID: " << prestamosActivos[i].libro << " | Titulo: " << titulo << endl;
        if (prestamosActivos[i].activo) {
            cout << "Estado: En tu poder (activo)" << endl;
        } else {
            cout << "Estado: Devuelto" << endl;
        }
        cout << "----------------------------------------" << endl;
    }

    if (misRegistros == 0) {
        cout << "No tienes prestamos registrados." << endl;
    }
}

// funcion para mostrar el reporte de prestamos
void reportePrestamos(prestamo prestamosActivos[], int totalPrestamos){

    cout << "\n========================================" << endl;
    cout << "        REPORTE DE PRESTAMOS" << endl;
    cout << "========================================" << endl;

    // verifica si hay prestamos registrados    
    if(totalPrestamos ==0){
        cout <<"No hay prestamos registrados"   <<endl;

    }else{

        //mostrar parametros registrados
        for(int i = 0; i < totalPrestamos; i++){
            cout <<"ID del prestamo: " <<prestamosActivos[i].id <<endl;
            cout << "Carnet: " << prestamosActivos[i].carnet << endl;
            cout <<"ID del libro: " <<prestamosActivos[i].libro <<endl;

            // verifica el estado del prestamo  
            if(prestamosActivos[i].activo == true){
                cout <<"Estado: prestado" <<endl;
            }else{
                cout <<"Estado: devuelto" <<endl;
            }
            cout << "----------------------------------------" << endl;
        }
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

string leerLinea(string mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

bool carnetSoloDigitos(string carnet) {
    if (carnet.empty()) {
        return false;
    }
    for (size_t i = 0; i < carnet.length(); i++) {
        if (carnet[i] < '0' || carnet[i] > '9') {
            return false;
        }
    }
    return true;
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
        getline(archivo, listaUsuarios[i].carnet);
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
        archivo >> inventarioLibros[i].unidades_totales;
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
        archivo << inventarioLibros[i].unidades_totales << endl;
        archivo << inventarioLibros[i].unidades_disponible << endl;
    }
    archivo.close();
}

void cargarPrestamos(prestamo prestamosActivos[], int &totalPrestamos, int max_prestamos) {
    ifstream archivo("prestamos.txt");
    if (archivo.is_open() == false) {
        totalPrestamos = 0;
        return;
    }

    archivo >> totalPrestamos;
    if (totalPrestamos > max_prestamos) {
        totalPrestamos = max_prestamos;
    }

    int estadoActivo = 0;
    archivo.ignore();
    for (int i = 0; i < totalPrestamos; i++) {
        archivo >> prestamosActivos[i].id;
        archivo.ignore();
        getline(archivo, prestamosActivos[i].carnet);
        archivo >> prestamosActivos[i].libro;
        archivo >> estadoActivo;
        archivo.ignore();
        prestamosActivos[i].activo = (estadoActivo == 1);
    }
    archivo.close();
}

void guardarPrestamos(prestamo prestamosActivos[], int totalPrestamos) {
    ofstream archivo("prestamos.txt");
    if (archivo.is_open() == false) {
        cout << "Error: no se pudo guardar el archivo de prestamos." << endl;
        return;
    }

    archivo << totalPrestamos << endl;
    for (int i = 0; i < totalPrestamos; i++) {
        archivo << prestamosActivos[i].id << endl;
        archivo << prestamosActivos[i].carnet << endl;
        archivo << prestamosActivos[i].libro << endl;
        archivo << (prestamosActivos[i].activo ? 1 : 0) << endl;
    }
    archivo.close();
}


