#include "pico/stdlib.h"
#define LED_MASK 1 << PICO_DEFAULT_LED_PIN
//What is closest increment period such that 2^16 ticks corresponds to roughly 3s?
// ANSWER1 --> ~46us (slightly over  by ~14.7 ms)
// ANSWER2 --> ~45us (slightly under by ~50.9 ms)
#define DELAY -46

uint16_t global_counter = 0;

bool repeating_timer_callback(struct repeating_timer *t) {
    global_counter++;
    if (global_counter == 0xFFFF)
      gpio_xor_mask(LED_MASK);
    //TODO if counter == 3ms, tell 2nd core to flicker 2nd LED pin
    return true;
}


int main() {
  // From timer example
  stdio_init_all();
  // Initialize GPIO
  gpio_init_mask(LED_MASK);
  // Set GPIO direction
  gpio_set_dir_out_masked(LED_MASK);
  // Give GPIO an initial state
  gpio_put(PICO_DEFAULT_LED_PIN, 0);

  // Create a repeating timer that calls repeating_timer_callback.
  struct repeating_timer timer;
  // Negative delay so we will call repeating_timer_callback, and call it again
  // 500ms later regardless of how long the callback took to execute
  add_repeating_timer_us(DELAY, repeating_timer_callback, NULL, &timer);

  while (true) {
    tight_loop_contents(); // From library, effectively looping on No-Ops
  }
}
