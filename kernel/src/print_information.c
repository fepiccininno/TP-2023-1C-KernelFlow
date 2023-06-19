#include "print_information.h"

// PRINTS FUNCTIONS

void print_menu()
{
    
    char line[2048];
    int i;
    int input = -1;
    printf("\n\nMenu:\n");
    printf("1. Mostrar config\n");
    printf("2. Mostrar colas\n");
    printf("3. Mostrar estados internos\n");
    printf("4. Mostrar PCB\n");
    printf("5. Mostrar recursos\n");
    printf("6. Salir\n");
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%d", &i)) {
            input = i;
        }
    }
    printf("\n\n");
    switch (input)
    {
    case 1:
        print_config();
        break;
    case 2:
        print_queues();
        break;
    case 3:
        print_internal_states();
        break;
    case 4:
        input = -1;
        printf("Ingrese el PID del PCB: ");
        if (fgets(line, sizeof(line), stdin)) {
            if (1 == sscanf(line, "%d", &i)) {
                input = i;
            }
        }
        t_pcb *pcb = get_pcb_by_pid(input);
        printf("\n");
        if (pcb != NULL)
            print_pcb(pcb);
        else
            printf("No se encontro el PCB\n");
        break;
    case 5:
        print_status_recursos();
        break;
    case 6:
        end_program_flag = true;
        break;
    default:
        printf("Opcion invalida\n");
        break;
    }
    sleep(1);
}

t_pcb *get_pcb_by_pid(int pid)
{
    t_pcb *pcb;
    for (int i = 0; i < list_size(queues->NEW); i++)
    {
        pcb = list_get(queues->NEW, i);
        if (pcb->pid == pid)
            return pcb;
    }
    for (int i = 0; i < list_size(queues->READY); i++)
    {
        pcb = list_get(queues->READY, i);
        if (pcb->pid == pid)
            return pcb;
    }
    for (int i = 0; i < list_size(queues->EXEC); i++)
    {
        pcb = list_get(queues->EXEC, i);
        if (pcb->pid == pid)
            return pcb;
    }
    for (int i = 0; i < list_size(queues->BLOCK); i++)
    {
        pcb = list_get(queues->BLOCK, i);
        if (pcb->pid == pid)
            return pcb;
    }
    for (int i = 0; i < list_size(queues->EXIT); i++)
    {
        pcb = list_get(queues->EXIT, i);
        if (pcb->pid == pid)
            return pcb;
    }
    return NULL;
}

void print_config()
{
    printf("Configuracion:\n");
    printf("IP_MEMORIA: %s\n", config_kernel->ip_memoria);
    printf("PUERTO_MEMORIA: %s\n", config_kernel->puerto_memoria);
    printf("IP_FILESYSTEM: %s\n", config_kernel->ip_filesystem);
    printf("PUERTO_FILESYSTEM: %s\n", config_kernel->puerto_filesystem);
    printf("IP_CPU: %s\n", config_kernel->ip_cpu);
    printf("PUERTO_CPU: %s\n", config_kernel->puerto_cpu);
    printf("PUERTO_ESCUCHA: %s\n", config_kernel->puerto_escucha);
    printf("GRADO_MAX_MULTIPROGRAMACION: %d\n", config_kernel->grado_max_multiprog);
    printf("ALGORITMO_PLANIFICACION: %s\n", config_kernel->algoritmo_planificacion);
    printf("ESTIMACION_INICIAL: %f\n", config_kernel->estimacion_inicial);
    printf("HRRN_ALFA: %f\n", config_kernel->hrrn_alfa);
    list_iterate(config_kernel->recursos, (void *)print_recurso);
    list_iterate(config_kernel->instancias_recursos, (void *)print_instancias_recursos);
}

void print_recurso(char *recurso)
{
    printf("RECURSO: %s\n", recurso);
}

void print_instancias_recursos(char *instancias_recursos)
{
    printf("INSTANCIAS X RECURSO: %s\n", instancias_recursos);
}

