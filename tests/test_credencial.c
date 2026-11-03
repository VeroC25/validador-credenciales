#include "minitest.h"
#include "credencial.h"

static void test_formato_acepta_ocho_digitos(void)
{
    MT_ASSERT_EQ(cred_formato_valido("12345678"), 1);
}

/* Verificar que se rechacen credenciales con menos de ocho dígitos. */
static void test_formato_rechaza_corta(void)
{
    MT_ASSERT_EQ(cred_formato_valido("1234567"), 0);
}

/* Verificar que se rechacen credenciales con más de ocho dígitos. */
static void test_formato_rechaza_larga(void)
{
    MT_ASSERT_EQ(cred_formato_valido("123456789"), 0);
}

/* Verificar que una credencial no contenga caracteres alfabéticos. */
static void test_formato_rechaza_letra(void)
{
    MT_ASSERT_EQ(cred_formato_valido("1234567A"), 0);
}

/* Verificar que una referencia nula sea considerada inválida. */
static void test_formato_rechaza_nulo(void)
{
    MT_ASSERT_EQ(cred_formato_valido(NULL), 0);
}

/* Verificar que el checksum utilice la suma módulo diez. */
static void test_checksum_suma_modulo_diez(void)
{
    MT_ASSERT_EQ(cred_checksum("12345678"), 8);
}

/* Verificar el cálculo del checksum con una suma pequeña. */
static void test_checksum_suma_pequena(void)
{
    MT_ASSERT_EQ(cred_checksum("11111117"), 7);
}

/* Verificar que no se calcule el checksum de una credencial inválida. */
static void test_checksum_rechaza_invalida(void)
{
    MT_ASSERT_EQ(cred_checksum("1234567A"), -1);
}

int main(void)
{
    printf("Pruebas del validador de credenciales\n");
    printf("-------------------------------------\n");

    MT_PRUEBA(test_formato_acepta_ocho_digitos);
/* Registrar las pruebas de formato y checksum para su ejecución. */
    MT_PRUEBA(test_formato_rechaza_corta);
    MT_PRUEBA(test_formato_rechaza_larga);
    MT_PRUEBA(test_formato_rechaza_letra);
    MT_PRUEBA(test_formato_rechaza_nulo);
    MT_PRUEBA(test_checksum_suma_modulo_diez);
    MT_PRUEBA(test_checksum_suma_pequena);
    MT_PRUEBA(test_checksum_rechaza_invalida);

    return mt_informe("build/reports/credencial.xml", "credencial");
}
