#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>

typedef enum 
{
    POMO_STATE_IDLE,
    POMO_STATE_FOCUS,
    POMO_STATE_BREAK
} PomoState_t;


typedef struct {
    float temperature;    // Nhiệt độ
    float humidity;       // Độ ẩm
    uint16_t light_level; // Mức độ ánh sáng
} Environment_t;

typedef struct {
    Environment_t env;    // Thông tin môi trường
    PomoState_t pomo_state;
    uint32_t time_left_sec;
    uint8_t focus_store;
} StudyDesk_t;

#endif // DATA_TYPES_H