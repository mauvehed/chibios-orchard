/*-
 * Copyright (c) 2016
 *      Bill Paul <wpaul@windriver.com>.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Bill Paul.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR THE VOICES IN HIS HEAD
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _TPM_H_
#define _TPM_H_

#define KINETIS_TPM0_IRQ_VECTOR		Vector84
#define KINETIS_TPM1_IRQ_VECTOR		Vector88
#define KINETIS_TPM2_IRQ_VECTOR		Vector8C

/*
 * We use:
 * TPM2 channel 0, which is wired to pin PTB2
 */

#define TPM2_CHANNEL	0

/*
 * We pre-scale the clock by a factor of 32
 */

#define TPM_PRESCALE	32

/*
 * Base TPM clock is the system clock (48MHz), which we divide by
 * the prescale factor when calculating the desired output
 * frequency.
 */

#define TPM_FREQ	(KINETIS_SYSCLK_FREQUENCY / TPM_PRESCALE)

/*
 * Structure for music array. Each entry in the array is a tone
 * and duration tuple that describes a single note. There are two
 * special cases for diration: PWM_DURATION_END, which indicates
 * the end of the tune to play, and PWM_DURATION_LOOP, which indicates
 * this tune should be played over and over again (until told to stop).
 * There are also two special cases for a note: PWM_NOTE_PAUSE, which
 * means we should just pause for the duration time, and PWM_NOTE_OFF,
 * which measn to turn off the tone generator completely.
 */

#pragma pack(1)
typedef struct pwm_note {
	uint8_t		pwm_note;
	uint8_t		pwm_duration;
} PWM_NOTE;
#pragma pack()

#define PWM_DURATION_END	0xFF
#define PWM_DURATION_LOOP	0xFE
#define PWM_NOTE_PAUSE		0xFF
#define PWM_NOTE_OFF		0xFE
#define PWM_NOTE_BUFEND		0xFD

#define PWM_BUFSIZ		8

#define pwmFileThreadPlay(x)
#define pwmChanThreadPlay(x,y,z) pwmThreadPlay(x)
/* TPM note player thread priority */

#define TPM_THREAD_PRIO	70

extern void pwmStart (void);

extern void pwmToneStart (uint8_t);
extern void pwmToneStop (void);

extern void pwmThreadPlay (const PWM_NOTE *);

#endif /* _TPM_H_ */
