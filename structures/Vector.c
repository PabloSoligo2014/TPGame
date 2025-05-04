#include<Vector.h>

int crearVector(Vector*vector, unsigned tamVector){

   vector->vec = malloc(tamVector*(sizeof(tNodo)));
   if(!vector->vec){
    return 0;
   }

   vector->ce = 0;
   vector->tam = tamVector;

   return 1;
}
void destruirVector(Vector*vector){
    free(vector->vec);
}

int insertarOrdenadoTDA(Vector* vector,void*nuevoNodo,Cmp cmp){
   if(vector->ce == vector->tam){
      if(redimensionarTDA(vector,(vector->tam+2))==-1){
         return -1;
      }
   }
   void*pos = vector->vec; //se guarda la primer pos

   if(vector->ce == 0){ //si no hay elementos inserta directamente
     memcpy(pos,nuevoNodo,sizeof(tNodo));
     vector->ce++;
     return 1;
   }

   void* ultPos = pos +( (vector->ce)*sizeof(tNodo)); //guardo la ultima posicion

   while( pos<ultPos && cmp(nuevoNodo , ultPos - sizeof(tNodo)) == 1 ){//nuevoNodo<ultPos retorna 1
     memcpy(ultPos,ultPos - sizeof(tNodo),sizeof(tNodo));
     ultPos-=sizeof(tNodo);
   }

    memcpy(ultPos,nuevoNodo,sizeof(tNodo));
    vector->ce++;
    return 2; //se inserto y se aumento
}

int redimensionarTDA(Vector* vector,size_t nuevoTamanio){

  void * nv = realloc((void*)vector->vec,nuevoTamanio*(sizeof(tNodo)));
  if(nv == NULL){
    return -1;
  }
  vector->vec = (tNodo*)nv;
  vector->tam = nuevoTamanio;
  return 1;
}
