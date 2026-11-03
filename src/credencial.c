#include "credencial.h"
#include <stddef.h>
#include <string.h>

int cred_formato_valido(const char *uid)
{
    size_t i;

    /* Rechazar credenciales nulas o con longitud incorrecta. */
    if (uid == NULL || strlen(uid) != CRED_LONGITUD) {
        return 0;
    }

    /* Comprobar que todos los caracteres sean dígitos. */
    for (i = 0; i < CRED_LONGITUD; i++) {
        if (uid[i] < '0' || uid[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int cred_checksum(const char *uid)
{
    int suma = 0;

    /* Evitar calcular el checksum de una credencial inválida. */
    if (!cred_formato_valido(uid)) {
        return -1;
    }

    /* Calcular la suma de los dígitos, excluyendo el último. */
    for (size_t i = 0; i < CRED_LONGITUD - 1; i++) {
        suma += uid[i] - '0';
    }

    return suma % 10;
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
