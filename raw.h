#include "raw_hid.h"
#include "string.h"

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