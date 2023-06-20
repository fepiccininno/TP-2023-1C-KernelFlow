#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

#include <commons/string.h>
#include <commons/collections/list.h>

#include "utils.h"
#include "types.h"
#include "kernel_vars.h"
#include "kernel_structs.h"
#include "kernel_core.h"

#include "planner.h"
#include "communication.h"


void actualizar_tablas(t_list *tablas_actualizadas);
bool execute_create_segment(t_instruccion *instruccion, t_pcb *pcb);
void compactar();
bool execute_delete_segment(t_instruccion *instruccion, t_pcb *pcb);
bool execute_fopen(t_instruccion *instruccion, t_pcb *pcb);
t_archivo_abierto *buscar_archivo_abierto(t_pcb *pcb, char *nombre_archivo);
bool execute_fclose(t_instruccion *instruccion, t_pcb *pcb);
bool execute_fseek(t_instruccion *instruccion, t_pcb *pcb);
void execute_fread(t_instruccion *instruccion, t_pcb *pcb);
void *file_processing(void *args);
void execute_fwrite(t_instruccion *instruccion, t_pcb *pcb);
void execute_ftruncate(t_instruccion *instruccion, t_pcb *pcb);
t_recurso *find_recurso(char *recurso_solicitado);
int find_pcb_index(t_list *cola, uint32_t pid);
bool execute_wait(char *recurso_solicitado, t_pcb *pcb);
bool execute_signal(char *recurso_solicitado, t_pcb *pcb);
void execute_io(int tiempo, t_pcb *pcb);
void *io(void *args);
char *get_status_code_string(t_status_code sc);
void execute_exit(t_pcb *pcb, t_status_code sc);
void execute_yield(t_pcb *pcb);

#endif /* INSTRUCCIONES_H */