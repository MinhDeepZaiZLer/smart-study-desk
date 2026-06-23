#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>

typedef struct {
    float temperature;    // Nhiệt độ
    float humidity;       // Độ ẩm
    uint16_t light_level; // Mức độ ánh sáng
} Environment_t;

typedef struct {
    Environment_t env;    // Thông tin môi trường
} StudyDesk_t;

#endif // DATA_TYPES_H