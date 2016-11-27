#include "ch.h"
#include "hal.h"
#include "orchard.h"
#include "shell.h"
#include "chprintf.h"

#include "flash.h"
#include "userconfig.h"
#include "orchard-shell.h"
#include <string.h>

static userconfig config_cache;

void configSave(userconfig *newConfig) {
  int8_t ret;
  uint8_t *config;
  
  config = (uint8_t *)CONFIG_FLASH_ADDR;
  //  memcpy(config, newConfig, sizeof(userconfig) );

  flashErase(CONFIG_FLASH_SECTOR_BASE,1);
  ret = flashProgram( (uint8_t *) newConfig, config, sizeof(userconfig) );

  if (ret == F_ERR_NOTBLANK) {
    chprintf(stream, "ERROR (%d): Unable to save config to flash.\r\n", ret);
  } else {
    chprintf(stream, "Config saved.\r\n");
  }
}

static void init_config(userconfig *config) {

  config->signature = CONFIG_SIGNATURE;
  config->version = CONFIG_VERSION;

  memset(config->name, 0, CONFIG_NAME_MAXLEN);

  /* reset here */
  config->won = 0;
  config->lost = 0;
  config->p_type = p_pleeb;
  config->in_combat = 0;
  config->lastcombat = 0; // how long since combat started

  /* stats, dunno if we will use */
  config->level = 1;
  config->hp = 1000;
  config->xp = 0;
  config->gold = 500;
  
  config->str = 0;
  config->ac = 0;
  config->dex = 0;
  config->won = 0;
  config->lost = 0;
  
  /* these fields are only used during attack-response */
  config->damage = 0;
  config->is_crit = 0;

  config->led_shift = 0;
}

void configStart(void) {
  const userconfig *config;

  config = (const userconfig *) CONFIG_FLASH_ADDR;

  if ( config->signature != CONFIG_SIGNATURE ) {
    chprintf(stream, "Config not found, Initializing!\r\n");
    init_config(&config_cache);
    config = &config_cache;
    configSave(&config_cache);
    // write to flash
  } else if ( config->version != CONFIG_VERSION ) {
    chprintf(stream, "Config found, but wrong version.\r\n");
    init_config(&config_cache);
    config = &config_cache;
    configSave(&config_cache);
  } else {
    chprintf(stream, "Config OK!\r\n");
  }
}


const struct userconfig *getConfig(void) {
  return &config_cache;
}
