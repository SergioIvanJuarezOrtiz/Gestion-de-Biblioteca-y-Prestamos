#include<iostream>
#include<string>
using namespace std;


    const int MAX_USUARIOS = 100;
    const int MAX_LIBROS = 100;

   
struct libro{
        int ID=0;
        string Titulo;
        string autor;
        int unidades_disponibles=0;
    
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
    
    usuario listaUsuarios[MAX_USUARIOS];
    int totalUsuarios=0;

    libro inventarioLibros[MAX_LIBROS];
    int totalLibros=0;

   

    void registrarLibro();
    void mostrarInventario();
    
    
    int main(){    

        int opcion = 0;

        






     
        

















        



   



















    

    
    
    









