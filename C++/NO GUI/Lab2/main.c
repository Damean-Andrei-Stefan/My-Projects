#include <stdio.h>
#include <stdlib.h>
// primele numere mai mici decat n prime si palindroame

// verificare nr prim
int nrPrim(int nr){
    for(int i=2; i<=nr/2; i++){
        if(nr % i == 0) return 0;
    }
    return 1;

}

//verificare palindrom
int nrPal(int nr){
    int suma = 0, copy = nr;
    while (copy > 0){
        suma = (suma*10) + (copy % 10);
        copy /= 10;
    }
    return suma == nr;
}


//functie pt alocarea valorilor n
int primeleNr(int* ptr, int n, int contor){


    // mergem de la n pana la ultimul nr prim palindrom
    while(n > 2){

        //verificare nr prim si palindrom
        if((nrPal(n) == 1) && (nrPrim(n) == 1)){

            //pozitia existenta ia val. n si creste indexul
           /*printf("%d", n);
            printf(" ");*/
            ptr[contor] = n;
            contor++;

            //alocam alta casuta a vectorului
            ptr = (int*)realloc(ptr,(contor + 1) * sizeof(int));

        }
        n--;
    }

    return contor;
}
void afis(int* ptr, int contor){
    for(int i = 1; i< contor; i++){
        printf("%d", ptr[i]);
        printf(" ");
    }
}


int main()
{

    int n, contor = 1;
    int* ptr;
    ptr = (int*)malloc(sizeof(int));
    printf("Numarul n:");
    scanf("%d",&n);
    contor = primeleNr(ptr,n,contor);
    afis(ptr, contor);
    return 0;
}
