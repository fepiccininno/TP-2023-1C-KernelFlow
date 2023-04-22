#include "communication.h"

/* OPERACIONES DE ENVIO DE INFORMACION */

/* CLIENTE -> SERVIDOR -> PROGRAMA */

t_package* get_package(int socket, t_log *logger)
{
    t_package* paquete = package_recv(socket, logger);
    return paquete;
};

t_persona* get_instrucciones(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};

t_persona* get_pcontexto(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};

t_persona* get_tsegmento(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};

t_persona* get_ofile(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};

t_persona* get_file(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};

t_persona* get_data(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};

t_persona* get_instruccion(t_package* paquete)
{
    t_persona* persona = t_persona_create_from_buffer(paquete->buffer);
    return persona;
};


/* PROGRAMA -> CLIENTE -> SERVIDOR */

bool send_instrucciones(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, INSTRUCCIONES);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_pcontexto(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, PCONTEXTO);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_tsegmento(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, TSEGMENTOS);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_ofile(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, OFILE);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_file(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, DFILE);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_data(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, DATA);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_instruccion(int socket, t_persona persona, t_log *logger)
{
    t_buffer *buffer = t_persona_create_buffer(persona);
    t_package *paquete = package_create(buffer, INSTRUCCION);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

bool send_end(int socket, t_log *logger)
{
    t_package *paquete = package_create(NULL, END);
    bool res = package_send(socket, paquete, logger);
    package_destroy(paquete);
    return res;
};

/* HANDSHAKE */

bool hs_server_to_module_valid(int socket_client, hs_code hs_module_origin, t_log *logger)
{
    int HS_Recv_A = -1;
    int HS_Recv_B = -1;
    int HS_Origin = hs_module_origin;
    // Recibo conexion
    recv(socket_client, &HS_Recv_A, sizeof(int), MSG_WAITALL);
    // Mando quien soy
    send(socket_client, &HS_Origin, sizeof(int), 0);
    // Espero confirmacion
    recv(socket_client, &HS_Recv_B, sizeof(int), MSG_WAITALL);
    // Chequeo si es el modulo se desconecta
    if (HS_Recv_B == HSOK)
    {
        log_info(logger, "Handshake valido - Conexion aceptada");
        return true;
    }
    else
    {
        log_warning(logger, "Handshake invalido - Conexion rechazada");
        return false;
    }
}

bool hs_client_to_module_valid(int socket_server, hs_code hs_module_origin, hs_code hs_module_expected, t_log *logger)
{
    int HS_Recv_A = -1;
    int HS_Send_A = -1;
    int HS_Origin = hs_module_origin;
    int HS_Expected = hs_module_expected;
    // Mando quien soy
    send(socket_server, &HS_Origin, sizeof(int), 0);
    // Recibo quien es el otro
    recv(socket_server, &HS_Recv_A, sizeof(int), MSG_WAITALL);
    // Chequeo si es el modulo que espero
    if (HS_Recv_A == HS_Expected)
    {
        log_info(logger, "Handshake valido - Conexion aceptada");
        HS_Send_A = HSOK;
    }
    else
    {
        log_warning(logger, "Handshake invalido - Conexion rechazada");
        HS_Send_A = HSFAIL;
    }
    send(socket_server, &HS_Send_A, sizeof(int), 0);
    return (HS_Send_A == HSOK);
}

/* Cliente - Servidor */

void socket_destroy(int socket)
{
    close(socket);
}