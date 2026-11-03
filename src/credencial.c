#include "credencial.h"
#include <stddef.h>
#include <string.h>

int cred_formato_valido(const char *uid)
{
    (void)uid;
    return 0;
}

int cred_checksum(const char *uid)
{
    (void)uid;
    return -1;
}

cred_resultado_t cred_autorizar(const char *uid,
                                const char *permitidas[],
                                size_t n)
{
    (void)uid;
    (void)permitidas;
    (void)n;
    return CRED_ERR_FORMATO;
}

const char *cred_nombre_resultado(cred_resultado_t r)
{
    switch (r) {
    case CRED_OK:                 return "OK";
    case CRED_ERR_FORMATO:        return "ERR_FORMATO";
    case CRED_ERR_CHECKSUM:       return "ERR_CHECKSUM";
    case CRED_ERR_NO_AUTORIZADA:  return "ERR_NO_AUTORIZADA";
    default:                      return "DESCONOCIDO";
    }
}
