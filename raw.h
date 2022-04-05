#include "raw_hid.h"


bool is_hid_connected = false; // Flag indicating if we have a PC connection yet

enum command_id {
    id_get_protocol_version                 = 0x01, // always 0x01
    id_get_keyboard_value                   = 0x02,
    id_set_keyboard_value                   = 0x03
};

enum command_value_id {
    id_oled_mode                   = 0x80,
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
                {
                    oled_mode = command_data[1];
                    break;
                }
            }
            break;
        }
    }

    raw_hid_send(data, length);
}