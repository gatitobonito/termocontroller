
#ifndef PROJECT_EWW_CORE_INC_TERMO_SENSOR_H_
#define PROJECT_EWW_CORE_INC_TERMO_SENSOR_H_
#include <stdint.h>
#include <math.h>

#define FILTER_SIZE 10

typedef struct
{
  uint16_t ntc_raw_adc[FILTER_SIZE];
  uint8_t cnt;
} filter_ntc_t;


uint16_t median_filter (uint16_t *p, size_t n);
void add_number(filter_ntc_t ntc_raw, uint16_t number);
int8_t ntc_get_temp(uint16_t adc_value);
#endif //PROJECT_EWW_CORE_INC_TERMO_SENSOR_H_
