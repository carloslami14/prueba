/******************************************
* Trabajo Practico N° 7                   *
* Profesor: Montesinos, Rafael            *
* Profesor: Canto, Javier Raúl Alejandro  *
* Nombre: Lami, Carlos Jacobo             *
* Comicion: 1K1                           *
* DNI: 39975776                           *
* Legajo: 42295                           *
*******************************************/

#include <stdlib.h>
#include <stdio.h>

typedef char cadena[50];

typedef char cadena200[200];

struct Paciente
{
  int nhc;     
  cadena nombre;      
  int edad;
  char sexo;
  cadena200 diagnostico;
};


void cargarArchivo(FILE * archivo)
{
  char seguir;
  Paciente regi;
  
  fseek(archivo, 0, SEEK_END);
  
  do 
  {
    system("cls");     
    printf("NHC: ");
    _flushall();
    scanf("%d", &regi.nhc);
    
    printf("\nNombre: ");
    _flushall();
    gets(regi.nombre);
    
    printf("\nEdad: ");
    _flushall();
    scanf("%d", &regi.edad);
    
    printf("\nSexo: ");
    _flushall();
    scanf("%c", &regi.sexo);
    
    printf("\nDiagnostico: ");
    _flushall();
    gets(regi.diagnostico);
    
    fwrite(&regi, sizeof(regi), 1, archivo);
    
    printf("\n");
    printf("\nIngresar otro paciente? (S/N)");
    _flushall();
    scanf("%c", &seguir);
    
       
  } while (seguir == 'S' || seguir == 's');   
     
     
} // cargarArchivo



void listarArchivo (FILE * archivo)
{
   Paciente regi;
   
   rewind(archivo);
   
   fread(&regi, sizeof(regi), 1, archivo);
   
   while ( !feof(archivo) )
   {

     printf("\n----------\n"); 
     printf("NHC: %d", regi.nhc); 
     printf("\nNombre: %s", regi.nombre);
     printf("\nEdad: %d", regi.edad);
     printf("\nSexo: %c", regi.sexo);
     printf("\nDiagnostico: %s", regi.diagnostico);
     printf("\n----------\n\n"); 

      
     fread(&regi, sizeof(regi), 1, archivo);
     
   } // while
        
}



void listarMujeres (FILE * archivo)
{
   Paciente regi;
   
   rewind(archivo);
   
   fread(&regi, sizeof(regi), 1, archivo);
   
   while ( !feof(archivo) )
   {
     if ( regi.sexo == 'F' )
     {
         printf("\n----------\n"); 
         printf("NHC: %d", regi.nhc); 
         printf("\nNombre: %s", regi.nombre);
         printf("\nEdad: %d", regi.edad);
         printf("\nSexo: %c", regi.sexo);
         printf("\nDiagnostico: %s", regi.diagnostico);
         printf("\n----------\n\n"); 
     }

      
     fread(&regi, sizeof(regi), 1, archivo);
     
   } // while
        
}



void listarPacientesMayores (FILE * archivo)
{
   int mayorEdad = 0;
     
   Paciente regi;
   
   rewind(archivo);
   
   fread(&regi, sizeof(regi), 1, archivo);
   
   while ( !feof(archivo) )
   {
         
     if (regi.edad > mayorEdad)
     {
       mayorEdad = regi.edad;            
     }   
     
     fread(&regi, sizeof(regi), 1, archivo);
     
   } // while
   
   
   // segundo recorrido 
   
   rewind(archivo);
   
   fread(&regi, sizeof(regi), 1, archivo);
   
   while ( !feof(archivo) )
   {
   
       if ( regi.edad == mayorEdad )
       {        
         printf("\n----------\n"); 
         printf("\nNombre: %s", regi.nombre);
         printf("\nEdad: %d", regi.edad);
         printf("\nDiagnostico: %s", regi.diagnostico);
         printf("\n----------\n\n"); 
       } 
      fread(&regi, sizeof(regi), 1, archivo);
   }
   
   
   
   
   
   
   
        
}








int contarVarones20 (FILE * archivo)
{
   int c = 0;
    
   Paciente regi;
   
   rewind(archivo);
   
   fread(&regi, sizeof(regi), 1, archivo);
   
   while ( !feof(archivo) )
   {
     
     if ( (regi.edad > 20) && (regi.sexo == 'M') )
     {
       c++; 
     }  
      
     fread(&regi, sizeof(regi), 1, archivo);
     
   } // while
        
   return ( c );     
        
}






main()
{
   int varones;   
      
   FILE * archi;
   
   archi = fopen("paciente.dat", "w+b");
      
   if (archi == NULL)
   {
     exit(1);        
   }   
      
   system("cls");
   
   cargarArchivo(archi);
   
   printf("\n\n");
   system("pause");
   

   listarArchivo(archi);   
   
   printf("\n\n");
   system("pause");
   
   varones = contarVarones20(archi);
   printf("\nHay %d varones mayores de 20.", varones);


   printf("\n\n");
   system("pause");
   listarMujeres(archi);   

   printf("\n\n");
   system("pause");
   
   listarPacientesMayores(archi);   
   
   fclose(archi);
   
   printf("\n\n");
   system("pause");
      
}