void print_queues()
{
    printf("Cola de NEW:\n");
    list_iterate(queues->NEW, (void *)print_pcb_pid);
    printf("Cola de READY:\n");
    list_iterate(queues->READY, (void *)print_pcb_pid);
    printf("Cola de EXEC:\n");
    list_iterate(queues->EXEC, (void *)print_pcb_pid);
    printf("Cola de BLOCK:\n");
    list_iterate(queues->BLOCK, (void *)print_pcb_pid);
    printf("Cola de EXIT:\n");
    list_iterate(queues->EXIT, (void *)print_pcb_pid);
}

void print_pcb_pid(t_pcb *pcb)
{
    printf("  PID: %d\n", pcb->pid);
}

void print_pcb(t_pcb *pcb)
{
    printf("  PID: %d\n", pcb->pid);
    printf("  Program Counter: %d\n", pcb->program_counter);
    printf("  Cantidad de instrucciones: %d\n", list_size(pcb->instrucciones));
    // printf("  Cantidad de segmentos: %d\n", list_size(pcb->segments_table));
    // printf("  Cantidad de archivos abiertos: %d\n", list_size(pcb->open_files_table));
    int64_t time_ready = temporal_diff(temporal_create(), pcb->tiempo_llegada_ready);
    printf("  Tiempo de llegada a READY: %ld\n", time_ready);
    printf("  Estimacion de rafaga: %f\n", pcb->est_sig_rafaga);
    printf("  Registros:\n");
    print_registers(pcb->registers);
    printf("  Segmentos:\n");
    print_segments(pcb->segments_table->segment_list);
}

void print_segments(t_list *segments) {
    printf("    ID\tBASE\tSIZE\n");
    for (int i = 0; i < list_size(segments); i++)
    {
        t_segment *segment = list_get(segments, i);
        printf("    %d\t%d\t%d\n", segment->id, segment->base_address, segment->size);
    }
}

void print_registers(t_registers *registers)
{
    printf("      AX: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%c", *(char *)(registers->AX + i));
    }
    printf("\n");
    printf("      BX: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%c", *(char *)(registers->BX + i));
    }
    printf("\n");
    printf("      CX: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%c", *(char *)(registers->CX + i));
    }
    printf("\n");
    printf("      DX: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%c", *(char *)(registers->DX + i));
    }
    printf("\n");
    printf("      EAX: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c", *(char *)(registers->EAX + i));
    }
    printf("\n");
    printf("      EBX: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c", *(char *)(registers->EBX + i));
    }
    printf("\n");
    printf("      ECX: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c", *(char *)(registers->ECX + i));
    }
    printf("\n");
    printf("      EDX: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c", *(char *)(registers->EDX + i));
    }
    printf("\n");
    printf("      RAX: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%c", *(char *)(registers->RAX + i));
    }
    printf("\n");
    printf("      RBX: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%c", *(char *)(registers->RBX + i));
    }
    printf("\n");
    printf("      RCX: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%c", *(char *)(registers->RCX + i));
    }
    printf("\n");
    printf("      RDX: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%c", *(char *)(registers->RDX + i));
    }
    printf("\n");
}

void print_internal_states()
{
    int grado_multiprog = list_size(queues->READY) + list_size(queues->EXEC) + list_size(queues->BLOCK);
    printf("Proximo PID: %d\n", pid_counter);
    printf("Grado de multiprogramacion: %d\n", grado_multiprog);
    printf("Aceptar conexiones consola: %d\n", accept_connections);
    printf("Nucleo kernel estado: %d\n", core_running);
}

void print_status_recursos()
{
    for (int i = 0; i < list_size(recursos); i++)
    {
        t_recurso *recurso = list_get(recursos, i);
        printf("RECURSO: %s\n", recurso->recurso);
        printf("INSTANCIAS: %d\n", recurso->instancias);
        printf("BLOQUEADOS: %d\n", list_size(recurso->lista_bloqueados));
    }
}
