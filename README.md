# TC-1031-Proyecto-A - Registro de records de Super Mario Odyssey

Este programa escribe los datos que correspode a los tiempos de speedrun de Super Mario Odyssey. Un speedrun consiste en tratar de completar ciertas cosas dentro de un juego en el menor tiempo posible, dependiendo de la categoria que se corre.

## Competencias

### SICT0301B Presenta Casos de Prueba correctos y completos para todas las funciones y procedimientos del programa

El archivo cpp "pruebasa.cpp" contiene casos de prueba para el programa

### SICT0302B Selecciona un algoritmo de ordenamiento adecuado al problema

El programa cuenta con un ordenamiento de Merge para ordenar los datos de manera que los tiempos en una lista vinculada esten a la cabeza.

### SICT0302B Selecciona y usa una estructura lineal adecuada al problema

El programa cuenta con un vector de apuntadores que es vinculado de ambos lados. Con el proposito de tener un registro de los tiempos en el orden que se agregan, esta misma lista puede ser ordenada por el algoritmo de ordenamiento antes mencionado.

### SICT0302B Usa un árbol adecuado para resolver un problema

El programa usa un arbol para tener un registro ordenado de los tiempos que se le alimentan, teniendo como raiz al primer registro que se le da.

### SICT0303B Implementa mecanismos de escritura de archivos correctos

El programa crea un archivo csv para imprimir los tiempos en la forma que dicta el usuario en el main.

# Analisis de complejidad de tiempo

## Funciones de clase Run

### find

Esta funcion hace recursion consigo misma para verificar si existe un nodo en el arbol de Runs que contenga el nombre y el tiempo que se piensan agregar para evitar repeticiones y sobreescrituras accidentales. Si encuentra el nombre y tiempo iguales, regresa True. Su complejidad de tiempo es de O(n) para el peor de los casos.

### add

Esta funcion hace recursion consigo misma para encontrar la posicion adecuada para agregar un nodo, una vez que lo encuentra, regresa este mismo nodo. Su complejidad de tiempo es de O(n) para el peor de los casos.

### succesor

Esta funcion recorre el arbol de tal forma que encuentra un valor para nombrar sucesor, preferiblemente de tal forma que regrese el valor que numericamente hablando le siga en decremento para reemplazar un puesto en el nodo. Su complejidad de tiempo es de O(n) para el peor de los casos debido a que existe la posibilidad de que el sucesor sea n.

### remove

Esta funcion hace recursion consigo misma para encontrar el tiempo que se debe borrar, nombrando un sucesor para poner en el lugar del nodo que se borará. Su complejidad de tiempo es de O(n) para el peor de los casos.

### removeChilds

Esta funcion hace recursion consigo misma para borrar todos los nodos y las conexiones faster o slower entre los Runs con el fin de liberar memoria. Su complejidad de tiempo es de O(n) para el peor de los casos.

### removeLinks

Esta funcion hace recursion consigo misma para borrar todas las conexiones nexst o previous entre los Runs. Su complejidad de tiempo es de O(n) para el peor de los casos.

### fromFastest

Esta funcion hace recursion consigo misma para imprimir los tiempos de manera ascendente (más rápidos al principio) sin importar el orden de agregación. Su complejidad de tiempo es de O(n) para el peor de los casos.

### byName

Esta funcion hace recursion consigo misma para imprimir los tiempos de manera ascendente (más rápidos al principio) sin importar el orden de agregación, de tal forma que solo se impriman los tiempos del nombre que se le da. Su complejidad de tiempo es de O(n) para el peor de los casos.

### maxHeight

Esta funcion hace recursion consigo misma para obtener el tamaño del árbol de busqueda binaria, comparando las distintas alturas entre las ramas. Su complejidad de tiempo es de O(n) para el peor de los casos.

### printTime

Esta funcion recibe los segundos totales de un Run, para luego convertirlos a un formato HH:MM:SS que es comunmente usado. Su complejidad de tiempo es de O(1) para el peor de los casos.

