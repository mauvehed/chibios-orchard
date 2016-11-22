#include "ch.h"
#include "hal.h"
#include "oled.h"
#include "spi.h"
#include "string.h"

#include "orchard.h"
#include "orchard-ui.h"

#include "gfx.h"
#include "images.h"
#include "buildtime.h"
void oledSDFail(void) {
  font_t font;

  font = gdispOpenFont ("UI1");
  gwinSetDefaultFont (font);
  
  gdispDrawStringBox (0, 210, gdispGetWidth(),
		      gdispGetFontMetric(font, fontHeight),
		      "IDES OF MARCH | Defcon 25 (2016)",
		      font, White, justifyCenter);
  
  gdispDrawStringBox (0, 225, gdispGetWidth(),
		      gdispGetFontMetric(font, fontHeight),
		      BUILDTIME,
		      font, White, justifyCenter);

  gdispCloseFont (font);  
  font = gdispOpenFont ("DejaVuSans24");
  
  gdispDrawStringBox (0, 0, gdispGetWidth(),
		      gdispGetFontMetric(font, fontHeight),
		      "CHECK SD CARD!",
		      font, Red, justifyCenter); 
  
}

void oledOrchardBanner(void)
{
	font_t font;
	static gdispImage myImage;

	if (gdispImageOpenFile (&myImage,
				IMG_SPLASH) == GDISP_IMAGE_ERR_OK) {
	  gdispImageDraw (&myImage,
			  0, 0,
			  myImage.width,
			  myImage.height, 0, 0);
	  
	  gdispImageClose (&myImage);
	}

	font = gdispOpenFont ("UI1");
	gwinSetDefaultFont (font);
	
	gdispDrawStringBox (0, 210, gdispGetWidth(),
			    gdispGetFontMetric(font, fontHeight),
			    "IDES OF MARCH | Defcon 25 (2016)",
			    font, White, justifyCenter);

	gdispDrawStringBox (0, 225, gdispGetWidth(),
			    gdispGetFontMetric(font, fontHeight),
			    BUILDTIME,
			    font, White, justifyCenter);

	gdispCloseFont (font);
	/* orchardGfxEnd(); */
	return;
}
