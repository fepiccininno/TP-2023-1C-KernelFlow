#ifndef MMU_H
#define MMU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "utils.h"
#include "cpu_vars.h"
#include "types.h"

int get_num_segmento(int dir_logica);

int get_desplazamiento_segmento(int dir_logica);

int get_direccion_fisica(int dir_logica, t_list *segmentos);

t_segment *get_by_num_segmento(int num_segmento, t_list *segmentos);

#endif