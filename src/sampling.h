#ifndef SAMPLING_H
#define SAMPLING_H

#include "Particle.h"
#include "adxl343.h"

#define RING_SIZE       64          //størrelse på circulær buffer
#define BEFORE_PEAK     20          
#define AFTER_PEAK      15
#define WINDOW_SIZE     (BEFORE_PEAK + AFTER_PEAK)
#define PEAK_THRESHOLD  1500.0f // denne kan justeres alt efter hvor hårdt man slår og hvor følsom accelerometeret er
#define COOLDOWN_MS     500         // der skal gå lidt til så man ikke laver dobbelt catch

typedef struct {
    float x[RING_SIZE];
    float y[RING_SIZE];
    float z[RING_SIZE];
    float mag[RING_SIZE];
    int   head;
} RingBuffer_t;

typedef enum {
    STATE_WAITING,
    STATE_CAPTURING,
    STATE_READY
} CaptureState_t;

// De variable loop() har brug for at læse
extern volatile CaptureState_t captureState;
extern float x_window[WINDOW_SIZE];
extern float y_window[WINDOW_SIZE];
extern float z_window[WINDOW_SIZE];
extern float mag_window[WINDOW_SIZE];

// Funktioner
void sampling_init();
void readAccelerometer();

#endif