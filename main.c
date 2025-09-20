#include <msp430.h> 
#include "src/flash_operations.h"
#include "src/SRAM_subroutine_copy.h"
#include "src/Serial.h"
#include <stdint.h>
#include <stdlib.h>

#define INFO_FLASH_SEG_B_START 0x001880


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer

  uint16_t* info_B_start = (void*)INFO_FLASH_SEG_B_START;

  flash_segment_erase(info_B_start);

  char* space = (char*) malloc((void*)end_flash_word_partial_write_10 \
      - (void*)flash_word_partial_write_10 + 8); // 8 bytes padding

  if (space == NULL)
    return 1; // not enough room for function in the heap

  copy_subroutine((char*)flash_word_partial_write_10, \
      (char*)end_flash_word_partial_write_10, space);

  void (*SRAM_function)(uint16_t, uint16_t*);
    // declare function pointer
  SRAM_function = (void*)space;

  SRAM_function(0xCCCC, info_B_start); // data doesnt really matter

  free(space); // deallocate memory

  while(1);
	
  return 0;
}
