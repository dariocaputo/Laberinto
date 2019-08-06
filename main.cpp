#include <iostream>
#include <windows.h>
#include <thread>
#include <string>
#include <stdlib.h>
#include <mutex>
#include <conio.h>
#include <fstream>
#include <locale.h>
#include <conio.h>

using namespace std;

bool resultado1;
bool resultado2;

int puntaje1 = 0;
int puntaje2 = 0;

int MAXFIL, MAXCOL;

int fil_salida1, col_salida1;
int fil_salida2, col_salida2;

int fil_llegada, col_llegada;

mutex m;


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void ColocarPortal(int** mat,int contador)
{

     int fila,columna;

    if(contador==2)
     {
         return;
     }

            srand(time(NULL));

            do
            {

                  fila = rand() % MAXFIL;//de 0 a MAXFIL-1
                   columna = rand() % MAXCOL;//de 0 a MAXCOL-1


            }while (mat[fila][columna] != 0);

            mat[fila][columna] = 6;//Coloca la trampa que vuelve al origen
            contador++;

         ColocarPortal(mat,contador);

}

void ColocarFreeze(int** mat,int contador)
{

      int fila,columna;

    if(contador==2)
     {
         return;
     }

        srand(time(NULL));
            do
            {

                   fila = rand() % MAXFIL;//de 0 a MAXFIL-1
                   columna = rand() % MAXCOL;//de 0 a MAXCOL-1

            }while (mat[fila][columna] != 0);

            mat[fila][columna] = -2;//Coloca la trampa de hielo
            contador++;

         ColocarFreeze(mat,contador);

}

void ColocarPuntos(int** mat,int contador)
{

     int fila,columna;
      int rdm;

     if(contador==4)
     {
         return;
     }

        srand(time(NULL));

            do
            {

                   fila = rand() % MAXFIL;//de 0 a MAXFIL-1
                   columna = rand() % MAXCOL;//de 0 a MAXCOL-1


            }while (mat[fila][columna] != 0);

            rdm= (1+(rand() % 5));//entre 1 y 5
            mat[fila][columna] = rdm;
            contador++;

      ColocarPuntos(mat,contador);

}


int** CargarMatriz(char opcion)
{
     int** matrizAux;
     string nombreArchivo;

     if(opcion == '1')
     {
         nombreArchivo = "matrix1";
         nombreArchivo += ".txt";
     }
     else if(opcion == '2')
     {
        nombreArchivo = "matrix2";
        nombreArchivo += ".txt";
     }
     else if(opcion == '3')
    {
        nombreArchivo = "matrix3";
        nombreArchivo += ".txt";

     }

    ifstream archivo(nombreArchivo);

   if(archivo.fail())
   {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
       cout<<"No se pudo abrir el archivo"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);

       exit (EXIT_FAILURE);
   }
   else
   {
       archivo >>  MAXFIL >> MAXCOL ;

        matrizAux = new int *[MAXFIL];
        for(int i = 0; i < MAXFIL; i++)
        {
            matrizAux[i] = new int[MAXCOL];
        }


        for (int i = 0; i <  MAXFIL; i++)
        {
            for (int j = 0; j <  MAXCOL ; j++)
            {
                archivo >> matrizAux[i][j];

            }
        }

     archivo >> fil_salida1 >> col_salida1 >> fil_salida2 >> col_salida2;
     archivo >> fil_llegada >> col_llegada;
   }
      ColocarPortal(matrizAux,0);
      ColocarFreeze(matrizAux,0);
      ColocarPuntos(matrizAux,0);

      archivo.close();
      system("cls");
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);
     cout<<"¡Carga exitosa!"<<endl;
     cout<<"Aguarde un momento..."<<endl;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |  FOREGROUND_RED |  FOREGROUND_BLUE |  FOREGROUND_INTENSITY);
      Sleep(3000);
     system("cls");

 return matrizAux;

}

void ImprimirMatriz(int** mat)
{

 ShowConsoleCursor(false);

    for(int i = 0; i < MAXFIL; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
           switch(mat[i][j])
           {
              case 9://jugador 1
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                  cout<<mat[i][j]<<" ";
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
              break;

              case 8://jugador 2
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                  cout<<mat[i][j]<<" ";
                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
              break;

              case 7://pared
                   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                   cout<<"#"<<" ";
                   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
              break;

              case 0://libre
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                    cout<<"."<<" ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
              break;

              case -2://freeze
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 11);
                    cout<<"F"<<" ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
              break;

              case 6://vuelve al origen
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 11);
                     cout<<"O"<<" ";
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
              break;

              default:
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | 14);
                    cout<<mat[i][j]<<" ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
                  break;

           }

        }
            cout << endl;
    }

}

