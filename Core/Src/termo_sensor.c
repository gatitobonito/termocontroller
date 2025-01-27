/**
  ******************************************************************************
  * @file           : termo_sensor.c
  * @brief          : module for ntc-10k-b3950
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "termo_sensor.h"



#define SERIESRESISTOR 10000 // 10K ohm resistor in series
#define BCOEFFICIENT 3950 // Beta coefficient for the thermistor
#define NOMINALRESISTANCE 10000 // Resistance at 25 degrees Celsius
#define NOMINALTEMPERATURE 25 // Nominal temperature in Celsius

filter_ntc_t ntc1_raw_adc;
filter_ntc_t ntc2_raw_adc;

void add_number(filter_ntc_t ntc_raw, uint16_t number)
{
  if (ntc_raw.cnt< FILTER_SIZE) {
    ntc_raw.ntc_raw_adc[ntc_raw.cnt++] = number;
  } else {
    // Shift values to remove the oldest one
    for (int i = 1; i < FILTER_SIZE; i++) {
      ntc_raw.ntc_raw_adc[i - 1] = ntc_raw.ntc_raw_adc[i];
    }
    ntc_raw.ntc_raw_adc[FILTER_SIZE - 1] = number; // Add new number
  }
}

uint16_t median_filter (uint16_t *p, size_t n)
{
  uint16_t temp = 0;
  if (n < 2) {
    return 0;
  }
  //bubble sort for mass
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 1; j < (n-i); j++)
    {
      if (p[j-1] > p[j])
      {
        temp = p[j-1];
        p[j-1] = p[j];
        p[j] = temp;
      }
    }
  }

  size_t i = n/2;
  if (n & 1)  {
    return (p[i]);
  }
  else {
    return (uint16_t)((uint32_t)p[i-1] + (uint32_t)p[i]) / 2U;
  }
}

int8_t ntc_get_temp(uint16_t adc_value)
{
  // Convert the ADC value to resistance
  float resistance = SERIESRESISTOR / ((1023.0 / adc_value) - 1);

  // Calculate temperature in Kelvin
  float temperatureK = 1.0 / (1.0 / (NOMINALTEMPERATURE + 273.15) + (1.0 / BCOEFFICIENT) * logf(resistance / NOMINALRESISTANCE));

  // Convert temperature to Celsius
  float temperatureC = temperatureK - 273.15;
  return (int8_t)temperatureC;
}

