#define GENE_SIGNATURE  0x424D3135  // BM15
#define GENE_BLOCK  0
#define GENE_OFFSET 0
#define GENE_VERSION 1

#define GENE_NAMELENGTH 20    // null terminated, so 19 char name max

/// ABSTRACTION VIOLATION WARNING
#define GENE_FAMILYSIZE 5     // up to 5 effects stored in memory
// due to limitations in the LED effects registry implementation, we have to create
// discrete registry entries for the lightgene that cannot be adjusted
// by simply changing the above #define parameter
// see led.c, lightGeneFB orchard_effects() registry calls, as well as the
// render_ui() calls that relay gene information to the display

typedef struct genome {
  uint8_t  cd_period;
  uint8_t  cd_rate;
  uint8_t  cd_dir;
  uint8_t  sat;
  uint8_t  hue;
  uint8_t  hue_ratedir;
  uint8_t  hue_bound;
  uint8_t  lin;
  uint8_t  strobe;
  uint8_t  accel;
  uint8_t  mic;
  char     name[GENE_NAMELENGTH];
} genome;

typedef struct genes {
  uint32_t  signature;
  uint32_t  version;
  char      name[GENE_NAMELENGTH];
  genome    individual[GENE_FAMILYSIZE];
} genes;

void geneStart(void);
void generateName(char *result);
