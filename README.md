# clasificador-residuos-ia
Clasificador inteligente de residuos mediante visión artificial, Edge Impulse y ESP32-CAM.
# Clasificador inteligente de residuos con IA

Prototipo de clasificación automática de residuos mediante **visión artificial, inteligencia artificial, electrónica, diseño 3D y control de actuadores**.

El sistema utiliza una **ESP32-CAM AI Thinker** para capturar imágenes de los residuos y un modelo desarrollado con **Edge Impulse** para clasificarlos. De acuerdo con el resultado de la clasificación, un **motor paso a paso 28BYJ-48** hace girar el cuerpo cilíndrico del recipiente hasta alinear el compartimento correspondiente con el punto de descarga.

---
## Equipo del proyecto

### Estudiantes autores

- Mateo Serna Echeverri — Programación
- Emmanuel Sánchez Zapata — Diseño 3D
- Juan José Osorio Tobón — Electrónica
- Miguel Ángel Zapata Serna — Visión artificial
- Gerónimo Rodríguez Chaverra — Mecánica

### Profesor asesor

- Frank Alexander Parra Sánchez

## 1. Descripción del proyecto

El proyecto busca desarrollar un clasificador inteligente capaz de identificar diferentes tipos de residuos y depositarlos automáticamente en el compartimento correspondiente.

El prototipo está compuesto por una estructura cilíndrica dividida en tres compartimentos:

* **Residuos aprovechables**
* **Residuos no aprovechables**
* **Residuos orgánicos**

La clasificación se realiza mediante una cámara y un modelo de reconocimiento de imágenes desarrollado con Edge Impulse. Una vez identificado el residuo, el sistema posiciona automáticamente el compartimento adecuado debajo del punto de descarga.

---

## 2. Problema

La correcta separación de residuos depende normalmente de que las personas identifiquen el tipo de residuo y lo depositen en el recipiente adecuado.

Cuando esta clasificación se realiza incorrectamente, los materiales aprovechables pueden mezclarse con residuos orgánicos o no aprovechables, dificultando su recuperación.

Este proyecto explora la posibilidad de utilizar **inteligencia artificial y automatización** para apoyar este proceso de clasificación.

---

## 3. Objetivo

Diseñar y construir un prototipo de clasificador de residuos que utilice inteligencia artificial para identificar el tipo de residuo y dirigirlo automáticamente al compartimento correspondiente.

---

## 4. Funcionamiento general

El funcionamiento propuesto del sistema es el siguiente:

1. El usuario deposita un residuo a través de una abertura ubicada en la **tapa fija**.
2. El residuo queda temporalmente en un **compartimento de análisis**.
3. La **ESP32-CAM** captura la imagen del residuo.
4. El modelo desarrollado con **Edge Impulse** identifica su categoría.
5. El **motor paso a paso** gira el cuerpo cilíndrico móvil hasta posicionar el compartimento correspondiente debajo del punto de descarga.
6. Se abre la compuerta inferior del compartimento de análisis.
7. El residuo cae en el compartimento seleccionado.
8. La compuerta se cierra.
9. El cuerpo móvil regresa a su posición inicial.

### Posiciones del recipiente

El cuerpo cilíndrico está dividido en tres sectores de aproximadamente **120°**.

El sistema utiliza diferentes posiciones angulares para alinear cada compartimento con el punto de descarga.

---

## 5. Diseño mecánico

La estructura está conformada por tres elementos principales:

### Tapa fija

Permanece inmóvil durante el funcionamiento y contiene:

* la abertura para ingresar el residuo;
* el espacio destinado al análisis del residuo;
* la cámara;
* la compuerta inferior de descarga.

### Cuerpo cilíndrico móvil

Es el recipiente principal y está dividido internamente en tres compartimentos.

Este cuerpo es el elemento que gira durante la clasificación.

La estructura se apoya sobre pequeñas **ruedas**, que permiten disminuir la fricción durante el movimiento.

### Base fija inferior

La base inferior permanece fija y soporta el cuerpo móvil.

Debajo de esta base se encuentra el motor paso a paso. El eje del motor atraviesa una abertura en la base fija y se acopla a la parte inferior del cuerpo móvil.

Una estructura lateral conecta la base fija inferior con la tapa fija superior.

---

## 6. Componentes electrónicos

Actualmente el prototipo utiliza los siguientes componentes:

| Componente                 | Función                                          |
| -------------------------- | ------------------------------------------------ |
| ESP32-CAM AI Thinker       | Captura de imágenes y ejecución del modelo de IA |
| Cámara OV2640              | Captura de imágenes de los residuos              |
| Motor paso a paso 28BYJ-48 | Giro del cuerpo cilíndrico                       |
| Driver ULN2003             | Control del motor 28BYJ-48                       |
| Servomotor                 | Accionamiento de la compuerta de descarga        |
| LM2596                     | Regulación del voltaje de alimentación           |
| Batería de 12 V            | Alimentación del sistema                         |
| Interruptor                | Encendido y apagado                              |
| Cables de conexión         | Interconexión de los componentes                 |

---

## 7. Inteligencia artificial

