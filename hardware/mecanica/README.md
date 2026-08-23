# Diseño mecánico del clasificador

Esta carpeta contiene la documentación y los archivos relacionados con el diseño mecánico y la fabricación mediante impresión 3D del clasificador inteligente de residuos.

## Diseño general

El clasificador tiene una geometría cilíndrica y está compuesto por una estructura fija y un cuerpo móvil.

El recipiente principal está dividido en tres compartimentos destinados a:

- Residuos aprovechables
- Residuos no aprovechables
- Residuos orgánicos

Durante el funcionamiento, la tapa permanece fija y el cuerpo cilíndrico es el elemento que gira para posicionar el compartimento correspondiente debajo del punto de descarga.

## Componentes principales

### Tapa fija

La tapa permanece inmóvil durante el funcionamiento.

Contiene:

- la abertura para depositar el residuo;
- el compartimento donde se realiza el análisis;
- la cámara;
- la compuerta inferior por donde posteriormente cae el residuo.

### Cuerpo cilíndrico móvil

Es el recipiente principal del clasificador.

Está dividido internamente en tres compartimentos y gira alrededor de su eje vertical para alinear el compartimento correcto con la abertura de descarga.

El cuerpo móvil se apoya sobre ruedas ubicadas entre este y la base fija inferior.

### Base fija inferior

La base inferior permanece inmóvil y sirve como soporte para el cuerpo giratorio.

Es hueca en su parte inferior para permitir la instalación del motor paso a paso.

El eje del motor atraviesa una abertura en esta base y se acopla a la parte inferior del cuerpo móvil.

### Estructura de soporte

Una estructura lateral conecta la base fija inferior con la tapa fija superior.

Esta estructura permite mantener ambos elementos inmóviles mientras el cuerpo cilíndrico gira entre ellos.

## Sistema de giro

El movimiento del cuerpo cilíndrico se realiza mediante un motor paso a paso 28BYJ-48.

El motor se encuentra ubicado debajo de la base fija inferior.

Su eje atraviesa la base fija y se acopla directamente con la parte inferior del cuerpo móvil.

Las ruedas ubicadas entre la base fija y el cuerpo móvil permiten reducir la fricción durante el giro.

## Posiciones de funcionamiento

Debido a que el recipiente está dividido en tres compartimentos, el sistema utiliza tres posiciones principales:

- 0°
- 120°
- 240°

El motor posiciona el cuerpo móvil de acuerdo con la categoría detectada por el modelo de inteligencia artificial.

## Diseño para impresión 3D

El prototipo se diseñó de forma modular debido a las dimensiones máximas disponibles en la impresora 3D.

Las piezas de mayor tamaño se dividen en diferentes secciones que posteriormente se ensamblan.

Este diseño modular también facilita:

- la impresión de las piezas;
- el reemplazo de componentes;
- la modificación del prototipo;
- el ajuste de dimensiones durante las pruebas.

## Estado actual

Actualmente se han diseñado e impreso algunas de las piezas principales del clasificador.

Se continúa trabajando en:

- el ensamble del cuerpo móvil;
- el sistema de apoyo mediante ruedas;
- el acople entre el motor y el cuerpo móvil;
- la tapa fija;
- el compartimento de análisis;
- la compuerta de descarga;
- y el ensamble completo del mecanismo.
