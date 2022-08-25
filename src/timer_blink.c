#include "pico/stdlib.h"
#include "pico/multicore.h"
#define FLAG_VALUE 123 // magic number for multicore

#define LOGIC_ANALYZER_TRIGGER_PIN 0
#define CHALLENGE_LED_PIN 1

#define LED_MASK  ((1 << PICO_DEFAULT_LED_PIN) | (1 << LOGIC_ANALYZER_TRIGGER_PIN))
#define LED_MASK2   1 << CHALLENGE_LED_PIN

//What is closest increment period such that 2^16 ticks corresponds to roughly 3s?
// ANSWER1 --> ~46us (slightly over  by ~14.7 ms)
// ANSWER2 --> ~45us (slightly under by ~50.9 ms)
#define DELAY -46

// Global counter, will be incremented every 46us
volatile uint16_t global_counter = 0;

// Routine to cause 2nd LED to blink 5x
void rapid_blink(){
      // 3s before next flicker request
      // Arbitrarily choosing some number until delay seems fine
      // and total blink duration is noticeably less than 3s
      for(uint8_t i = 0; i < 9; ++i){
        gpio_xor_mask(LED_MASK2);
        sleep_ms(150);
      }
      gpio_xor_mask(LED_MASK2);
      // 10th toggle doesn't require us to waste cycles sleeping
      return;
}

// Start point for 2nd core. Awaits function pointer on FIFO
// Uses function pointer (expected every 3s) to cause 2nd LED
// to blink 5x
void core1_entry(){
  while (1) {
    // Wait for arrival of function pointer on FIFO
    // cast the received value into a 32bit function pointer
    void (*func)() = (void(*)()) multicore_fifo_pop_blocking();

    (*func)(); // Dereference the function pointer to call on function
  }
}

// Callback function for interrupt caused by hardware timer
// Toggles one LED every time counter is about to overflow
// Signals 2nd core to flicker other LED every 3s
// Increment period for counter was selected such that this
// occurs at the same time :)
bool repeating_timer_callback(struct repeating_timer *t) {
    global_counter++;
    if (global_counter == 0xFFFF) {// Approx 3s
      gpio_xor_mask(LED_MASK);
      // When counter == 3ms, tell 2nd core to flicker 2nd LED pin
      // by sending address of rapid_blink function
      multicore_fifo_push_blocking((uintptr_t) &rapid_blink);
    }
    return true;
}


int main() {
  // Needed to initialize hardware timer
  stdio_init_all();

  // Initialize GPIO
  gpio_init_mask(LED_MASK | LED_MASK2); 

  // Set GPIO direction
  gpio_set_dir_out_masked(LED_MASK | LED_MASK2);

  // Give GPIO an initial state of cleared
  gpio_clr_mask(LED_MASK | LED_MASK2);

  // Second core will await arbitrary function pointers to execute
  multicore_launch_core1(core1_entry);

  // Create a repeating timer that calls repeating_timer_callback.
  struct repeating_timer timer;

  // Negative delay so we will call repeating_timer_callback, and call it again
  // 500ms later regardless of how long the callback took to execute
  add_repeating_timer_us(DELAY, repeating_timer_callback, NULL, &timer);

  // Infinite loop
  while (true) {
    tight_loop_contents(); // From library, effectively looping on No-Ops
  }
}
