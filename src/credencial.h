#ifndef CREDENCIAL_H
#define CREDENCIAL_H

#include <stdint.h>
#include <stddef.h>

#define CRED_LONGITUD   8u
#define CRED_MAX_PERMIT 16u

typedef enum {
    CRED_OK = 0,
    CRED_ERR_FORMATO,
    CRED_ERR_CHECKSUM,
    CRED_ERR_NO_AUTORIZADA
} cred_resultado_t;

int cred_formato_valido(const char *uid);

int cred_checksum(const char *uid);

cred_resultado_t cred_autorizar(const char *uid,
                                const char *permitidas[],
                                size_t n);

const char *cred_nombre_resultado(cred_resultado_t r);

#endif /* CREDENCIAL_H */
