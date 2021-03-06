/*
 * ides_config.h
 * 
 * #defines go here to control app-fight and other badge features 
 *
 * J. Adams 4/2017
 * jna@retina.net
 */

#ifndef __IDES_CONFIG_H__
#define __IDES_CONFIG_H__

/* the maximum level you can reach if you change this you have to
 * update userconfig.c */
#define LEVEL_CAP        10

/* We we will attempt to find a new caesar every these many seconds */
#define CS_ELECT_INT     MS2ST(60000) 

/* You must be this tall to ride this ride */
#define MIN_CAESAR_LEVEL 3           

/* % chance of becoming caesar during election */
#define CAESAR_CHANCE    15

/* The max number of seconds you can assume another form (caesar, bender) */
#define MAX_BUFF_TIME    S2ST(3600)

/* how long to reach full heal */
#define HEAL_TIME        20           /* seconds */

/* We will heal the player at N hp per this interval or 2X HP if
 * UL_PLUSDEF has been activated */
#define HEAL_INTERVAL_US 1000000      /* 1 second */

/* The game framerate is 15 frames per second. We advance one frame
 * per state tick and track this in the animtick global variable.
 *
 * If you make large updates to the screen that take longer than 66mS,
 * you will have to reduce the frame rate and adjust animtion timings
 * (animtick) in app-fight.c.
 *
 * We do not dynamically adjust the animiation times
 * based on FPS or wallclok.
 *
 * 15FPS seems to be a good balance for this CPU. 
 */
#define FRAME_INTERVAL_US 66666

/* *_WAIT_TIMEs are always in system ticks. */
/* caveat! the system timer is a uint32_t and can roll over! be aware! */
#define DEFAULT_WAIT_TIME MS2ST(10000) // how long we wait for the user to respond. MUST BE IN SYSTEM TICKS. 
#define MIN_HOLDOFF 50                 // we introduce a small delay if we are resending (contention protocol). MUST BE IN mS
#define MAX_RETRIES 4                  // if we do that 3 times, abort.
#define MOVE_WAIT_TIME MS2ST(15000)    // Max game time. MUST BE IN SYSTEM TICKS. If you do nothing, the game ends.

#endif

