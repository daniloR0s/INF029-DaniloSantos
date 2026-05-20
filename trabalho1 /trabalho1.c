// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Danilo Rosário dos Santos
//  email: 20252160038@ifba.edu.br
//  Matrícula:20252160038
//  Semestre:2026.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho1.h"

DataQuebrada quebraData(char data[]);

int somar(int x, int y)
{
    return x + y;
}

int fatorial(int x)
{
    int fat = 1;

    for(int i = x; i > 1; i--){
        fat *= i;
    }

    return fat;
}

/*
====================================================
FUNÇÕES AUXILIARES
====================================================
*/

int ehBissexto(int ano)
{
    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
        return 1;
    }

    return 0;
}

int diasNoMes(int mes, int ano)
{
    int diasMes[12] =
    {
        31,28,31,30,31,30,31,31,30,31,30,31
    };

    if(mes == 2 && ehBissexto(ano)){
        return 29;
    }

    return diasMes[mes - 1];
}

char normalizar(char c)
{
    if(c >= 'A' && c <= 'Z'){
        return c + 32;
    }

    return c;
}

int tamanhoString(char str[])
{
    int tam = 0;

    while(str[tam] != '\0'){
        tam++;
    }

    return tam;
}

/*
====================================================
Q1
====================================================
*/

int q1(char data[])
{
    DataQuebrada dq = quebraData(data);

    if(dq.valido == 0){
        return 0;
    }

    if(dq.iAno < 100){
        dq.iAno += 2000;
    }

    if(dq.iMes < 1 || dq.iMes > 12){
        return 0;
    }

    if(dq.iDia < 1 || dq.iDia > diasNoMes(dq.iMes, dq.iAno)){
        return 0;
    }

    if(dq.iAno <= 0){
        return 0;
    }

    return 1;
}

/*
====================================================
Q2
====================================================
*/

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;

    if(q1(datainicial) == 0){
        dma.retorno = 2;
        return dma;
    }

    if(q1(datafinal) == 0){
        dma.retorno = 3;
        return dma;
    }

    DataQuebrada ini = quebraData(datainicial);
    DataQuebrada fim = quebraData(datafinal);

    if(ini.iAno < 100) ini.iAno += 2000;
    if(fim.iAno < 100) fim.iAno += 2000;

    if(
        ini.iAno > fim.iAno ||
        (ini.iAno == fim.iAno && ini.iMes > fim.iMes) ||
        (ini.iAno == fim.iAno && ini.iMes == fim.iMes && ini.iDia > fim.iDia)
    ){
        dma.retorno = 4;
        return dma;
    }

    int anos = fim.iAno - ini.iAno;
    int meses = fim.iMes - ini.iMes;
    int dias = fim.iDia - ini.iDia;

    if(dias < 0){

        meses--;

        int mesAnterior = fim.iMes - 1;

        if(mesAnterior == 0){
            mesAnterior = 12;
            fim.iAno--;
        }

        dias += diasNoMes(mesAnterior, fim.iAno);
    }

    if(meses < 0){
        anos--;
        meses += 12;
    }

    dma.qtdDias = dias;
    dma.qtdMeses = meses;
    dma.qtdAnos = anos;
    dma.retorno = 1;

    return dma;
}

/*
====================================================
Q3
====================================================
*/

