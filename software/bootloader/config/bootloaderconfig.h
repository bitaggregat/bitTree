 /* Name: bootloaderconfig.h
 * Micronucleus configuration file.
 * This file (together with some settings in Makefile.inc) configures the boot loader
 * according to the hardware.
 *
 * Controller type: ATmega328P - with external crystal
 * Configuration:   Aggresively size optimized configuration
 *       USB D- :   PC1
 *       USB D+ :   PC2
 *       Entry  :   Always
 *       LED    :   ACTIVE_HIGH at pin PD0
 *       OSCCAL :   Stays at 16 MHz
 * Note: Uses 16 MHz V-USB implementation.
 *
 * License: GNU GPL v2 (see License.txt
 */

#ifndef __bootloaderconfig_h_included__
#define __bootloaderconfig_h_included__

/* ------------------------------------------------------------------------- */
/*                       Hardware configuration.                             */
/*      Change this according to your CPU and USB configuration              */
/* ------------------------------------------------------------------------- */

#define USB_CFG_IOPORTNAME      B
  /* This is the port where the USB bus is connected. When you configure it to
   * "B", the registers PORTB, PINB and DDRB will be used.
   */

#define USB_CFG_DMINUS_BIT      4
/* This is the bit number in USB_CFG_IOPORT where the USB D- line is connected.
 * This may be any bit in the port.
 * USB- has a 1.5k pullup resistor to indicate a low-speed device.
 */
#define USB_CFG_DPLUS_BIT       3
/* This is the bit number in USB_CFG_IOPORT where the USB D+ line is connected.
 * This may be any bit in the port, but must be configured as a pin change interrupt.
 */

#define USB_CFG_CLOCK_KHZ       (F_CPU/1000)
/* Clock rate of the AVR in kHz. Legal values are 12000, 12800, 15000, 16000,
 * 16500, 18000 and 20000. The 12.8 MHz and 16.5 MHz versions of the code
 * require no crystal, they tolerate +/- 1% deviation from the nominal
 * frequency. All other rates require a precision of 2000 ppm and thus a
 * crystal!
 * Since F_CPU should be defined to your actual clock rate anyway, you should
 * not need to modify this setting.
 */

/* ----------------------- Optional Hardware Config ------------------------ */
//#define USB_CFG_PULLUP_IOPORTNAME   B
/* If you connect the 1.5k pullup resistor from D- to a port pin instead of
 * V+, you can connect and disconnect the device from firmware by calling
 * the macros usbDeviceConnect() and usbDeviceDisconnect() (see usbdrv.h).
 * This constant defines the port on which the pullup resistor is connected.
 */
//#define USB_CFG_PULLUP_BIT          0
/* This constant defines the bit number in USB_CFG_PULLUP_IOPORT (defined
 * above) where the 1.5k pullup resistor is connected. See description
 * above for details.
 */

/* ------------- Set up interrupt configuration (CPU specific) --------------   */
/* The register names change quite a bit in the ATtiny family. Pay attention    */
/* to the manual. Note that the interrupt flag system is still used even though */
/* interrupts are disabled. So this has to be configured correctly.             */


// setup interrupt for Pin Change for D+
// register where interrupt features are configured
#define USB_INTR_CFG            PCMSK0
// feature bits to set
#define USB_INTR_CFG_SET        (1 << USB_CFG_DPLUS_BIT)
// feature bits to clear
#define USB_INTR_CFG_CLR        0
// register where interrupt enable bit resides
#define USB_INTR_ENABLE         PCICR
// bit number in above register
#define USB_INTR_ENABLE_BIT     PCIE0
// register where interrupt pending bit resides
#define USB_INTR_PENDING        PCIFR
// bit number in above register
#define USB_INTR_PENDING_BIT    PCIF0

/* ------------------------------------------------------------------------- */
/*       Configuration relevant to the CPU the bootloader is running on      */
/* ------------------------------------------------------------------------- */

// how many milliseconds should host wait till it sends another erase or write?
// needs to be above 4.5 (and a whole integer) as avr freezes for 4.5ms
#define MICRONUCLEUS_WRITE_SLEEP 10


