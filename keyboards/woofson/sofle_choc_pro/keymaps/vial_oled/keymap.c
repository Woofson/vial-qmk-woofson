#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "bitmaps.h"
#endif

enum layers {
    _BASE  = 0,
    _LOWER = 1,
    _RAISE = 2
};

// --- CUSTOM PER-LAYER LED LOGIC ---
// Updated to 'bool' to fix "conflicting types" error
bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case _BASE:
            // Base: White background
            rgb_matrix_set_color_all(255, 255, 255);
            // Red Keys: Esc, 1, 2, 3, 4, Tab, Q, W, E, Caps, A, S, LShift, Z
            int r_b[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 12, 13, 14, 18, 19};
            for (int i = 0; i < 14; i++) rgb_matrix_set_color(r_b[i], 255, 0, 0);
            // Orange Keys: 5, R, D, X, TL_LOWR
            int o_b[] = {5, 10, 15, 20, 24};
            for (int i = 0; i < 5; i++) rgb_matrix_set_color(o_b[i], 255, 165, 0);
            // Yellow Keys: T, F, C, LGUI
            int y_b[] = {11, 16, 21, 25};
            for (int i = 0; i < 4; i++) rgb_matrix_set_color(y_b[i], 255, 255, 0);
            break;

        case _LOWER:
            // Lower: Dim White background for "Darker" feel
            rgb_matrix_set_color_all(60, 60, 60);
            // Deep/Dark Red
            int r_l[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 12, 13, 14, 18, 19};
            for (int i = 0; i < 14; i++) rgb_matrix_set_color(r_l[i], 130, 0, 0);
            // Dark Orange/Brown-ish
            int o_l[] = {5, 10, 15, 20, 24};
            for (int i = 0; i < 5; i++) rgb_matrix_set_color(o_l[i], 150, 70, 0);
            // Dark Gold
            int y_l[] = {11, 16, 21, 25};
            for (int i = 0; i < 4; i++) rgb_matrix_set_color(y_l[i], 120, 120, 0);
            break;

        case _RAISE:
            // Raise: Synthwave theme (Hot Pink/Cyan on Purple)
            rgb_matrix_set_color_all(80, 0, 150); // Deep Purple Base
            // Hot Pink
            int p_r[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 12, 13, 14, 18, 19};
            for (int i = 0; i < 14; i++) rgb_matrix_set_color(p_r[i], 255, 20, 147);
            // Electric Blue/Cyan
            int b_r[] = {5, 10, 15, 20, 24};
            for (int i = 0; i < 5; i++) rgb_matrix_set_color(b_r[i], 0, 255, 255);
            // Bright White/Neon
            int w_r[] = {11, 16, 21, 25};
            for (int i = 0; i < 4; i++) rgb_matrix_set_color(w_r[i], 255, 255, 255);
            break;

        default:
            rgb_matrix_set_color_all(255, 255, 255);
            break;
    }
    return false; // Return false to indicate we have overridden the indicators
}

// --- KEYMAP DATA ---
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_split_4x6_5(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_MPLY,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 KC_LGUI,KC_LALT,KC_LCTL, TL_LOWR, KC_ENT,      KC_SPC,  TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
),

[_LOWER] = LAYOUT_split_4x6_5(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_split_4x6_5(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, XXXXXXX,   KC_UP, XXXXXXX,C(KC_BSPC), KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,  _______,       _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_LOWER] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_RAISE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif

#ifdef OLED_ENABLE
#include "transactions.h"
static const uint8_t OLED_WIDTH = OLED_DISPLAY_HEIGHT;
static const uint16_t SPLASH_DURATION_MS = 2500;

static const char PROGMEM QMK_LOGO_1[] = { 0x81, 0x82, 0x83, 0x84, 0x00 };
static const char PROGMEM QMK_LOGO_2[] = { 0xA1, 0xA2, 0xA3, 0xA4, 0x00 };
static const char PROGMEM QMK_LOGO_3[] = { 0xC1, 0xC2, 0xC3, 0xC4, 0x00 };

typedef struct { bool oled_on; } oled_state_m2s_t;
typedef struct { uint16_t keycode; } lastkey_m2s_t;
typedef struct { uint32_t left; uint32_t right; } presses_m2s_t;

static bool g_oled_init_done = false;
static uint8_t g_oled_max_char;
static uint8_t g_oled_max_line;
static bool g_splash_active = true;
static bool g_splash_rendered = false;
static uint32_t g_splash_start_ms = 0;
static uint32_t g_user_ontime = 0;
static uint16_t g_last_keycode = KC_NO;
static uint32_t g_press_left = 0;
static uint32_t g_press_right = 0;
static oled_state_m2s_t g_remote_oled_state = { true };
static presses_m2s_t g_remote_presses = {0, 0};

static inline pin_t get_charge_pump_enable_pin(void) { return GP20; }

void oled_blit_16x16_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 16; i++) {
        char top = pgm_read_byte(&icon[i]);
        char bot = pgm_read_byte(&icon[16 + i]);
        oled_write_raw_byte(top, page * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 1) * OLED_WIDTH + x + i);
    }
}

