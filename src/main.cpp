#include "Particle.h"
#include "sampling.h"
#include "features.h"
#include "boxing_model.h"

SYSTEM_MODE(MANUAL);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup() {
    Serial.begin(115200);
    pinMode(D7, OUTPUT);
    digitalWrite(D7, LOW);
    sampling_init();
}

void loop() {
    if (captureState != STATE_READY) return;

    BoxingFeatures_t feats;
    BoxingFeaturesQuantized_t feats_q;

    extract_features(x_window, y_window, z_window, mag_window, WINDOW_SIZE, &feats);
    quantize_features(&feats, &feats_q);

    int prediction = boxing_model_predict(feats_q.values, NUM_FEATURES);

    if      (prediction == 0) Serial.println("Punch detected: hook");
    else if (prediction == 1) Serial.println("Punch detected: jab");
    else if (prediction == 2) Serial.println("Punch detected: uppercut");

    digitalWrite(D7, HIGH);
    delay(50);
    digitalWrite(D7, LOW);

    captureState = STATE_WAITING;
}