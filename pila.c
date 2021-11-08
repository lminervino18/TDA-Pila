#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

//CONSTANTES
#define CANTIDAD_INICAL 0
#define CAPACIDAD_INICIAL 2
#define VACIO 0
#define DOBLE 2
#define CUADRUPLE 4
#define MITAD 2
#define TAMANIO_ELEMENTOS sizeof(void*)

/* Definición del struct pila proporcionado por la cátedra.
 */
typedef struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
} pila_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t *pila_crear(void) {

    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }

    pila->datos = malloc(TAMANIO_ELEMENTOS * CAPACIDAD_INICIAL);

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }

    pila->cantidad = CANTIDAD_INICAL;
    pila->capacidad = CAPACIDAD_INICIAL;
    return pila;
}

bool _pila_redimensionar(pila_t *pila, size_t nueva_capacidad) {

    void** auxiliar = realloc(pila->datos, nueva_capacidad * TAMANIO_ELEMENTOS);

    if (auxiliar) {
        pila->datos = auxiliar;
        pila->capacidad = nueva_capacidad;
        return true;
    }

    return false;
}

void pila_destruir(pila_t *pila) {

    free(pila->datos);
    free(pila);

}

bool pila_esta_vacia(const pila_t *pila) {
    
    return pila->cantidad == VACIO;

    }

bool pila_apilar(pila_t *pila, void *valor) {

    if (pila->cantidad == pila->capacidad) { 

        if (!_pila_redimensionar(pila, pila->capacidad*DOBLE)) return false;

        }

    pila->datos[pila->cantidad++] = valor;
    return true;

}

void *pila_ver_tope(const pila_t *pila) {

    if (pila_esta_vacia(pila)) return NULL;

    return pila->datos[pila->cantidad - 1];

}

void *pila_desapilar(pila_t *pila){

    if (pila_esta_vacia(pila)) return NULL;

    void* elemento_a_desapilar = pila->datos[(pila->cantidad--) - 1];

    if (pila->cantidad*CUADRUPLE <= pila->capacidad && pila->capacidad > CAPACIDAD_INICIAL) {

        if (!_pila_redimensionar(pila, pila->capacidad / MITAD)) return elemento_a_desapilar;

    }
    
    return elemento_a_desapilar;
}

