#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define pi 3.14159265358979323846

long long m[30][30];

double minhaPow(double v,double base){

    double resp=1;
    double aux = base;

    while(base > 0){

        resp *= v;

        base--;
    }

    return resp;
}

void iniMatrix(){ // inicializar a matriz de memoização com 0's

    memset(m, 0, sizeof(long long) * 30 * 30);
}

double converteGrau(double grau){

    double resp = (grau * pi) / 180.0;

    return resp;
}

long long fat(long long x){ // uso tabulação por questão de desempenho

    if(x==0 || x==1)
        return 1;

    if(m[x][x]!=0){

        return m[x][x];
    }
    else
        return m[x][x] = (x * fat(x-1));
}

double meuSeno(double x){

    double somaSeno = 0.0;
    int i;

    for(i=0;i<9;i++){ // série de Taylor para cálculo do seno

        double numerador = (double)minhaPow(-1,i) * (double)minhaPow(x,2 * i + 1);
        double denominador = (double)fat(2 * i + 1);

        somaSeno = somaSeno + numerador / denominador;
    }

    return somaSeno;
}

double meuCosseno(double x){

    double soma = 0.0;
    int i;

    for(i=0;i<9;i++){ // série de Taylor para cálculo do seno

        double numerador = (double)minhaPow(-1,i) * (double)minhaPow(x,2 * i);
        double denominador = (double)fat(2 * i);

        soma = soma + numerador / denominador;
    }
    return soma;
}

int main()
{
    iniMatrix();
    int valor;

    printf("informe o valor pra calcular seno e cosseno ou -1 pra sair e tecle enter\n");
    scanf("%d",&valor);

    while(valor!=-1){

        printf("Seno Usando Sequencia de Taylor = %lf\n",meuSeno(converteGrau(valor)));
        printf("Cosseno Usando Sequencia de Taylor = %lf\n",meuCosseno(converteGrau(valor)));

        printf("-----------------------------------------------------------\n");

        printf("Seno pela biblioteca do C = %lf\n",sin(converteGrau(valor)));
        printf("Cosseno pela biblioteca do C = %lf\n\n",cos(converteGrau(valor)));

        printf("informe o valor pra calcular seno e cosseno ou -1 pra sair e tecle enter\n");
        printf("\n");
        scanf("%d",&valor);
    }

    return 0;
}
