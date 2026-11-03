#include "minitest.h"
#include "credencial.h"

static void test_formato_acepta_ocho_digitos(void)
{
    MT_ASSERT_EQ(cred_formato_valido("12345678"), 1);
}

int main(void)
{
    printf("Pruebas del validador de credenciales\n");
    printf("-------------------------------------\n");

    MT_PRUEBA(test_formato_acepta_ocho_digitos);

    return mt_informe("build/reports/credencial.xml", "credencial");
}
