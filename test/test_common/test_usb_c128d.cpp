#include <unity.h>
#include "usb_c128d.hpp"

PinsState right_shift = {
    false, false, false, false, true, false, false, false,
    false, false, false,
    false, false, false, false, false, false, true, false,
    false, false, false,
    false 
};

PinsState no_pins = {
    false, false, false, false, false, false, false, false,
    false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false,
    false 
};

PinsState a_pins = {
    false, true, false, false, false, false, false, false,
    false, false, false,
    false, false, true, false, false, false, false, false,
    false, false, false,
    false 
};

PinsState b_pins = {
    false, false, false, false, true, false, false, false,
    false, false, false,
    false, false, false, true, false, false, false, false,
    false, false, false,
    false 
};

void _combine_pins(PinsState& a, PinsState& b, PinsState& output) {
    output.row0 = a.row0 | b.row0;
    output.row1 = a.row1 | b.row1;
    output.row2 = a.row2 | b.row2;
    output.row3 = a.row3 | b.row3;
    output.row4 = a.row4 | b.row4;
    output.row5 = a.row5 | b.row5;
    output.row6 = a.row6 | b.row6;
    output.row7 = a.row7 | b.row7;

    output.restore      = a.restore | b.restore;
    output.forty_eighty = a.forty_eighty | b.forty_eighty;
    output.caps_lock    = a.caps_lock | b.caps_lock;

    output.col0 = a.col0 | b.col0;
    output.col1 = a.col1 | b.col1;
    output.col2 = a.col2 | b.col2;
    output.col3 = a.col3 | b.col3;
    output.col4 = a.col4 | b.col4;
    output.col5 = a.col5 | b.col5;
    output.col6 = a.col6 | b.col6;
    output.col7 = a.col7 | b.col7;

    output.k0 = a.k0 | b.k0;
    output.k1 = a.k1 | b.k1;
    output.k2 = a.k2 | b.k2;

    output.restore0 = a.restore0 | b.restore0;
}


void test_no_keys_pressed() {
    USB_C128D usb_c128d;
    PinsState* state = usb_c128d.get_output_pins(false, false);
    TEST_ASSERT_EQUAL_MEMORY(&no_pins, state, sizeof(PinsState));
}


void test_single_key_press() {
    USB_C128D usb_c128d;

    usb_c128d.usb_key_down(USB_KEY_A);
    PinsState* state = usb_c128d.get_output_pins(false, false);
    TEST_ASSERT_EQUAL_MEMORY(&a_pins, state, sizeof(PinsState));
}


void test_key_down_and_key_up() {
    USB_C128D usb_c128d;

    usb_c128d.usb_key_down(USB_KEY_A);
    PinsState* state = usb_c128d.get_output_pins(false, false);
    TEST_ASSERT_EQUAL_MEMORY(&a_pins, state, sizeof(PinsState));

    usb_c128d.usb_key_up(USB_KEY_A);
    state = usb_c128d.get_output_pins(false, false);
    TEST_ASSERT_EQUAL_MEMORY(&no_pins, state, sizeof(PinsState));
}


void test_multiple_keys_pressed() {
    USB_C128D usb_c128d;

    usb_c128d.usb_key_down(USB_KEY_A);
    usb_c128d.usb_key_down(USB_KEY_B);
    PinsState* state = usb_c128d.get_output_pins(false, false);

    PinsState expected_a_and_b;
    _combine_pins(a_pins, b_pins, expected_a_and_b);

    TEST_ASSERT_EQUAL_MEMORY(&expected_a_and_b, state, sizeof(PinsState));
}


void test_usb_capslock_on() {
    USB_C128D usb_c128d;

    PinsState* state = usb_c128d.get_output_pins(true, false);
    PinsState expected_left_shift = {
        false, false, false, false, false, false, false, true,
        false, false, false,
        false, true, false, false, false, false, false, false,
        false, false, false,
        false 
    };

    TEST_ASSERT_EQUAL_MEMORY(&expected_left_shift, state, sizeof(PinsState));
}

void test_usb_numlock() {
    USB_C128D usb_c128d;

    usb_c128d.usb_key_down(USB_KEY_KP_4);
    PinsState* state = usb_c128d.get_output_pins(false, true);
    PinsState expected_kp_4 = {
        false, false, false, false, false, true, false, false,
        false, false, false,
        false, false, false, false, false, false, false, false,
        true, false, false,
        false 
    };

    TEST_ASSERT_EQUAL_MEMORY(&expected_kp_4, state, sizeof(PinsState));

    state = usb_c128d.get_output_pins(false, false);
    PinsState expected_top_cursor_left = {
        false, false, false, false, false, true, false, false,
        false, false, false,
        false, false, false, false, false, false, false, false,
        false, false, true,
        false 
    };

    TEST_ASSERT_EQUAL_MEMORY(&expected_top_cursor_left, state, sizeof(PinsState));
}

void test_4080_lock_key() {}
void test_cursor_keys() {}


void run_usb_c128d_tests() {
    UNITY_BEGIN();
    RUN_TEST(test_no_keys_pressed);
    RUN_TEST(test_single_key_press);
    RUN_TEST(test_key_down_and_key_up);
    RUN_TEST(test_usb_capslock_on);
    RUN_TEST(test_usb_numlock);
    UNITY_END();
}