int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i;

    for (i = 0; texto[i] != '\0'; i++)
    {
        if ((int)texto[i] == -61)
        {
            continue;
        }

        char atual = texto[i];

        if (isCaseSensitive != 1)
        {
            if (atual >= 'A' && atual <= 'Z')
            {
                atual += 32;
            }

            if (c >= 'A' && c <= 'Z')
            {
                c += 32;
            }
        }

        if (atual == c)
        {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
====================================================
Q4
====================================================
*/

int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int tamanhoTexto = tamanhoString(strTexto);
    int tamanhoTextoBusca = tamanhoString(strBusca);
    int CharStrNum[tamanhoTexto], CharSearchNum[tamanhoTextoBusca];
    int iCont, jCont, kCont = 0;

    for(iCont = 0, jCont = 0; strTexto[iCont]; iCont++, jCont++){
        if(strTexto[iCont] == -61)
            iCont++;
        CharStrNum[jCont] = strTexto[iCont];
    }
    for(iCont = 0, jCont = 0; strBusca[iCont]; iCont++, jCont++){
        if(strBusca[iCont] == -61)
            iCont++;
        CharSearchNum[jCont] = strBusca[iCont];
    }

    for(iCont = 0; iCont <= tamanhoTexto - tamanhoTextoBusca; iCont++){
        for(jCont = 0; jCont < tamanhoTextoBusca; jCont++){
            if(CharStrNum[iCont + jCont] != CharSearchNum[jCont]){
                break;
            }
                
        }
        if(jCont == tamanhoTextoBusca){
            qtdOcorrencias++;
            posicoes[kCont] = iCont + 1;
            kCont++;
            posicoes[kCont] = iCont + jCont;
            kCont++;

            iCont += jCont - 1;
        }
    }

    return qtdOcorrencias;
}
/*
====================================================
Q5
====================================================
*/

int q5(int num)
{
    int invertido = 0;

    while(num > 0){

        invertido = invertido * 10 + (num % 10);

        num /= 10;
    }

    return invertido;
}

/*
====================================================
Q6
====================================================
*/

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;

    int tempBusca = numerobusca;
    int qtdDigitosBusca = 0;

    while(tempBusca > 0)
    {
        qtdDigitosBusca++;
        tempBusca /= 10;
    }

    int divisor = 1;

    int i;

    for(i = 0; i < qtdDigitosBusca; i++)
    {
        divisor *= 10;
    }

    while(numerobase >= numerobusca)
    {
        int parte = numerobase % divisor;

        if(parte == numerobusca)
        {
            qtdOcorrencias++;

            for(i = 0; i < qtdDigitosBusca; i++)
            {
                numerobase /= 10;
            }
        }
        else
        {
            numerobase /= 10;
        }
    }

    return qtdOcorrencias;
}
/*
====================================================
Q7
====================================================
*/

int q7(char matriz[8][10], char palavra[5])
{
    int tamPalavra = tamanhoString(palavra);

    int direcoes[8][2] =
    {
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
        {1,1},
        {-1,-1},
        {1,-1},
        {-1,1}
    };

    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 10; j++){

            for(int d = 0; d < 8; d++){

                int achou = 1;

                for(int k = 0; k < tamPalavra; k++){

                    int ni = i + direcoes[d][0] * k;
                    int nj = j + direcoes[d][1] * k;

                    if(
                        ni < 0 || ni >= 8 ||
                        nj < 0 || nj >= 10 ||
                        matriz[ni][nj] != palavra[k]
                    ){
                        achou = 0;
                        break;
                    }
                }

                if(achou){
                    return 1;
                }
            }
        }
    }

    return 0;
}

/*
====================================================
QUEBRA DATA
====================================================
*/

DataQuebrada quebraData(char data[])
{
    DataQuebrada dq;

    dq.valido = 1;

    char sDia[3];
    char sMes[3];
    char sAno[5];

    int i = 0;
    int j = 0;

    int barras = 0;

    for(i = 0; data[i] != '\0'; i++){

        if(data[i] == '/'){
            barras++;
        }
    }

    if(barras != 2){
        dq.valido = 0;
        return dq;
    }

    i = 0;

    while(data[i] != '/' && data[i] != '\0'){

        if(data[i] < '0' || data[i] > '9'){
            dq.valido = 0;
            return dq;
        }

        sDia[j++] = data[i];

        if(j > 2){
            dq.valido = 0;
            return dq;
        }

        i++;
    }

    sDia[j] = '\0';

    if(j < 1 || j > 2){
        dq.valido = 0;
        return dq;
    }

    i++;
    j = 0;

    while(data[i] != '/' && data[i] != '\0'){

        if(data[i] < '0' || data[i] > '9'){
            dq.valido = 0;
            return dq;
        }

        sMes[j++] = data[i];

        if(j > 2){
            dq.valido = 0;
            return dq;
        }

        i++;
    }

    sMes[j] = '\0';

    if(j < 1 || j > 2){
        dq.valido = 0;
        return dq;
    }

    i++;
    j = 0;

    while(data[i] != '\0'){

        if(data[i] < '0' || data[i] > '9'){
            dq.valido = 0;
            return dq;
        }

        sAno[j++] = data[i];

        if(j > 4){
            dq.valido = 0;
            return dq;
        }

        i++;
    }

    sAno[j] = '\0';

    if(j != 2 && j != 4){
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno);

    return dq;
}
