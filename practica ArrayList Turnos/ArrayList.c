#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Asigne un nuevo arrayList con elementos AL_INITIAL_VALUE.
 * \param void
 * \return ArrayList * Return (NULL) si Error [si no puede asignar memoria]
 * - (puntero a la nueva lista de arreglos) si está bien
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));


    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;

            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Agregue un elemento a arrayList y si es
 * nesesario cambia el tamaño de la matriz
 * \param pList ArrayList * Puntero a arrayList
 * \param pElement void * Puntero al elemento
 * \return int Return (-1) si Error [pList o pElement son puntero NULL] - (0) si Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int flag=0;

    if(this!=NULL && pElement!=NULL)
    {
        if(this->size == this->reservedSize)
        {
            if(resizeUp(this))
            {
                flag=1;
            }
        }

        if(flag==0)
        {
            *(this->pElements+this->size)=pElement;
            this->size++;
            returnAux=0;
        }
    }

return returnAux;
}

/** \brief  Eliminar arrayList
 * \param pList ArrayList * Puntero a arrayList
 * \return int Return (-1) si Error [pList es puntero NULL] - (0) si Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        al_clear(this);

        returnAux = 0;
    }
    return returnAux;
}

/** \brief  Retorna el tamaño del ArrayList. Verificando que el puntero pList sea distinto de NULL.
 *          Si la  verificación falla la función retorna (-1) y si tiene éxito retorna la longitud del array.
 * \param pList ArrayList * Puntero a arrayList
 * \return int Devuelve la longitud de la matriz o (-1) si Error [pList es un puntero NULL]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
      returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Retorna un puntero al elemento que se encuentra en el índice especificado.
            Verificando que el puntero pList sea distinto de NULL y que index sea positivo e inferior al tamaño del array.
 *          Si la verificación falla la función retorna (NULL) y si tiene éxito retorna el elemento.
 *\ param pList ArrayList * Puntero a arrayList
 *\ param index int Índice del elemento
 *\ return void * Return (NULL) si Error [pList es puntero NULL o índice no válido] - (Puntero al elemento) si Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;

    if(this!=NULL && index >= 0 && index <= this->len(this))
    {
        returnAux = *(this ->pElements + index);
    }

    return returnAux;
}


/** \brief  Comprueba si existe el elemento que se le pasa como parámetro.
 *          Verificando que tanto el puntero pList como pElement sean distintos de NULL.
 *          Si la verificación falla la función retorna (-1) , si encuentra el elemento (1) y si no lo encuentra (0).
 * \param pList ArrayList * Puntero a arrayList
 * \param pElement void * Puntero al elemento
 * \return int Retorno (-1) si Error [pList o pElement son puntero NULL]
 * - (0) si está bien pero no encontró un elemento
 * - (1) si esta lista contiene al menos un elemento pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;

    if (this !=NULL && pElement!=NULL)
    {
        returnAux =0;

            for(int i=0; i<al_len(this); i++)
            {
                if(al_get(this,i) == pElement)
                {
                    returnAux =1;
                    break;
                }
            }
    }
return returnAux;
}

 /** \brief Inserta un elemento en el ArrayList, en el índice especificado.
 *          Verificando que tanto el puntero pList como pElement sean distintos de NULL y que index sea positivo e inferior al tamaño del array.
 *          Si la verificación falla la función retorna (-1) y si tiene éxito (0).
 * \param pList ArrayList * Puntero a arrayList
 * \param index int Índice del elemento
 * \param pElement void * Puntero al elemento
 * \return int Retorno (-1) si Error [pList o pElement son puntero NULL o índice no válido]
 * - (0) si está bien
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux = -1;

    if(this!=NULL && pElement!=NULL)
    {
         if(index==(al_len(this)))
        {
            al_add(this, pElement);
        }
            else if(index<(al_len(this)) && index>=0)
            {
                *(this->pElements+index)=pElement;
                returnAux=0;
            }
    }
    return returnAux;
}

/** \brief Elimina un elemento del ArrayList, en el índice especificado.
 *         Verificando que el puntero pList sea distinto de NULL y que index sea positivo e inferior al tamaño del array.
 *         Si la verificación falla la función retorna (-1) y si tiene éxito (0).
 * \param pList ArrayList * Puntero a arrayList
 * \param index int Índice del elemento
 * \return int Retorno (-1) si Error [pList es puntero NULL o índice no válido]
 * - (0) si está bien
 */
