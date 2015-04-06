Same Game Resolver
===============

Introducción
------------

El objetivo de este trabajo es la implementación de un solucionador del juego SAME.

El trabajo permite equipos de hasta 2 personas. Se permite compartir información, pero no es permitido compartir código. Trabajos que tengan porciones significativas de código, o copiados de internet, serán anulados.

Descripción
-----------

El Juego Same (https://en.wikipedia.org/wiki/SameGame) consiste en un campo rectangular inicialmente lleno de bloques de colores. El jugador puede seleccionar un grupo (haciendo clic en una posición) para ser eliminado. Dos bloques están en el mismo grupo si tienen el mismo color y son adyacentes (vertical u horizontalmente). Después de seleccionar un grupo, los bloques que se encontraban por encima del grupo de bloques se caen y se llenan los espacios en blanco. Cuando una columna se queda sin bloques, los bloques se desplazan a la derecha a la izquierda. Sólo los grupos con más de un bloque se pueden seleccionar.

La figura (http://www.ime.usp.br/~alvaroma/ucsp/proglang/gameSAME.png) presenta 4 etapas del juego.

    1. Juego inicial;
    2. grupo seleccionado para eliminación;
    3. despues de la eliminación del grupo, los bloques caen;
    4. bloques desplazados a la izquierda.

Una solución para el juego SAME es una secuencia de posiciones que cuando se "clicka" se eliminan todos los bloques.

El trabajo consiste en la implementación de un solucionador para el juego SAME.

El programa debe recibir como parámetro en la línea de comando el nombre de un archivo con la especificación del juego y escribir en la salida estándar una resolución para el juego, o no-solucion, si no hay una solución al juego. Una resolución consiste en una secuencia de movimientos (posiciones) y los resultados (campo obtenido después de cada jugada). Las jugadas y los resultados deben estar separados por una línea en blanco.

Por ejemplo, considere un archivo con el siguiente contenido:

2 1 3 1
2 2 2 3
2 3 3 1

En el archivo de entrada, las filas y las columnas son las siguientes:

2 | 2 1 3 1
1 | 2 2 2 3
0 | 2 3 3 1
--+--------
  | 0 1 2 3
  
Una posible solución a este juego es:

0 0

0 0 1 0
1 3 3 0
3 3 1 0

1 2

0 0 0 0
0 1 0 0
1 1 0 0

1 1

0 0 0 0
0 0 0 0
0 0 0 0

Tenga en cuenta que las posiciones se representan por el número de fila seguida por el número de columna.

Una estrategia simple para encontrar una solución para un juego SAME, es:

    1. Seleccionar cualquier grupo;
    2. eliminar el grupo;
    3. si no existe un grupo que pueda ser eliminado, retroceder a la jugada anterior y seleccionar otro grupo;
    4. se se acaban las opciones de grupos en la primera jugada, entonces el juego no tiene solución;
    5. utilizar recursivamente el mismo método para resolver el juego a partir del paso 2.

Tenga en cuenta que este es un problema de búsqueda. Este tipo de problema es muy adecuado para ser resuelto con Prolog.
