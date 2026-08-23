/*
  Prueba independiente del motor paso a paso 28BYJ-48
  Proyecto: Clasificador inteligente de residuos con IA

  Hardware:
  - ESP32-CAM AI Thinker
  - Driver ULN2003
  - Motor paso a paso 28BYJ-48

  Objetivo:
  Verificar el movimiento del motor antes de integrarlo con
  la cámara, Edge Impulse y el mecanismo completo.

  Posiciones de prueba:
  - 85 pasos   ≈ 15°   (movimiento corto de verificación)
  - 683 pasos  ≈ 120°
  - 1365 pasos ≈ 240°

  Nota:
  Se considera aproximadamente 2048 pasos por revolución.
*/

#include <Stepper.h>

#define IN1 2
#define IN2 14
#define IN3 15
#define IN4 12

#define STEPS_PER_REVOLUTION 2048

#define STEPPER_PRUEBA_CORTA 85
#define STEPPER_120_GRADOS 683
#define STEPPER_240_GRADOS 1365

Stepper stepper(STEPS_PER_REVOLUTION, IN1, IN2, IN3, IN4);

void setup() {
  Serial.begin(115200);

  stepper.setSpeed(5);

  Serial.println();
  Serial.println("=== PRUEBA DEL MOTOR 28BYJ-48 ===");
  Serial.println("La prueba comenzara en 3 segundos...");
  delay(3000);

  Serial.println("Prueba 1: 85 pasos");
  stepper.step(STEPPER_PRUEBA_CORTA);
  delay(2000);

  Serial.println("Regresando a la posicion inicial...");
  stepper.step(-STEPPER_PRUEBA_CORTA);
  delay(3000);

  Serial.println("Prueba 2: aproximadamente 120 grados");
  stepper.step(STEPPER_120_GRADOS);
  delay(3000);

  Serial.println("Regresando a la posicion inicial...");
  stepper.step(-STEPPER_120_GRADOS);
  delay(3000);

  Serial.println("Prueba 3: aproximadamente 240 grados");
  stepper.step(STEPPER_240_GRADOS);
  delay(3000);

  Serial.println("Regresando a la posicion inicial...");
  stepper.step(-STEPPER_240_GRADOS);

  Serial.println("=== PRUEBA FINALIZADA ===");
}

void loop() {
  // La prueba se ejecuta una sola vez al encender o reiniciar la ESP32-CAM.
}
