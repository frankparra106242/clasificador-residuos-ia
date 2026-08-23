# Diagramas electrónicos

Esta carpeta contiene los diagramas, esquemas de conexión y representaciones del sistema electrónico del clasificador inteligente de residuos.

## Propósito

Los diagramas permiten documentar la forma en que se conectan los diferentes componentes del prototipo y registrar los cambios realizados durante el proceso de desarrollo.

## Componentes principales

Los diagramas del sistema contemplan actualmente:

- ESP32-CAM AI Thinker
- Cámara OV2640
- Driver ULN2003
- Motor paso a paso 28BYJ-48
- Servomotor
- Regulador DC-DC LM2596
- Batería de 12 V
- Interruptor
- Cableado de conexión

## Subsistemas

La documentación electrónica se organizará en los siguientes subsistemas:

### Sistema de reconocimiento

Comprende la ESP32-CAM y la cámara OV2640 utilizadas para capturar las imágenes y ejecutar el modelo desarrollado con Edge Impulse.

### Sistema de giro

Está formado por:

- ESP32-CAM
- Driver ULN2003
- Motor paso a paso 28BYJ-48

Este sistema se encarga de hacer girar el cuerpo cilíndrico móvil del clasificador.

### Sistema de apertura de la compuerta

Está compuesto principalmente por el servomotor encargado de abrir y cerrar la compuerta inferior del compartimento de análisis.

### Sistema de alimentación

La alimentación principal proviene de una batería de 12 V.

El regulador DC-DC LM2596 se utiliza para reducir y ajustar el voltaje requerido por los componentes electrónicos.

## Diagramas por desarrollar

En esta carpeta se incorporarán progresivamente:

- diagrama de conexión ESP32-CAM → ULN2003 → motor 28BYJ-48;
- conexión del servomotor;
- esquema de alimentación;
- conexión del LM2596;
- integración completa del sistema electrónico;
- fotografías o esquemas del cableado implementado físicamente.

## Estado actual

Actualmente se han realizado pruebas independientes del motor paso a paso y pruebas de integración entre la ESP32-CAM, Edge Impulse y las órdenes de movimiento.

Los diagramas serán actualizados a medida que se defina y pruebe la configuración final del sistema.
