#include<iostream>
#include<string>
using namespace std;


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
    string contrasena;
};
struct prestamo{
    string carnet_usuario;
    string id_prestamo;
    string id_libro;
    bool activo;
};

// Declaración de funciones
void registrarLibro(libro inventarioLibros[], int &totalLibros, int max_libros);
void mostrarInventario(libro inventarioLibros[], int totalLibros); 
void buscarLibro(libro inventarioLibros[], int totalLibros);       
void registrarUsuario(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios);
void prestarLibro(libro inventarioLibros[], int totalLibros);
void devolverLibro(libro inventarioLibros[], int totalLibros);
void mostrarUsuarios(usuario listaUsuarios[], int totalUsuarios);
void mostrarIntegrantes();
// Función para iniciar sesión
int iniciarSesion(usuario listaUsuarios[], int totalUsuarios);

int main() {
    int max_usuarios = 100;
    int max_libros = 100;

    usuario listaUsuarios[100];
    int totalUsuarios = 0;

    libro inventarioLibros[100];
    int totalLibros=0;

    bool sistemaActivo = true; // Variable maestra para mantener el programa encendido
    
    // Bucle principal del sistema
    while (sistemaActivo) {
        
        int rolActual = 0; // 0 = No logueado, 1 = Admin, 2 = Usuario normal
        
        // Bucle de Login
        while (rolActual == 0) {
            rolActual = iniciarSesion(listaUsuarios, totalUsuarios);
            
            if (rolActual == 0) {
                cout << "Error: Credenciales incorrectas. Intente nuevamente." << endl;
            } else if (rolActual == -1) {
                cout << "Apagando el sistema..." << endl;
                sistemaActivo = false;
                break; // Rompe el bucle de login
            }
        }
    // Si se apaga el sistema desde el login, evitamos entrar al menú
    if (!sistemaActivo) {
        break; 
    }

    // Bucle del menú
        int opcion = -1;
    while (rolActual != 0 && sistemaActivo) {
            cout << "\n=====Bienvenido al sistema de biblioteca y prestamos===== " << endl;
            cout << "Rol actual: " << (rolActual == 1 ? "Administrador" : "Estudiante") << endl;
            cout << "Seleccione una opcion del menu:" << endl;
            cout << "1. Registrar Libro "<<endl;
            cout << "2. Mostrar Inventario " <<endl;
            cout << "3. Buscar Libro (Titulo o ID) " <<endl;
            cout << "4. Registrar Usuario " <<endl;
            cout << "5. Prestar Libro " <<endl;
            cout << "6. Delvolver Libro " <<endl;
            cout << "7. Mostrar Usuarios " <<endl;
            cout << "8. Mostrar Integrantes "<<endl;
            cout << "9. Cerrar Sesion (Volver al Login) "<<endl;
            cout << "0. Salir del programa completamente "<<endl;
            cout <<"Ingrese su opcion: ";
            cin >> opcion;

            switch(opcion){
                case 1: registrarLibro(inventarioLibros, totalLibros, max_libros); break;
                case 2: mostrarInventario(inventarioLibros, totalLibros); break;
                case 3: buscarLibro(inventarioLibros, totalLibros); break;
                case 4: registrarUsuario(listaUsuarios, totalUsuarios, max_usuarios); break;
                case 5: prestarLibro(inventarioLibros, totalLibros); break;
                case 6: devolverLibro(inventarioLibros, totalLibros); break;
                case 7: mostrarUsuarios(listaUsuarios, totalUsuarios); break;
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
int iniciarSesion(usuario listaUsuarios[], int totalUsuarios) {
    string user, pass;
    cout << "\n=== INICIO DE SESION ===" << endl;
    cout << "Usuario (Carnet, 'admin' o escriba 'salir' para apagar): ";
    cin >> user;
    
    //validación para salir del programa
    if (user == "salir" || user == "Salir" || user == "SALIR") {
        return -1; //señal de apagado general
    }
    
    cout << "Contraseña: ";
    cin >> pass;

    // Validación para el Administrador
    if (user == "admin" && pass == "1234") {
        return 1; //Rol Administrador
    }

    // Validación para los Estudiantes usando su contraseña real
    for (int i = 0; i < totalUsuarios; i++) {
        if (listaUsuarios[i].carnet == user && listaUsuarios[i].contrasena == pass) {
            return 2; //Rol Usuario normal
        }
    }
    return 0; //Credenciales incorrectas
}

// Módulo de Registro de Usuarios
void registrarUsuario(usuario listaUsuarios[], int &totalUsuarios, int max_usuarios ) {
    // if-else para controlar que no se exceda el límite de usuarios
    if (totalUsuarios < max_usuarios) {
        cout << "\n--- Registro de Nuevo Usuario ---" << endl;
        
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
            
            // Limpia el salto de línea residual en el buffer de entrada
            cin.ignore(); 
            
            cout << "Ingrese la facultad: ";
            // Permite capturar la cadena completa con espacios
            getline(cin, listaUsuarios[totalUsuarios].Facultad);
            
            totalUsuarios++;
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
        cout <<"=====Registro de nuevo libro====" <<endl;
        
        cin.ignore();
    
        cout <<"Ingrese el Titulo del libro: ";
        getline(cin, inventarioLibros[totalLibros].Titulo); 

        cout <<"Ingrese el Autor del libro: ";
        getline(cin, inventarioLibros[totalLibros].autor);

        cout <<"Ingrese las unidades disponibles: ";
        cin >> inventarioLibros[totalLibros].unidades_disponible;

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

        cout<<"========inventario de libros=========" <<endl;

        //mostrar los libros registrados
        for(int i = 0; i <totalLibros; i++){
            cout <<"ID: " <<inventarioLibros[i].ID <<endl;
            cout <<"Titulo: " <<inventarioLibros[i].Titulo <<endl;
            cout <<"autor: " <<inventarioLibros[i]. autor <<endl;
            cout <<"unidades: " <<inventarioLibros[i]. unidades_disponible <<endl;
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
void prestarLibro(libro inventarioLibros[], int totalLibros) {
    cout << "\n--- Modulo de Prestamos ---" << endl;
    int idBuscar;
    cout << "Ingrese el ID del libro que desea prestar: ";
    cin >> idBuscar;

    bool libroEncontrado = false;
    
    for (int i = 0; i < totalLibros; i++) {
        if (inventarioLibros[i].ID == idBuscar) {
            libroEncontrado = true;
            
            if (inventarioLibros[i].unidades_disponible > 0) {
                inventarioLibros[i].unidades_disponible--;
                cout << "Prestamo realizado con exito. Disfrute su lectura." << endl;
            } else {
                cout << "Error: No hay unidades disponibles." << endl;
            }
        }
    }

    if (libroEncontrado == false) {
        cout << "Error: El libro no existe." << endl;
    }
}

// Módulo de Devoluciones
void devolverLibro(libro inventarioLibros[], int totalLibros) {
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
void mostrarUsuarios(usuario listaUsuarios[], int totalUsuarios) {
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


