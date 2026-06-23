#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "data_types.h"

// Hàm giả lập đọc cảm biến Nhiệt độ bằng cách ghi trực tiếp vào vùng nhớ qua con trỏ
void Mock_Read_Temperature(float *p_temp) {
    if (p_temp == NULL) return;
  
    *p_temp = 24.0f + ((float)rand() / (float)RAND_MAX) * 6.0f;
}

// Hàm giả lập đọc cảm biến Độ ẩm
void Mock_Read_Humidity(float *p_humidity) {
    if (p_humidity == NULL) return;
  
    *p_humidity = 50.0f + ((float)rand() / (float)RAND_MAX) * 30.0f;
}

// Hàm giả lập đọc cảm biến Ánh sáng (Trả về giá trị Lux từ 0 - 1000)
void Mock_Read_Light(uint16_t *p_light) {
    if (p_light == NULL) return;
    
    *p_light = 200 + (rand() % 601); // 200 đến 800 Lux
}
void Update_Desk_Sensors(StudyDesk_t *desk) {
    if (desk == NULL) return; 

    Mock_Read_Temperature(&(desk->env.temperature));
    Mock_Read_Humidity(&(desk->env.humidity));
    Mock_Read_Light(&(desk->env.light_level));


}
int main() {
    // Khởi tạo bộ sinh số ngẫu nhiên dựa trên thời gian thực
    srand(time(NULL));
    StudyDesk_t myDesk;
   

    myDesk.env.temperature = 0.0f;
    myDesk.env.humidity = 0.0f;
    myDesk.env.light_level = 0;

    printf("===========================================\n");
    printf("   SMART STUDY DESK - INITIALIZATION       \n");
    printf("===========================================\n\n");

    // Giả lập việc lấy dữ liệu theo chu kỳ (ví dụ 3 lần)
    for (int i = 1; i <= 3; i++) {
        printf("[Sample %d] Reading sensors...\n", i);

      
        Update_Desk_Sensors(&myDesk);

       
        printf(" -> Temperature: %.2f *C\n", myDesk.env.temperature);
        printf(" -> Humidity   : %.2f %%\n", myDesk.env.humidity);
        printf(" -> Light Level: %u Lux\n", myDesk.env.light_level);
        printf("-------------------------------------------\n");
    }

    printf("Day 1 completed successfully!\n");
    return 0;
}