#include QMK_KEYBOARD_H

enum custom_keycodes {
    WEB_OPENAI = SAFE_RANGE,
    WEB_YOUTUBE,
    WEB_INSTAGRAM,
    WEB_GOOGLE,
    WEB_GITHUB,
    WEB_GMAIL
};

static void open_url(const char *url) {
    // Windows/Linux browsers: Ctrl+L focuses the address bar.
    tap_code16(KC_LCTL(KC_L));
    wait_ms(80);
    send_string(url);
    tap_code(KC_ENT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case WEB_OPENAI:
            open_url("https://openai.com/");
            return false;
        case WEB_YOUTUBE:
            open_url("https://www.youtube.com/");
            return false;
        case WEB_INSTAGRAM:
            open_url("https://www.instagram.com/");
            return false;
        case WEB_GOOGLE:
            open_url("https://www.google.com/");
            return false;
        case WEB_GITHUB:
            open_url("https://github.com/");
            return false;
        case WEB_GMAIL:
            open_url("https://mail.google.com/");
            return false;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_2x3(
        WEB_OPENAI,  WEB_YOUTUBE,   WEB_INSTAGRAM,
        WEB_GOOGLE,  WEB_GITHUB,    WEB_GMAIL
    )
};

#ifdef OLED_ENABLE

static void oled_render_uptime(void) {
    uint32_t seconds = timer_read32() / 1000;
    uint32_t hours = seconds / 3600;
    uint8_t minutes = (seconds / 60) % 60;
    uint8_t secs = seconds % 60;

    char buf[16];

    oled_write_P(PSTR("WEB MACRO PAD\n"), false);
    oled_write_P(PSTR("UP "), false);

    // HH:MM:SS, wrapping hours at 99 for a compact display.
    hours %= 100;
    buf[0] = '0' + (hours / 10);
    buf[1] = '0' + (hours % 10);
    buf[2] = ':';
    buf[3] = '0' + (minutes / 10);
    buf[4] = '0' + (minutes % 10);
    buf[5] = ':';
    buf[6] = '0' + (secs / 10);
    buf[7] = '0' + (secs % 10);
    buf[8] = '\0';

    oled_write(buf, false);
    oled_write_P(PSTR("\n2x3 RP2040"), false);
}

bool oled_task_user(void) {
    oled_clear();
    oled_render_uptime();
    return false;
}

#endif
