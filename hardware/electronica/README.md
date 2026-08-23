# Sistema electrónico

Esta carpeta contiene la documentación relacionada con los componentes electrónicos, alimentación, conexiones y control del clasificador inteligente de residuos.

## Componentes utilizados

El prototipo utiliza actualmente los siguientes componentes:

| Componente | Función |
|---|---|
| ESP32-CAM AI Thinker | Control principal, captura de imágenes y ejecución del modelo de IA |
| Cámara OV2640 | Captura de imágenes de los residuos |
| Motor paso a paso 28BYJ-48 | Giro del cuerpo cilíndrico móvil |
| Driver ULN2003 | Control del motor paso a paso |
| Servomotor | Accionamiento de la compuerta de descarga |
| Regulador LM2596 | Reducción y regulación del voltaje de alimentación |
| Batería de 12 V | Fuente principal de energía |
| Interruptor | Encendido y apagado del sistema |
| Cables de conexión | Interconexión de los diferentes componentes |

## Control del sistema

La ESP32-CAM funciona como controlador principal.

Además de capturar las imágenes utilizadas para la clasificación, ejecuta el modelo desarrollado con Edge Impulse y determina la acción que debe realizar el sistema.

El flujo general es:

```text
Cámara
   │
   ▼
ESP32-CAM
   │
   ▼
Modelo Edge Impulse
   │
   ▼
Clasificación del residuo
   │
   ├── Motor paso a paso
   │       ↓
   │   Giro del recipiente
   │
   └── Servomotor
           ↓
       Apertura de compuerta
```

## Motor paso a paso

El cuerpo cilíndrico móvil es accionado mediante un motor paso a paso **28BYJ-48** controlado por un driver **ULN2003**.

El motor se utiliza para posicionar los tres compartimentos del recipiente en diferentes posiciones angulares.

Durante las pruebas se han utilizado aproximadamente:

- 2048 pasos para 360°
- 683 pasos para 120°
- 1365 pasos para 240°

Estos valores podrán ajustarse durante las pruebas del mecanismo completo.

## Servomotor

El servomotor está destinado al accionamiento de la compuerta ubicada en la parte inferior del compartimento de análisis.

Su integración mecánica y electrónica todavía se encuentra en desarrollo.

## Alimentación

La fuente principal del sistema es una batería de **12 V**.

Se utiliza un regulador DC-DC **LM2596** para adaptar el voltaje requerido por los diferentes componentes.

La configuración definitiva de alimentación será documentada después de realizar las pruebas de integración del sistema completo.

## Estado actual

Se han realizado pruebas independientes del motor paso a paso y pruebas de integración entre la ESP32-CAM, Edge Impulse y las órdenes de movimiento.

Actualmente se continúa trabajando en:

- integración del motor con el sistema de reconocimiento;
- integración del servomotor;
- distribución definitiva de la alimentación;
- organización del cableado;
- y pruebas del sistema electrónico completo.