### printLinkList

Esta funcion hace recursion consigo misma para imprimir los tiempos en el orden que tienen en un dado momento, si la lista no esta ordenada los imprimira en el orden que se agregaron.  Su complejidad de tiempo es de O(1) para el peor de los casos.

##Funciones de clase BSTree

### mergeSplit (privada)

Esta funcion hace recursion para dividir una lista en mitades hasta que ya no pueda, luego manda dichas mitades a fusionarse en mergeArr para luego hacer la copia en copyArr. Su complejidad de tiempo es de O(n log n) para el peor de los casos. Debido a los multiples recorridos que hace en la lista.

### mergeArr (privada)

Esta funcion añade las mitades que recibe de tal forma que ordena los datos de forma ascendente. Su complejidad de tiempo es de O(n) para el peor de los casos.

### copyArr (privada)

Esta funcion copia los valores de la lista ordenada a la lista principal de la clase.  Su complejidad de tiempo es de O(n) para el peor de los casos.

### empty

Esta función regresa un true si no hay ninguna raíz. Su complejidad de tiempo es de O(1) para el peor de los casos.

### add

Esta función primero se asegura de que el arbol no esta vacio, para así crear una raíz, caso contrario manda a llamar la función add de clase Run para encontrar el lugar adecuado para el nuevo nodo. Una vez que regresa, agrega el apuntador al vector de apuntadores. Su complejidad de tiempo es de O(n) para el peor de los casos.

### remove

Esta función primero manda a llamar a la función find de clase Run para asegurarse de que el nodo a borrar existe en el árbol y así evitar que borre otro valor. Su complejidad de tiempo es de O(n log n) para el peor de los casos debido a que recorre el árbol hasta llegar a la misma posición 2 veces.

### removeAll

Esta función primero checa que la raíz no sea nula. Si la raíz tiene un valor asociado con ella, mandará a llamar la función removeLinks y removeChilds (en ese orden) de la clase Run, para eliminar todos los nodos y vinculos que haya entre estos. Después define la cabeza, raíz, y cola como nulos. Finalmente, elimina los contenidos de la lista con un clear y define el tamaño como 0. Su complejidad de tiempo es de O(n log n) para el peor de los casos debido a que hace un recorrido completo de la lista, y luego otro del arbol. 

### fromFastest

Esta función manda a llamar a la función fromFastest de la clase Run, con el fin de imprimir los tiempos desde el más rápido sin importar el orden que tenga el vector de apuntadores. Su complejidad de tiempo es de O(n) para el peor de los casos. 

### byName

Esta función manda a llamar a la función byName de la clase Run, con el fin de imprimir solo los tiempos del nombre que se le de. Su complejidad de tiempo es de O(n) para el peor de los casos. 

### size

Esta función regresa el conteo de elementos que están en el arbol. Su complejidad de tiempo es de O(1) para el peor de los casos.

### height

Esta función manda a llamar la función maxHeight de la clase Run, con el fin de desplegar la altura maxima del arbol. Su complejidad de tiempo es de O(n) para el peor de los casos.

### linkTimes

Esta funcion recorre la lista desde la posición 0 hasta la posición n, para poder vincular los tiempos entre sí sin excepciones y tomando en cuenta si esta en la última posición. Su complejidad de tiempo es de O(n) para el peor de los casos.

### sortMerge

Esta funcion primero crea un arreglo secundario del mismo tamaño que la lista de Runs, con el fin de ordenarlos de forma ascendente mediante el uso de las funciones privadas mergeSplit, mergeArr, y copyArr. Su complejidad de tiempo es de O(n log n) para el peor de los casos.

### printLinkList

Esta funcion primero vincula los tiempos con linkTimes, luego llama a la funcion printLinkList de clase Run para imprimir los tiempos desde la cabeza. Su complejidad de tiempo es de O(n log n) para el peor de los casos debido a que primero va de 0 a n para el vinculamiento, y luego hace otro recorrido de 0 a n para imprimir los valores.
