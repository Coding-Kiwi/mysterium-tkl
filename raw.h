#include "raw_hid.h"
#include "string.h"

bool is_hid_connected = false; // Flag indicating if we have a PC connection yet
int screen_data_index = 0; // Current index into the screen_data_buffer that we should write to

enum command_id {
    id_get_protocol_version                 = 0x01, // always 0x01
    id_get_keyboard_value                   = 0x02,
    id_set_keyboard_value                   = 0x03
};

enum command_value_id {
    id_oled_mode                   = 0x80,
    id_oled_buffer                 = 0x81,
    id_oled_buffer_data            = 0x82,
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);

    is_hid_connected = true;

    switch (*command_id) {
        case id_get_keyboard_value:
        {
            switch(command_data[0]){
                case id_oled_mode:
                {
                    command_data[1] = oled_mode;
                    break;
                }
            }
            break;
        }
        case id_set_keyboard_value:
        {
            switch(command_data[0]){
                case id_oled_mode:
                    oled_mode = command_data[1];
                    break;

                case id_oled_buffer:
                case id_oled_buffer_data:
                    if(command_data[0] == id_oled_buffer){
                        // New connection so restart screen_data_buffer
                        screen_data_index = 0;
                        oled_mode = OLED_OFF;
                    }

                    //copy 21 bytes from data starting at index 1 to screen_data_buffer
                    for(int i = 0; i < 21; i++){
                        screen_data_buffer[screen_data_index * 21 + i] = data[2 + i];
                    }
                    //memcpy(&screen_data_buffer[screen_data_index * 21], &data[2], 21);

                    screen_data_index++;

                    if (screen_data_index == 4) {
                        oled_mode = OLED_TEST;
                        oled_request_wakeup();
                    }
                    break;
            }
            break;
        }
    }

    raw_hid_send(data, length);
}