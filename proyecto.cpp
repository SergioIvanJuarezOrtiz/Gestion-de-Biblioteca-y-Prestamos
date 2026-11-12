#include<iostream>
#include<string>
using namespace std;


    const int MAX_USUARIOS = 100;
    const int MAX_LIBROS = 100;

   
struct libro{
<<<<<<< HEAD
        int ID=0;
        string Titulo;
        string autor;
        int unidades_disponibles=0;
=======

        int ID=0;
        string Titulo;
        string autor;
        int unidades_disponibles;
>>>>>>> 209014de720a7baa592e851c738142371957dc55
    
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

<<<<<<< HEAD
    }; 
    
    usuario listaUsuarios[MAX_USUARIOS];
    int totalUsuarios=0;

    libro inventarioLibros[MAX_LIBROS];
    int totalLibros=0;

   
=======
    };

    libro inventario_libro[MAX_LIBROS];
    int total_libros=0;

    usuario lista_usuarios[MAX_USUARIOS];
    int total_usuarios=0;
>>>>>>> 209014de720a7baa592e851c738142371957dc55

    void registrarLibro();
    void mostrarInventario();
    
    
<<<<<<< HEAD
    int main(){    

        int opcion = 0;

        






     
        

















        
=======
    int main(){
>>>>>>> 209014de720a7baa592e851c738142371957dc55



   



















    

    
    
    









