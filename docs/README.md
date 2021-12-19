![UCN](images/60x60-ucn-negro.png)

# Informe Técnico 
## Curso: Estructura de datos
### Entrega Final del Taller de EDD

**Alumnos:**

* Valentina Belén Henríquez Fuentes (Coordinadora)
* Josefina Elisa Figueroa Ubilla (Encargada de Bitácora)

## Resumen 

    El trabajo realizado buscaba implementar todas las historias de usuario. Cabe mencionar que el source code se encuentra guardado en una branch de codigo del repositorio y al finalizar, se dejo con el tag “release 1.0”.



## 1. Introducción

El presente trabajo busca la implementación de todas las historias de usuario. La cuales son:

    1. COMO guardia QUIERO observar todas las caras detectadas en pantalla identificadas por un rectángulo de color rojo PARA observar visualmente las caras que fueron correctamente detectadas por el algoritmo.

    2. COMO guardia QUIERO observar las últimas cinco identidades que más tiempo han sido vistas por el sistema PARA para las últimas personas que más tiempo pasan por la cámara de video o que están en la secuencia de video.

    3. COMO Administrador QUIERO establecer la hora de inicio y término de la sesión por día (en caso de que se adquiera las imágenes con una cámara) PARA poder contar las entidades o personas en un intervalo de tiempo acotado, por ejemplo, cuando abre o cierra una tienda.

    4. COMO Administrador QUIERO contar con un listado por sesión (por día) de todas las identidades detectadas indicando el tiempo total de las veces que apareció en el video PARA conocer la presencia que identidad estuvo más tiempo frente a la cámara en diferentes ocasiones dada una sesión.

    5. COMO Administrador QUIERO almacenar el video obtenido en cada sesión PARA para contar con la evidencia real si es que se produce un problema o anomalía.

    6. COMO Administrador QUIERO obtener un listado con las identidades obtenidas en una sesión con todos los intervalos de tiempo donde aparece PARA poder recuperar el trozo o los trozos de videos asociados a una identidad.

Para la implementación de las historias de usuario utilizamos un árbol binario y la libreria openCV.

### 1.1 Descripción del problema

El problema es que se le resulta difícil a un humano detectar rápida y eficazmente los rostros de personas, ya sea en una foto o un video de una cámara de vigilancia y al mismo tiempo recordarlos, diferenciar un rostro del otro y documentar el historial de comportamiento.

### 1.2 Objetivos 

**Objetivo General**

Implementar un sistema que permite identificar visualmente con un rectángulo rojo a todas las caras humanas identificadas en un frame. También reconocer los rostros, asignarles un ID , guardar el crop del frame del rostro identificado en un árbol binario y mantener la información del tiempo en cámara de cada ID distinto y guardar esos datos en un registro.

También se busca mantener registro del video obtenido con las caras detectadas para después poder corroborar información o evidenciar problemas o anomalías en la detección e identificación de rostros.

**Objetivos específicos**

01. Estandarizar todos los aspectos en la imagen que queremos procesar
02. Detectar las coordenadas de los caras humanas en la imagen
03. Enmarcar en rojo las caras detectadas
04. Mostrar el frame original con las enmarcaciones
05. Guardar crops de los rostros en un árbol binario
06. Diferenciar una cara se otra
07. Asignar IDs
06. Guardar datos de cada ID
08. Generar un registro de la ejecución de la solución en video
09. Mantener registro del tiempo
10. Mantener un código entendible
11. Generar un registro final de los ids de la sesión en un .txt

### 1.3 Solución propuesta

Detectar e identificar visualmente caras humanas en un frame con ayuda de la librería OpenCV, específicamente, con el uso de “haarcascade_frontalface_alt.xml” de la clase CascadeClassifier.

También utilizar estructuras de datos, tales como un árbol binario para guardar datos o imágenes y VideoWriter de la clase videoio de OpenCV para mantener registro de los IDs detectados y de la ejecución de nuestro programa.

## 2. Materiales y métodos

Los materiales utilizados fueron el IDE Visual Studio 2019, el IDE CLion y la librería OpenCV.

Los métodos utilizados fueron mencionados en la introducción del presente informe.


### 2.1 Instalación
Librería:
- OpenCV

IDE:
- Visual Studio 2019
- CLion

