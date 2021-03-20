# Organicacón de archivos

QuackEngineSol es la solucion y en este repos solo habrá una sola solucion. <br>
Dentro de esta carpeta tenemops el bin (donde van todos los exe y donde deberian ir todos los assets.<br>
En la caprta es Projects donde van todos los proyectos(física, sonido, ogre...) y el QuackEnginePro es el proyecto general del motor, y aquí es donde irá la lógica principal del motor,<br>
Src es donde va a ir todo el código fuente organizandolo en carpetas segun el proyecto, dentro de esa carpeta segun 
la funcionalidad (movimiento, render...), y dentro de la funcionalidad seguns si es .cpp o .h. Por último tenemos el Temp donde van todos los archivos temporales (la compilación) y no se sube al git así que chill.<br>
Aquí dejo un esquema para que quede mas claro.
![alt text](OrganicacionP3.png)


## Para crear arvhivos nuevos:
A la hora de crear los archivos (.cpp y .h) no se crean desde visual por que los crea en donde le da la gana, hay que abrir el explorador de archivos, buscar en \Src la carpeta del proyecto al que pertenece, y dentro de esa carpeta navegar hasta donde tiene sentido que esté y crearlo alli a mano. Luego se pasa a visual y se le da a *click derecho en el proyecto*, *agregar, elemento existente* y se busca el que queremos.

## Para crear proyecos nuevos:
<p>*clic derecho en la solución, agregar, nuevo proyecto*. Visual una vez mas lo crea donde le da la gana y lo tenemos que mover. Primero quitamos (no elimanr) el .cpp y lo movemos manualmente a la carpeta dentro de \Src que corresponda. Ahora quitamos el proyecto (que se ha creado en la carpeta \QuackEngineSol) y lo movemos a \QuackEngineSol\Projects\"nueva carpeta". Ya tenemos todo movido y podemos volver a visual y agregarlo de nuevo: /clic derecho en la solucion, agregar, proyecto existente, y buscamos el .vcxproj. Ahora solo falta agregar el .cpp que hemos quitado antes.</p>


**IMPORTANTE:** se tiene que revisar que todas las rutas estén bien para que se situen automáticamente en las carpetas que queremos, para eso tenemos que ir a las propiedades del proyecto (*clic derecho en el proyecto y abajo del todo esta propiedades*). En general queremos que los proyectos que añadimos sean bibliotecas (excepto el proyecto principal de los dos juegos) <br>
Tenemos que asegurarnos de que estén estas opciones: (si son bibliotecas) <br>
**Directorio de salida:** $(SolutionDir)lib\$(Platform)\$(Configuration)\ <br>
**Directorio intermedio:** $(SolutionDir)Temp\$(ProjectName)\$(Platform)\$(Configuration)\ <br>
**Nombre de destino:** $(ProjectName) <br>
**Tipo de configuración:** Biblioteca estática (.lib) <br>


<br> Dentro de este proyecto ya se meten todas las cosas de las librerias que nos hallamos descargado <br><br><br>

## MUY IMPORTANTE 
Al descargaros el repos ejecutarlo tal cual, os dirá: **ERROR: el fichero no se ha abierto** seguido de unos mensajes de debug para ver si el link ha funcionado. Para solucionar esto hay que volver a las propiedades del proyecto principal (QuackEnginePro), ir a la parte de depuración y en donde pone: **Directorio de trabajo** poner esto: $(SolutionDir)bin\ <br>

Si os quereis asegurar de que todo funciona bien, hay que abrir la consola y ejecutar el .exe, tanto el .exe de la consola como visual pone que funciona pues está todo bien.

Las librerias a la hora de descargarlas tenemos que fijarnos en la version x86 (32 bits)<br>

Y ya estaria hulio.