void Congelar(int** laberinto, int fil, int col, int id)
{
        if(laberinto[fil][col]==-2 && id==9)
        {
            laberinto[fil][col] = id;
            ImprimirMatriz(laberinto);
            laberinto[fil][col] = 0;
            cout <<"\nJugador 1 se congela 3 segundos..."<<endl;
            PlaySound(TEXT("freeze.wav"), NULL, SND_SYNC);
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            system("cls");
        }
        else if(laberinto[fil][col]==-2 && id==8)
        {
            laberinto[fil][col] = id;
            ImprimirMatriz(laberinto);
            laberinto[fil][col] = 0;
            cout <<"\nJugador 2 se congela 3 segundos..."<<endl;
            PlaySound(TEXT("freeze.wav"), NULL, SND_SYNC);
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            system("cls");
        }

}

void VolverAOrigen(int** laberinto, int& fil, int& col, int id)
{

        if(laberinto[fil][col]==6 && id==9)
        {
            laberinto[fil][col] = id;
            ImprimirMatriz(laberinto);
            laberinto[fil][col] = 0;
            fil = fil_salida1;
            col = col_salida1;
            cout <<"\nJugador 1 vuelve al origen..."<<endl;
            PlaySound(TEXT("volverInicio.wav"), NULL, SND_SYNC);
            Sleep(800);
            system("cls");


        }
        else if(laberinto[fil][col]==6 && id==8)
        {
            laberinto[fil][col] = id;
            ImprimirMatriz(laberinto);
            laberinto[fil][col] = 0;
            fil = fil_salida2;
            col = col_salida2;
            cout <<"\nJugador 2 vuelve al origen..."<<endl;
            PlaySound(TEXT("volverInicio.wav"), NULL, SND_SYNC);
            Sleep(800);
            system("cls");
        }

}

void RecogerPunto(int** laberinto,int fil, int col,int& puntaje,int id)
{
       int ptos;

        if((laberinto[fil][col]>=1 && laberinto[fil][col]<=5) && id==9)
        {
            ptos = laberinto[fil][col];
            puntaje += laberinto[fil][col];
            laberinto[fil][col] = id;
            ImprimirMatriz(laberinto);
            cout <<"\n¡Jugador 1 recogió " << ptos <<" puntos!" <<endl;
            laberinto[fil][col] = 0;
            PlaySound(TEXT("punto.wav"), NULL, SND_SYNC);
            system("cls");

        }
        else if((laberinto[fil][col]>=1 && laberinto[fil][col]<=5) && id==8)
        {
            ptos = laberinto[fil][col];
            puntaje += laberinto[fil][col];
            laberinto[fil][col] = id;
            ImprimirMatriz(laberinto);
            cout <<"\n¡Jugador 2 recogió " << ptos <<" puntos!" <<endl;
            laberinto[fil][col] = 0;
            PlaySound(TEXT("punto.wav"), NULL, SND_SYNC);
            system("cls");

        }
}