/* ---------------------- feature / code size options ---------------------- */
/*               Configure the behavior of the bootloader here               */
/* ------------------------------------------------------------------------- */

/*
 *  Define Bootloader entry condition
 *
 *  If the entry condition is not met, the bootloader will not be activated and the user program
 *  is executed directly after a reset. If no user program has been loaded, the bootloader
 *  is always active.
 *
 *  ENTRY_ALWAYS        Always activate the bootloader after reset. Requires the least
 *                      amount of code.
 *
 *  ENTRY_WATCHDOG      Activate the bootloader after a watchdog reset. This can be used
 *                      to enter the bootloader from the user program.
 *                      Adds 22 bytes.
 *
 *  ENTRY_EXT_RESET     Activate the bootloader after an external reset was issued by
 *                      pulling the reset pin low. It may be necessary to add an external
 *                      pull-up resistor to the reset pin if this entry method appears to
 *                      behave unreliably.
 *                      Adds 22 bytes.
 *
 *  ENTRY_JUMPER        Activate the bootloader when a specific pin is pulled low by an
 *                      external jumper.
 *                      Adds 34 bytes.
 *
 *       JUMPER_PIN     Pin the jumper is connected to. (e.g. PB0)
 *       JUMPER_PORT    Port out register for the jumper (e.g. PORTB)
 *       JUMPER_DDR     Port data direction register for the jumper (e.g. DDRB)
 *       JUMPER_INP     Port inout register for the jumper (e.g. PINB)
 *
 */

#define ENTRYMODE ENTRY_ALWAYS

#define JUMPER_PIN    PB0
#define JUMPER_PORT   PORTB
#define JUMPER_DDR    DDRB
#define JUMPER_INP    PINB

/*
  Internal implementation, don't change this unless you want to add an entrymode.
*/

#define ENTRY_ALWAYS    0
#define ENTRY_WATCHDOG  1
#define ENTRY_EXT_RESET 2
#define ENTRY_JUMPER    4

#if ENTRYMODE==ENTRY_ALWAYS
  #define bootLoaderInit()
  #define bootLoaderExit()
  #define bootLoaderStartCondition() 1
#elif ENTRYMODE==ENTRY_WATCHDOG
  #define bootLoaderInit()
  #define bootLoaderExit()
  #define bootLoaderStartCondition() (MCUSR&_BV(WDRF))
#elif ENTRYMODE==ENTRY_EXT_RESET
  #define bootLoaderInit()
  #define bootLoaderExit()
  #define bootLoaderStartCondition() (MCUSR&_BV(EXTRF))
#elif ENTRYMODE==ENTRY_JUMPER
  // Enable pull up on jumper pin and delay to stabilize input
  #define bootLoaderInit()   {JUMPER_DDR &= ~_BV(JUMPER_PIN);JUMPER_PORT |= _BV(JUMPER_PIN);_delay_ms(1);}
  #define bootLoaderExit()   {JUMPER_PORT &= ~_BV(JUMPER_PIN);}
  #define bootLoaderStartCondition() (!(JUMPER_INP&_BV(JUMPER_PIN)))
#else
   #error "No valid entry mode defined"
#endif

/*
 * Define bootloader timeout value.
 *
 *  The bootloader will only time out if a user program was loaded.
 *
 *  FAST_EXIT_NO_USB_MS        The bootloader will exit after this delay if no USB is connected.
 *                             Set to < 120 to disable.
 *                             Adds ~6 bytes.
 *                             (This will wait for an USB SE0 reset from the host)
 *
 *  AUTO_EXIT_MS               The bootloader will exit after this delay if no USB communication
 *                             from the host tool was received.
 *                             Set to 0 to disable -> never leave the bootloader except on receiving an exit command by USB.
 *
 *  All values are approx. in milliseconds
 */

