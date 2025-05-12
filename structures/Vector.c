#include "Vector.h"

int Vector_create(Vector*v, unsigned tamVector){

   v->vec = malloc(tamVector*(sizeof(tNodo)));
   if(!v->vec){
    return 0;
   }

   v->ce = 0;
   v->tam = tamVector;

   return 1;
}
void Vector_destroy(Vector*v){
    free(v->vec);
}

// Función para insertar en orden
int Vector_insertInOrder(Vector* v, void* elemento, size_t tamDato, Cmp cmp) {
    tNodo nodo;
    nodo.dato = malloc(tamDato);  // Reservamos memoria para el nuevo dato
    if (!nodo.dato) return -1;

    memcpy(nodo.dato, elemento, tamDato);
    nodo.tam = tamDato;

    // Verificar si hay espacio para el nuevo elemento
    if (v->ce == v->tam) {
        if (_resize(v, v->tam + 2) == -1) {
            free(nodo.dato);  // Liberamos la memoria si falla el redimensionado
            return -1;
        }
    }

    // Desplazamos los elementos mayores
    int i = v->ce - 1;
    while (i >= 0 && cmp(nodo.dato, v->vec[i].dato) < 0) {
        v->vec[i + 1] = v->vec[i];
        i--;
    }

    // Insertamos el nuevo nodo
    v->vec[i + 1] = nodo;
    v->ce++;

    return 1;
}
// Función de búsqueda binaria
tNodo* Vector_bsearch(Vector* v, void* valor, Cmp cmp) {
    tNodo* base = v->vec;
    int ini = 0;
    int fin = v->ce - 1;

    while (ini <= fin) {
        int medio = ini + (fin - ini) / 2;
        int comp = cmp(valor, base[medio].dato);
        if (comp == 0) {
            return &base[medio];  // Se encontró el valor
        } else if (comp > 0) {
            ini = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return NULL;  // No se encontró el valor
}
int Vector_getByPos(Vector* v, int pos, void * valor, size_t tamValor){

    tNodo * ini = ((v->vec) + pos);
    void* aux = ini->dato;
    int i;

    if(pos<=v->ce && pos >= 0){
      for(i=0;i<tamValor;i++){
        *(char*)valor = *(char*)aux;
        aux++;
        valor++;
      }
      return 1;
    }

    return -1;//si la posicion es incorrecta
}

int _resize(Vector* v,size_t nuevoTamanio){

  void * nv = realloc((void*)v->vec,nuevoTamanio*(sizeof(tNodo)));
  if(nv == NULL){
    return -1;
  }
  v->vec = (tNodo*)nv;
  v->tam = nuevoTamanio;
  return 1;
}

//Función de comparación entre dos Nodos
int compararInt(const void* a, const void* b) {
    int valorA = *(int*)a;
    int valorB = *(int*)b;
    return valorA - valorB;
}
