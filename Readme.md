# Operando Imagen

##### - By MindBlast

Este programa recibe dos imágenes a través de la terminal dos imágenes almacenadas del disco duro, para con ellas, realizar distintas operaciones (suma, resta, producto punto, producto cruz) y las imágenes resultantes almacenarlas nuevamente en el disco duro en formato de Bitmap (.bmp)

## ¿Cómo Funciona?

1.  Descargar el programa del repositorio de Github (https://github.com/Grey-Matter-Co/OperandoImagen/)

    ```
    > git clone git@github.com:Grey-Matter-Co/OperandoImagen.git
    ```

2.  Dirígete a la raíz del proyecto dentro de la carpeta en la que la descargaste

    ```
    > cd ./OperandoImagen
    ```

3.  Compila el programa, incluyendo la librería agregada ImageOperator.h

    ```
    > gcc ImageOperator.c main.c -o main -lm
    ```

4.  Si el programa no arroja ningún Warning o Error, ejecuta el programa

    ```
    > ./main
    ```

    En caso de que el programa arroje algún problema, reportarlo en GitHub UwU.

## Distribución De Directorios

OperandoImagen
|- resources
	Imágenes muestra para prueba del programa
|- stb
	Librería para entrada/salida de imagenes
|- SFML (Probable elimnación)
	Librería para desplegar una ventana en windows )?