#!/bin/bash

echo "====================== Corriendo pruebas de tipo 1 ======================"

./juliaSet

echo "====================== Corriendo pruebas de tipo 2 ======================"

./juliaSet -r 1920x1080 -o Prueba2a.pgm
echo "si se manda como parametro -r y se especifica una resolucion, se dibuja el archivo de salida con esa resolucion"
./juliaSet -c -1+1i -o Prueba2b.pgm
echo "si se le pasa por parametro -c y se especifica un numero imaginario (a+bi), se centra el dibujo en esas coordenadas"
./juliaSet -w 0.5 -o Prueba2c.pgm
echo "si se pasa por parametro -w y se especifica un numero, se escala la imagen de salida para tener ese ancho"
./juliaSet -H 0.5 -o Prueba2d.pgm
echo "si se pasa por parametro -H y se especifica un numero, se escala la imagen de salida para tener ese alto"
./juliaSet -s -0.75+0.18i -o Prueba2e.pgm
echo "si se pasa por parametro -s y se especifica un numero imaginario (a+bi), se reemplaza la 'semilla' del fractal por el valor pasado"
./juliaSet -o Prueba2f.pgm
echo "si se manda como parametro -o y se especifica un archivo, se crea el archivo"

echo "====================== Corriendo pruebas de tipo 3 ======================"

./juliaSet -r 1920x1080 -w 0.05 -H 0.05 -s -0.74+0.175i -o Prueba3.pgm
echo "si se pasan multiples parametros por comando, se genera una imagen que cumple todos esos parametros pedidos"

echo "====================== Corriendo pruebas de tipo 4 ======================"

echo "Si la resolucion es mayor a 5120x2880, el programa devuelve error:"
./juliaSet -r 5500x2900 -o Prueba4a.pgm
echo "Si se excede el floating point max value para alguno de los parametros -w, -s, -H o -c, el programa devuelve error:"
./juliaSet -w 3.4e+40F -o Prueba4b.pgm
echo "Si la resolucion pedida es menor a 1x1, el programa devuelve error:"
./juliaSet -r 1x0.5 -o Prueba4c.pgm

echo "La resolucion debe se pasa como dos numeros separados por 'x' o ','. Si el programa recibe otra convension, se devuelve un error de parseo:"
./juliaSet -r 600-500 -o Prueba4d.pgm
echo "Los comandos -c y -s deben recibir un numero complejo. Si el programa recibe otra cosa, se devuelve un error de parseo:"
./juliaSet -s 4F -o Prueba4e.pgm
echo "Los comandos -H y -w deben recibir un numero en punto flotante. Si el programa recibe otra cosa, devuelve un error de parseo"
./juliaSet -w 4i -o Prueba4f.pgm
