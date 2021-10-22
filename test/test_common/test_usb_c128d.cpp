#include <unity.h>
#include "usb_c128d.hpp"


void test_no_keys_pressed() {
    USB_C128D usb_c128d;
    PinsState* state = usb_c128d.get_output_pins(false, false);
    PinsState expected = {
        false, false, false, false, false, false, false, false,
        false, false, false,
        false, false, false, false, false, false, false, false,
        false, false, false,
        false 
    };
    
    TEST_ASSERT_EQUAL_MEMORY(&expected, state, sizeof(PinsState));
}


void test_single_key_press() {
    USB_C128D usb_c128d;

    usb_c128d.usb_key_down(USB_KEY_A);
    PinsState* state = usb_c128d.get_output_pins(false, false);
    PinsState expected = {
        false, true, false, false, false, false, false, false,
        false, false, false,
        false, false, true, false, false, false, false, false,
        false, false, false,
        false 
    };
    
    TEST_ASSERT_EQUAL_MEMORY(&expected, state, sizeof(PinsState));
}


void test_multiple_key_press() {}
void test_usb_capslock_on() {}
void test_usb_numlock_on() {}
void test_4080_lock_key() {}
void test_cursor_keys() {}



void run_usb_c128d_tests() {
    UNITY_BEGIN();
    RUN_TEST(test_no_keys_pressed);
    RUN_TEST(test_single_key_press);
    UNITY_END();
}