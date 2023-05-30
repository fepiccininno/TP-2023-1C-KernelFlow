#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "package.h"
#include "mmu.h"
#include "client_handle.h"


t_pcontexto_desalojo *stop_exec(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

void SET(char *registro, char *valor);

char *MOV_IN();

char *MOV_OUT();

t_pcontexto_desalojo *I_O(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *F_OPEN(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *F_CLOSE(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *F_SEEK(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *F_READ(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *F_WRITE(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *F_TRUNCATE(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *WAIT(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *SIGNAL(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *CREATE_SEGMENT(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *DELETE_SEGMENT(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *YIELD(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

t_pcontexto_desalojo *EXIT(t_pcontexto *contexto, t_instruccion* instruccionListaParaEjecutar);

// aux
void *get_register(char *register_char);

void instruction_destroyer(t_instruccion *instruccion);

t_pcontexto_desalojo *copy_pcontexto(t_pcontexto *contexto);

void copy_registers(t_registers *dest, t_registers *src);

t_list *copy_instructions_list(t_list *instructions);

t_instruccion *copy_instruction(t_instruccion *instruction);

t_instruccion *new_instruction(t_identificador identificador, t_list *parametros);

void add_param_to_instruction(t_list *parametros, t_instruccion *instruccion);

#endif