El reconocimiento de residuos fue desarrollado utilizando **Edge Impulse**.

El modelo actualmente trabaja con tres categorías:

```text
Residuos_Aprovechables
Residuos_No_Aprovechables
Residuos_Orgánicos
```

La ESP32-CAM captura la imagen y ejecuta la inferencia. Cuando se detecta un residuo, el resultado de la clasificación determina el movimiento que debe realizar el motor paso a paso.

---

## 8. Software y herramientas

Para el desarrollo del proyecto se han utilizado:

* **Arduino IDE**
* **Edge Impulse**
* **Collect Images for Edge Impulse**
* **Tinkercad**
* Diseño e impresión 3D
* Lenguaje de programación C/C++ para Arduino

---

## 9. Pruebas realizadas

Hasta el momento se han desarrollado pruebas independientes y de integración.

### Motor paso a paso

Se comprobó el funcionamiento del:

* motor 28BYJ-48;
* driver ULN2003;
* movimiento mediante la ESP32.

### Reconocimiento de residuos

Se comprobó que el modelo puede realizar inferencias desde la ESP32-CAM y generar las etiquetas correspondientes a las tres categorías.

Ejemplo de salida observada en el monitor serial:

```text
Residuos_Aprovechables
Es un residuo aprovechable!
Moviendo el stepper con 85 pasos
```

```text
Residuos_No_Aprovechables
Es un residuo no aprovechable!
Moviendo el stepper con 683 pasos
```

```text
Residuos_Orgánicos
Es un residuo organico!
Moviendo el stepper con 1365 pasos
```

Actualmente se está trabajando en la integración entre el reconocimiento mediante IA y el movimiento físico del recipiente.

---

## 10. Diseño e impresión 3D

El prototipo se está diseñando de manera modular para permitir su fabricación mediante impresión 3D.

El recipiente tiene una geometría cilíndrica y está dividido en tres compartimentos independientes.

Debido a las dimensiones del prototipo y al área disponible en la impresora 3D, las piezas se diseñan por secciones para posteriormente ensamblarlas.

Actualmente ya se han diseñado e impreso algunas partes de la estructura.

---

## 11. Estado actual del proyecto

### Completado

* [x] Definición del concepto del clasificador
* [x] Definición de las tres categorías de residuos
* [x] Entrenamiento inicial del modelo en Edge Impulse
* [x] Ejecución del modelo en ESP32-CAM
* [x] Diseño inicial de la estructura cilíndrica
* [x] Diseño modular para impresión 3D
* [x] Impresión de algunas piezas
* [x] Prueba independiente del motor paso a paso
* [x] Detección de las tres categorías desde la ESP32-CAM

### En desarrollo

* [ ] Integración estable entre la clasificación y el motor paso a paso
* [ ] Ensamble completo del cuerpo móvil
* [ ] Diseño y prueba de la compuerta de descarga
* [ ] Integración del servomotor
* [ ] Integración completa de la electrónica
* [ ] Pruebas del mecanismo de giro con carga
* [ ] Pruebas completas de clasificación y descarga

---

## 12. Arquitectura general

```text
                    RESIDUO
                       │
                       ▼
              ┌─────────────────┐
              │   Tapa fija     │
              │    Entrada      │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │ Compartimento   │
              │   de análisis   │
              │                 │
              │   ESP32-CAM     │
              └────────┬────────┘
                       │
                       ▼
                Edge Impulse
                       │
                       ▼
               Clasificación IA
                       │
                       ▼
              Motor paso a paso
                       │
                       ▼
          Giro del recipiente móvil
                       │
                       ▼
            Compartimento alineado
                       │
                       ▼
             Apertura de compuerta
                       │
                       ▼
              Depósito del residuo
```

---

## 13. Organización del repositorio

```text
clasificador-residuos-ia/
│
├── README.md
│
├── firmware/
│   ├── pruebas_motor/
│   ├── prueba_ia_motor/
│   └── clasificador_completo/
│
├── edge-impulse/
│
├── hardware/
│   ├── electronica/
│   └── mecanica/
│       ├── modelos-3d/
│       └── stl/
│
├── docs/
│
└── images/
    ├── prototipo/
    ├── impresiones-3d/
    └── pruebas/
```

---

## 14. Próximas etapas

Las siguientes etapas del proyecto estarán orientadas a:

1. solucionar la integración entre el reconocimiento y el movimiento del motor;
2. finalizar el mecanismo de giro del recipiente;
3. construir la compuerta automática;
4. integrar el servomotor;
5. ensamblar los componentes electrónicos;
6. realizar pruebas con residuos reales;
7. evaluar la precisión de la clasificación;
8. identificar posibles atascos o fallos mecánicos;
9. ajustar el diseño 3D;
10. construir y evaluar el prototipo completo.

---

## 15. Tecnologías utilizadas

`ESP32-CAM` · `Edge Impulse` · `Arduino` · `C++` · `28BYJ-48` · `ULN2003` · `Impresión 3D` · `Tinkercad` · `Visión artificial`

---

## Licencia

La licencia del proyecto se definirá antes de la publicación definitiva del repositorio.
