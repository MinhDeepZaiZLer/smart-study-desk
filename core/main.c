#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "data_types.h"

// Hàm giả lập đọc cảm biến Nhiệt độ bằng cách ghi trực tiếp vào vùng nhớ qua con trỏ
void Mock_Read_Temperature(float *p_temp)
{
    if (p_temp == NULL)
        return;

    *p_temp = 24.0f + ((float)rand() / (float)RAND_MAX) * 6.0f;
}

// Hàm giả lập đọc cảm biến Độ ẩm
void Mock_Read_Humidity(float *p_humidity)
{
    if (p_humidity == NULL)
        return;

    *p_humidity = 50.0f + ((float)rand() / (float)RAND_MAX) * 30.0f;
}

// Hàm giả lập đọc cảm biến Ánh sáng (Trả về giá trị Lux từ 0 - 1000)
void Mock_Read_Light(uint16_t *p_light)
{
    if (p_light == NULL)
        return;

    *p_light = 200 + (rand() % 601); // 200 đến 800 Lux
}
void Update_Desk_Sensors(StudyDesk_t *desk)
{
    if (desk == NULL)
        return;

    Mock_Read_Temperature(&(desk->env.temperature));
    Mock_Read_Humidity(&(desk->env.humidity));
    Mock_Read_Light(&(desk->env.light_level));
}

void Calculate_focus_score(StudyDesk_t *desk)
{
    if (desk == NULL)
        return;

    if (desk->pomo_state != POMO_STATE_FOCUS)
    {
        desk->focus_store = 0;
        return;
    }

    int16_t temp_score = 80;

    if (desk->env.temperature < 18.0f || desk->env.temperature > 28.0f)
    {
        temp_score -= 30;
    }
    else if ((desk->env.temperature >= 18.0f && desk->env.temperature <= 22.0f) ||
             (desk->env.temperature >= 26.0f && desk->env.temperature <= 28.0f))
    {
        temp_score -= 15;
    }

    if (desk->env.light_level < 300)
    {
        temp_score -= 25;
    }

    uint32_t total_focus_time = 10;
    uint32_t elapsed_time = total_focus_time - desk->time_left_sec;
    int16_t time_bonus = (elapsed_time * 20) / total_focus_time;

    temp_score += time_bonus;

    if (temp_score > 100)
        temp_score = 100;
    if (temp_score < 0)
        temp_score = 0;

    desk->focus_store = (uint8_t)temp_score;
}

// Hàm cập nhận State dựa trên Pomodoro Clock
void Pomodoro_FSM_Update(StudyDesk_t *desk)
{
    if (desk == NULL)
        return;

    switch (desk->pomo_state)
    {
    case POMO_STATE_IDLE:
    {
        {
            if (desk->env.light_level > 300)
            {
                printf("[EVENT] Light detected! Automatically starting FOCUS session.\n");
                desk->pomo_state = POMO_STATE_FOCUS;
                desk->time_left_sec = 10;
            }
        }
        break;
    }
    case POMO_STATE_FOCUS:
    {
        {
            if (desk->time_left_sec > 0)
            {
                desk->time_left_sec--;
                printf("[FOCUSING] Time left: %d s\n", desk->time_left_sec);
            }
            else
            {
                printf("[EVENT] Focus session finished! Changing to BREAK.\n");
                desk->pomo_state = POMO_STATE_BREAK;
                desk->time_left_sec = 5;
            }
        }
        break;
    }
    case POMO_STATE_BREAK:
    {
        {
            if (desk->time_left_sec > 0)
            {
                desk->time_left_sec--;
                printf("[BREAKING] Time left: %d s\n", desk->time_left_sec);
            }
            else
            {
                printf("[BREAKING] Time left: %d s\n", desk->time_left_sec);
                desk->pomo_state = POMO_STATE_IDLE;
            }
        }
        break;
    }
    default:
        desk->pomo_state = POMO_STATE_IDLE;
        break;
    }
}
int main()
{
    // Khởi tạo bộ sinh số ngẫu nhiên dựa trên thời gian thực
    srand(time(NULL));
    StudyDesk_t myDesk;

    myDesk.time_left_sec = 0;
    myDesk.pomo_state = POMO_STATE_IDLE;

    myDesk.env.temperature = 0.0f;
    myDesk.env.humidity = 0.0f;
    myDesk.env.light_level = 0;

    printf("===========================================\n");
    printf("   SMART STUDY DESK - INITIALIZATION       \n");
    printf("===========================================\n\n");

    // Giả lập việc lấy dữ liệu theo chu kỳ
    for (int i = 1; i <= 20; i++)
    {
        printf("[Sample %d] Reading sensors...\n", i);

        Update_Desk_Sensors(&myDesk);

        Pomodoro_FSM_Update(&myDesk);
        Calculate_focus_score(&myDesk);

        printf(" -> Temperature: %.2f *C\n", myDesk.env.temperature);
        printf(" -> Humidity   : %.2f %%\n", myDesk.env.humidity);
        printf(" -> Light Level: %u Lux\n", myDesk.env.light_level);
        printf(" -> Focus Score: %u/100 \n", myDesk.focus_store);
        printf("-------------------------------------------\n");
    }

    printf("Day 3 completed successfully!\n");
    return 0;
}