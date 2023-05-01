#include "consola.h"

int main(int argc, char **argv)
{

  // inicializo loggers
  logger_console = log_create(logger_console_path, "Consola", 1, LOG_LEVEL_DEBUG);

  // leer configuracion
  char *path_console_config = "/home/utnso/Desktop/Merge/tp-2023-1c-KernelFlow/consola/config/console.config"; // argv[1];
  // char *path_console_config = argv[1];
  t_config_console *config = NULL;
  config = read_config(path_console_config, logger_console);

  // abro archivo de instrucciones
  char *path_pseudocodigo = "/home/utnso/Desktop/Merge/tp-2023-1c-KernelFlow/consola/pseudocodigo.txt"; // argv[2];
  // char *path_pseudocodigo = argv[2];
  FILE *file_instructions = fopen(path_pseudocodigo, "rt");

  if (config == NULL)
  {
    end_program(logger_console, config);
    return EXIT_FAILURE;
  }

  if (logger_console == NULL)
  {
    log_error(logger_console, "No se pudo iniciar la consola"),
        end_program(logger_console, config);
    return EXIT_FAILURE;
  }

  log_debug(logger_console, "Consola iniciada.");

  // inicializo socket
  int kernel_socket = start_console_client(config->ip_kernel, config->puerto_kernel, logger_console);

  // parsear archivo pseudocodigo
  t_list *lista_instrucciones = parsear_pseudocodigo(file_instructions, logger_console);

  if (lista_instrucciones == NULL)
  {
    end_program(logger_console, config);
    return 0;
  }

  // enviar lista de instrucciones a kernel
  if (send_instrucciones(kernel_socket, lista_instrucciones, logger_console))
  {
    log_debug(logger_console, "kkkkkk");
  }

  // Espero que la instruccion recibida sea END para saber que finalizo
  // t_package *p = get_package(kernel_socket, logger_console);
  // if (get_instruccion(p)->identificador == EXIT){
  //   log_debug(logger_console, "Instruccion recibida: %s", get_instruccion(p));
  // }

  // fin del programa
  socket_destroy(kernel_socket);
  end_program(logger_console, config);
  fclose(file_instructions);
  destroy_lista_instrucciones(lista_instrucciones);

  return EXIT_SUCCESS;
}
