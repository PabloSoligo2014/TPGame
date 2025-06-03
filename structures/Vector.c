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
    v->ce = 0;
    v->tam = 0;
}

//Funcion para insertar en orden y no repetir
int Vector_insertInOrderNoRepeat(Vector* v, void* elemento, size_t tamDato, Cmp cmp) {

    tNodo nodo;
    nodo.dato = malloc(tamDato);  // Reservamos memoria para el nuevo dato
    if (!nodo.dato) return -1;

    memcpy(nodo.dato, elemento, tamDato);
    nodo.tam = tamDato;

    void* search = Vector_bsearch(v,nodo.dato,cmp); //busca el elemento por la condicion

    if(search){
        memcpy(search,nodo.dato,tamDato); //si lo encuentra lo reemplaza y retorna 2
        return 2;
    }

    // Verificar si hay espacio para el nuevo elemento
    if (v->ce == v->tam) {
        if (_resize(v, v->tam + 2) == -1) {
            free(nodo);
            return -1;
        }
    }

    // Puntero al �ltimo nodo v�lido
    tNodo* actual = v->vec + v->ce - 1;

    // Puntero a la posici�n donde vamos a insertar
    tNodo* destino = v->vec + v->ce;

    // Desplazamos los elementos mayores
    while (actual >= v->vec && cmp(nodo.dato, actual->dato) < 0) {
        *destino = *actual;
        destino--;
        actual--;
    }

    // Insertamos el nuevo nodo
    *destino = nodo;
    v->ce++;
    return 1;
}

// Funci�n para insertar en orden
int Vector_insertInOrder(Vector* v, void* elemento, size_t tamDato, Cmp cmp) {

    // Verificar si hay espacio para el nuevo elemento
    if (v->ce == v->tam) {
        if (_resize(v, v->tam + 2) == -1) {
            return -1;
        }
    }

    tNodo nodo;
    nodo.dato = malloc(tamDato);  // Reservamos memoria para el nuevo dato
    if (!nodo.dato) return -1;

    memcpy(nodo.dato, elemento, tamDato);
    nodo.tam = tamDato;

    // Puntero al �ltimo nodo v�lido
    tNodo* actual = v->vec + v->ce - 1;

    // Puntero a la posici�n donde vamos a insertar
    tNodo* destino = v->vec + v->ce;

    // Desplazamos los elementos mayores
    while (actual >= v->vec && cmp(nodo.dato, actual->dato) < 0) {
        *destino = *actual;
        destino--;
        actual--;
    }

    // Insertamos el nuevo nodo
    *destino = nodo;
    v->ce++;

    return 1;
}

// Funci�n de b�squeda binaria
void* Vector_bsearch(Vector* v, void* valor, Cmp cmp) {
    tNodo* ini = v->vec;
    tNodo* fin = v->vec + v->ce - 1;

    while (ini <= fin) {
        tNodo* medio = ini + (fin - ini) / 2;
        int comp = cmp(valor, medio->dato);

        if (comp == 0) {   // Se encontr� el valor
            return medio->dato;  // Se retorna la direccion
        }
        else
        {
            if (comp > 0) {
                ini = medio + 1;
            } else {
                fin = medio - 1;
            }
        }
    }
    return NULL;  // No se encontr� el valor
}

int Vector_getByPos(Vector* v, int pos, void * valor, size_t tamValor){

    tNodo * ini = ((v->vec) + pos);
    void* aux = ini->dato;
    int i;

    if(v->ce!= 0 && pos<=v->ce && pos >= 0){
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

void Vector_map(Vector*v,Accion accion){
  int i;
  tNodo*pivot= v->vec;

  for(i=0;i<v->ce;i++){
    accion(pivot->dato);
    pivot++;
  }
}

//Funci�n de comparaci�n entre dos Nodos
int compararInt(const void* a, const void* b) {
    int valorA = *(int*)a;
    int valorB = *(int*)b;
    return (valorA - valorB);
}
