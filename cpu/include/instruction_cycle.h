#ifndef INSTRUCTION_CYCLE_H
#define INSTRUCTION_CYCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "instructions.h"

// Busca la siguiente instruccion a ejecutar del pcb y suma 1 al program counter
t_instruccion* fetch(t_pcontexto* contexto);

// Interpreta la instruccion y traduce con MMU de ser necesario. Si la instruccion es SET tiene que hacer un RETARDO_INSTRUCCION
t_instruccion* decode(t_instruccion* instruccionSiguiente);

// Ejecuta la instruccion
t_pcontexto_desalojo *execute(t_instruccion* instruccionListaParaEjecutar, t_pcontexto *contexto);

t_pcontexto_desalojo *execute_instruction_cycle(t_pcontexto* contexto);

t_pcontexto_desalojo * execute_process(t_pcontexto* contexto);

#endif