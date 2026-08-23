# Versiones del firmware

Esta carpeta conserva las diferentes versiones oficiales del programa desarrollado para el clasificador inteligente de residuos.

Las versiones se mantienen sin modificar con el propósito de documentar la evolución del sistema durante el proceso de diseño, programación e integración de sus componentes.

## Versiones disponibles

### V1.0

Primera versión del sistema de reconocimiento mediante Edge Impulse.

Esta versión se concentra en la captura de imágenes y ejecución del modelo de inteligencia artificial, sin integrar todavía el motor paso a paso ni el servomotor.

Archivo:

`Seleccionador_De_Residuos_Con_IA_V1.0.ino`

---

### V2.0

Incorpora la ESP32-CAM AI Thinker, el modelo de Edge Impulse, el motor paso a paso 28BYJ-48, el driver ULN2003 y el servomotor.

En esta versión se implementan las primeras órdenes de movimiento asociadas a las categorías detectadas por el modelo.

Archivo:

`Seleccionador_De_Residuos_Con_IA_V2.0.ino`

---

### V3.0

Evolución de la versión anterior en la que se incorporan instrucciones adicionales relacionadas con el retorno del motor a la posición inicial.

Esta versión forma parte del proceso experimental de desarrollo y será utilizada como referencia para corregir posteriormente la secuencia completa de:

`detectar → girar → abrir compuerta → cerrar compuerta → regresar`

Archivo:

`Seleccionador_De_Residuos_Con_IA_V3.0.ino`

---

## Nota

Las versiones almacenadas en esta carpeta representan etapas del desarrollo y no necesariamente corresponden a versiones finales o completamente funcionales del clasificador.

Las pruebas independientes de componentes se almacenan en carpetas separadas dentro de `firmware/`.
