#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//declaracion de constantes
#define arr_x 10
#define arr_y 10
#define MAX_NUM_DESC 100
const char rutaMatriz[] = "matriz.txt";//creo una constante que lleva la ruta del archivo a leer (el asterisco dice que es un puntero)
const char  buscador='1', objeto='3', nada='0', escondidos='2';
const int FALSE=0, TRUE=1;
//declaracion de variables
char matrix[arr_x][arr_y];//declaro la matriz
typedef struct _enc{
    int coo_X;
    int coo_Y;
    struct _enc *sig;
} encontrados;

typedef encontrados *pNodo;
typedef encontrados *Lista;

Lista lis;

//declaracion de funciones
void LlenaMartiz();
void BuscaDiagonal(int, int);
void BuscaRecto(int, int);
void Insertar(Lista *, int, int);
int ListaVacia(Lista);
void MostrarLista(Lista);
void IniDesc(int, int);
void Descomponer(int, int, int, int);
int desc[MAX_NUM_DESC];

int main(){
    int i,j,p_x,p_y,entro=FALSE,cuenta=0,num;
    lis = NULL;
    //char *num=NULL;

    //num = (char *) malloc(sizeof(int)* 4);

    printf("###################Escondidas###################\n");

    LlenaMartiz();

    for(i=0;i<arr_x;i++){
        for(j=0;j<arr_y;j++){
            printf("%c\t", matrix[i][j]);
            if(matrix[i][j] == buscador){
                p_x = i;
                p_y = j;

                entro = TRUE;
                cuenta++;
            }
        }

        printf("\n");
    }

    if(entro){
        if(cuenta == 1){
            BuscaRecto(p_x, p_y);
            BuscaDiagonal(p_x, p_y);
            MostrarLista(lis);
        }else{
            printf("muchos quieren contar\n");
        }
    }else{
        printf("Nadie quiere contar\n");
    }

    printf("################################################");

    printf("\n\n#####################descomposicion#############\n");

    printf("\n\nIngrese el numero a descomponer : ");
    scanf("%d", &num);
    
    if(num <= MAX_NUM_DESC){
        IniDesc(num, 0);
        printf("\n");
    }else{
        printf("numero muy grande\n");
    }

    printf("################################################");

    printf("\n\n\n\n>>>>>>>>--------------------------------->by Che-cheX");
}

void LlenaMartiz(){
    char aux[1],datos[1];
    short int i=0,j=0,cont;
    FILE *archivo;//varible de tipo FILE para asignarle el archivo

    archivo = fopen(rutaMatriz,"r");//abro el archivo y se lo asigno a la variable archivo (el r dice que se puede leer solamente)
    /*si el archivo no existe no lo abre*/
    if(archivo != NULL){
        /*si el archivo llega al final sale del while(feof), (el signo de exclamacion niega a la pregunta es un ~q en algebra de bool)*/
        /*el fread lee desde hasta en un archivo y retorna true si los pudo leer y false si hubo algun error, lo que hago es leer solo un caracter del archivo y pregunto si es ture*/
        /*entonces si feof es true es que llego al final del archivo, si lo niego queda en false y fread retorna false si hay un error false y false = false y no hace el while*/
        /*el fread se hace por si hay un error, ej: quedan 9 caracteres por leer en el archivo y se quieren leer 10, como quedan no va ha haber problemaas en este punto, el problema que el cursor no va a saber si es el final del archivo va a apuntar a null y en la siguiente ves que quiera leer va a tirar un error.*/
        while(!feof(archivo) && fread(aux,1,1,archivo)){
            fseek(archivo,-1, SEEK_CUR);//fseek deja el cursor en el lugar especificado del archivo y seek_cur donde esta el archivo, lo que hago es retroceder el cursor 1 caracter por que ya habia leido anteriormente
            fscanf(archivo,"%s",datos);//leo hasta un espacio, salto de linea o un tab

            //realizo esto por que se que es de largo uno, si fuera de mas pisaria los datos en el arreglo
            for(cont=0;cont<strlen(datos);cont++){
                matrix[i][j] = datos[cont];
            }

            //imprimo para saber que viene
            //printf("matriz [%i],[%i],[%c]\n", i,j,matrix[i][j]);

            j++;//avanzo la columna
            if(j == arr_x){//como sabemos que el arrelo es hasta 10 hacemos esto
                i++;//avanzo la fila
                j=0;//devuelvo la columna a 0
            }
        }

        fflush(archivo);//libero de memoria el archivo (puede quedar en el steam)
        fclose(archivo);//lo cierro
    }
}

