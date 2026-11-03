#include <stdio.h>
#include "credencial.h"

#ifndef APP_VERSION
#define APP_VERSION "0.0.0-dev"
#endif

int main(void)
{
    static const char *permitidas[] = {
        "12345678",
        "20250010",
        "99887764"
    };
    static const char *ensayos[] = {
        "12345678",
        "20250010",
        "1234567",
        "1234567A",
        "12345670",
        "99887764",
        "11111115"
    };
    const size_t n_perm = sizeof(permitidas) / sizeof(permitidas[0]);
    const size_t n_ens  = sizeof(ensayos) / sizeof(ensayos[0]);
    size_t i;

    printf("validador-credenciales %s\n", APP_VERSION);
    printf("Longitud requerida: %u digitos\n\n", (unsigned)CRED_LONGITUD);
    printf("  %-12s | %s\n", "credencial", "resultado");
    printf("  -------------+--------------------\n");

    for (i = 0u; i < n_ens; ++i) {
        cred_resultado_t r = cred_autorizar(ensayos[i], permitidas, n_perm);
        printf("  %-12s | %s\n", ensayos[i], cred_nombre_resultado(r));
    }

    printf("\n");
    return 0;
}
