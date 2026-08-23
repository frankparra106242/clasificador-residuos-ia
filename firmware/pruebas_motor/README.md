# Pruebas del motor paso a paso

Esta carpeta contiene los programas utilizados para probar de manera independiente el funcionamiento del sistema de giro del clasificador de residuos.

## Hardware utilizado

- ESP32-CAM AI Thinker
- Motor paso a paso 28BYJ-48
- Driver ULN2003
- Regulador de voltaje LM2596
- Batería de 12 V
- Cables de conexión

## Propósito de las pruebas

Antes de integrar el motor con el sistema de reconocimiento de residuos desarrollado con Edge Impulse, se realizaron pruebas independientes para verificar:

- el funcionamiento del motor 28BYJ-48;
- la comunicación entre la ESP32-CAM y el driver ULN2003;
- el sentido de giro;
- el número de pasos necesarios para diferentes posiciones;
- el retorno a la posición inicial.

Estas pruebas permitieron comprobar que el motor y el driver funcionan correctamente de manera independiente.

## Posiciones utilizadas

Para las pruebas se considera una revolución aproximada de:

- **2048 pasos = 360°**
- **683 pasos ≈ 120°**
- **1365 pasos ≈ 240°**

Posteriormente estos valores serán ajustados experimentalmente de acuerdo con el mecanismo físico del clasificador.
