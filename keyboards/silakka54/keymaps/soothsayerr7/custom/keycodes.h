#pragma once

void tap_sequence(uint16_t keycode1, uint16_t keycode2, bool shifted) {
    const uint8_t saved_mods         = get_mods();
    const uint8_t saved_weak_mods    = get_weak_mods();
    const uint8_t saved_oneshot_mods = get_oneshot_mods();

    const bool mods_are_active = (saved_mods || saved_weak_mods || saved_oneshot_mods);

    if (mods_are_active) {
        clear_mods();
        clear_weak_mods();
        clear_oneshot_mods();
        send_keyboard_report();
    }

    tap_code16(keycode1);
    tap_code16(shifted ? LSFT(keycode2) : keycode2);

    if (mods_are_active) {
        set_mods(saved_mods);
        set_weak_mods(saved_weak_mods);
        set_oneshot_mods(saved_oneshot_mods);
        send_keyboard_report();
    }
}

enum custom_keycodes {
    RW_QUOT = SAFE_RANGE,
    RW_GRV,
    RW_6,

    A_ACUT,
    A_CIRC,
    A_TILD,
    A_GRAV,
    E_ACUT,
    E_CIRC,
    I_ACUT,
    O_ACUT,
    O_CIRC,
    O_TILD,
    U_ACUT,
    C_CEDL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool shifted = (get_mods() | get_weak_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;

    switch (keycode) {
        case RW_QUOT: if (record->event.pressed) {
            tap_sequence(shifted ? LSFT(KC_QUOT) : KC_QUOT, KC_SPC, false);
            return false;
        }

        case RW_GRV: if (record->event.pressed) {
            tap_sequence(shifted ? LSFT(KC_GRV) : KC_GRV, KC_SPC, false);
            return false;
        }

        case RW_6: if (record->event.pressed) {
            if (shifted) {
                tap_sequence(LSFT(KC_6), KC_SPC, false);
            } else {
                tap_code16(KC_6);
            }
            return false;
        }

        case A_ACUT: if (record->event.pressed) {
            tap_sequence(KC_QUOT, KC_A, shifted);
            return false;
        }
        case E_ACUT: if (record->event.pressed) {
            tap_sequence(KC_QUOT, KC_E, shifted);
            return false;
        }
        case I_ACUT: if (record->event.pressed) {
            tap_sequence(KC_QUOT, KC_I, shifted);
            return false;
        }
        case O_ACUT: if (record->event.pressed) {
            tap_sequence(KC_QUOT, KC_O, shifted);
            return false;
        }
        case U_ACUT: if (record->event.pressed) {
            tap_sequence(KC_QUOT, KC_U, shifted);
            return false;
        }

        case A_CIRC: if (record->event.pressed) {
            tap_sequence(LSFT(KC_6), KC_A, shifted);
            return false;
        }
        case E_CIRC: if (record->event.pressed) {
            tap_sequence(LSFT(KC_6), KC_A, shifted);
            return false;
        }
        case O_CIRC: if (record->event.pressed) {
            tap_sequence(LSFT(KC_6), KC_A, shifted);
            return false;
        }

        case A_TILD: if (record->event.pressed) {
            tap_sequence(LSFT(KC_GRV), KC_A, shifted);
            return false;
        }
        case O_TILD: if (record->event.pressed) {
            tap_sequence(LSFT(KC_GRV), KC_O, shifted);
            return false;
        }

        case A_GRAV: if (record->event.pressed) {
            tap_sequence(KC_GRV, KC_A, shifted);
            return false;
        }

        case C_CEDL: if (record->event.pressed) {
            tap_sequence(KC_QUOT, KC_C, shifted);
            return false;
        }

        default: return true;
    }
}
