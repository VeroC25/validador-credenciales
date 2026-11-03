/*
 * minitest.h - Micro marco de pruebas que emite informe JUnit XML.
 * Demostracion de CI/CD embebido con Jenkins.
 *
 * Jenkins lee ese XML con el paso junit y muestra la pestana
 * "Test Result" con el detalle de cada prueba.
 */
#ifndef MINITEST_H
#define MINITEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MT_MAX_PRUEBAS 32

static int   mt_total  = 0;
static int   mt_fallas = 0;
static char  mt_nombre[MT_MAX_PRUEBAS][64];
static char  mt_motivo[MT_MAX_PRUEBAS][160];
static int   mt_estado[MT_MAX_PRUEBAS];
static int   mt_actual = -1;

#define MT_PRUEBA(fn)                                                  \
    do {                                                               \
        mt_actual = mt_total;                                          \
        snprintf(mt_nombre[mt_actual], 64, "%s", #fn);                 \
        mt_estado[mt_actual] = 1;                                      \
        mt_motivo[mt_actual][0] = 0;                                   \
        mt_total++;                                                    \
        fn();                                                          \
        printf("[ %s ] %s\n",                                          \
               mt_estado[mt_actual] ? " ok " : "FALLA",                 \
               mt_nombre[mt_actual]);                                   \
    } while (0)

#define MT_ASSERT(cond)                                                \
    do {                                                               \
        if (!(cond)) {                                                 \
            mt_estado[mt_actual] = 0;                                  \
            mt_fallas++;                                               \
            snprintf(mt_motivo[mt_actual], 160,                        \
                     "linea %d: se esperaba %s", __LINE__, #cond);     \
            return;                                                    \
        }                                                              \
    } while (0)

#define MT_ASSERT_EQ(obtenido, esperado)                               \
    do {                                                               \
        if ((obtenido) != (esperado)) {                                \
            mt_estado[mt_actual] = 0;                                  \
            mt_fallas++;                                               \
            snprintf(mt_motivo[mt_actual], 160,                        \
                     "linea %d: se obtuvo %d, se esperaba %d",         \
                     __LINE__, (int)(obtenido), (int)(esperado));      \
            return;                                                    \
        }                                                              \
    } while (0)

static int mt_informe(const char *ruta, const char *suite)
{
    FILE *f = fopen(ruta, "w");
    int i;

    if (f == NULL) {
        fprintf(stderr, "minitest: no se pudo escribir %s\n", ruta);
        return 1;
    }
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<testsuite name=\"%s\" tests=\"%d\" failures=\"%d\">\n",
            suite, mt_total, mt_fallas);
    for (i = 0; i < mt_total; ++i) {
        fprintf(f, "  <testcase classname=\"%s\" name=\"%s\"",
                suite, mt_nombre[i]);
        if (mt_estado[i]) {
            fprintf(f, "/>\n");
        } else {
            fprintf(f, ">\n    <failure message=\"%s\"/>\n  </testcase>\n",
                    mt_motivo[i]);
        }
    }
    fprintf(f, "</testsuite>\n");
    fclose(f);

    printf("\nminitest: informe JUnit en %s\n", ruta);
    printf("Resumen: %d pruebas, %d fallas\n", mt_total, mt_fallas);
    return (mt_fallas > 0) ? 1 : 0;
}

#endif /* MINITEST_H */