int al_remove(ArrayList* this,int index)
{
    int returnAux = -1;

    if(this!=NULL && index>=0 && index<(this->len(this)))
    {
        contract(this, index);
        returnAux=0;
    }
    return returnAux;
}


/** \brief  Borra todos los elementos de ArrayList. Verificando que el puntero pList sea distinto de NULL.
            Si la verificación falla la función retorna (-1) y si tiene éxito (0).
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    void** aux;

    if(this!=NULL)
    {
        this->size=0;
        aux=(void**)realloc(this->pElements, sizeof(void*)*(AL_INCREMENT));

        if(aux != NULL)
      {
         this->pElements = aux;
         this->reservedSize=AL_INCREMENT;
         returnAux = 0;
      }
    }

    return returnAux;
}

/** \brief  Retorna un nuevo ArrayList copia del ArrayList original.
 *          Verificando que el puntero pList sea distinto de NULL.
 *          Si la verificación falla la función retorna (NULL) y si tiene éxito retorna el nuevo array.
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
//1)se crea una lista vacia2)add-get/iterando

{
    ArrayList* returnAux = NULL;
    int i = 0;
    if(this!= NULL)
    {
        returnAux = al_newArrayList();

        if(returnAux != NULL)
        {
            for(i = 0; i<=this->len(this); i++)
            {
                al_add(returnAux, al_get(this, i));
            }
        }
    }
    return returnAux;
}


/** \brief  Desplaza los elementos e inserta en la posición index.
            Verificando que tanto el puntero pList como pElement sean distintos de NULL y que index sea positivo e inferior al tamaño del array.
            Si la verificación falla la función retorna (-1) y si tiene éxito (0).
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL && pElement!=NULL)
    {
        if (index >=0 && index<=this->len(this))
            {
                al_add(this, pElement);

                if(index<this->len(this))
                {
                    expand(this,index);
                    al_set(this,index,pElement);
                }
            }
            returnAux=0;
    }
    return returnAux;
}


/** \brief  Retorna el índice de la primera aparición de un elemento (element) en el ArrayList.
            Verificando que tanto el puntero pList como pElement sean distintos de NULL.
            Si la verificación falla o no encuentra el elemento la función retorna (-1) y si encuentra el elemento retorna su índice.
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int tamanio;

    if (this !=NULL && pElement!=NULL )
    {
        tamanio = this->len(this);

        for(int i=0; i<tamanio; i++) //break y retorno el indice
        {
            if(*(this->pElements+i)== pElement)
            {
                returnAux=i;
                break;
            }
        }
    }
    return returnAux;

}


/** \brief  Retorna cero si contiene elementos y uno si no los tiene.
            Verificando que el puntero pList sea distinto de NULL.
            Si la verificación falla la función retorna (-1), si esta vacío (1) y si contiene elementos (0).
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        if(this->len(this) == 0)
        {
            returnAux=1;
        }
            else
            {
                returnAux=0;
            }
    }
    return returnAux;
}




/** \brief  Retorna un puntero al elemento que se encuentra en el índice especificado y luego lo elimina de la lista.
            Verificando que el puntero pList sea distinto de NULL y que index sea positivo e inferior al tamaño del array.
            Si la verificación falla la función retorna (NULL) y si tiene éxito retorna el elemento.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)
{
    void* returnAux = NULL;

    if (this !=NULL && index >=0 && index<(this->len(this)))
    {
        returnAux = *(this->pElements+index);
        contract(this,index);
    }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)
{
    void* returnAux = NULL;
    void *pElementAux;
    int i;

    if(this!=NULL && from>=0 && from<=(this->len(this)) &&  to>= 0 && to<=(this->len(this)) && from < to)
    {
        returnAux=al_newArrayList();

        if(returnAux!=NULL)
        {
            for(i=from; i<to; i++)
            {
                pElementAux=al_get(this,i);
                al_add(returnAux,pElementAux);
            }
        }
    }
return returnAux ;
}

/** \brief  Comprueba si los elementos pasados son contenidos por el ArrayList.
            Verificando que tanto el puntero pList como pList2 sean distintos de NULL.
            Si la verificación falla o no encuentra el elemento la función retorna (-1),
            si las listas difieren (0) y si ambas listas son iguales retorna (1).
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)
{
    int returnAux = -1;
    int i;

    if(this!=NULL && this2!= NULL)
    {
        if(this2->len(this2)==this->len(this))
        {
            for(i=0; i<this->len(this); i++)
            {
                if(( al_contains(this,al_get(this2,i)))==1)
                {
                    returnAux=1;
                }
                else
                {
                    returnAux=0;
                    break;
                }
            }
        }
        else
        {
            returnAux= 0;
        }
    }
return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order)
{//modificar los for de modo que devuelva 1 o -1 acorde al sort ascendente o descendente
    int returnAux = -1;
    void *aux;
    int i,j;
    if(this!=NULL && pFunc!=NULL)
    {
        if(order==1)//sort DOWN
        {
            for(i=0 ; i<this->size-1 ; i++)
            {
                for(j=i+1; j<this->size; j++)
                {
                    if((pFunc(al_get(this,i), al_get(this,j)))==1)
                    {
                        aux=al_get(this,i);
                        al_set(this,i,al_get(this,j));
                        al_set(this,j,aux);
                    }
                }
            }
            returnAux=0;
        }
        if(order==0)//sort UP
        {
             for(i=0 ; i<this->size-1 ; i++)
            {
                for(j=i+1; j<this->size; j++)
                {
                    if((pFunc(al_get(this,i), al_get(this,j)))==-1)
                    {
                        aux=al_get(this,i);
                        al_set(this,i,al_get(this,j));
                        al_set(this,j,aux);
                    }
                }
            }
            returnAux=0;
        }
    }

   return returnAux;

}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
 /** \brief Incrementa la cantidad de elementos en pList en los elementos AL_INCREMENT.
 * \param pList ArrayList * Puntero a arrayList
 * \return int Retorno (-1) si Error [pList es puntero NULL o no puede asignar memoria]
 * - (0) si está bien
 */