bool Avanzar(int** laberinto,int fil, int col,int& puntaje,int facing,int id)
{

      m.lock();
      bool exito = false;
     Congelar(laberinto,fil,col,id);
     VolverAOrigen(laberinto,fil,col,id);
     RecogerPunto(laberinto,fil,col,puntaje,id);

        laberinto[fil][col] = id;
        ImprimirMatriz(laberinto);
           laberinto[fil][col] = 0;

           cout << "\nPuntaje 1: " << puntaje1;
           cout << "\nPuntaje 2: " << puntaje2<<endl;

          Sleep(100);
            system("cls");

                        if(fil == fil_llegada && col == col_llegada)
                        {
                            laberinto[fil][col] = id;
                            exito = true;
                        }
                        else if(facing == 0)//si mira arriba
                        {

                            if((col+1>=0 && col+1<=MAXCOL-1) && ((laberinto[fil][col+1] >= 0 && laberinto[fil][col+1]<=5) || laberinto[fil][col+1]==-2 || laberinto[fil][col+1]==6))//chequea si se puede mover a la derecha
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil,col+1,puntaje,1,id);//mueve a la derecha

                            }
                            else if((fil-1>=0 && fil-1<=MAXFIL-1) && ((laberinto[fil-1][col] >= 0 && laberinto[fil-1][col] <= 5) || laberinto[fil-1][col]==-2 || laberinto[fil-1][col]==6))
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil-1,col,puntaje,0,id);//mueve arriba

                            }
                            else if((col-1>=0 && col-1<=MAXCOL-1) && ((laberinto[fil][col-1] >= 0 && laberinto[fil][col-1] <= 5) || laberinto[fil][col-1]==-2 || laberinto[fil][col-1]==6))
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil,col-1,puntaje,3,id);//mueve izquierda

                            }
                            else//si no hay adonde ir
                            {
                                 m.unlock();
                                exito = Avanzar(laberinto,fil+1,col,puntaje,2,id);//REGRESA abajo
                            }

                        }
                        else if(facing == 1)//si mira a la derecha
                        {

                            if((fil+1>=0 && fil+1<=MAXFIL-1) && ((laberinto[fil+1][col] >= 0 && laberinto[fil+1][col]<=5) || laberinto[fil+1][col]==-2 || laberinto[fil+1][col]==6))//chequea si se puede mover abajo
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil+1,col,puntaje,2,id);//mueve abajo

                            }
                            else if((col+1>=0 && col+1<=MAXCOL-1) && ((laberinto[fil][col+1] >= 0 && laberinto[fil][col+1] <= 5) || laberinto[fil][col+1]==-2 || laberinto[fil][col+1]==6))
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil,col+1,puntaje,1,id);//mueve a la derecha

                            }
                            else if((fil-1>=0 && fil-1<=MAXFIL-1) && ((laberinto[fil-1][col] >= 0 && laberinto[fil-1][col] <= 5) || laberinto[fil-1][col]==-2 || laberinto[fil-1][col]==6))
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil-1,col,puntaje,0,id);//mueve arriba

                            }
                            else//si no hay adonde ir
                            {
                                 m.unlock();
                                exito = Avanzar(laberinto,fil,col-1,puntaje,3,id);//REGRESA a izquierda
                            }

                        }
                        else if(facing == 2)//si mira abajo
                        {
                            if((col-1>=0 && col-1<=MAXCOL-1) && ((laberinto[fil][col-1] >= 0 && laberinto[fil][col-1]<=5) || laberinto[fil][col-1]==-2 || laberinto[fil][col-1]==6))//chequea si se puede mover a izquierda
                            {
                                m.unlock();
                                exito = Avanzar(laberinto,fil,col-1,puntaje,3,id);//mueve a izquierda

                            }
                            else if((fil+1>=0 && fil+1<=MAXFIL-1) && ((laberinto[fil+1][col] >= 0 && laberinto[fil+1][col] <= 5) || laberinto[fil+1][col]==-2 || laberinto[fil+1][col]== 6))
                            {
                                m.unlock();
                                exito = Avanzar(laberinto,fil+1,col,puntaje,2,id);//mueve abajo

                            }
                            else if((col+1>=0 && col+1<=MAXCOL-1) && ((laberinto[fil][col+1] >= 0 && laberinto[fil][col+1] <= 5) || laberinto[fil][col+1]==-2 || laberinto[fil][col+1]== 6))
                            {
                                    m.unlock();
                                    exito = Avanzar(laberinto,fil,col+1,puntaje,1,id);//mueve derecha

                            }
                            else//si no hay adonde ir
                            {
                                 m.unlock();
                                exito = Avanzar(laberinto,fil-1,col,puntaje,0,id);//REGRESA arriba
                            }

                        }
                        else if(facing == 3)//si mira a la izquierda
                        {

                            if((fil-1>=0 && fil-1<=MAXFIL-1) && ((laberinto[fil-1][col] >= 0 && laberinto[fil-1][col]<=5) || laberinto[fil-1][col]==-2 || laberinto[fil-1][col]==6))//chequea si se puede mover arriba
                            {
                                             m.unlock();
                                            exito = Avanzar(laberinto,fil-1,col,puntaje1,0,id);//mueve arriba

                            }
                            else if((col-1>=0 && col-1<=MAXCOL-1) && ((laberinto[fil][col-1] >= 0 && laberinto[fil][col-1] <= 5) || laberinto[fil][col-1]==-2 || laberinto[fil][col-1]==6))
                            {
                                             m.unlock();
                                            exito = Avanzar(laberinto,fil,col-1,puntaje,3,id);//mueve izquierda

                            }
                            else if((fil+1>=0 && fil+1<=MAXFIL-1) && ((laberinto[fil+1][col] >= 0 && laberinto[fil+1][col] <= 5) || laberinto[fil+1][col]==-2 || laberinto[fil+1][col]==6))
                            {
                                         m.unlock();
                                        exito = Avanzar(laberinto,fil+1,col,puntaje,2,id);//mueve abajo

                            }
                            else//si no hay adonde ir
                            {
                                 m.unlock();
                                exito = Avanzar(laberinto,fil,col+1,puntaje,1,id);//REGRESA a derecha

                            }

                        }
    return exito;
}