#define FAST_EXIT_NO_USB_MS    0
#define AUTO_EXIT_MS           2000

 /*
 *  Defines the setting of the RC-oscillator calibration after quitting the bootloader. (OSCCAL)
 *
 *  OSCCAL_RESTORE_DEFAULT    Set this to '1' to revert to OSCCAL factore calibration after bootloader exit.
 *                            This is 8 MHz +/-2% on most devices or 16 MHz on the ATtiny 85 with activated PLL.
 *                            Adds ~14 bytes.
 *
 *  OSCCAL_SAVE_CALIB         Set this to '1' to save the OSCCAL calibration during program upload.
 *                            This value will be reloaded after reset and will also be used for the user
 *                            program unless "OSCCAL_RESTORE_DEFAULT" is active. This allows calibrate the internal
 *                            RC oscillator to the F_CPU target frequency +/-1% from the USB timing. Please note
 *                            that this is only true if the ambient temperature does not change.
 *                            Adds ~38 bytes.
 *
 *  OSCCAL_HAVE_XTAL          Set this to '1' if you have an external crystal oscillator. In this case no attempt
 *                            will be made to calibrate the oscillator. You should deactivate both options above
 *                            if you use this to avoid redundant code.
 *
 *  OSCCAL_SLOW_PROGRAMMING   Setting this to '1' will set OSCCAL back to the factory calibration during programming to make
 *                            sure correct timing is used for the flash writes. This is needed if the micronucleus clock
 *                            speed significantly deviated from the default clock. E.g. 12 Mhz on ATtiny841 vs. 8Mhz default.
 *
 *  If both options are selected, OSCCAL_RESTORE_DEFAULT takes precedence.
 *
 *  If no option is selected, OSCCAL will be left untouched and stays at either factory calibration or F_CPU depending
 *  on whether the bootloader was activated. This will take the least memory. You can use this if your program
 *  comes with its own OSCCAL calibration or an external clock source is used.
 */

#define OSCCAL_RESTORE_DEFAULT 1
#define OSCCAL_SAVE_CALIB 1
#define OSCCAL_HAVE_XTAL 0
#define OSCCAL_SLOW_PROGRAMMING 1

/*
 *  Defines handling of an indicator LED while the bootloader is active.
 *
 *  LED_MODE                  Define behavior of attached LED or suppress LED code.
 *
 *          NONE              Do not generate LED code (gains 18 bytes).
 *          ACTIVE_HIGH       LED is on when output pin is high. This will toggle between 1 and 0.
 *          ACTIVE_LOW        LED is on when output pin is low.  This will toggle between Z and 0. + 2 bytes
 *
 *  LED_DDR,LED_PORT,LED_PIN  Where is your LED connected?
 *
 */

#define LED_MODE    ACTIVE_HIGH

#define LED_DDR     DDRD
#define LED_PORT    PORTD
#define LED_PIN     PD6


/*
 *  This is the implementation of the LED code. Change the configuration above unless you want to
 *  change the led behavior
 *
 *  LED_INIT                  Called once after bootloader entry
 *  LED_EXIT                  Called once during bootloader exit
 *  LED_MACRO                 Called in the main loop with the idle counter as parameter.
 *                            Use to define pattern.
*/

#define NONE        0
#define ACTIVE_HIGH 1
#define ACTIVE_LOW  2

#if LED_MODE==ACTIVE_HIGH
  #define LED_INIT(x)   LED_DDR |= _BV(LED_PIN);
  #define LED_EXIT(x)   {LED_DDR &= ~_BV(LED_PIN);LED_PORT &= ~_BV(LED_PIN);}
  #define LED_MACRO(x)  if ( x & 0x4c ) {LED_PORT &= ~_BV(LED_PIN);} else {LED_PORT |= _BV(LED_PIN);}
#elif LED_MODE==ACTIVE_LOW
  #define LED_INIT(x)   LED_PORT &= ~_BV(LED_PIN);
  #define LED_EXIT(x)   LED_DDR &= ~_BV(LED_PIN);
  #define LED_MACRO(x)  if ( x & 0x4c ) {LED_DDR &= ~_BV(LED_PIN);} else {LED_DDR |= _BV(LED_PIN);}
#elif LED_MODE==NONE
  #define LED_INIT(x)
  #define LED_EXIT(x)
  #define LED_MACRO(x)
#endif

#endif /* __bootloader_h_included__ */
