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

/* Definir las credenciales autorizadas para las pruebas. */
static const char *PERMITIDAS[] = {
    "12345678",
    "20250010"
};

/* Verificar que se autorice una credencial válida y permitida. */
static void test_autoriza_credencial_valida(void)
{
    MT_ASSERT_EQ(cred_autorizar("12345678", PERMITIDAS, 2), CRED_OK);
}

/* Verificar que se rechacen credenciales con formato incorrecto. */
static void test_rechaza_formato_invalido(void)
{
    MT_ASSERT_EQ(cred_autorizar("1234567A", PERMITIDAS, 2),
                 CRED_ERR_FORMATO);
}

/* Verificar que se rechacen credenciales con checksum incorrecto. */
static void test_rechaza_checksum_erroneo(void)
{
    MT_ASSERT_EQ(cred_autorizar("12345670", PERMITIDAS, 2),
                 CRED_ERR_CHECKSUM);
}

/* Verificar que una credencial ausente de la lista sea rechazada. */
static void test_rechaza_no_autorizada(void)
{
    MT_ASSERT_EQ(cred_autorizar("11111117", PERMITIDAS, 2),
                 CRED_ERR_NO_AUTORIZADA);
}

/* Verificar que el formato se evalúe antes de la autorización. */
static void test_formato_gana_al_orden(void)
{
    MT_ASSERT_EQ(cred_autorizar("ABC", PERMITIDAS, 2),
                 CRED_ERR_FORMATO);
}

/* Verificar que una lista nula no autorice credenciales. */
static void test_lista_vacia_no_autoriza(void)
{
    MT_ASSERT_EQ(cred_autorizar("12345678", NULL, 0),
                 CRED_ERR_NO_AUTORIZADA);
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
/* Registrar las pruebas de autorización de credenciales. */
    MT_PRUEBA(test_autoriza_credencial_valida);
    MT_PRUEBA(test_rechaza_formato_invalido);
    MT_PRUEBA(test_rechaza_checksum_erroneo);
    MT_PRUEBA(test_rechaza_no_autorizada);
    MT_PRUEBA(test_formato_gana_al_orden);
    MT_PRUEBA(test_lista_vacia_no_autoriza);

    return mt_informe("build/reports/credencial.xml", "credencial");
}
