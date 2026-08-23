


/* Includes ---------------------------------------------------------------- */
#include <ESP32Servo.h>
#include <Seleccionador_de_residuos_con_IA_inferencing.h>
#include <Stepper.h>

#include "edge-impulse-sdk/dsp/image/image.hpp"
#include "esp_camera.h"

// #define CAMERA_MODEL_ESP_EYE // Has PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM

#if defined(CAMERA_MODEL_ESP_EYE)

#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 4
#define SIOD_GPIO_NUM 18
#define SIOC_GPIO_NUM 23

#define Y9_GPIO_NUM 36
#define Y8_GPIO_NUM 37
#define Y7_GPIO_NUM 38
#define Y6_GPIO_NUM 39
#define Y5_GPIO_NUM 35
#define Y4_GPIO_NUM 14
#define Y3_GPIO_NUM 13
#define Y2_GPIO_NUM 34
#define VSYNC_GPIO_NUM 5
#define HREF_GPIO_NUM 27
#define PCLK_GPIO_NUM 25

#elif defined(CAMERA_MODEL_AI_THINKER)

#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#else
#error "Camera model not selected"
#endif

/* Constant defines -------------------------------------------------------- */

#define EI_CAMERA_RAW_FRAME_BUFFER_COLS 320
#define EI_CAMERA_RAW_FRAME_BUFFER_ROWS 240
#define EI_CAMERA_FRAME_BYTE_SIZE 3

/* Private variables ------------------------------------------------------- */

static bool debug_nn = false;
static bool is_initialised = false;

uint8_t* snapshot_buf;

// Pin del servo
const int PinServo = 13;

// Pines para el motor
#define IN1 2
#define IN2 14
#define IN3 15
#define IN4 12

// Vuelta completa del stepper
#define STEPS_PER_REVOLUTION 2048

// Grados del stepper
#define STEPPER_360_GRADOS STEPS_PER_REVOLUTION
#define STEPPER_CERO_GRADOS 85
#define STEPPER_120_GRADOS 683
#define STEPPER_240_GRADOS 1365

Servo servo;

// Inicializa el stepper
Stepper stepper(
    STEPS_PER_REVOLUTION,
    IN1,
    IN2,
    IN3,
    IN4
);

