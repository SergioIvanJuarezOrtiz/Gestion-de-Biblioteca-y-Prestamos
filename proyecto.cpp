#include<iostream>
#include<string>
using namespace std;


    const int MAX_USUARIOS = 100;
    const int MAX_LIBROS = 100;

   
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



   



















    

    
    
    









