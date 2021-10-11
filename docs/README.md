![UCN](images/60x60-ucn-negro.png)


# Informe Técnico 
## Curso: Estructura de datos
### Implementación de la primera historia de usuario

**Alumnos:**

* Valentina Belén Henríquez Fuentes (Coordinadora)
* Josefina Elisa Figueroa Ubilla (Encargada de Bitácora)

## Resumen 

> El trabajo realizado buscaba implementar la primera historia de usuario del sistema, la cual buscaba que el guardia pudiera observar todas la caras detectadas en las pantallas y que estas fueran identificadas por un rectángulo rojo, para así, observar visualmente las caras que fueron correctamente detectadas por el algoritmo.<br /> <br />El resultado del trabajo fue la implementación de esa historia de usuario en código C++ con la ayuda de la librería OpenCV. Terminamos implementando un codigo que permitía detectar caras en cualquier imagen. Cabe mencionar, que la detección es visualmente representada por un cuadrado rojo que enmarca las caras detectadas.



## 1. Introducción

El presente trabajo busca la implementación de la primera historia de usuario. La cual es:

> “COMO guardia QUIERO observar todas las caras detectadas en pantalla identificadas por un rectángulo de color rojo PARA observar visualmente las caras que fueron correctamente detectadas por el algoritmo.”

Lo primero que se hace es buscar dos imágenes que sirvan para probar el funcionamiento del programa a implementar. Lo importante es utilizar una imagen que muestra solo un rostro y otra imagen con múltiples rostros, para así observar el funcionamiento del programa en dos casos importantes de funcionamiento. En la presente ocasión, se utilizaron las imágenes, “lena.jpg” y “kids.png”.

Una vez que se yienes la imagen se debe, estandarizar todos los aspectos en la imagen que queremos procesar, detectar las coordenadas de los caras humanas en la imagen, enmarcar en rojo las caras detectadas y al final, mostrar la imagen original con las enmarcaciones.

### 1.1 Descripción del problema

El problema es que se le resulta difícil a un humano detectar rápido y eficazmente los rostros de personas, ya sea en una foto o un video de una cámara de vigilancia y al mismo tiempo recordarlos y apuntarlos.

### 1.2 Objetivos 

**Objetivo General**


Implementar un sistema que perimita identificar visualmente con un rectangulo rojo a todas las caras humanas identificadas en una imagen.

**Objetivos específicos**

1. Estandarizar todos los aspectos en la imagen que queremos procesar. 
2. Detectar las coordenadas de los caras humanas en la imagen.
3. Enmarcar en rojo las caras detectadas. 
4. Mostrar la imagen original con las enmarcaciones.

### 1.3 Solución propuesta

Detectar y identificar visualmente cars humanas en una imagen con ayuda de la libreria OpenCv, especificamente con el uso de “haarcascade_frontalface_alt.xml” de la clase CascadeClassifier.

## 2. Materiales y métodos

Los materiales utilizados fueron el IDE Visual Studio 2019 y la librería OpenCV.

Los métodos utilizados fueron mencionados en la introducción del presente informe.


### 2.1 Instalación
Librería:
- OpenCV

IDE:
- Visual Studio 2019

[Guía de Instalación](https://www.youtube.com/watch?v=Hu7ArOaFm2g&feature=youtu.be)


### 2.2 Diseño 

Los modulos y clases de OpenCv utilizados se encuentran mencionados y explicados en la sección 2.3 del informe.

La arquitectura del proyecto es la default de un programa en C++ ejecutable por consola.

### 2.3 Implementación

Para reproducir el sistema propuesto por la primera historia de usuario, se utiliza C++ y la librería OpenCV. OpenCV facilita la tarea de detectar las caras en las fotos, ya que aquella librería cuenta con clasificadores en cascada entrenados específicamente para la detección de rostros. Cabe mencionar que los clasificadores de rostros y de otros objetos se encuentran almacenados en archivos XML. En la descarga de OpenCV se encuentran incluidos los clasificadores y también todas las herramientas para crear alguno específico a otro objeto que no se encuentre disponible.

Para poder detectar caras en una imagen, lo primero que se debe hacer es cargar la imagen en la cual se quiere detectar caras. Lo siguiente es convertir la imagen a escala de grises, lo cual es necesario para que los algoritmos de detección de la librería OpenCV funcionen correctamente. En el presente código se utilizó:

>cvtColor(imagen, gray, COLOR_BGR2GRAY);

Luego de convertir la imagen a escala de grises, se debe aplicar ecualización de histograma a la imagen en grises para estandarizar el contraste y brillo de la imagen, para que el algoritmo sea más eficaz al detectar las caras presentes en la imagen.

> equalizeHist(gray, dest);

Una vez que la imagen se encuentra procesada, se le pasa el nombre del clasificador al método load de la clase CascadeClassifier. Para detectar caras desde el frente, usaremos “haarcascade_frontalface_alt.xml”. En el presente código se utilizó:

> CascadeClassifier detector;

Ya que el archivo se encontraba en la carpeta del proyecto. Una vez que se puede abrir el clasificador, se pueden detectar las caras en las imágenes. Las coordenadas de las caras detectadas se guardan en una variable llamada rect. 

> vector<Rect> rect;

>detector.detectMultiScale(dest, rect);

El presente código recorre los rectángulos encontrados por el algoritmo y los enmarca con rectángulos rojos en la imagen original.

> for (Rect rc : rect)

>	{

>rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(255,4,0), 2);

>	}

Al final, la imagen original con las enmarcaciones es mostrada gracias a:

> imshow("Imagen original", imagen);

## 3. Resultados obtenidos

Sin importar la imagen, el resultado obtenido será el mismo. Una imagen con las caras humanas enmarcadas en rojo.

## 4. Conclusiones

La librería OpenCV hace que el trabajo de detección de rostros no sea largo y tedioso, ya que la librería cuenta con un algoritmo de detección que ya se 
encuentra entrenado para identificar caras humanas.
# Referecias

1. Wu, W. H., Zhao, Y. J., & Che, Y. F. (2014). Research and Implementation of Face Detection Based on OpenCV. Advanced Materials Research, 971-973, 1710-1713. doi:10.4028/www.scientific.net/amr.971-973.1710
2. Kaehler, A., & Bradski, G.R. (2016). Learning OpenCV 3: Computer Vision in C++ with the OpenCV Library.


