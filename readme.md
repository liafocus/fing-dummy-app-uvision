# Etapa 1: Setup entorno de desarrollo (borrador)

### Descripción

Este documento detalla los pasos necesarios para configurar el entorno de desarrollo destinado a realizar pruebas de debugging, scripting y automatización de inyección de fallas en un sistema basado en STM32F407-DISC1. Se abordan aspectos como la configuración del hardware, limitaciones de los IDEs Keil uVision y STM32 Cube, y la automatización de pruebas utilizando scripts en Python y archivos .bat y .ini.

### Hardware

- STM32F407-DISC1
- ULINKpro
- Adaptador de conector ETM + Debug 20-pin a placa STM32 

#### Desarrollo de adaptador para ULINKpro

...

### Limitaciones de los IDEs Keil uVision y STM32 Cube

- Objetivo: Obtener el trace de un programa
- Problema: El debugger que viene con la placa STM32F407-DISC1 no permite obtener el trace
- Solución: ULINKpro ArmKeil debugger
- Problema 2: CubeIDE no soporta el debugger ULINKpro
- Solución 2: IDE uVision de keil (único IDE compatible con ULINKpro)

Como el fin es poder obtener el Trace del programa, se debe utilizar el debugger ULINKpro de ArmKeil. Este debugger solo se puede utilizar con el IDE de Keil, uVision.
uVision permite utilizar algunas de sus herramientas desde la línea de comandos (ref: https://developer.arm.com/documentation/101407/0539/Command-Line), pero no incluyen nada sobre el trace.

No se logró encontrar comandos para utilizar con el ULINKpro, por lo que no parece que sea posible obtener el trace desde la linea de comandos. Frente a ello, se piensa que la mejor opción es usar un script de uVision,basándose en el tutorial https://www.keil.com/appnotes/files/apnt_307.pdf (aunque está hecho para el ULINKplus, es de mucha ayuda).

Consulta hacha en el support de ARM:

```
Hello ARM community,
I am currently working with Keil uVision and ULINKpro for embedded software development, with the goal of automating tests. I am trying to automate the process of exporting the trace.csv file from within a script or command line, but I haven't been able to find any documentation or resources on how to achieve this.
I have searched through the documentation, application notes, and forums, but I couldn't find any information on exporting the trace.csv file programmatically. Some users have asked similar questions in the past, but unfortunately, they didn't receive any replies.
Could someone please provide guidance on how to export the trace.csv file from a Keil uVision script or command line? Any insights, tips, or workarounds would be greatly appreciated.
Thank you in advance for your help!
Best regards,
Lía 
```

Respuesta:
```
From Kevin Bernhardt - Arm Partner Enablement Group

Lia,


You can use the trace information that appears in the event recorder. 
ER STAT path\filename
see https://developer.arm.com/documentation/101407/0539/Debug-Commands/EventRecorder?lang=en

You can also save information in a GCOV format:
see https://developer.arm.com/documentation/101407/0539/Debug-Commands/COVERAGE/COVERAGE-GCOV-Export



Kind regards,

Kevin

For more support information, documentation, downloads and other useful resources see: https://developer.arm.com/support/

```



### Configuración Keil uVision

- Adjuntar fotos de la configuración del programa

### Prueba de herramientas de debugging y scripting mediante programa Dummy

...

### Automatización de inyección de fallas

Todo es desde windows (Por qué? por los programas)

- Script python -> script .bat -> script .ini (Parece que no hay otra opción)
- El python no es necesario por ahora pero podria permitir más funcionalidades
- explicar paso a paso (guía) cómo modificar los paths para que funcione en tu propia PC
  - en script de python
  - en .bat
  - en uVision   

#### Guía

1. En el archivo uVision_flash_debug.bat, se debe actualizar la ruta del archivo UV4.exe para que corresponda con la ubicación en la computadora donde se esté utilizando.


X. Crear un entorno virtual de conda par usar los cripts de python.

Y. coverage y herramienta a instalar.

[//]: # (a veces me pasa que al no me deja flashear porque otro proceso está usando la aplicación (o algo así) y la solución es desenchufar y enchufar la placa. )

### Medición de tiempos

Se realizó una evaluación sobre la viabilidad de introducir fallas mediante breakpoints (¿por hardware?), interrumpiendo el programa, modificando un bit y reanudando la ejecución hasta un punto determinado (n veces en el bucle). Para este propósito, se desarrollaron varios scripts de debug: _time_ref.ini_ y _time_fault.ini_.

- _time_ref.ini_ comienza abriendo un archivo de registro llamado "Test.log". Luego, ejecuta un programa hasta alcanzar un punto específico definido en el archivo "main.c" en la línea 71. Después de alcanzar este punto, detiene la ejecución del programa y cierra el archivo de registro. Durante la ejecución, imprime mensajes indicando el inicio y el final del script. 

- _time_fault.ini_ es similar al archivo _time_ref.ini_. Comienza abriendo un archivo de registro llamado "Test.log". Luego, ejecuta un programa hasta alcanzar un punto específico definido en el archivo "main.c" en la línea 71. Después de alcanzar este punto, inyecta una falla al cambiar el valor en la memoria a partir de la dirección 0x20000004. Posteriormente, detiene la ejecución del programa y cierra el archivo de registro. Durante la ejecución, imprime mensajes indicando el inicio y el final del script.

 Tabla de resultados  (2/2/24) + (8/2/24) - trace desactivado (n=1)

| iter   | T s/falla+salida por bk | T c/falla+salida por bk | T s/falla   | T c/falla  |
|--------|-------------------------|-------------------------|-------------|------------|
| 1      | 3.400 s                 | 3.248 s                 | 3.542 s     | 3.470 s    |
| 2      | 3.342 s                 | 3.307 s                 | 3.426 s     | 3.506 s    |
| 3      | 3.357 s                 | 3.318 s                 | 3.465 s     | 3.508 s    |
| 4      | 3.659 s                 | 3.313 s                 | 3.443 s     | 3.485 s    |
| 5      | 3.204 s                 | 3.363 s                 | 3.425 s     | 3.560 s    |
| 6      | 3.227 s                 | 3.328 s                 | 3.458 s     | 3.540 s    |
| 7      | 3.353 s                 | 3.378 s                 | 3.438 s     | 3.580 s    |
| 8      | 3.470 s                 | 3.365 s                 | 3.381 s     | 3.512 s    |
| 9      | 3.302 s                 | 3.373 s                 | 3.438 s     | 3.430 s    |
| 10     | 3.390 s                 | 3.420 s                 | 3.465 s     | 3.546 s    |
| 11     | 3.360 s                 | 3.395 s                 | 3.384 s     | 3.530 s    |
| 12     | 3.430 s                 | 3.510 s                 | 3.470 s     | 3.548 s    |
| 13     | 3.347 s                 | 3.619 s                 | 3.427 s     | 3.522 s    |
| 14     | 3.357 s                 | 3.298 s                 | 3.443 s     | 3.502 s    |
| 15     | 3.219 s                 | 3.339 s                 | 3.483 s     | 3.560 s    |
| 16     | 3.292 s                 | 3.393 s                 | 3.260 s     | 3.490 s    |
| 17     | 3.337 s                 | 3.284 s                 | 3.303 s     | 3.530 s    |
| 18     | 3.368 s                 | 3.437 s                 | 3.434 s     | 3.511 s    |
| 19     | 3.233 s                 | 3.347 s                 | 3.397 s     | 3.591 s    |
| 20     | 3.393 s                 | 3.256 s                 | 3.423 s     | 3.538 s    |
|**prom**| **3.36435 s**           | **3.3755 s**            |**3.42745 s**|**3.5205 s**|

* Para los resultados de las dos primeras columnas se utilizó un programa con un loop infinito y un breakpoint para detener la ejecución. Para las dos columnas siguientes se utilizó un programa con un loop de 3 iteraciones.

Además, para distinguir la inyección de fallas en una misma línea de código en función de la vez que se ejecutó, se busca establecer un breakpoint en la n-ésima iteración a través de esa línea e inyectar la falla. Por lo tanto, la idea es determinar si el retraso en la inyección de la falla aumenta con n. Con este fin, se crearon los scripts _time_ref_n.ini_ y _time_fault_n.ini_.

 Tabla de resultados (2/2/24) - trace desactivado

n = 1000

| Iter   | T s/falla+salida por bk | T c/falla+salida por bk | T s/falla   | T c/falla    |
|--------|-------------------------|-------------------------|-------------|--------------|
| 1      | 66.810 s                | 66.529 s                | 3.982 s     | 66.509 s     |
| 2      | 66.435 s                | 66.303 s                | 3.551 s     | 66.947 s     |
| 3      | 66.153 s                | 66.381 s                | 3.503 s     | 66.678 s     |
| 4      | 66.301 s                | 66.011 s                | 3.466 s     | 66.560 s     |
| 5      | 66.799 s                | 65.100 s                | 3.491 s     | 66.950 s     |
|**prom**| **66.4996 s**           | **66.2648 s**           | **3.5986 s**| **66.7288 s**|

* Para los resultados de las dos primeras columnas se utilizó un programa con un loop infinito y un breakpoint para detener la ejecución. Para las dos columnas siguientes se utilizó un programa con un loop de 1002 iteraciones.

A continuación se presentan los resultados de inyectar fallas en la n-ésima iteración, en el programa Dummy de 1002 iteraciones.

| iter \ n   | 1           | 10          | 100         | 1000         |
|------------|-------------|-------------|-------------|--------------|
| 1          | 3.427 s     | 3.918 s     | 9.623 s     | 66.509 s     |
| 2          | 3.516 s     | 4.054 s     | 9.950 s     | 66.947 s     |
| 3          | 3.441 s     | 3.880 s     | 9.582 s     | 66.678 s     |
| 4          | 3.450 s     | 4.048 s     | 9.629 s     | 66.560 s     |
| 5          | 3.452 s     | 4.009 s     | 10.11 s     | 66.950 s     |
| 6          | 3.409 s     | 3.923 s     | 9.665 s     | 66.225 s     |
| 7          | 3.418 s     | 4.007 s     | 9.710 s     | 66.723 s     |
| 8          | 3.371 s     | 4.011 s     | 9.733 s     | 66.913 s     |
| 9          | 3.486 s     | 3.995 s     | 9.752 s     | 67.242 s     |
| **Prom**   | **3.431 s** | **3.972 s** | **9.743 s** | **66.787 s** |

Conclusión: El tiempo que se demora en inyectar la falla aumenta cuando cuando el número de iteración en que se inyecta la falla es mayor (no queda claro en que proporción)


Tabla de resultados  n = 1000 con con trace y GUI activados (2/2/24) 

n = 1000
| Iter | T s/falla | T c/falla |
|------|-----------|-----------|
| 1    |   | 264.98 s  |
| 2    |   | 239.25 s  |
| 3    |   | 241.30 s  |


Tabla de resultados  n = 1000 con con trace y GUI activados (5/2/24) 

n = 100
| Iter | T s/falla | T c/falla |
|------|-----------|-----------|
| 1    |   | 32.744 s  |
| 2    |   | 31.476 s  |
| 3    |   | 31.710 s  |
| 4    |   | 28.922 s  |
| 5    |   | 31.025 s  |
| 6    |   | 31.851 s  |
| 7    |   | 28.749 s  |
| 8    |   | 29.153 s  |
| 9    |   | 28.834 s  |

n = 10
| Iter | T s/falla | T c/falla |
|------|-----------|-----------|
| 1    |   | 6.5042 s  |
| 2    |   | 6.3918 s  |
| 3    |   | 6.2450 s  |
| 4    |   | 6.2572 s  |

* Cuando se quiere inyectar la falla obteniendo el trace dos veces seguidas, en la segunda no detecta más el hardware y hay que desenchufar y enchufar la placa STM32. El programa tampoco queda corriendo luego de salir del debug. 

[//]: # (Ahora antes de irme vi que empezó a correr de nuevo. Lo que se me ocurre es que capaz se queda sacando los datos de trace y demora un rato en poder volver a usarse. )
[//]: # (con n = 1000 y n = 100 se rompe a la primera.)

[//]: # (con n = 10 anda bien las primeras veces perop después deja de andar.)





### Mover código a RAM

... 

### Trabajar sin HAL

...

## Referencias

- [uVision from command line](https://developer.arm.com/documentation/101407/0539/Command-Line)
- [uVision debug commands](https://developer.arm.com/documentation/101407/0539/Debug-Commands?lang=en)
- [Test automation with MDK and ULINKplus](https://www.keil.com/appnotes/files/apnt_307.pdf)
- [gcovr](https://gcovr.com/en/stable/)