void oled_blit_24x24_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 24; i++) {
        char top = pgm_read_byte(&icon[i]);
        char mid = pgm_read_byte(&icon[24 + i]);
        char bot = pgm_read_byte(&icon[48 + i]);
        oled_write_raw_byte(top, page * OLED_WIDTH + x + i);
        oled_write_raw_byte(mid, (page + 1) * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 2) * OLED_WIDTH + x + i);
    }
}

uint16_t unwrap_keycode(uint16_t kc) {
    if (kc >= QK_MOD_TAP && kc <= QK_MOD_TAP_MAX) return QK_MOD_TAP_GET_TAP_KEYCODE(kc);
    if (kc >= QK_LAYER_TAP && kc <= QK_LAYER_TAP_MAX) return QK_LAYER_TAP_GET_TAP_KEYCODE(kc);
    return kc;
}

uint16_t get_current_dwpm(void) { return (uint16_t)get_current_wpm() * 10u; }

uint8_t round_percentage(float x) {
    float f = x + 0.5f;
    uint8_t r = (uint8_t)f;
    if ((f - (float)r) == 0.0f && (r & 1)) r--;
    return r;
}

void oled_print_right_aligned(const char *text, const uint8_t width) {
    uint8_t len = strlen(text);
    uint8_t pad = (len < width) ? (width - len) : 0;
    for (uint8_t i = 0; i < pad; i++) oled_write_P(PSTR(" "), false);
    oled_write(text, false);
}

void print_current_layer(uint8_t row) {
    char layer_str[8];
    switch (get_highest_layer(layer_state)) {
        case _BASE: strcpy(layer_str, "Base"); break;
        case _LOWER: strcpy(layer_str, "Lower"); break;
        case _RAISE: strcpy(layer_str, "Raise"); break;
        default: snprintf(layer_str, sizeof(layer_str), "%d", get_highest_layer(layer_state));
    }
    oled_set_cursor(0, row);
    oled_print_right_aligned(layer_str, g_oled_max_char);
}

void print_uptime(uint8_t row) {
    uint32_t total_min = timer_read32() / 60000u;
    uint32_t hours = total_min / 60u;
    uint32_t minutes = total_min % 60u;
    char buf[8];
    snprintf(buf, sizeof(buf), "%3luh%02lum", (hours > 999u ? 999u : hours), minutes);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void print_wpm(uint8_t row) {
    uint16_t wpm = get_current_dwpm();
    char buf[11];
    snprintf(buf, sizeof(buf), "%3u.%1u WPM", wpm / 10u, wpm % 10u);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void print_balance(uint8_t row, uint8_t pct) {
    char buf[6];
    snprintf(buf, sizeof(buf), "%3u %%", pct);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void render_splash(void) {
    if (g_splash_rendered) return;
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_raw_P(STARTUP_BITMAP, sizeof(STARTUP_BITMAP));
    g_splash_rendered = true;
}

static void user_sync_oled_state_slave(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(oled_state_m2s_t)) memcpy(&g_remote_oled_state, in_data, sizeof(oled_state_m2s_t));
}

static void user_sync_lastkey_slave(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(lastkey_m2s_t)) g_last_keycode = ((const lastkey_m2s_t*)in_data)->keycode;
}

static void user_sync_presses_slave(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len >= sizeof(presses_m2s_t)) memcpy(&g_remote_presses, in_data, sizeof(presses_m2s_t));
}

