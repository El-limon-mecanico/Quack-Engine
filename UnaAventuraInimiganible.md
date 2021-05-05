Bienvenido a esta aventura que es compilar CEGUI

Espero que tengas tiempo y paciencia porque lo vas a necesitar

Vale empecemos, lo primero que debes hacer es abrir Cmake y en la ruta de source debemos poner la ruta absoulta que lleva a:**...\Quack-Engine\QuackEngineSol\dependencies\CEGUI\dependecies**,luego en la carpeta destino debe ser la misma ruta añadiendo una nueva carpeta llamada build una vez hecho esto le damos a configurar, nos aseguramos que los siguientes campos esten seleccionados
- CEGUI_BUILD_DEVIL
- CEGUI_BUILD_EXPAT
- CEGUI_BUILD_FREETYPE2
- CEGUI_BUILD_FREEIMAGE
- CEGUI_BUILD_GLEW
- CEGUI_BUILD_GLFW
- CEGUI_BUILD_GLM
- CEGUI_BUILD_LUA
- CEGUI_BUILD_PCRE
- CEGUI_BUILD_SILLY

Una vez has seleccionado las casillas correspondientes le damos al boton de generar esto durará unos segundos

Una vez hecho esto habrimos la carpeta build y abrimos el ***CEGUI-DEPS.sln*** lo compilamos tanto en release como en debug si hay fallos da igual.
Lo has compilado en ambos genial acabas de llegar a la mitad del proceso bueno en verdad no pero supon que si
Ahora copiamos la carpeta dependecies que se ha generado dentro de la carpeta build (...\Quack-Engine\QuackEngineSol\dependencies\CEGUI\dependecies\build\dependecies) y la pegamos dentro de la carpeta cegui-0.8.7 y reemplazamos todo.

Ahora en CMake sí has leido bien tienes que volver a Cmake y en la ruta source ponemos la ruta absoluta que nos lleve a: **...\Quack-Engine\QuackEngineSol\dependencies\CEGUI\cegui-0.8.7**,luego en la carpeta destino debe ser la misma ruta añadiendo una nueva carpeta llamada build una vez hecho esto le damos a configurar, tendras que deseleccionar todos aquellos que contienen la palabra samples y seleccionar el campo CEGUI_BUILD_RENDERER_OGRE.
Creias que era tan facil como hacer esto? pues no ahora debes seleccionar en la parte superior la configuracion avanzada y cambiar los siguientes valores recordad que todos ellos deben establecerse en rutas absolutas
- OGRE_H_BUILD_SETTINGS_PATH: ...\Quack-Engine\QuackEngineSol\dependencies\Ogre\build\include
- OGRE_H_PATH: ...\Quack-Engine\QuackEngineSol\dependencies\Ogre\src\OgreMain\include
- OGRE_LIB: ...\Quack-Engine\QuackEngineSol\dependencies\Ogre\build\lib\Release\OgreMain.lib
- OGRE_LIB_DBG: ...\Quack-Engine\QuackEngineSol\dependencies\Ogre\build\lib\Debug\OgreMain_d.lib

Una vez habeis cambiado esto le dais a generar pero NO compìles aún ahora debes buscar el siguiente archivo: **...\build\cegui\include\CEGUI\Config.h** aqui debemos cambiar las siguientes lineas 


#ifndef CEGUI_OGRE_VERSION_MAJOR
#   define CEGUI_OGRE_VERSION_MAJOR 1
#endif
#ifndef CEGUI_OGRE_VERSION_MINOR
#   define CEGUI_OGRE_VERSION_MINOR 12
#endif
#ifndef CEGUI_OGRE_VERSION_PATCH
#   define CEGUI_OGRE_VERSION_PATCH 11
#endif
#ifndef CEGUI_OGRE_VERSION
#   define CEGUI_OGRE_VERSION ((CEGUI_OGRE_VERSION_MAJOR << 16) | (CEGUI_OGRE_VERSION_MINOR << 8) | CEGUI_OGRE_VERSION_PATCH)
#endif

Ahora ya podemos abrir el ***cegui.sln*** que se ha generado y compilarlo tanto en release como en debug