# Documentación del proyecto

Esta carpeta reúne la documentación técnica y de seguimiento del **Clasificador Inteligente de Residuos**.

Su propósito es complementar el código fuente, los modelos 3D y las evidencias disponibles en el repositorio, conservando la trazabilidad del proceso de diseño, construcción, programación, integración y prueba del prototipo.

## Organización de la documentación

### Funcionamiento del sistema

Documentación relacionada con la arquitectura general y la secuencia de funcionamiento del clasificador.

El proceso previsto es:

1. El usuario deposita un residuo a través de la abertura ubicada en la tapa fija.
2. El residuo queda en el compartimento de análisis.
3. La ESP32-CAM captura la imagen.
4. El modelo desarrollado con Edge Impulse identifica la categoría del residuo.
5. El motor paso a paso hace girar el cuerpo cilíndrico móvil.
6. El compartimento correspondiente se alinea con el punto de descarga.
7. El servomotor abre la compuerta inferior.
8. El residuo cae en el compartimento seleccionado.
9. La compuerta se cierra.
10. El cuerpo móvil regresa a su posición inicial.

---

### Documentación electrónica

Incluye la descripción de:

- ESP32-CAM AI Thinker;
- cámara OV2640;
- driver ULN2003;
- motor paso a paso 28BYJ-48;
- servomotor;
- regulador DC-DC LM2596;
- batería de 12 V;
- interruptor;
- alimentación y tierra común;
- conexiones entre los diferentes componentes.

También se documentarán los esquemas eléctricos y las modificaciones realizadas durante las pruebas.

---

### Documentación mecánica

Incluye información relacionada con:

- tapa fija;
- compartimento de análisis;
- cuerpo cilíndrico móvil;
- división interna en tres compartimentos;
- base fija inferior;
- ruedas de apoyo;
- acople entre el motor y la base móvil;
- estructura lateral de soporte;
- piezas desarrolladas mediante impresión 3D.

---

### Pruebas

Se documentarán progresivamente:

- pruebas independientes del motor paso a paso;
- pruebas de reconocimiento mediante Edge Impulse;
- pruebas de la ESP32-CAM;
- integración entre IA y motor;
- pruebas del servomotor;
- pruebas del mecanismo de giro;
- pruebas de descarga;
- pruebas del prototipo completo.

Las evidencias fotográficas y audiovisuales asociadas se encuentran en la carpeta:

`/evidencias`

---

## Documentos disponibles

Los documentos técnicos elaborados durante el desarrollo del proyecto se incorporarán progresivamente en esta sección.

Entre ellos se incluirán:

- esquema lógico electrónico;
- descripción del mecanismo;
- documentación de conexiones;
- registros de pruebas;
- modificaciones del diseño;
- resultados y ajustes realizados durante el desarrollo.

---

## Estado de la documentación

La documentación se encuentra en construcción y será actualizada a medida que avance el desarrollo del prototipo.

El repositorio busca conservar tanto los resultados finales como la evolución del proceso de diseño y construcción.
