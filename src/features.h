#ifndef FEATURES_H
#define FEATURES_H

#include <stdint.h>

#define NUM_FEATURES 19

typedef struct {
    float accX_mean; //  0 accX_mean
    float accX_std; //  1 accX_std
    float accX_max; //  2 accX_max
    float accX_min; //  3 accX_min
    float accX_rms; //  4 accX_rms
    float accY_mean; //  5 accY_mean
    float accY_std; //  6 accY_std
    float accY_max; //  7 accY_max
    float accY_min; //  8 accY_min
    float accY_rms; //  9 accY_rms
    float accZ_mean; // 10 accZ_mean
    float accZ_std; // 11 accZ_std
    float accZ_max; // 12 accZ_max
    float accZ_min; // 13 accZ_min
    float accZ_rms; // 14 accZ_rms
    float mag_mean; // 15 mag_mean
    float mag_std;  // 16 mag_std
    float mag_max;  // 17 mag_max
    float mag_rms;  // 18 mag_rms
}BoxingFeatures_t;

typedef struct {
int16_t values[NUM_FEATURES];
}BoxingFeaturesQuantized_t;

void extract_features(
    const float *x,
    const float *y,
    const float *z,
    const float *mag,
    int n,
    BoxingFeatures_t *out
);

void quantize_features(
    const BoxingFeatures_t *in,
    BoxingFeaturesQuantized_t *out
);

float compute_mean(const float *data, int n);
float compute_std(const float *data, int n, float mean);
float compute_max(const float *data, int n);
float compute_min(const float *data, int n);
float compute_rms(const float *data, int n);


#endif // FEATURES_H