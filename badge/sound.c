/* sound.c - monotonic music for the badge */
#include "ch.h"
#include "hal.h"
#include "tpm_lld.h"
#include "dac_lld.h"
#include "notes.h"
#include "sound.h"

#define note4  50 /*400*/ /* mS per quarter note @ 140bpm */
#define note16 12 /*100*/ /* 16th note */
#define note32 5 /*50*/  /* 32nd note */

/* slow! */
#define snote4  60 /*400*/ /* mS per quarter note @ 140bpm */
#define snote8  30 /*400*/ /* 8th note */
#define snote16 15 /*100*/ /* 16th note */
#define snote32 10 /*50*/  /* 32nd note */

#ifdef notdef
static const PWM_NOTE soundStart[] = {
  { NOTE_FS3, note32 * 3 },
  { PWM_NOTE_PAUSE, note32 * 2 },
  { NOTE_CS5, note32 * 2 },
  { NOTE_D5, note32 * 2 },
  { NOTE_A4, note32 * 2 },
  { NOTE_FS5, note32 * 5 },
  { 0, PWM_DURATION_END }
};
#endif

static const PWM_NOTE soundNope[] = {
  /* Not allowed sound */
  { NOTE_GS3, note32 },
  { PWM_NOTE_PAUSE, note32 },
  { NOTE_GS3, note32 },
  { PWM_NOTE_PAUSE, note32 },  
  { NOTE_GS3, note32 },
  { 0, PWM_DURATION_END }
};

static const PWM_NOTE soundSadPanda[] = {
  /* dissonant failure sound */
  { NOTE_GS3, note16 },
  { NOTE_F3, note16 },
  { NOTE_E3, note4 },
  { 0, PWM_DURATION_END }
};

static const PWM_NOTE soundAttacked[] = {
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_A6, note16 },
  { NOTE_A7, note16 },  
  { 0, PWM_DURATION_END }
};

static const PWM_NOTE soundVictory[] = {
  { NOTE_D4, note16 },
  { NOTE_FS4, note16 },
  { NOTE_A4, note16 },
  { NOTE_D5, note16 },
  { PWM_NOTE_PAUSE, note16 * 2 },
  { NOTE_D4, note16 * 2 },
  { NOTE_D5, note16 * 3 },
  { 0, PWM_DURATION_END }
};

#ifdef notdef
static const PWM_NOTE soundHit[] = {
  { NOTE_FS4, note16 },
  { NOTE_FS3, note16 },
  { 0, PWM_DURATION_END }
};
#endif

static const PWM_NOTE soundDefeat[] = {
  { NOTE_GS4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_GS4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_GS4, snote16 },
  { NOTE_GS4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_B4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_AS4, snote16 },
  { NOTE_AS4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_GS4, snote16 },
  { NOTE_GS4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_G4, snote16 },
  { PWM_NOTE_PAUSE, snote16 },
  { NOTE_GS4, snote4 },
  { 0, PWM_DURATION_END }
};

void playTone(uint8_t idx, uint16_t duration) {
  /* note that these are indexed tones, not frequences (see pwmtonestart) */
  pwmToneStart(idx);
  chThdSleepMilliseconds (duration);
  pwmToneStop();
}

void playStartupSong(void) {
  /* the galaga game start sound */
  dacPlay ("galaga.raw");
}

void playConfigReset(void) {
  /* played when a hard factory reset occurs */
  playTone(99, 500);
}


void playPacman(void) {
  dacPlay ("pacman.raw");
}

void playMsPacman(void) {
  dacPlay ("mspac.raw");
}

void playCantina(void) {
  dacPlay ("cantina.raw");
}

void playKombat(void) {
  dacPlay ("kombat.raw");
}

void playMario(void) {
  dacPlay ("mario.raw");
}

void playDoh(void) {
  dacPlay ("doh.raw");
}

void playWoohoo(void) {
  dacPlay ("woohoo.raw");
}

void playDrWho(void) {
  dacPlay ("drwho.raw");
}

void playRickroll(void) {
  dacPlay ("rickroll.raw");
}

void playHardFail(void) {
  /* sad panda tone */
  pwmThreadPlay (soundSadPanda);
}

void playNope(void) {
  /* sad panda tone */
  pwmThreadPlay (soundNope);
}

void playAttacked(void) {
  /* played when you're getting attacked by another player */
  pwmThreadPlay (soundAttacked);
}

void playVictory(void) {
  /* played when you win */
  pwmThreadPlay (soundVictory);
}

void playDefeat(void) {
  /* played when you lose */
  pwmThreadPlay (soundDefeat);
}

void playDodge(void) {
  /* played when you dodge an attack */
  dacPlay("fight/clank1.raw");
}

void playHit(void) {
  /* played when you're hit */
  dacPlay("fight/hit1.raw");
}