void LiberarMemoria(int** mat)
{
    for (int i = 0; i < MAXFIL; i++)
    {
       delete[] mat[i];
    }
    delete[]mat;
}

void DeterminarGanador(int** mat,bool resultado1,bool resultado2)
{
            if(resultado1)
            {
                 ImprimirMatriz(mat);
                 cout<<"\n¡Felicitaciones, jugador 1 ha encontrado la salida!"<<endl;


            }
            else if(resultado2)
            {
                 ImprimirMatriz(mat);
                 cout<<"\n¡Felicitaciones, jugador 2 ha encontrado la salida!"<<endl;


            }
            else if(resultado1 && resultado2)
            {
                 ImprimirMatriz(mat);
                 cout<<"\n¡Ambos jugadores lograron salir pero...!"<<endl;
                 Sleep(3000);
                 if(puntaje1>puntaje2)
                 {
                     cout<<"\n¡Gana Jugador 1 por mayor puntaje!"<<endl;
                 }
                 else if(puntaje1<puntaje2)
                 {
                       cout<<"\n¡Gana Jugador 2 por mayor puntaje!"<<endl;
                 }
                 else
                 {
                     cout<<"\n¡Empate!"<<endl;
                     cout<<"\nAmbos tienen el mismo puntaje"<<endl;
                 }


            }

     PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
      cout << "\nPuntaje total jugador 1: " << puntaje1<<endl;
      cout << "Puntaje total jugador 2: " << puntaje2<<endl;
}

void Turno(int** mat,int jugador)
{

    if(jugador == 1)
    {
         resultado1 = Avanzar(mat,fil_salida1,col_salida1,puntaje1,2,9);
     }
    else
     {
         resultado2 = Avanzar(mat,fil_salida2,col_salida2,puntaje2,1,8);

     }

    DeterminarGanador(mat,resultado1,resultado2);

    LiberarMemoria(mat);

  exit(0);

}


void ChequearOpcion(char& opcion)
{
     while(opcion!='1' && opcion!='2' && opcion!='3')
     {
        system("cls");

         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "Solo puede elegir 1, 2 o 3!!! Reingrese..."<<endl<<endl;
         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
        PlaySound(TEXT("fail.wav"), NULL, SND_SYNC);
         cout << "1) 10x10 " << endl;
         cout << "2) 12x12 " << endl;
         cout << "3) 15x15 " << endl;
         opcion = getch();
     }
}


int main()
{
        setlocale(LC_CTYPE, "Spanish");

        int** mat;
        char opcion;
       cout << "***BIENVENIDO A LABERINTO***" << endl << endl;

    cout<<"+-----------------------------------+"<<endl;
    cout<<"| Elija un tamaño:                  |"<<endl;
    cout<<"|                                   |"<<endl;
    cout<<"| 1) 10x10                          |"<<endl;
    cout<<"| 2) 12x12                          |"<<endl;
    cout<<"| 3) 15x15                          |"<<endl;
    cout<<"|                                   |"<<endl;
    cout<<"+-----------------------------------+"<<endl;

      opcion = getch();

        ChequearOpcion(opcion);

        switch(opcion)
        {
              case '1':
                   mat = CargarMatriz(opcion);
              break;

              case '2':
                    mat = CargarMatriz(opcion);
              break;

              case '3':
                  mat = CargarMatriz(opcion);
              break;
        }


	thread hilo_1(Turno,mat,1);
    thread hilo_2(Turno,mat,2);
    hilo_1.join();
    hilo_2.join();

   return 0;
}
