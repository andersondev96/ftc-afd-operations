#ifndef __AFD_H__
#define __AFD_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Estrutura para representar uma transição
    from: Estado onde se encontra o AFDno momento da transição
    read: Símbolo que o AFD irá realizar a leitura quando ocorrer a transição
    to: Estado para onde vai o AFD após a transição
*/

typedef struct transition_state
{
    char *from;
    char *read;
    char *to;

} Transition;

/* Estrutura para representar um AFD
    states: array que armazena os estados, conforme a quant_states
    symbols: array que armazena os símbolos, de acordo como quant_symbols
    initial_state: Estado inicial do AFD
    final_states: Estado final do AFD de acordo com a quant_final_states
    transitions: array que armazena as transições de acordo com a quant_transitions
*/
typedef struct afd_state
{
    char **states;
    int quant_states;

    char **symbols;
    char quant_symbols;

    char *initial_state;

    char **final_states;
    char quant_final_states;

    Transition *transitions;
    int quant_transitions;

} AFD;

/*
    Método que retorna a instância da transição, passando como
    parâmetro o AFD e outros campos que são necessários para
    estruturar a transição.
*/
Transition *getTransition(AFD *afd, char *from, char *to, char *read);

/*
    Método que aloca a memória e retorna uma transição vazia.
*/
Transition *getEmptyTransition();

/*
    Método que busca e retorna uma posição dentro de uma AFD,
    é necessário passar a AFD utilizada e o estado que
    será encontrado, caso o estado não seja encontrado,
    a função retornará o valor -1.
*/
int getStatePosition(AFD *afd, char *state);

/*
    Método que busca e  retorna um símbolo dentro da AFD,
    é necesspario passar a AFD utilizada e o símbolo
    que será encontrado, caso o símbolo não seja encontado
    a função retornará o valor -1.
*/
int getSymbolPosition(AFD *afd, char *symbol);

/* Método que retorna uma AFD vazia */
AFD *getEmptyAFD();

/*
    Método que faz a leitura de um AFD a partir de um arquivo e retorna a AFD correspondente
*/
AFD *readAFD(char *fileName);

/*
    Método que escreve a AFD em um arquivo.
*/
void writeAFD(AFD *afd, char *fileName);

/*
    Método que libera a memória alocada por um AFD
*/
void freeAFD(AFD *afd);

#endif