void BuscaDiagonal(int coo_x, int coo_y){
    int x,y;

    x = coo_x-1;
    y = coo_y-1;
    //busca en -x y +y como si fuera un plano carteciano
    while(x >= 0){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }

        x--;
        y--;
    }

    x = coo_x+1;
    y = coo_y-1;
    //busca en +x y +y como si fuera un plano carteciano
    while(y >= 0){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }

        x++;
        y--;
    }

    x = coo_x-1;
    y = coo_y+1;
    //busca en -x y -y como si fuera un plano carteciano
    while(x >= 0){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }

        x--;
        y++;
    }

    x = coo_x+1;
    y = coo_y+1;
    //busca en +x y +y como si fuera un plano carteciano
    while(y <= 9){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }
        
        x++;
        y++;
    }
}

void BuscaRecto(int coo_x, int coo_y){
    int x,y;

    x = coo_x-1;
    y = coo_y;
    //busca en -x y +y como si fuera un plano carteciano(izquierda)
    while(x >= 0){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }

        x--;
    }

    x = coo_x+1;
    y = coo_y;
    //busca en +x y +y como si fuera un plano carteciano(derecha)
    while(x <= 9){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }

        x++;
    }

    x = coo_x;
    y = coo_y-1;
    //busca en -x y -y como si fuera un plano carteciano(arriba)
    while(y >= 0){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }

        y--;
    }

    x = coo_x;
    y = coo_y+1;
    //busca en +x y +y como si fuera un plano carteciano(abajo)
    while(y <= 9){
        if(matrix[x][y] == escondidos){
            Insertar(&lis,x,y);
        }

        if(matrix[x][y] == objeto){
            break;
        }
        
        y++;
    }
}

void Insertar(Lista *lista, int cx, int cy){
   pNodo nuevo, anterior;

   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(encontrados));
   nuevo->coo_X = cx;
   nuevo->coo_Y = cy;

   /* Si la lista está vacía */
   if(ListaVacia(*lista)){
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->sig = *lista;
      /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
      *lista = nuevo;
   }else{
      /* Buscar el nodo de valor menor a v */
      anterior = *lista;
      /* Avanzamos hasta el último elemento o hasta que el siguiente tenga un valor mayor que v */
      while(anterior->sig)
         anterior = anterior->sig;
      /* Insertamos el nuevo nodo después del nodo anterior */
      nuevo->sig = anterior->sig;
      anterior->sig = nuevo;
   }
}

int ListaVacia(Lista lista){
   return (lista == NULL);
}

void MostrarLista(Lista lista){
   pNodo nodo = lista;

   if(ListaVacia(lista)) printf("No se encontro a nadie\n");
   else{
      while(nodo){
         printf("animalito encontrado en [%d][%d]\n", nodo->coo_X,nodo->coo_Y);
         nodo = nodo->sig;
     }
     printf("\n");
   }
}

void IniDesc(int num, int valor){
    valor++;
    
    if(valor < num){
        Descomponer(num, valor, valor, 0);
    }
}

void Descomponer(int num, int valor, int valorCam, int pos){
    int i,suma=0;

    desc[pos] = valorCam;

    for(i=0;i<=pos;i++){
        suma = desc[i] + suma;
    }

    if(suma == num){
        for(i=0;i<pos;i++){
            printf("%d + ", desc[i]);
        }

        printf("%d = %d\n", valorCam,suma);

        valorCam++;
        pos++;

        Descomponer(num, valor, valorCam, pos);
    }else if(suma < num){
        valorCam++;
        pos++;

        Descomponer(num, valor, valorCam, pos);
    }else{
        if(valorCam < num && pos > 1){
            Descomponer(num, valor, valorCam, 1);
        }else{
            IniDesc(num, valor);
        }
    }
}