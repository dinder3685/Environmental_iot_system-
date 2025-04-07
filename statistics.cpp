#include "statistics.h"
#include <math.h>
#include <string.h>

void calculateStats(float* data, int count, float* min, float* max, float* median, float* stdDev) {
  if (count == 0) return;

  *min = data[0];
  *max = data[0];
  float sum = 0;

  for (int i = 0; i < count; i++) {
    if (data[i] < *min) *min = data[i];
    if (data[i] > *max) *max = data[i];
    sum += data[i];
  }

  float mean = sum / count;

  float variance = 0;
  for (int i = 0; i < count; i++) {
    variance += pow(data[i] - mean, 2);
  }

  *stdDev = sqrt(variance / count);

  float temp[count];
  memcpy(temp, data, count * sizeof(float));

  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (temp[j] > temp[j + 1]) {
        float swap = temp[j];
        temp[j] = temp[j + 1];
        temp[j + 1] = swap;
      }
    }
  }

  if (count % 2 == 0) {
    *median = (temp[count / 2 - 1] + temp[count / 2]) / 2;
  } else {
    *median = temp[count / 2];
  }
}
