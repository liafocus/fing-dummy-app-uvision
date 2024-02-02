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
No logré encontrar comandos para utilizar con el ULINKpro, por lo que no parece que sea posible obtener el trace desde la linea de comandos.
Frente a esto, creemos que la mejor opción es usar un script de uVision, para ello estoy basándome en el  tutorial https://www.keil.com/appnotes/files/apnt_307.pdf (aunque está hecho para el ULINKplus me parece que es de mucha ayuda).



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

- a veces me pasa que al no me deja flashear porque otro proceso está usando la aplicación (o algo así) y la solución es desenchufar y enchufar (debgger o placa?)

### Medición de tiempos

Se realizó una evaluación sobre la viabilidad de introducir fallas mediante breakpoints (¿por hardware?), interrumpiendo el programa, modificando un bit y reanudando la ejecución hasta un punto determinado (n veces en el bucle). Para este propósito, se desarrollaron varios scripts de debug: time_ref.ini y time_fault.ini. En time_ref.ini ...(añadir más explicación)... y en time_fault.ini ...(añadir más explicación)...

 Tabla de resultados  (2/2/24)

| iter | T s/falla | T c/falla |
|------|-----------|-----------|
| 1    | 3.400 s   | 3.248 s   |
| 2    | 3.342 s   | 3.307 s   |
| 3    | 3.357 s   | 3.318 s   |
| 4    | 3.659 s   | 3.313 s   |
| 5    | 3.204 s   | 3.363 s   |
| 6    | 3.227 s   | 3.328 s   |
| 7    | 3.353 s   | 3.378 s   |
| 8    | 3.470 s   | 3.365 s   |
| 9    | 3.302 s   | 3.373 s   |
| 10   | 3.390 s   | 3.420 s   |
| 11   | 3.360 s   | 3.395 s   |
| 12   | 3.430 s   | 3.510 s   |
| 13   | 3.347 s   | 3.619 s   |
| 14   | 3.357 s   | 3.298 s   |
| 15   | 3.219 s   | 3.339 s   |
| 16   | 3.292 s   | 3.393 s   |
| 17   | 3.337 s   | 3.284 s   |
| 18   | 3.368 s   | 3.437 s   |
| 19   | 3.233 s   | 3.347 s   |
| 20   | 3.393 s   | 3.256 s   |
| prom | 3.36435 s | 3.3755 s  |


Además, para distinguir la inyección de fallas en una misma línea de código en función de la vez que se ejecutó, se busca establecer un breakpoint en la n-ésima iteración a través de esa línea e inyectar la falla. Por lo tanto, la idea es determinar si el retraso en la inyección de la falla aumenta con n. Con este fin, se crearon los scripts time_ref_n.ini y time_fault_n.ini.




### Mover código a RAM

... 

### Trabajar sin HAL

...?

## Referencias

- [uVision from command line](https://developer.arm.com/documentation/101407/0539/Command-Line)
- [uVision debug commands](https://developer.arm.com/documentation/101407/0539/Debug-Commands?lang=en)
- [Test automation with MDK and ULINKplus](https://www.keil.com/appnotes/files/apnt_307.pdf)