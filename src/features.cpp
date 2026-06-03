#include "features.h"
#include <math.h>


float compute_mean(const float *data, int n)
{
    float sum = 0.0f;
    for(int i =0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

float compute_std(const float *data, int n, float mean)
{
    float sum = 0.0f;
    for(int i =0; i < n; i++) {
         sum += (data[i] - mean) * (data[i] - mean);
    }
    return sqrt(sum / n);
}

float compute_max(const float *data, int n)
{
    float maximum = data[0];
    for(int i = 1; i < n; i++) {
        if (data[i] > maximum) {
            maximum = data[i];
        }
    }
    return maximum;
}

float compute_min(const float *data, int n)
{
    float minimum = data[0];
    for(int i = 1; i < n; i++) {
        if (data[i] < minimum) {
            minimum = data[i];
        }
    }
    return minimum;
}

float compute_rms(const float *data, int n)
{
    float sum = 0.0f;
    for(int i =0; i < n; i++) {
         sum += data[i] * data[i];
    }
    return sqrt(sum / n);
}

void extract_features(const float *x, const float *y, const float *z, const float *mag, int n, BoxingFeatures_t *out)
{
    out->accX_mean = compute_mean(x, n);
    out->accX_std = compute_std(x, n, out->accX_mean);
    out->accX_max = compute_max(x, n);
    out->accX_min = compute_min(x, n);
    out->accX_rms = compute_rms(x, n);

    out->accY_mean = compute_mean(y, n);
    out->accY_std = compute_std(y, n, out->accY_mean);
    out->accY_max = compute_max(y, n);
    out->accY_min = compute_min(y, n);
    out->accY_rms = compute_rms(y, n);

    out->accZ_mean = compute_mean(z, n);
    out->accZ_std = compute_std(z, n, out->accZ_mean);
    out->accZ_max = compute_max(z, n);
    out->accZ_min = compute_min(z, n);
    out->accZ_rms = compute_rms(z, n);

    out->mag_mean = compute_mean(mag, n);
    out->mag_std = compute_std(mag, n, out->mag_mean);
    out->mag_max = compute_max(mag, n);
    out->mag_rms = compute_rms(mag, n);
}

void quantize_features(const BoxingFeatures_t *in, BoxingFeaturesQuantized_t *out)
{
    int k = 0;

    out->values[k++] = (int16_t)roundf(in->accX_mean);
    out->values[k++] = (int16_t)roundf(in->accX_std);
    out->values[k++] = (int16_t)roundf(in->accX_max);
    out->values[k++] = (int16_t)roundf(in->accX_min);
    out->values[k++] = (int16_t)roundf(in->accX_rms);

    out->values[k++] = (int16_t)roundf(in->accY_mean);
    out->values[k++] = (int16_t)roundf(in->accY_std);
    out->values[k++] = (int16_t)roundf(in->accY_max);
    out->values[k++] = (int16_t)roundf(in->accY_min);
    out->values[k++] = (int16_t)roundf(in->accY_rms);

    out->values[k++] = (int16_t)roundf(in->accZ_mean);
    out->values[k++] = (int16_t)roundf(in->accZ_std);
    out->values[k++] = (int16_t)roundf(in->accZ_max);
    out->values[k++] = (int16_t)roundf(in->accZ_min);
    out->values[k++] = (int16_t)roundf(in->accZ_rms);

    out->values[k++] = (int16_t)roundf(in->mag_mean);
    out->values[k++] = (int16_t)roundf(in->mag_std);
    out->values[k++] = (int16_t)roundf(in->mag_max);
    out->values[k++] = (int16_t)roundf(in->mag_rms);
}