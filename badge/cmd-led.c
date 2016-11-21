/*
  cmd-led.c

  change the state of the led's
  J. Adams <jna@retina.net>
*/

#include "ch.h"
#include "hal.h"
#include "led.h"
#include "shell.h"
#include "chprintf.h"

#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "orchard.h"
#include "orchard-shell.h"

extern void (*current_fx)(void);

extern struct FXENTRY fxlist[];

static void led_stop(BaseSequentialStream *chp) {
  chprintf(chp, "Off.\r\n");
}

static void led_run(BaseSequentialStream *chp, int argc, char *argv[]) {

  uint8_t pattern;

  if (argc != 2) {
    chprintf(chp, "No pattern specified\r\n");
    return;
  }

  pattern = strtoul(argv[1], NULL, 0);
  if ((pattern < 1) || (pattern > FX_COUNT)) {
    chprintf(chp, "Invaild pattern #!\r\n");
    return;
  }

  current_fx = fxlist[pattern-1].function;
  ledResetPattern();
  
  chprintf(chp, "pattern changed to %s...\r\n", fxlist[pattern-1].name);
}
static void led_list(BaseSequentialStream *chp) {
  chprintf(chp, "\r\nAvailable LED Patterns\r\n");

  for (int i=0; i <FX_COUNT; i++) {
    chprintf(chp, "%2d) %s\r\n", i+1, fxlist[i].name);
  }
}

static void cmd_led(BaseSequentialStream *chp, int argc, char *argv[]) {

  if (argc == 0) {
    chprintf(chp, "led commands:\r\n");
    chprintf(chp, "   list             list animations available\r\n");
    chprintf(chp, "   run [n]          run pattern #n\r\n");
    chprintf(chp, "   stop             stop and blank LEDs\r\n");
    return;
  }

  if (!strcasecmp(argv[0], "list")) {
    led_list(chp);
    return;
  }

  if (!strcasecmp(argv[0], "run"))
    led_run(chp, argc, argv);
  else
    if (!strcasecmp(argv[0], "stop"))
      led_stop(chp);
    else
      chprintf(chp, "Unrecognized LED command\r\n");
}

orchard_command("led", cmd_led);
