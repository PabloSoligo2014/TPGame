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


void Vector_map(Vector*v, void action(void*)){
    tNodo* n = v->vec;
    int i;
    for(i=0;i<v->ce;i++){
        action(n->dato);
        n++;
    }

}


void Vector_destroy(Vector*v){
    free(v->vec);
}

// Funci�n para insertar en orden
int Vector_insertInOrder(Vector* v, void* elemento, size_t tamDato, Cmp cmp) {
    //Si existe sobreescribe
    // Verificar si hay espacio para el nuevo elemento
    int c = -1;
    tNodo* actual;


    // Esto no siempre es necesario
    if (v->ce == v->tam) {
        if (_resize(v, v->tam + 2) == -1) {
            return -1;
        }
    }

    actual = v->vec + v->ce;

    // Desplazamos los elementos mayores

    while ((actual > v->vec) && ((c = cmp(elemento, (actual-1)->dato)) < 0)) {
        *actual = *(actual-1);
        actual--;
    }


    // Insertamos el nuevo nodo
    if ((actual >= v->vec)&&(c==0)){
        actual--;
        memcpy(actual->dato, elemento, tamDato);
    }else{
        actual->dato = malloc(tamDato);  // Reservamos memoria para el nuevo dato
        if (!actual->dato)
            return -1;
        memcpy(actual->dato, elemento, tamDato);
        actual->tam = tamDato;
        v->ce++;
    }


    return 1;
}
// Funci�n de b�squeda binaria
void* Vector_bsearch(Vector* v, void* valor, Cmp cmp) {
    tNodo* ini = v->vec;
    tNodo* fin = v->vec + v->ce - 1;

    while (ini <= fin) {
        tNodo* medio = ini + (fin - ini) / 2;
        int comp = cmp(valor, medio->dato);

        if (comp == 0) {
            return medio->dato;  // Se encontr� el valor
        } else if (comp > 0) {
            ini = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return NULL;  // No se encontr� el valor
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

//Funci�n de comparaci�n entre dos Nodos
int compararInt(const void* a, const void* b) {
    int valorA = *(int*)a;
    int valorB = *(int*)b;
    return valorA - valorB;
}
