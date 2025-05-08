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

int Vector_insertInOrder(Vector* v,void*elemento,size_t tamDato,Cmp cmp){
   tNodo nodo;
   nodo.dato = (void*)elemento;
   nodo.tam = tamDato;

   if(v->ce == v->tam){
      if(_resize(v,(v->tam+2))==-1){
         return -1;
      }
   }
   void*pos = v->vec;

   if(v->ce == 0){
     memcpy(pos,&nodo,sizeof(tNodo));
     v->ce++;
     return 1;
   }

   void* ultPos = pos +( (v->ce)*sizeof(tNodo));

   while( pos<ultPos && cmp(&nodo , (ultPos - sizeof(tNodo))) < 0 ){
     memcpy(ultPos,ultPos - sizeof(tNodo),sizeof(tNodo));
     ultPos-=sizeof(tNodo);
   }

   memcpy(ultPos,&nodo,sizeof(tNodo));
   v->ce++;
   return 2;
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
