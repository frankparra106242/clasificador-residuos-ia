# Prueba de integración IA + motor

Esta carpeta contiene una versión de prueba del clasificador de residuos en la que se integra el reconocimiento mediante inteligencia artificial con el movimiento del motor paso a paso.

## Objetivo de la prueba

Comprobar que la ESP32-CAM puede:

1. Capturar la imagen de un residuo.
2. Ejecutar el modelo desarrollado con Edge Impulse.
3. Identificar la categoría del residuo.
4. Enviar la orden correspondiente al motor paso a paso 28BYJ-48.

En esta etapa todavía no se evalúa el mecanismo completo de descarga ni la apertura de la compuerta.

## Categorías del modelo

El modelo reconoce actualmente:

- `Residuos_Aprovechables`
- `Residuos_No_Aprovechables`
- `Residuos_Orgánicos`

## Movimientos utilizados

Durante las pruebas se utilizaron los siguientes valores:

| Categoría | Pasos |
|---|---:|
| Aprovechables | 85 |
| No aprovechables | 683 |
| Orgánicos | 1365 |

Los 85 pasos utilizados para residuos aprovechables corresponden a un movimiento corto de verificación y no representan una posición angular definitiva.

Los valores de 683 y 1365 pasos corresponden aproximadamente a 120° y 240°, respectivamente, considerando una revolución aproximada de 2048 pasos.

## Resultado observado

El monitor serial confirmó que:

- el modelo realiza la inferencia;
- las etiquetas son reconocidas correctamente;
- el programa entra en la condición correspondiente;
- se ejecuta la función encargada de enviar la orden al motor.

Ejemplos:

```text
Residuos_Aprovechables
Es un residuo aprovechable!
Moviendo el stepper con 85 pasos