int resizeUp(ArrayList* this)
{
   int returnAux = -1;
   void** aux;

   if(this!=NULL)
   {
      aux = (void**)realloc(this->pElements, sizeof(void*)*(this->reservedSize+AL_INCREMENT));

      if(aux != NULL)
      {
         this->pElements = aux;
         this->reservedSize=(this->reservedSize + AL_INCREMENT);
         returnAux = 0;
      }
   }
   return returnAux;
}

/** \brief Expandir una lista de array
* \param pList ArrayList * Puntero a arrayList
* \param index int Índice del elemento
* \return int Retorno (-1) si da Error [pList es puntero NULL o índice no válido]
* - (0) si está bien
*/
int expand(ArrayList* this,int index)
{
    int i=0;
    int returnAux=-1;

    if(this != NULL && (index >= 0 && index <= this->size))
    {
        for(i = this->size-1; i >= index; i--)
        {
            this->pElements[i+1] = this->pElements[i];
        }
        returnAux = 0;
    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
 /** \brief Contrae una lista de arreglos
 * \param pList ArrayList * Puntero a arrayList
 * \param index int Índice del elemento
 * \return int Retorno (-1) si Error [pList es puntero NULL o índice no válido]
 * - (0) si está bien
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    int auxTam;

    auxTam=this->len(this);

        for(int i=index;i<auxTam;i++)
        {
            *(this->pElements+i)=*(this->pElements+(i+1));
        }
        returnAux=0;
        this->size--;
    }
    return returnAux;
}


