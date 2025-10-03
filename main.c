/*-----------------------------------------------------------------------------
* NAME: main.c
* AUTHOR: Jack Pyburn
* PURPOSE: To demonstrate the usage of the partial word write functions and
* investigate the functionanlity of the partial word write with different delay
-----------------------------------------------------------------------------*/
#include <msp430.h> 
#include "src/flash_operations.h"
#include "src/SRAM_subroutine_copy.h"
#include "src/Serial.h"
#include "src/event_timer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define INFO_FLASH_SEG_C_START 0x001880
#define F5529_FLASH_BANK_D    0x1C400     /* FLASH BANK D starts at 0x1_C400 and ends at 0x2_43FF */

void init_and_wait(void);

int main(void)
{
  void (*SRAM_f_pwrite_0)(uint16_t, uint16_t*); // declare function pointer
  void (*SRAM_f_pwrite_4)(uint16_t, uint16_t*);
  void (*SRAM_f_pwrite_6)(uint16_t, uint16_t*);
  void (*SRAM_f_pwrite_8)(uint16_t, uint16_t*);
  void (*SRAM_f_pwrite_10)(uint16_t, uint16_t*);
  char outStr[64];
  f_segment_t bankD0 = F5529_FLASH_BANK_D;

  WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer
  Serial0_setup();
  init_and_wait();

  event_timer_start();
  event_timer_stop();



  SRAM_f_pwrite_10 = malloc_subroutine(f_word_partial_write_10, end_f_word_partial_write_10);
  if (!SRAM_f_pwrite_10)
    return 1;

  f_segment_erase(bankD0);
  SRAM_f_pwrite_10(0x0000, bankD0);
  Serial0_write("| 10 NOP ");
  if(*((uint16_t*)bankD0)) // if value at address is NOT ZERO
    Serial0_write("|    Fail ");
  else
    Serial0_write("| Success ");
  
  sprintf(outStr, "| %04X | %06u us |\n", *((uint16_t*)bankD0), (uint16_t)_event_timer_value);
  Serial0_write(outStr);
  free(SRAM_f_pwrite_10);


  SRAM_f_pwrite_8 = malloc_subroutine(f_word_partial_write_8, end_f_word_partial_write_8);
  if (!SRAM_f_pwrite_8)
    return 1;

  f_segment_erase(bankD0);
  SRAM_f_pwrite_8(0x0000, bankD0);
  Serial0_write("|  8 NOP ");
  if(*((uint16_t*)bankD0)) // if value at address is NOT ZERO
    Serial0_write("|    Fail ");
  else
    Serial0_write("| Success ");
  
  sprintf(outStr, "| %04X | %06u us |\n", *((uint16_t*)bankD0), (uint16_t)_event_timer_value);
  Serial0_write(outStr);
  free(SRAM_f_pwrite_8);


  SRAM_f_pwrite_6 = malloc_subroutine(f_word_partial_write_6, end_f_word_partial_write_6);
  if (!SRAM_f_pwrite_6)
    return 1;

  f_segment_erase(bankD0);
  SRAM_f_pwrite_6(0x0000, bankD0);
  Serial0_write("|  6 NOP ");
  if(*((uint16_t*)bankD0)) // if value at address is NOT ZERO
    Serial0_write("|    Fail ");
  else
    Serial0_write("| Success ");
  
  sprintf(outStr, "| %04X | %06u us |\n", *((uint16_t*)bankD0), (uint16_t)_event_timer_value);
  Serial0_write(outStr);
  free(SRAM_f_pwrite_6);


  SRAM_f_pwrite_4 = malloc_subroutine(f_word_partial_write_4, end_f_word_partial_write_4);
  if (!SRAM_f_pwrite_4)
    return 1;

  f_segment_erase(bankD0);
  SRAM_f_pwrite_4(0x0000, bankD0);
  Serial0_write("|  4 NOP ");
  if(*((uint16_t*)bankD0)) // if value at address is NOT ZERO
    Serial0_write("|    Fail ");
  else
    Serial0_write("| Success ");
  
  sprintf(outStr, "| %04X | %06u us |\n", *((uint16_t*)bankD0), (uint16_t)_event_timer_value);
  Serial0_write(outStr);
  free(SRAM_f_pwrite_4);


  SRAM_f_pwrite_0 = malloc_subroutine(f_word_partial_write_0, end_f_word_partial_write_0);
  if (!SRAM_f_pwrite_0)
    return 1;

  f_segment_erase(bankD0);
  SRAM_f_pwrite_0(0x0000, bankD0);
  Serial0_write("|  0 NOP ");
  if(*((uint16_t*)bankD0)) // if value at address is NOT ZERO
    Serial0_write("|    Fail ");
  else
    Serial0_write("| Success ");
  
  sprintf(outStr, "| %04X | %06u us |\n", *((uint16_t*)bankD0), (uint16_t)_event_timer_value);
  Serial0_write(outStr);
  free(SRAM_f_pwrite_0);


  return 0;
}



void init_and_wait(void)
{
  P1REN |= BIT1;
  P1DIR |= BIT0;
  P1OUT |= BIT1 + BIT0;
  while(P1IN & BIT1);// wait till button press to start
  P1OUT &= ~BIT0;
}
