#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>
#include <pthread.h>
#include "memory_vars.h"

typedef struct
{
    char* port;
	size_t memory_size;
	size_t segment_zero_size;
	int segment_quantity;
	int memory_time_delay;
	int compactation_time_delay;
	char* compactation_algorithm;
} t_config_memoria;

t_config_memoria *read_config(char *path);
void end_program(t_log *logger_main, t_log *logger_aux, t_config_memoria *config);

#endif /* UTILS_H */