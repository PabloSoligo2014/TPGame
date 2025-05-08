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

//return -1,No hay memoria
//return 1 Inserto Directamente
//return 2 Inserto e incremento la cantidad de elementos
int Vector_insertInOrder(Vector* v,void*nuevoNodo,Cmp cmp){
   if(v->ce == v->tam){
      if(_resize(v,(v->tam+2))==-1){
         return -1;
      }
   }
   void*pos = v->vec; //se guarda la primer pos

   // TODO: Is this specific condition necessary? I don't think so.
   if(v->ce == 0){ //si no hay elementos inserta directamente
     memcpy(pos,nuevoNodo,sizeof(tNodo));
     v->ce++;
     return 1;
   }

   void* ultPos = pos +( (v->ce)*sizeof(tNodo)); //guardo la ultima posicion

   while( pos<ultPos && cmp(nuevoNodo , ultPos - sizeof(tNodo)) == 1 ){//nuevoNodo<ultPos retorna 1
     memcpy(ultPos,ultPos - sizeof(tNodo),sizeof(tNodo));
     ultPos-=sizeof(tNodo);
   }

    memcpy(ultPos,nuevoNodo,sizeof(tNodo));
    v->ce++;
    return 2; //se inserto y se aumento
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