void keyboard_post_init_user(void) {
    pin_t dsp_pen_pin = get_charge_pump_enable_pin();
    gpio_set_pin_output(dsp_pen_pin);
    gpio_write_pin_low(dsp_pen_pin);
    wait_ms(5);
    transaction_register_rpc(USER_SYNC_OLED_STATE, user_sync_oled_state_slave);
    transaction_register_rpc(USER_SYNC_LASTKEY, user_sync_lastkey_slave);
    transaction_register_rpc(USER_SYNC_PRESSES, user_sync_presses_slave);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 50) {
            oled_state_m2s_t oled_state_pkt = { is_oled_on() };
            (void)transaction_rpc_send(USER_SYNC_OLED_STATE, sizeof(oled_state_pkt), &oled_state_pkt);
            last_sync = timer_read32();
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    g_user_ontime = timer_read32();
    if (record->event.pressed) {
        g_last_keycode = keycode;
        if (record->event.key.row < MATRIX_ROWS / 2) g_press_left++; else g_press_right++;
        if (is_keyboard_master()) {
            lastkey_m2s_t keycode_pkt = { g_last_keycode };
            transaction_rpc_send(USER_SYNC_LASTKEY, sizeof(keycode_pkt), &keycode_pkt);
            presses_m2s_t presses_pkt = { g_press_left, g_press_right };
            transaction_rpc_send(USER_SYNC_PRESSES, sizeof(presses_pkt), &presses_pkt);
        }
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_post_init(void) {
    if (!g_oled_init_done) {
        g_oled_max_char = oled_max_chars();
        g_oled_max_line = oled_max_lines();
        gpio_write_pin_high(get_charge_pump_enable_pin());
        wait_ms(20);
        oled_clear();
        g_splash_start_ms = timer_read32();
        g_splash_active = true;
        g_oled_init_done = true;
    }
    return false;
}

bool oled_task_user(void) {
    oled_post_init();
    if (g_splash_active) {
        if (timer_elapsed32(g_splash_start_ms) > SPLASH_DURATION_MS) {
            g_splash_active = false; oled_clear(); g_user_ontime = timer_read32();
        } else render_splash();
        return false;
    }

    uint32_t lp_l = is_keyboard_master() ? g_press_left : g_remote_presses.left;
    uint32_t lp_r = is_keyboard_master() ? g_press_right : g_remote_presses.right;

    if (is_keyboard_master()) {
        const uint32_t idle = timer_elapsed32(g_user_ontime);
        if (idle > OLED_TIMEOUT_USER) { oled_off(); return false; } else oled_on();
    } else {
        if (g_remote_oled_state.oled_on) oled_on(); else { oled_off(); return false; }
    }

    uint32_t total = (lp_l + lp_r == 0) ? 1 : (lp_l + lp_r);
    uint8_t pct_l = round_percentage((100.0f * lp_l) / total);
    uint8_t pct_r = round_percentage((100.0f * lp_r) / total);

    if (is_keyboard_left()) {
        oled_set_cursor(0, 0); oled_write_P(PSTR("Layer:"), false); print_current_layer(1);
        led_t ls = host_keyboard_led_state();
        oled_blit_16x16_P(ls.num_lock ? NUM_LOCK_BITMAP : EMPTY_BITMAP, 0, 3);
        oled_blit_16x16_P(ls.caps_lock ? CAPS_LOCK_BITMAP : EMPTY_BITMAP, 24, 3);
        oled_blit_16x16_P(ls.scroll_lock ? SCROLL_LOCK_BITMAP : EMPTY_BITMAP, 48, 3);
        oled_set_cursor(0, 7); oled_write_P(PSTR("Left:"), false); print_balance(8, pct_l);
        oled_set_cursor(0, 10); oled_write_P(PSTR("Last Key:"), false); oled_set_cursor(0, 11);
        oled_print_right_aligned(get_keycode_string(unwrap_keycode(g_last_keycode)), g_oled_max_char);
        oled_set_cursor(0, 13); oled_write_P(QMK_LOGO_1, false);
        oled_set_cursor(0, 14); oled_write_P(QMK_LOGO_2, false);
        oled_set_cursor(0, 15); oled_write_P(QMK_LOGO_3, false);
        oled_set_cursor(7, 15); oled_write_P(PSTR("QMK"), false);
    } else {
        oled_set_cursor(0, 0); oled_write_P(PSTR("Uptime:"), false); print_uptime(1);
        oled_set_cursor(0, 3); oled_write_P(PSTR("Avg Speed"), false);
        oled_set_cursor(0, 4); oled_write_P(PSTR("(25 s):"), false); print_wpm(5);
        oled_set_cursor(0, 7); oled_write_P(PSTR("Right:"), false); print_balance(8, pct_r);
        oled_blit_24x24_P(KEEBART_BITMAP_24x24, 20, 11);
        oled_set_cursor(2, 15); oled_write_P(PSTR("KEEBART"), false);
    }
    return false;
}
#endif
