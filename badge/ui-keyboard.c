#include "orchard-app.h"
#include "orchard-events.h"
#include "orchard-ui.h"
#include "tpm.h"

#include <string.h>

#include "fontlist.h"

/*
 * We need two widgets: a console and the keyboard.
 * We also need one listener object for detecting keypresses
 */

typedef struct _KeyboardHandles {
	GListener	gl;
	GHandle		ghConsole;
	GHandle		ghKeyboard;
	font_t		font;
	uint8_t		pos;
} KeyboardHandles;

static uint8_t handle_input (char * name, uint8_t max,
	GEventKeyboard * pk, KeyboardHandles * p)
{
	GConsoleObject * cons;
	uint8_t r;
	uint8_t y;

	if (pk->bytecount == 0)
		return (0);

	cons = (GConsoleObject *)p->ghConsole;

	cons->cx = 0;
	y = cons->cy;
	gdispGFillArea (p->ghConsole->display, cons->cx, cons->cy,
	    gdispGetWidth(), gdispGetFontMetric (p->font, fontHeight), Black);

	switch (pk->c[0]) {
	case GKEY_BACKSPACE:
		p->pos--;
		name[p->pos] = 0x0;
		gwinPrintf (p->ghConsole, "%s_", name);
		cons->cy = y;
		r = 0;
		break;
	case GKEY_ENTER:
		r = 1;
		break;
	default:
		if (p->pos == max) {
			pwmToneStart (400);
			chThdSleepMilliseconds (100);
			pwmToneStop ();
		} else {
			name[p->pos] = pk->c[0];
			p->pos++;
		}
		gwinPrintf (p->ghConsole, "%s_", name);
		cons->cy = y;
		r = 0;
		break;
	}

	return (r);
}

static void keyboard_start (OrchardAppContext *context)
{
	KeyboardHandles * p;
	OrchardUiContext * ctx;
	GWidgetInit wi;

	ctx = context->instance->uicontext;
	ctx->priv = chHeapAlloc (NULL, sizeof(KeyboardHandles));
	p = ctx->priv;

	p->font = gdispOpenFont (FONT_KEYBOARD);
	gwinSetDefaultFont (p->font);

	/* Draw the console/text entry widget */

	gwinWidgetClearInit (&wi);
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight() / 2;
	p->ghConsole = gwinConsoleCreate (0, &wi.g);
	gwinSetColor (p->ghConsole, Yellow);
	gwinSetBgColor (p->ghConsole, Black);
	gwinShow (p->ghConsole);
	gwinClear (p->ghConsole);
	gwinPrintf (p->ghConsole, "%s\n\n",
		context->instance->uicontext->itemlist[0]);

	/* Draw the keyboard widget */
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = gdispGetHeight() / 2;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight() / 2;
	p->ghKeyboard = gwinKeyboardCreate (0, &wi);
	gwinSetStyle (p->ghKeyboard, &WhiteWidgetStyle);
	gwinShow (p->ghKeyboard);

	/* Wait for events */
	geventListenerInit (&p->gl);
	gwinAttachListener (&p->gl);

	geventAttachSource (&p->gl, gwinKeyboardGetEventSource (p->ghKeyboard),
		GLISTEN_KEYTRANSITIONS | GLISTEN_KEYUP);

	geventRegisterCallback (&p->gl, orchardAppUgfxCallback, &p->gl);

	gwinPrintf (p->ghConsole, "%s_", ctx->itemlist[1]);
	p->pos = strlen (ctx->itemlist[1]);

	return;
}

static void keyboard_event(OrchardAppContext *context,
	const OrchardAppEvent *event)
{
 	GEventKeyboard * pk;
	KeyboardHandles * p;
	GEvent * pe;
	char * name;
	uint8_t max;

	p = context->instance->uicontext->priv;

	if (event->type != ugfxEvent)
		return;

	pe = event->ugfx.pEvent;

	if (pe->type == GEVENT_KEYBOARD)
		pk = (GEventKeyboard *)pe;
	else
		return;

	name = (char *)context->instance->uicontext->itemlist[1];
	max = context->instance->uicontext->total;

	if (handle_input (name, max, pk, p) != 0)
		chEvtBroadcast (&ui_completed);

	return;  
}

static void keyboard_exit(OrchardAppContext *context)
{
	KeyboardHandles * p;

	p = context->instance->uicontext->priv;

	geventRegisterCallback (&p->gl, NULL, NULL);
	geventDetachSource (&p->gl, NULL);
	gwinDestroy (p->ghConsole);
	gwinDestroy (p->ghKeyboard);

	gdispCloseFont (p->font);

	gdispClear (Black);

	chHeapFree (p);
	context->instance->uicontext->priv = NULL;

	return;
}

orchard_ui("keyboard", keyboard_start, keyboard_event, keyboard_exit);

