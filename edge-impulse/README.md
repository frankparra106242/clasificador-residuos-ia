# Modelo de inteligencia artificial — Edge Impulse

Esta carpeta contiene la documentación y los archivos relacionados con el modelo de visión artificial utilizado en el clasificador inteligente de residuos.

## Objetivo del modelo

El modelo permite identificar el tipo de residuo observado por la cámara de la ESP32-CAM para posteriormente determinar el movimiento que debe realizar el sistema de clasificación.

## Plataforma utilizada

El modelo fue desarrollado utilizando **Edge Impulse** y posteriormente exportado para su implementación en **Arduino IDE** sobre una **ESP32-CAM AI Thinker**.

Para la captura de las imágenes utilizadas durante el desarrollo del modelo también se utilizó **Collect Images for Edge Impulse**.

## Categorías reconocidas

Actualmente el modelo trabaja con tres categorías:

- `Residuos_Aprovechables`
- `Residuos_No_Aprovechables`
- `Residuos_Orgánicos`

## Flujo de funcionamiento

```text
Residuo
   │
   ▼
ESP32-CAM
   │
   ▼
Captura de imagen
   │
   ▼
Modelo de Edge Impulse
   │
   ▼
Detección y clasificación
   │
   ├── Residuos_Aprovechables
   ├── Residuos_No_Aprovechables
   └── Residuos_Orgánicos
   │
   ▼
Orden al sistema de movimiento
```

## Integración con la ESP32-CAM

El modelo fue exportado desde Edge Impulse como una librería compatible con Arduino.

Esta librería se incorpora al código mediante:

```cpp
#include <Seleccionador_de_residuos_con_IA_inferencing.h>
```

La ESP32-CAM captura la imagen y ejecuta localmente la inferencia del modelo.

## Resultados de las pruebas

Durante las pruebas de integración se comprobó mediante el monitor serial que el sistema reconoce las tres categorías y ejecuta la condición correspondiente en el programa.

Ejemplos observados:

```text
Residuos_Aprovechables
Es un residuo aprovechable!
```

```text
Residuos_No_Aprovechables
Es un residuo no aprovechable!
```

```text
Residuos_Orgánicos
Es un residuo organico!
```

## Estado actual

El modelo se encuentra integrado con la ESP32-CAM y realiza inferencias correctamente.

Actualmente se continúa trabajando en la integración entre los resultados de la clasificación y el movimiento físico del clasificador.