[Guía de Instalación para  Visual Studio 2019 - Windows](https://www.youtube.com/watch?v=Hu7ArOaFm2g&feature=youtu.be)

[Guía de Instalación para CLion - MacOS Catalina](https://programmerah.com/mac-clion-configuring-opencv-environment-18573/)


### 2.2 Diseño 

Los modulos y clases de OpenCv utilizados se encuentran mencionados y explicados en la sección 2.3 del informe.

La arquitectura del proyecto es la default de un programa en C++ ejecutable por consola.

### 2.3 Implementación

Para reproducir la solución propuesta, se utiliza C++, la librería OpenCV y distintas estructuras de datos. OpenCV facilita la tarea de detectar las caras en los frames, ya que aquella librería cuenta con clasificadores en cascada entrenados específicamente para la detección de rostros. La estructura del árbol binario nos permite diferenciar las caras unas a otras, y así, asignarle un ID al rostro identificado. También es importante mencionar que el árbol permite guardar registro de los IDs y la ejecución de la solución. 

Para poder detectar caras en un video, lo primero que se debe hacer es instanciar la estructura en la cual vamos a guardar los frames de los rostros, cargar el video en el cual se quiere detectar caras, definir el lugar en cual se quiere guardar la ejecución del programa. En el presente código se utilizó:
 
> BinarySearchTree* tree = new BinarySearchTree();

 
> VideoCapture capture("ATH/nombre_video_a_detectar.mp4");

 
>VideoWriter video("PATH/nombre_sesion.avi",VideoWriter::fourcc('M','J','P','G'),10, Size(480,270));
 
 
Después cada frame del video se considera como una imagen a utilizar. En el presente código se utilizó:
 
> capture >> imagen;
 
Lo siguiente es convertir la imagen a escala de grises, lo cual es necesario para que los algoritmos de detección de la librería OpenCV funcionen correctamente. En el presente código se utilizó:
 
> cvtColor(imagen, gray, COLOR_BGR2GRAY);
 
Luego de convertir la imagen a escala de grises, se debe aplicar ecualización de histograma a la imagen en grises para estandarizar el contraste y brillo de la imagen, para que el algoritmo sea más eficaz al detectar las caras presentes en la imagen.
 
> equalizeHist(gray, dest);
 
Una que el archivo se encontraba en la carpeta del proyecto. Una vez que se puede abrir el clasificador, se pueden detectar las caras en las imágenes. Las coordenadas de las caras detectadas se guardan en una variable llamada rect.
 
> vector rect;
 
> detector.detectMultiScale(dest, rect);
 
El presente código recorre los rectángulos encontrados por el algoritmo y los enmarca con rectángulos rojos en la imagen original.
 
> for (Rect rc : rect)
 
> {
 
> rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(255,4,0), 2);
 
> }
 
Luego cada imagen de rostro detectado es guardado en árbol binario. En el presente código se utilizó:

>Mat resizedDown;

>resize(imgCrop, resizedDown, Size(25, 25), INTER_LINEAR);

>tree->insert(resizedDown);

Al final de la ejecución de la solución se puede mostrar la información por ID de cara rostro identificado y también se cierra todo correctamente. En la presente resolución se utilizó:

> capture.release();
> video.release();

> tree->createList1(typeToString(now))

> int cant;

> cout << "Ingrese el numero de identidades que quiere revisar con mas segundos en el video: " << endl;
cin >> cant;

> cout << "\tREPORTE" << endl;

> tree->getPrint(cant); //NUEVA FORMA

> destroyAllWindows();

> return 0;

## 3. Resultados obtenidos

Sin importar el vídeo, el resultado obtenido será el mismo. Un vídeo con las caras humanas enmarcadas en rojo, una carpeta con los recortes de las caras detectadas , un árbol con nodos que contienen crops de rostros detectados, un árbol con nodos que contienen registros de los IDs identificados en el video en orden de aparición y una carpeta con las grabaciones de la ejecución y registros en .txt.

## 4. Conclusiones

La librería OpenCV hace que el trabajo de detección de rostros no sea largo y tedioso, ya que la librería cuenta con un algoritmo de detección que ya se 
encuentra entrenado para identificar caras humanas.

Nos dimos cuenta que realizar un algoritmo de reconocimiento facial no era tan simple como esperábamos, pero el usar el árbol binario para identificar y definir IDs lo hizo mucho más simple.
 
Cabe mencionar que no siempre se detectan todas las caras identificables, ya que en gran parte la identificación depende de las condiciones de luz, nitidez y visibilidad del vídeo.

# Referecias

1. Wu, W. H., Zhao, Y. J., & Che, Y. F. (2014). Research and Implementation of Face Detection Based on OpenCV. Advanced Materials Research, 971-973, 1710-1713. doi:10.4028/www.scientific.net/amr.971-973.1710
2. Kaehler, A., & Bradski, G.R. (2016). Learning OpenCV 3: Computer Vision in C++ with the OpenCV Library.


