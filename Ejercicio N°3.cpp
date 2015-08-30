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


typedef struct Cliente
{
  int dni;
  cadena apellido;
  cadena nombre;      
  int poliza;
  float montoAsegurado;
  cadena ciudad;
} Cliente;




void cargarUnCliente(Cliente &regi)
{
  int tipoDePoliza = -1;   
     
  printf("\n------------- ");
  printf("\nNuevo Cliente ");
  printf("\nDNI: ");
  _flushall();
  scanf("%d", &regi.dni);

  printf("\nApellido: ");
  _flushall();
  gets(regi.apellido);


  printf("\nNombre: ");
  _flushall();
  gets(regi.nombre);


  do 
  {
      printf("\nPoliza (0 a 4): ");
      _flushall();
      scanf("%d", &tipoDePoliza);
  }
  while ( ( tipoDePoliza < 0 ) || ( tipoDePoliza > 4) );

  regi.poliza = tipoDePoliza; 

  printf("\nMonto: ");
  _flushall();
  scanf("%f", &regi.montoAsegurado);


  printf("\nCiudad: ");
  _flushall();
  gets(regi.ciudad);
  
  printf("\n------------- ");
     
}




void cargarClientes(FILE * archivo)
{
     char res;
     Cliente registro;
     
     do 
     {
        cargarUnCliente(registro);
        
        fwrite(&registro, sizeof(registro), 1, archivo);
        
        printf("\n Otro cliente? (S/N): ");
        _flushall();
        scanf("%c", &res);     
     }
     while (res != 'N');
     
}



void generarVectorPolizas(FILE * archivo, Cliente v[], int &N)
{
   int i = 0;
     
   Cliente regi;  
   
   rewind(archivo);
   
   fread(&regi, sizeof(Cliente), 1, archivo);
   
   while ( !feof(archivo) )
   {
      if ( regi.montoAsegurado > 400 )
      {
        v[i] = regi;
        i++;     
      }     
         
      fread(&regi, sizeof(Cliente), 1, archivo);
         
   }
   
   N = i;
     
}




void listarVector (int N, Cliente v[])
{
  int i=0;
  
  
  for (i=0; i<N; i++)
  {
    printf("\n%s", v[i].apellido);  
  }   
  
}



int frecuenciaMayor(FILE * archivo)
{
   int v[5] = {0};
   int fmax = -10;
   int i=0;
   
   Cliente regi;
  
   rewind(archivo);
   
   fread(&regi, sizeof(Cliente), 1, archivo);
   while ( !feof(archivo) )
   {
         
     //opcion 1
     /*
     if (regi.poliza == 0) 
     {
       v[0] = v[0] + 1;              
     }
         
     if (regi.poliza == 1) 
     {
       v[1] = v[1] + 1;              
     }

     if (regi.poliza == 2) 
     {
       v[2] = v[2] + 1;              
     }

     if (regi.poliza == 3) 
     {
       v[3] = v[3] + 1;              
     }

     if (regi.poliza == 4) 
     {
       v[4] = v[4] + 1;              
     }
     */
     
     // opcion 2
     switch ( regi.poliza )
     {
       case 0: { v[0] = v[0] + 1; break; }     
       case 1: { v[1] = v[1] + 1; break; }     
       case 2: { v[2] = v[2] + 1; break; }     
       case 3: { v[3] = v[3] + 1; break; }     
       case 4: { v[4] = v[4] + 1; break; }     
     };
     
     // opcion 3
     
     // v[regi.poliza]++;
         
     fread(&regi, sizeof(Cliente), 1, archivo);
   }


   // frecuencia maxima
   for (i=0; i<5; i++)
   {
      if ( v[i] > fmax )
      {
           fmax = v[i];
      } 
       
   } // for  
   
   return fmax;
    
}



void deArchivoAMatriz(FILE *archivo, float m[][5])
{
   int f0=0, f1=0, f2=0, f3=0, f4=0; 
   
   Cliente regi;
   
   rewind (archivo);
   
   
   fread(&regi, sizeof(Cliente), 1, archivo);
   
   while (!feof(archivo))
   {
     
     
     switch ( regi.poliza )
     {
           case 0:
                {  
                   m[f0][0] = regi.montoAsegurado;
                   f0++;
                          
                   break;         
                }; 
                
           case 1:
                {
                   m[f1][1] = regi.montoAsegurado;
                   f1++;
                          
                   break;         
                }; 
                
           case 2:
                {
                   m[f2][2] = regi.montoAsegurado;
                   f2++;
                          
                   break;         
                }; 
                
           case 3:
                {
                   m[f3][3] = regi.montoAsegurado;
                   f3++;
                          
                   break;         
                }; 
                
           case 4:
                {
                   m[f4][4] = regi.montoAsegurado;
                   f4++;
                          
                   break;         
                }; 
     }
     
         
         
     fread(&regi, sizeof(Cliente), 1, archivo);
   }
   
   
   
     
}



void iniciarMatriz(int filas, float m[][5])
{
   int i,j;
   
   
   for (i=0; i<filas; i++)
   {
       for (j=0; j<5; j++)
       {
           
           m[i][j]=0.0;
           
       } // columnas
       
   } // filas
     
     
}




void mostrarMatriz(int filas, float m[][5])
{
   int i,j;
   
   
   for (i=0; i<filas; i++)
   {
       for (j=0; j<5; j++)
       {
           
           printf("%.2f\t", m[i][j]);
           
       } // columnas
       
       printf("\n");
       
   } // filas
     
     
}






main()
{
      
   FILE * archi;  

   
   int tamanoRegistro = sizeof(Cliente);
   
   int cantidadRegistros; 
   
   int N = -1;
   
   int filas;
   
  
   system("cls");
   
   archi = fopen("clientes.dat", "w+b");
   
   if (archi == NULL)
   {
     exit(1);        
   }
   
   //TODO aqui va el menu
   
   cargarClientes(archi);
   
   cantidadRegistros = ftell(archi) / tamanoRegistro;
   
   Cliente vec[cantidadRegistros];
   
   
   generarVectorPolizas(archi, vec, N);
   
   listarVector(N, vec);  
   
   
   
   filas = frecuenciaMayor(archi); 

   printf("\n\nFrecuencia Maxima: %d", filas);
   
   printf("\n\n");
   
   float matriz[filas][5];
   
   iniciarMatriz(filas, matriz);
   
   deArchivoAMatriz(archi, matriz);

   
   mostrarMatriz(filas, matriz);

   
   fclose(archi);
   
   printf("\n\n");
   system("pause");   
      
}


