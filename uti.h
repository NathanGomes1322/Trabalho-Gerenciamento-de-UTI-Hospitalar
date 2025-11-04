#ifndef UTI_H
#define UTI_H

#define MAX_UTI 50
#include "fura_fila.h"
#include "lista_espera_uti.h"


int verificarDisponibilidadeUTI(int uti[], int tamanho);
void cadastrarNaUTI(FilaHeap *filaPrioridade, int leitosUTI[], int tamanhoUTI);
void darAltaUTI(int leitos[], int tamanho, ListaEspera *lista);
Paciente removerListaEspera(ListaEspera *lista);



#endif
