#include "sampling.h"
#include <math.h>

// global variabler
volatile CaptureState_t captureState = STATE_WAITING; //skal være volatile da den bliver ændret i interrupt
float x_window[WINDOW_SIZE];
float y_window[WINDOW_SIZE];
float z_window[WINDOW_SIZE];
float mag_window[WINDOW_SIZE];

static RingBuffer_t ring = {};
static int captureCount = 0;
static unsigned long lastPunch = 0;
static ADXL343 accelerometer;
static Timer accelerometerTicker(10, readAccelerometer);

void sampling_init() {
    if (!accelerometer.begin()) {
        Log.error("Failed to initialize ADXL343.");
    }
    accelerometerTicker.start();
}

void readAccelerometer() {
    float x_g, y_g, z_g;
    accelerometer.readAccelerationG(&x_g, &y_g, &z_g);

    float x   = x_g * 1000.0f;
    float y   = y_g * 1000.0f;
    float z   = z_g * 1000.0f;
    float mag = sqrtf(x*x + y*y + z*z);

    ring.x[ring.head]   = x;
    ring.y[ring.head]   = y;
    ring.z[ring.head]   = z;
    ring.mag[ring.head] = mag;
    ring.head = (ring.head + 1) & (RING_SIZE - 1);

    if (captureState == STATE_WAITING &&
        mag > PEAK_THRESHOLD &&
        (millis() - lastPunch) > COOLDOWN_MS)
    {
        for (int i = 0; i < BEFORE_PEAK; i++) {
            int idx = (ring.head - BEFORE_PEAK + i + RING_SIZE) & (RING_SIZE - 1);
            x_window[i]   = ring.x[idx];
            y_window[i]   = ring.y[idx];
            z_window[i]   = ring.z[idx];
            mag_window[i] = ring.mag[idx];
        }
        captureCount = 0;
        captureState = STATE_CAPTURING;
    }

    if (captureState == STATE_CAPTURING) {
        x_window[BEFORE_PEAK + captureCount]   = x;
        y_window[BEFORE_PEAK + captureCount]   = y;
        z_window[BEFORE_PEAK + captureCount]   = z;
        mag_window[BEFORE_PEAK + captureCount] = mag;
        captureCount++;

        if (captureCount >= AFTER_PEAK) {
            captureState = STATE_READY;
            lastPunch = millis();
        }
    }
}