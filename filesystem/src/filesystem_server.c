#include "filesystem_server.h"

void start_filesystem_server()
{
    int server_socket = server_start(config_fs->puerto_escucha, logger_aux);
    int client_socket;
    bool accept_connection = true;
    while (accept_connection)
    {
        client_socket = client_wait(server_socket, logger_aux);
        if (client_socket != -1)
        {
            log_info(logger_aux, "Se conecto un cliente");

            if (hs_server_to_module_valid(client_socket, HSFS, logger_aux))
                process_client(client_socket);

            log_info(logger_aux, "Cerrando conexion con cliente");
            socket_destroy(client_socket);
            socket_destroy(server_socket);
            accept_connection = false;
        }
    }
}

void process_client(int client_socket)
{
    bool exit = false;
    while (exit == false)
    {
        t_package *package = get_package(client_socket, logger_aux);
        switch (package->operation_code)
        {
        case INSTRUCCION:
            t_instruccion *instruccion = get_instruccion(package);
            handle_instruccion(instruccion, client_socket);
            instruccion_destroy(instruccion);
            break;
        case END:
            log_warning(logger_aux, "Conexion Finalizada");
            exit = true;
            break;
        default:
            log_warning(logger_aux, "Operacion desconocida.");
            exit = true;
            break;
        }
        package_destroy(package);
    }
}

void handle_instruccion(t_instruccion *instruccion, int client_socket)
{
    char *nombre = NULL;
    int response = -1;
    int puntero_archivo = -1;
    int cant_bytes = -1;
    int direccion_fisica = -1;
    switch (instruccion->identificador)
    {
    case I_F_OPEN:
        log_info(logger_aux, "Se recibio una instruccion de abrir archivo");
        nombre = (char*)list_get(instruccion->parametros, 0);
        response = open_file(nombre);
        if (response)
            send_status_code(client_socket, FILE_OPEN, logger_aux);
        else
            send_status_code(client_socket, ERROR, logger_aux);
        break;
    case I_F_READ:
        log_info(logger_aux, "Se recibio una instruccion de leer archivo");
        nombre = list_get(instruccion->parametros, 0);
        direccion_fisica = atoi((char*)list_get(instruccion->parametros, 1));
        cant_bytes = atoi((char*)list_get(instruccion->parametros, 2));
        puntero_archivo = atoi((char*)list_get(instruccion->parametros, 3));
        response = read_file(nombre, puntero_archivo, cant_bytes, direccion_fisica);
        if (response)
            send_status_code(client_socket, FILE_READ, logger_aux);
        else
            send_status_code(client_socket, ERROR, logger_aux);
        break;
    case I_F_WRITE:
        log_info(logger_aux, "Se recibio una instruccion de escribir archivo");
        nombre = (char*)list_get(instruccion->parametros, 0);
        direccion_fisica = atoi((char*)list_get(instruccion->parametros, 1));
        cant_bytes = atoi((char*)list_get(instruccion->parametros, 2));
        puntero_archivo = atoi((char*)list_get(instruccion->parametros, 3));
        response = write_file(nombre, puntero_archivo, cant_bytes, direccion_fisica);
        if (response)
            send_status_code(client_socket, FILE_WRITTEN, logger_aux);
        else
            send_status_code(client_socket, ERROR, logger_aux);
        break;
    case I_F_TRUNCATE:
        log_info(logger_aux, "Se recibio una instruccion de truncar archivo");
        nombre = list_get(instruccion->parametros, 0);
        int nuevo_tamanio = atoi((char*)list_get(instruccion->parametros, 1));
        response = truncate_file(nombre, nuevo_tamanio);
        if (response)
            send_status_code(client_socket, FILE_TRUNCATED, logger_aux);
        else 
            send_status_code(client_socket, FILE_NOT_EXISTS, logger_aux);
        break;
    default:
        log_warning(logger_aux, "Instruccion desconocida.");
        send_status_code(client_socket, ERROR, logger_aux);
        break;
    }
}
