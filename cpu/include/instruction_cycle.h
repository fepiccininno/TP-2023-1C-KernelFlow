#ifndef INSTRUCTION_CYCLE_H
#define INSTRUCTION_CYCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "instructions.h"
#include "types_controllers.h"

// Busca la siguiente instruccion a ejecutar del pcb y suma 1 al program counter
t_instruccion* fetch(t_pcontexto* contexto);

// Interpreta la instruccion y traduce con MMU de ser necesario. Si la instruccion es SET tiene que hacer un RETARDO_INSTRUCCION
t_instruccion* decode(t_instruccion* instruccionSiguiente, t_pcontexto *contexto);

// Ejecuta la instruccion
t_pcontexto_desalojo *execute(t_instruccion* instruccionListaParaEjecutar, t_pcontexto *contexto);

// Ejecuta una instruccion completa (fetch decode y execute) del contexto pasado
t_pcontexto_desalojo *execute_instruction_cycle(t_pcontexto* contexto);

// Ejecuta el proceso pasado por contexto
t_pcontexto_desalojo * execute_process(t_pcontexto* contexto);


// aux
char *get_instruction_string(t_identificador id);

char *get_params_string(t_instruccion *instruction);

void cambiar_dir_logica_a_fisica(t_instruccion *instruccion, t_list *segmentos, int index_parametro);

bool checkear_seg_fault(t_instruccion *instruction, t_list *segments);

#endif