static camera_config_t camera_config = {

    .pin_pwdn = PWDN_GPIO_NUM,
    .pin_reset = RESET_GPIO_NUM,
    .pin_xclk = XCLK_GPIO_NUM,
    .pin_sscb_sda = SIOD_GPIO_NUM,
    .pin_sscb_scl = SIOC_GPIO_NUM,

    .pin_d7 = Y9_GPIO_NUM,
    .pin_d6 = Y8_GPIO_NUM,
    .pin_d5 = Y7_GPIO_NUM,
    .pin_d4 = Y6_GPIO_NUM,
    .pin_d3 = Y5_GPIO_NUM,
    .pin_d2 = Y4_GPIO_NUM,
    .pin_d1 = Y3_GPIO_NUM,
    .pin_d0 = Y2_GPIO_NUM,

    .pin_vsync = VSYNC_GPIO_NUM,
    .pin_href = HREF_GPIO_NUM,
    .pin_pclk = PCLK_GPIO_NUM,

    .xclk_freq_hz = 20000000,

    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG,

    .frame_size = FRAMESIZE_QVGA,

    .jpeg_quality = 12,

    .fb_count = 1,

    .fb_location = CAMERA_FB_IN_PSRAM,

    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

/* Function definitions --------------------------------------------------- */

bool ei_camera_init(void);
void ei_camera_deinit(void);

bool ei_camera_capture(
    uint32_t img_width,
    uint32_t img_height,
    uint8_t* out_buf
);

/* ----------------------------------------------------------------------- */
/* SETUP                                                                   */
/* ----------------------------------------------------------------------- */

void setup() {

    Serial.begin(115200);

    while (!Serial);

    Serial.println("Edge Impulse Inferencing Demo");

    if (ei_camera_init() == false) {

        ei_printf("Failed to initialize Camera!\r\n");

    }
    else {

        ei_printf("Camera initialized\r\n");
    }

    ei_printf(
        "\nStarting continious inference in 2 seconds...\n"
    );

    ei_sleep(2000);

    servo.attach(PinServo);

    stepper.setSpeed(19);
}

/* ----------------------------------------------------------------------- */
/* MOTOR PASO A PASO                                                       */
/* ----------------------------------------------------------------------- */

void moverStepper(int pasos, int segundos) {

    ei_printf(
        "Moviendo el stepper con %d pasos\n",
        pasos
    );

    stepper.step(pasos);

    ei_printf(
        "Esperando %d segundos\n",
        segundos
    );

    delay(segundos * 1000);

    ei_printf(
        "Volviendo a la posicion inicial\n"
    );

    stepper.step(-pasos);
}

/* ----------------------------------------------------------------------- */
/* SERVOMOTOR                                                              */
/* ----------------------------------------------------------------------- */

void moverServo(int grados, int segundos) {

    ei_printf(
        "Moviendo el servo %d grados\n",
        grados
    );

    servo.write(grados);

    ei_printf(
        "Esperando %d segundos\n",
        segundos
    );

    delay(segundos * 1000);

    ei_printf(
        "Volviendo a la posicion inicial\n"
    );

    servo.write(0);
}

/* ----------------------------------------------------------------------- */
/* LOOP                                                                    */
/* ----------------------------------------------------------------------- */

void loop() {

    if (ei_sleep(5) != EI_IMPULSE_OK) {

        return;
    }

    snapshot_buf = (uint8_t*)malloc(
        EI_CAMERA_RAW_FRAME_BUFFER_COLS *
        EI_CAMERA_RAW_FRAME_BUFFER_ROWS *
        EI_CAMERA_FRAME_BYTE_SIZE
    );

    if (snapshot_buf == nullptr) {

        ei_printf(
            "ERR: Failed to allocate snapshot buffer!\n"
        );

        return;
    }

    ei::signal_t signal;

    signal.total_length =
        EI_CLASSIFIER_INPUT_WIDTH *
        EI_CLASSIFIER_INPUT_HEIGHT;

    signal.get_data =
        &ei_camera_get_data;

    if (
        ei_camera_capture(
            (size_t)EI_CLASSIFIER_INPUT_WIDTH,
            (size_t)EI_CLASSIFIER_INPUT_HEIGHT,
            snapshot_buf
        ) == false
    ) {

        ei_printf(
            "Failed to capture image\r\n"
        );

        free(snapshot_buf);

        return;
    }

    /* Ejecutar clasificador */

    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR err =
        run_classifier(
            &signal,
            &result,
            debug_nn
        );

    if (err != EI_IMPULSE_OK) {

        ei_printf(
            "ERR: Failed to run classifier (%d)\n",
            err
        );

        return;
    }

    /* Mostrar predicciones */

    ei_printf(
        "Predictions "
        "(DSP: %d ms., "
        "Classification: %d ms., "
        "Anomaly: %d ms.): \n",

        result.timing.dsp,
        result.timing.classification,
        result.timing.anomaly
    );

    ei_printf(
        "Object detection bounding boxes:\r\n"
    );

    for (
        uint32_t i = 0;
        i < result.bounding_boxes_count;
        i++
    ) {

        ei_impulse_result_bounding_box_t bb =
            result.bounding_boxes[i];

        if (bb.value == 0) {

            continue;
        }

        ei_printf(
            "  %s (%f) "
            "[ x: %u, y: %u, "
            "width: %u, height: %u ]\r\n",

            bb.label,
            bb.value,
            bb.x,
            bb.y,
            bb.width,
            bb.height
        );

        String objectLabel =
            String(bb.label);

        /* --------------------------------------------------------------- */
        /* RESIDUOS APROVECHABLES                                          */
        /* --------------------------------------------------------------- */

        if (
            objectLabel.equals(
                "Residuos_Aprovechables"
            )
        ) {

            ei_printf(
                "Es un residuo aprovechable!\n"
            );

            moverStepper(
                STEPPER_CERO_GRADOS,
                5
            );

            moverServo(
                90,
                2
            );
        }

        /* --------------------------------------------------------------- */
        /* RESIDUOS NO APROVECHABLES                                       */
        /* --------------------------------------------------------------- */

        else if (
            objectLabel.equals(
                "Residuos_No_Aprovechables"
            )
        ) {

            ei_printf(
                "Es un residuo no aprovechable!\n"
            );

            moverStepper(
                STEPPER_120_GRADOS,
                5
            );

            moverServo(
                90,
                2
            );
        }

        /* --------------------------------------------------------------- */
        /* RESIDUOS ORGÁNICOS                                               */
        /* --------------------------------------------------------------- */

        else if (
            objectLabel.equals(
                "Residuos_Orgánicos"
            )
        ) {

            ei_printf(
                "Es un residuo organico!\n"
            );

            moverStepper(
                STEPPER_240_GRADOS,
                5
            );

            moverServo(
                90,
                2
            );
        }
    }

    free(snapshot_buf);
}

/* ----------------------------------------------------------------------- */
/* INICIALIZACIÓN DE LA CÁMARA                                              */
/* ----------------------------------------------------------------------- */

bool ei_camera_init(void) {

    if (is_initialised) {

        return true;
    }

#if defined(CAMERA_MODEL_ESP_EYE)

    pinMode(
        13,
        INPUT_PULLUP
    );

    pinMode(
        14,
        INPUT_PULLUP
    );

#endif

    esp_err_t err =
        esp_camera_init(
            &camera_config
        );

    if (err != ESP_OK) {

        Serial.printf(
            "Camera init failed with error 0x%x\n",
            err
        );

        return false;
    }

    sensor_t* s =
        esp_camera_sensor_get();

    if (
        s->id.PID ==
        OV3660_PID
    ) {

        s->set_vflip(
            s,
            1
        );

        s->set_brightness(
            s,
            1
        );

        s->set_saturation(
            s,
            0
        );
    }

#if defined(CAMERA_MODEL_M5STACK_WIDE)

    s->set_vflip(
        s,
        1
    );

    s->set_hmirror(
        s,
        1
    );

#elif defined(CAMERA_MODEL_ESP_EYE)

    s->set_vflip(
        s,
        1
    );

    s->set_hmirror(
        s,
        1
    );

    s->set_awb_gain(
        s,
        1
    );

#endif

    is_initialised = true;

    return true;
}

/* ----------------------------------------------------------------------- */
/* DESINICIALIZACIÓN DE LA CÁMARA                                           */
/* ----------------------------------------------------------------------- */

void ei_camera_deinit(void) {

    esp_err_t err =
        esp_camera_deinit();

    if (err != ESP_OK) {

        ei_printf(
            "Camera deinit failed\n"
        );

        return;
    }

    is_initialised = false;
}

/* ----------------------------------------------------------------------- */
/* CAPTURA DE IMAGEN                                                        */
/* ----------------------------------------------------------------------- */

bool ei_camera_capture(
    uint32_t img_width,
    uint32_t img_height,
    uint8_t* out_buf
) {

    bool do_resize = false;

    if (!is_initialised) {

        ei_printf(
            "ERR: Camera is not initialized\r\n"
        );

        return false;
    }

    camera_fb_t* fb =
        esp_camera_fb_get();

    if (!fb) {

        ei_printf(
            "Camera capture failed\n"
        );

        return false;
    }

    bool converted =
        fmt2rgb888(
            fb->buf,
            fb->len,
            PIXFORMAT_JPEG,
            snapshot_buf
        );

    esp_camera_fb_return(
        fb
    );

    if (!converted) {

        ei_printf(
            "Conversion failed\n"
        );

        return false;
    }

    if (
        (img_width !=
         EI_CAMERA_RAW_FRAME_BUFFER_COLS)
        ||
        (img_height !=
         EI_CAMERA_RAW_FRAME_BUFFER_ROWS)
    ) {

        do_resize = true;
    }

    if (do_resize) {

        ei::image::processing::
            crop_and_interpolate_rgb888(

                out_buf,

                EI_CAMERA_RAW_FRAME_BUFFER_COLS,

                EI_CAMERA_RAW_FRAME_BUFFER_ROWS,

                out_buf,

                img_width,

                img_height
            );
    }

    return true;
}

/* ----------------------------------------------------------------------- */
/* OBTENER DATOS DE LA IMAGEN                                               */
/* ----------------------------------------------------------------------- */

static int ei_camera_get_data(
    size_t offset,
    size_t length,
    float* out_ptr
) {

    size_t pixel_ix =
        offset * 3;

    size_t pixels_left =
        length;

    size_t out_ptr_ix =
        0;

    while (
        pixels_left != 0
    ) {

        out_ptr[out_ptr_ix] =
            (
                snapshot_buf[
                    pixel_ix + 2
                ] << 16
            )
            +
            (
                snapshot_buf[
                    pixel_ix + 1
                ] << 8
            )
            +
            snapshot_buf[
                pixel_ix
            ];

        out_ptr_ix++;

        pixel_ix += 3;

        pixels_left--;
    }

    return 0;
}

#if !defined(EI_CLASSIFIER_SENSOR) || \
    EI_CLASSIFIER_SENSOR != \
    EI_CLASSIFIER_SENSOR_CAMERA

#error "Invalid model for current sensor"

#endif
