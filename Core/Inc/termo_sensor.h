
#ifndef PROJECT_EWW_CORE_INC_TERMO_SENSOR_H_
#define PROJECT_EWW_CORE_INC_TERMO_SENSOR_H_
#include <stdint.h>
#include <math.h>



uint16_t median_filter (uint16_t *p, size_t n);
void add_number(uint16_t *filter, uint16_t number);
int8_t ntc_get_temp(uint16_t adc_value);
#endif //PROJECT_EWW_CORE_INC_TERMO_SENSOR_H_
