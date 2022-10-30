#include <stdio.h>
#include <stdlib.h>

int encontrar(int M[10][10],int n,int m);

void main(){
 int M[10][10] = {
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,1,0,0,0},
 };

 int i,j;

 for(i=0;i<10;i++){
    for(j=0;j<10;j++){
        printf("%i ", M[i][j]);
    }

    printf ("\n");
 }

    encontrar(M,10,10);
}

int encontrar(int M[10][10],int n,int m){
 int i=0,j=0;
 for(i=0;i<n;i++)
 {
  for(j=0;j<m;j++)
   {
   if(M[i][j]==1){
       printf ("\n");
       printf ("Encontro algo!");
       printf ("\n");
       }
   }
}
}