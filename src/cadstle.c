#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
//#include <math.h>
#include <stdio.h>

#define NAV_WIDTH (300)
#define NAV_HEIGHT (50)

//#define NK_PRIVATE
#define NK_MEMSET memset
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE STANDARD_BOOL
//#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
//#define NK_INCLUDE_FONT_BAKING
//#define NK_INCLUDE_DEFAULT_FONT
//#define NK_INCLUDE_COMMAND_USERDATA
#define NK_BUTTON_TRIGGER_ON_RELEASE
//#define NK_ZERO_COMMAND_MEMORY
#define NK_UNIT_DRAW_INDEX
#define NK_KEYSTATE_BASED_INPUT

#include "nuklear.h"
#include "cadstle.h"

const char *generators[] = { "Greek Columns", "Corinthian Column", "Column adorned with crosses", "Column adorned with acanthus leaves", "SOIC clip side" };

void make3DNoiseTexture();
extern unsigned char *Noise3DTexPtr;
extern int Noise3DTexSize;
extern void cadstle_download(uint32_t size, stl_t *stl);
extern void cadstle_set_stl_gl(void *stl, uint32_t len);
extern void stlviewer_rot(float dx, float dy);
extern float cosf(float);
extern float sinf(float);
extern float sqrtf(float);
const float M_PI = 3.14159265358979323846264338327950288f;

void set_style_local(struct nk_context *ctx)
{
  struct nk_color table[NK_COLOR_COUNT];
  /*
  table[NK_COLOR_TEXT] = nk_rgba(255, 255, 255, 255);
  table[NK_COLOR_WINDOW] = nk_rgba(11, 95, 164, 255);
  table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
  table[NK_COLOR_BORDER] = nk_rgba(35, 67, 97, 255);
  table[NK_COLOR_BUTTON] = nk_rgba(7, 4, 119, 255);
  table[NK_COLOR_BUTTON_HOVER] = nk_rgba(11, 6, 179, 255);
  table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(11, 6, 179, 255);
  table[NK_COLOR_TOGGLE] = nk_rgba(35, 67, 97, 255);
  table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
  table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(235, 31, 39, 255);
  table[NK_COLOR_SELECT] = nk_rgba(255, 255, 255, 255);
  table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(235, 31, 39, 255);
  table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
  table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
  table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
  table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
  table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
  table[NK_COLOR_EDIT] = nk_rgba(255, 255, 255, 225);
  table[NK_COLOR_EDIT_CURSOR] = nk_rgba(35, 67, 97, 255);
  table[NK_COLOR_COMBO] = nk_rgba(7, 4, 119, 255);
  table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
  table[NK_COLOR_CHART_COLOR] = nk_rgba(255, 255, 255, 255);
  table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
  table[NK_COLOR_SCROLLBAR] = nk_rgba(255, 255, 255, 255);
  table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(35, 67, 97, 255);
  table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
  table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
  table[NK_COLOR_TAB_HEADER] = nk_rgba(255, 255, 255, 225);
  table[NK_COLOR_KNOB] = table[NK_COLOR_SLIDER];
  table[NK_COLOR_KNOB_CURSOR] = table[NK_COLOR_SLIDER_CURSOR];
  table[NK_COLOR_KNOB_CURSOR_HOVER] = table[NK_COLOR_SLIDER_CURSOR_HOVER];
  table[NK_COLOR_KNOB_CURSOR_ACTIVE] = table[NK_COLOR_SLIDER_CURSOR_ACTIVE];
  */
  table[NK_COLOR_TEXT] = nk_rgba(255, 255, 255, 255);
  table[NK_COLOR_WINDOW] = nk_rgba(11, 95, 164, 255);
  table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
  table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
  table[NK_COLOR_BUTTON] = nk_rgba(7, 4, 119, 255);
  table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
  table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
  table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
  table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
  table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
  table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
  table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
  table[NK_COLOR_SLIDER] = table[NK_COLOR_BUTTON];
  table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
  table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
  table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
  table[NK_COLOR_PROPERTY] = table[NK_COLOR_BUTTON];
  table[NK_COLOR_EDIT] = table[NK_COLOR_BUTTON];
  table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
  table[NK_COLOR_COMBO] = table[NK_COLOR_BUTTON];
  table[NK_COLOR_CHART] = table[NK_COLOR_BUTTON];
  table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
  table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
  table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
  table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
  table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
  table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
  table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
  table[NK_COLOR_KNOB] = table[NK_COLOR_SLIDER];
  table[NK_COLOR_KNOB_CURSOR] = table[NK_COLOR_SLIDER_CURSOR];
  table[NK_COLOR_KNOB_CURSOR_HOVER] = table[NK_COLOR_SLIDER_CURSOR_HOVER];
  table[NK_COLOR_KNOB_CURSOR_ACTIVE] = table[NK_COLOR_SLIDER_CURSOR_ACTIVE];
  nk_style_from_table(ctx, table);
}
/*

uint32_t rev_32(uint32_t a)
{
  union {
    uint8_t  u8[4];
    uint32_t u32;
  } val;
  val.u32 = a;
  return val.u8[0] << 24 | val.u8[1] << 16 | val.u8[2] << 8 | val.u8[3];
}

void rev_endian(stl_t *stl)
{
  stl->h.n = rev_32(stl->h.n);
}
*/

void nk_app_nav(struct nk_context *ctx, int width, int height, generator_t *gen_id, stl_t *stl)
{
  float btn_wd = 50.0f / (float)width;
  float ratio[] = { (float)NAV_WIDTH / (float)width,
                    (width - 2.0f * (float)NAV_WIDTH) / (float)width,
                    (float)NAV_WIDTH / (float)width };
  nk_layout_row(ctx, NK_DYNAMIC, NAV_HEIGHT, 3, ratio);
  nk_label(ctx, "[cadstle]", NK_TEXT_CENTERED);
  *gen_id = nk_combo(ctx, generators, NK_LEN(generators), *gen_id, NAV_HEIGHT, nk_vec2(width,300));
  if (nk_button_label(ctx, "download")) {
    if (stl != NULL) {
      uint32_t size = atof(stl->h.hdr);
      cadstle_download(size, stl);
    }
  }
}

void assign_pt(void *data, float x, float y, float z)
{
  if (data == NULL) {
    return;
  }
  point_t *pt = data;
  pt->x = x;
  pt->y = y;
  pt->z = z;
}

void nk_app_parameters_greek_columns(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
{
  static float    height            = 10.0f;
  static float    radius            = 1.0f;
  static int      segments          = 32;
  uint32_t        size              = 0;
  nk_bool         is_realloc_needed = false;
  int             i                 = 0;
  int             j                 = 0;

  nk_layout_row_dynamic(ctx, 50, 1);
  nk_property_float(ctx, "Height:", 0.01f, &height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  nk_property_float(ctx, "Radius:", 0.01f, &radius, 100.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  nk_property_int(ctx, "Segments:", 10, &segments, 256, 1, 1.0f);

  size = sizeof((*stl)->h) + sizeof((*stl)->tri[0]) * ((segments * 2) + (segments * 2));

  if (*stl == NULL) {
    is_realloc_needed = true;
  } else {
    size_t bufsize;
    bufsize = atof((*stl)->h.hdr);
    if (size > bufsize) {
      is_realloc_needed = true;
    }
  }

  if (is_realloc_needed) {
    *stl = realloc(*stl, size);
  }
  snprintf((*stl)->h.hdr, sizeof((*stl)->h.hdr), "%d", size);
  (*stl)->h.n = segments * 4;

  for (int i=0; i<segments; i++) {
    float delta    = (1.0f / (float)segments);
    float theta    = 2 * M_PI * i * delta;
    float theta_2  = 2 * M_PI * (i + 1) * delta;
    float x1       = radius * cosf(theta);
    float x2       = radius * cosf(theta_2);
    float y1       = radius * sinf(theta);
    float y2       = radius * sinf(theta_2);
    float ht       = height;
    float n_x      = cosf((theta + theta_2) / 2.0f);
    float n_y      = sinf((theta + theta_2) / 2.0f);

    assign_pt(&(*stl)->tri[j].data[0],  0 , -1.0f  ,0);
    assign_pt(&(*stl)->tri[j].data[12], 0 , 0 , 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36], x1, 0, y1);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    0 , 1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], 0 , ht, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[24], x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[24], x1, 0, y1);
    assign_pt(&(*stl)->tri[j].data[36], x2, 0, y2);
    j++;
  }
  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
}

#include "AI/nk_app_corinthian_column.c"
#include "AI/nk_app_gen_column_adorn_acanthus.c"

typedef struct {
  float radius;
  float y;
  float angle;
  float depth;
  float width;
  float top;
  float bottom;
} nk_app_gen_column_adorn_cross_arg_t;

int nk_app_gen_column_adorn_cross_sub(struct nk_context *ctx, stl_t **stl, nk_app_gen_column_adorn_cross_arg_t *arg, int j)
{
  float d = arg->depth;
  float d2 = d / 2.0f;
  float y_bot = arg->y - arg->bottom;
  float y_top = arg->y + arg->top;
  float w2 = arg->width / 2.0f;

#define ROT_X(X,Z) ((arg->radius + X) * cosf(arg->angle) - Z * sinf(arg->angle))
#define ROT_Z(X,Z) ((arg->radius + X) * sinf(arg->angle) + Z * cosf(arg->angle))
  // CENTER
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0.0f, -1.0f, 0.0f);
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), y_bot, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_bot, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f,-d2), y_bot, ROT_Z(0.0f,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0.0f, -1.0f, 0.0f);
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f,-d2), y_bot, ROT_Z(0.0f,-d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_bot, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d,-d2), y_bot, ROT_Z(d,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(1.0f, 0.0f), 0.0f, ROT_Z(1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, d2), y_bot, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d,-d2), y_bot, ROT_Z(d,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(1.0f, 0.0f), 0.0f, ROT_Z(1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d,-d2), y_bot, ROT_Z(d,-d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d,-d2), y_top, ROT_Z(d,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(-1.0f, 0.0f), 0.0f, ROT_Z(-1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0, d2), y_bot, ROT_Z(0, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0, d2), y_top, ROT_Z(0, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0,-d2), y_bot, ROT_Z(0,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(-1.0f, 0.0f), 0.0f, ROT_Z(-1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0,-d2), y_bot, ROT_Z(0,-d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0, d2), y_top, ROT_Z(0, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0,-d2), y_top, ROT_Z(0,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0.0f, 1.0f, 0.0f);
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), y_top, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f,-d2), y_top, ROT_Z(0.0f,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0.0f, 1.0f, 0.0f);
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f,-d2), y_top, ROT_Z(0.0f,-d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d,-d2), y_top, ROT_Z(d,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), y_bot, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_bot, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, d2), arg->y - d2, ROT_Z(d, d2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), y_bot, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), arg->y - d2, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, d2), arg->y - d2, ROT_Z(0.0f, d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -d2), y_bot, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -d2), y_bot, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -d2), arg->y - d2, ROT_Z(d, -d2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -d2), y_bot, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -d2), arg->y - d2, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -d2), arg->y - d2, ROT_Z(0.0f, -d2));
  }
  j++;
//---
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), arg->y + d2, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), arg->y + d2, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, d2), y_top, ROT_Z(d, d2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), arg->y + d2, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, d2), y_top, ROT_Z(0.0f, d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -d2), arg->y + d2, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -d2), arg->y + d2, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -d2), y_top, ROT_Z(d, -d2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -d2), arg->y + d2, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -d2), y_top, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -d2), y_top, ROT_Z(0.0f, -d2));
  }
  j++;

  // ARM 1
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(-1.0f, 0.0f), 0.0f, ROT_Z(-1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), arg->y + d2, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, w2), arg->y + d2, ROT_Z(0.0f, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, d2), arg->y - d2, ROT_Z(0.0f, d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(-1.0f, 0.0f), 0.0f, ROT_Z(-1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, d2), arg->y - d2, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, w2), arg->y + d2, ROT_Z(0.0f, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, w2), arg->y - d2, ROT_Z(0.0f, w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(1.0f, 0.0f), 0.0f, ROT_Z(1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, d2), arg->y + d2, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, w2), arg->y + d2, ROT_Z(d, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, d2), arg->y - d2, ROT_Z(d, d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(1.0f, 0.0f), 0.0f, ROT_Z(1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, d2), arg->y - d2, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, w2), arg->y + d2, ROT_Z(d, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, w2), arg->y - d2, ROT_Z(d, w2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), -1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, d2), arg->y - d2, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, d2), arg->y - d2, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, w2), arg->y - d2, ROT_Z(0.0f, w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), -1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, w2), arg->y - d2, ROT_Z(0.0f, w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, w2), arg->y - d2, ROT_Z(d, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, d2), arg->y - d2, ROT_Z(d, d2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), 1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, d2), arg->y + d2, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, d2), arg->y + d2, ROT_Z(0.0f, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, w2), arg->y + d2, ROT_Z(0.0f, w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), 1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, w2), arg->y + d2, ROT_Z(0.0f, w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, w2), arg->y + d2, ROT_Z(d, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, d2), arg->y + d2, ROT_Z(d, d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, w2), arg->y + d2, ROT_Z(d, w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, w2), arg->y + d2, ROT_Z(0.0f, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, w2), arg->y - d2, ROT_Z(0.0f, w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, w2), arg->y + d2, ROT_Z(d, w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, w2), arg->y - d2, ROT_Z(0.0f, w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, w2), arg->y - d2, ROT_Z(d, w2));
  }
  j++;

  // ARM 2
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(-1.0f, 0.0f), 0.0f, ROT_Z(-1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -d2), arg->y + d2, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, -w2), arg->y + d2, ROT_Z(0.0f, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -d2), arg->y - d2, ROT_Z(0.0f, -d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(-1.0f, 0.0f), 0.0f, ROT_Z(-1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -d2), arg->y - d2, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, -w2), arg->y + d2, ROT_Z(0.0f, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -w2), arg->y - d2, ROT_Z(0.0f, -w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(1.0f, 0.0f), 0.0f, ROT_Z(1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, -d2), arg->y + d2, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -w2), arg->y + d2, ROT_Z(d, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -d2), arg->y - d2, ROT_Z(d, -d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(1.0f, 0.0f), 0.0f, ROT_Z(1.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, -d2), arg->y - d2, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -w2), arg->y + d2, ROT_Z(d, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -w2), arg->y - d2, ROT_Z(d, -w2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), -1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, -d2), arg->y - d2, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, -d2), arg->y - d2, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -w2), arg->y - d2, ROT_Z(0.0f, -w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), -1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -w2), arg->y - d2, ROT_Z(0.0f, -w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -w2), arg->y - d2, ROT_Z(d, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -d2), arg->y - d2, ROT_Z(d, -d2));
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), 1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, -d2), arg->y + d2, ROT_Z(d, -d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, -d2), arg->y + d2, ROT_Z(0.0f, -d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -w2), arg->y + d2, ROT_Z(0.0f, -w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 0.0f), 1.0f, ROT_Z(0.0f, 0.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0.0f, -w2), arg->y + d2, ROT_Z(0.0f, -w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, -w2), arg->y + d2, ROT_Z(d, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -d2), arg->y + d2, ROT_Z(d, -d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, -w2), arg->y + d2, ROT_Z(d, -w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, -w2), arg->y + d2, ROT_Z(0.0f, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0.0f, -w2), arg->y - d2, ROT_Z(0.0f, -w2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, -w2), arg->y + d2, ROT_Z(d, -w2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0.0f, -w2), arg->y - d2, ROT_Z(0.0f, -w2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d, -w2), arg->y - d2, ROT_Z(d, -w2));
  }
  j++;

  
  return j;
}


void nk_app_gen_column_adorn_cross(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
{
  static float    height            = 10.0f;
  static float    radius            = 1.0f;
  static int      segments          = 32;
  static int      ncrosses          = 7;
  static float    mount_space       = 0.1f;
  static float    mount_height      = 8.0f;
  static nk_app_gen_column_adorn_cross_arg_t arg = {
    0.0f,
    0.0f,
    0.0f,
    0.15f,
    0.75f,
    0.50f,
    1.15f,
  };
  float           mount_radius;
  uint32_t        size              = 0;
  nk_bool         is_realloc_needed = nk_false;
  static nk_bool  is_recompute_needed = nk_true;
  int             i                 = 0;
  int             j                 = 0;
  int             ntris             = 0;
  float tmp_f;
  int   tmp_i;

#define NK_PROP_FLOAT(ctx, label, min, var, max, step_1, step_2) \
  tmp_f = var; \
  nk_property_float(ctx, label, min, &tmp_f, max, step_1, step_2); \
  if (tmp_f != var) { \
    is_recompute_needed = nk_true; \
    var = tmp_f; \
  }

#define NK_PROP_INT(ctx, label, min, var, max, step_1, step_2) \
  tmp_i = var; \
  nk_property_int(ctx, label, min, &tmp_i, max, step_1, step_2); \
  if (tmp_i != var) { \
    is_recompute_needed = nk_true; \
    var = tmp_i; \
  }

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Height:", 0.01f, height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Radius:", 0.01f, radius, 100.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "Segments:", 10, segments, 256, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "Crosses:", 1, ncrosses, 32, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Mt Space:", 0.0f, mount_space, 2.0f, 1.0f, 0.01f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Mt Ht:", 0.0f, mount_height, height, 1.0f, 0.1f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Cr Dp:", 0.01f, arg.depth, 2.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Cr Wd:", 0.01f, arg.width, 2.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Cr Top:", 0.01f, arg.top, 2.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Cr Bot:", 0.01f, arg.bottom, 2.0f, 1.0f, 0.05f);

  if (is_recompute_needed == nk_false) {
    return;
  }

  mount_radius = radius + mount_space;

  ntris = segments * 4 + ncrosses * nk_app_gen_column_adorn_cross_sub(ctx, NULL, &arg, 0);
  size = sizeof((*stl)->h) + sizeof((*stl)->tri[0]) * ntris;

  if (*stl == NULL) {
    is_realloc_needed = true;
  } else {
    size_t bufsize;
    bufsize = atof((*stl)->h.hdr);
    if (size > bufsize) {
      is_realloc_needed = true;
    }
  }

  if (is_realloc_needed) {
    *stl = realloc(*stl, size);
  }
  snprintf((*stl)->h.hdr, sizeof((*stl)->h.hdr), "%d", size);
  (*stl)->h.n = ntris;

  for (int i=0; i<segments; i++) {
    float delta    = (1.0f / (float)segments);
    float theta    = 2 * M_PI * i * delta;
    float theta_2  = 2 * M_PI * (i + 1) * delta;
    float x1       = radius * cosf(theta);
    float x2       = radius * cosf(theta_2);
    float y1       = radius * sinf(theta);
    float y2       = radius * sinf(theta_2);
    float ht       = height;
    float n_x      = cosf((theta + theta_2) / 2.0f);
    float n_y      = sinf((theta + theta_2) / 2.0f);

    assign_pt(&(*stl)->tri[j].data[0],    0 , -1.0f  ,0);
    assign_pt(&(*stl)->tri[j].data[12], 0 , 0 , 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36], x1, 0, y1);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    0 , 1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], 0 , ht, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[24], x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[24], x1, 0, y1);
    assign_pt(&(*stl)->tri[j].data[36], x2, 0, y2);
    j++;
  }

  for (int i=0; i<ncrosses; i++) {
    arg.angle = (2.0f * M_PI * (float)i) / (float)ncrosses;
    arg.radius = mount_radius;
    arg.y = mount_height;
    j = nk_app_gen_column_adorn_cross_sub(ctx, stl, &arg, j);
  }

  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
  is_recompute_needed = nk_false;
}

typedef enum {
  RECTOID_POS_X = 1 << 0,
  RECTOID_NEG_X = 1 << 1,
  RECTOID_POS_Y = 1 << 2,
  RECTOID_NEG_Y = 1 << 3,
  RECTOID_POS_Z = 1 << 4,
  RECTOID_NEG_Z = 1 << 5,
  RECTOID_ALL   = 0x3F,
} rectoid_side_t;

int nk_app_gen_rectoid(stl_t **stl, int j, float x1, float y1, float z1, float x2, float y2, float z2, rectoid_side_t sides, bool invert_normal)
{
  float tmp;
  float normal = 1.0f;
  if (x2 < x1) {
    tmp = x1;
    x1 = x2;
    x2 = tmp;
  }
  if (y2 < y1) {
    tmp = y1;
    y1 = y2;
    y2 = tmp;
  }
  if (z2 < z1) {
    tmp = z1;
    z1 = z2;
    z2 = tmp;
  }
  if (invert_normal) {
    normal = -1.0f;
  }
  if (sides & RECTOID_POS_X) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  normal,  0,  0);
      assign_pt(&(*stl)->tri[j].data[12], x2, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y1, z2);
      assign_pt(&(*stl)->tri[j].data[36], x2, y2, z2);
    }
    j++;

    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  normal,  0,  0);
      assign_pt(&(*stl)->tri[j].data[12], x2, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y2, z2);
      assign_pt(&(*stl)->tri[j].data[36], x2, y2, z1);
    }
    j++;
  }
  if (sides & RECTOID_NEG_X) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0], -normal,  0,  0);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x1, y1, z2);
      assign_pt(&(*stl)->tri[j].data[36], x1, y2, z2);
    }
    j++;

    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0], -normal,  0,  0);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x1, y2, z2);
      assign_pt(&(*stl)->tri[j].data[36], x1, y2, z1);
    }
    j++;
  }
  if (sides & RECTOID_POS_Y) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0,  normal,  0);
      assign_pt(&(*stl)->tri[j].data[12], x1, y2, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y2, z1);
      assign_pt(&(*stl)->tri[j].data[36], x2, y2, z2);
    }
    j++;

    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0,  normal,  0);
      assign_pt(&(*stl)->tri[j].data[12], x1, y2, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y2, z2);
      assign_pt(&(*stl)->tri[j].data[36], x1, y2, z2);
    }
    j++;
  }
  if (sides & RECTOID_NEG_Y) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, -normal,  0);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y1, z1);
      assign_pt(&(*stl)->tri[j].data[36], x2, y1, z2);
    }
    j++;

    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, -normal,  0);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y1, z2);
      assign_pt(&(*stl)->tri[j].data[36], x1, y1, z2);
    }
    j++;
  }
  if (sides & RECTOID_POS_Z) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0,  0,  normal);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z2);
      assign_pt(&(*stl)->tri[j].data[24], x2, y1, z2);
      assign_pt(&(*stl)->tri[j].data[36], x2, y2, z2);
    }
    j++;

    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0,  0,  normal);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z2);
      assign_pt(&(*stl)->tri[j].data[24], x2, y2, z2);
      assign_pt(&(*stl)->tri[j].data[36], x1, y2, z2);
    }
    j++;
  }
  if (sides & RECTOID_NEG_Z) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, 0,  -normal);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y1, z1);
      assign_pt(&(*stl)->tri[j].data[36], x2, y2, z1);
    }
    j++;

    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, 0,  -normal);
      assign_pt(&(*stl)->tri[j].data[12], x1, y1, z1);
      assign_pt(&(*stl)->tri[j].data[24], x2, y2, z1);
      assign_pt(&(*stl)->tri[j].data[36], x1, y2, z1);
    }
    j++;
  }
  return j;
}

/* Fixed in z-plane.
 * x,y,z is center
 * in_side - side of inner square
 * out_side - side of outer square
 * is_normal_up - whether pointing up or down
 */
int nk_app_gen_z_rect_flange(stl_t **stl, int j, float x, float y, float z, float in_side, float out_side, bool is_normal_pos)
{
  float in_side_2 = in_side / 2.0f;
  float out_side_2 = out_side / 2.0f;
  float normal = 1.0f;
  if (!is_normal_pos) {
    normal = -1.0f;
  }

  /* Long-side (-X) */
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y - out_side_2, z);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y - out_side_2, z);
    assign_pt(&(*stl)->tri[j].data[36], x + out_side_2, y - in_side_2,  z);
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y - out_side_2, z);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y - in_side_2,  z);
    assign_pt(&(*stl)->tri[j].data[36], x - out_side_2, y - in_side_2,  z);
  }
  j++;
 
  /* Long-side (+X) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y + in_side_2,  z);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y + in_side_2,  z);
    assign_pt(&(*stl)->tri[j].data[36], x + out_side_2, y + out_side_2, z);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y + in_side_2,  z);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y + out_side_2, z);
    assign_pt(&(*stl)->tri[j].data[36], x - out_side_2, y + out_side_2, z);
  }
  j++;
 
  /* Short-side mid-x (-Z) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y - in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[24], x - in_side_2,  y - in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[36], x - in_side_2,  y + in_side_2, z);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y - in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[24], x - in_side_2,  y + in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[36], x - out_side_2, y + in_side_2, z);
  }
  j++;

  /* Short-side mid-x (+Z) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x + in_side_2,  y - in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y - in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[36], x + out_side_2, y + in_side_2, z);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, normal);
    assign_pt(&(*stl)->tri[j].data[12], x + in_side_2,  y - in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y + in_side_2, z);
    assign_pt(&(*stl)->tri[j].data[36], x + in_side_2,  y + in_side_2, z);
  }
  j++;
  return j;
}

/* Fixed in x-plane.
 * x,y,z is center
 * in_side - side of inner square
 * out_side - side of outer square
 * is_normal_up - whether pointing up or down
 */
int nk_app_gen_x_rect_flange(stl_t **stl, int j, float x, float y, float z, float in_side, float out_side, bool is_normal_pos)
{
  float in_side_2 = in_side / 2.0f;
  float out_side_2 = out_side / 2.0f;
  float normal = 1.0f;
  if (!is_normal_pos) {
    normal = -1.0f;
  }

  /* Long-side (-X) */
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x, y - out_side_2, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x, y - out_side_2, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x, y - in_side_2,  z + out_side_2);
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x, y - out_side_2, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x, y - in_side_2,  z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x, y - in_side_2,  z - out_side_2);
  }
  j++;
 
  /* Long-side (+X) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x, y + in_side_2,  z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x, y + in_side_2,  z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x, y + out_side_2, z + out_side_2);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x,  y + in_side_2, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x, y + out_side_2, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x, y + out_side_2, z - out_side_2);
  }
  j++;
 
  /* Short-side mid-x (-Z) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x,  y - in_side_2, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x,  y - in_side_2, z - in_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x,  y + in_side_2, z - in_side_2);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x,  y - in_side_2, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x,  y + in_side_2, z - in_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x,  y + in_side_2, z - out_side_2);
  }
  j++;

  /* Short-side mid-x (+Z) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x,  y - in_side_2, z + in_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x,  y - in_side_2, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x,  y + in_side_2, z + out_side_2);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  normal, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x,  y - in_side_2, z + in_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x,  y + in_side_2, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x,  y + in_side_2, z + in_side_2);
  }
  j++;
  return j;
}

/* Fixed in y-plane.
 * x,y,z is center
 * in_side - side of inner square
 * out_side - side of outer square
 * is_normal_up - whether pointing up or down
 */
int nk_app_gen_y_rect_flange(stl_t **stl, int j, float x, float y, float z, float in_side, float out_side, bool is_normal_up)
{
  float in_side_2 = in_side / 2.0f;
  float out_side_2 = out_side / 2.0f;
  float normal = 1.0f;
  if (!is_normal_up) {
    normal = -1.0f;
  }

  /* Long-side (-X) */
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x - out_side_2, y, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x - in_side_2,  y, z + out_side_2);
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x - out_side_2, y, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x - in_side_2,  y, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x - in_side_2,  y, z - out_side_2);
  }
  j++;
 
  /* Long-side (+X) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x + in_side_2,  y, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x + in_side_2,  y, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x + out_side_2, y, z + out_side_2);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x + in_side_2,  y, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x + out_side_2, y, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x + out_side_2, y, z - out_side_2);
  }
  j++;
 
  /* Short-side mid-x (-Z) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x - in_side_2,  y, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x - in_side_2,  y, z - in_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x + in_side_2,  y, z - in_side_2);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x - in_side_2,  y, z - out_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x + in_side_2,  y, z - in_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x + in_side_2,  y, z - out_side_2);
  }
  j++;

  /* Short-side mid-x (+Z) */ 
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x - in_side_2,  y, z + in_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x - in_side_2,  y, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x + in_side_2,  y, z + out_side_2);
  }
  j++;
  
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, normal, 0);
    assign_pt(&(*stl)->tri[j].data[12], x - in_side_2,  y, z + in_side_2);
    assign_pt(&(*stl)->tri[j].data[24], x + in_side_2,  y, z + out_side_2);
    assign_pt(&(*stl)->tri[j].data[36], x + in_side_2,  y, z + in_side_2);
  }
  j++;
  return j;
}

typedef struct {
  float bot_height;
  float mid_height;
  float plate_thickness;
  float in_side;
  float out_side;
  float catch_side;
  int   number;
  float pin_header_side;
  float pivot_radius;
  int   pivot_seg_cutoff;
  int   pivot_segments;
  float pivot_bot_ht;
  float top_ht;
  float top_pin_side;
  float top_pin_space;
  float top_pin_len;
} nk_app_soic_clip_side_single_t;

int nk_app_gen_soic_clip_side_single(stl_t **stl, int j, float x_off, nk_app_soic_clip_side_single_t *arg)
{
  /* Main tube */
  rectoid_side_t sides = RECTOID_NEG_Z | RECTOID_POS_Z | RECTOID_NEG_X | RECTOID_POS_X; 
  j = nk_app_gen_rectoid(stl, j,

	  x_off, 
	  0.0f,
	  0.0f,

	  arg->out_side + x_off,
	  arg->mid_height,
	  arg->out_side,

	  sides, false);

  j = nk_app_gen_rectoid(stl, j,

          x_off + (arg->out_side / 2.0f) - (arg->in_side / 2.0f),
	  0.0f,
	  (arg->out_side / 2.0f) - (arg->in_side / 2.0f),

          x_off + (arg->out_side / 2.0f) + (arg->in_side / 2.0f),
	  arg->mid_height,
	  (arg->out_side / 2.0f) + (arg->in_side / 2.0f),
	  

	  sides, true);


  j = nk_app_gen_y_rect_flange(stl, j,
                               x_off + arg->out_side / 2.0f,
                               arg->mid_height,
                               arg->out_side / 2.0f,
                               arg->in_side,
                               arg->out_side, true);
  j = nk_app_gen_y_rect_flange(stl, j,
                               x_off + arg->out_side / 2.0f,
                               0,
                               arg->out_side / 2.0f,
                               arg->in_side,
                               arg->out_side, false);

  /* Lower catch */
  sides = RECTOID_ALL & ~(RECTOID_POS_Y);
  j = nk_app_gen_rectoid(stl, j,

          x_off,
	  0.0f,
	  (arg->out_side / 2.0f) + (arg->in_side / 2.0f),

          x_off + arg->out_side,
	  -arg->bot_height,
	  arg->out_side,
	  

	  sides, false);

  sides = RECTOID_ALL & ~(RECTOID_POS_Y|RECTOID_POS_Z);
  j = nk_app_gen_rectoid(stl, j,

          x_off,
	  0.0f,
	  (arg->out_side / 2.0f) + (arg->in_side / 2.0f),

          x_off + arg->catch_side,
	  -arg->bot_height,
	  0,

	  sides, false);
  j = nk_app_gen_rectoid(stl, j,

          x_off + arg->out_side - arg->catch_side,
	  0.0f,
	  (arg->out_side / 2.0f) + (arg->in_side / 2.0f),

          x_off + arg->out_side,
	  -arg->bot_height,
	  0,

	  sides, false);

  return j;
}

int nk_app_gen_soic_clip_side_pin_header_plate(stl_t **stl, int j, nk_app_soic_clip_side_single_t *arg)
{
  rectoid_side_t sides = RECTOID_ALL & ~(RECTOID_POS_Z | RECTOID_NEG_Z);
  float pin_hdr_spacing = 4.0f * arg->out_side;
  float pin_hdr_side_2 = arg->pin_header_side / 2.0f;
  int number = (arg->number >> 2) << 2;
  j = nk_app_gen_rectoid(stl, j,

          0.0f,
	  -arg->bot_height,
	  arg->out_side,

          arg->number * arg->out_side,
	  arg->mid_height + 4.0f * pin_hdr_spacing,
	  arg->out_side + arg->plate_thickness,

	  sides, false);


  for (int i=0; i<number; i++) {
    float x = pin_hdr_spacing / 2.0f + pin_hdr_spacing * (i >> 2);
    float y = arg->mid_height + pin_hdr_spacing / 2.0f + pin_hdr_spacing * (i & 3);
    j = nk_app_gen_rectoid(stl, j,

		    x - pin_hdr_side_2,
		    y - pin_hdr_side_2,
		    arg->out_side,

		    x + pin_hdr_side_2,
		    y + pin_hdr_side_2,
		    arg->out_side + arg->plate_thickness,

		    sides, true);

    j = nk_app_gen_z_rect_flange(stl, j,
                               x,
                               y,
                               arg->out_side,
                               arg->pin_header_side,
                               pin_hdr_spacing, false);

    j = nk_app_gen_z_rect_flange(stl, j,
                               x,
                               y,
                               arg->out_side + arg->plate_thickness,
                               arg->pin_header_side,
                               pin_hdr_spacing, true);
  }

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, 1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0,  -arg->bot_height, arg->out_side + arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[24], arg->number * arg->out_side, -arg->bot_height, arg->out_side + arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[36], arg->number * arg->out_side, arg->mid_height, arg->out_side + arg->plate_thickness);
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, 1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0, -arg->bot_height, arg->out_side + arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[24], arg->number * arg->out_side, arg->mid_height, arg->out_side + arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[36], 0, arg->mid_height, arg->out_side + arg->plate_thickness);
  }
  j++;

  return j;
}

int nk_app_gen_soic_clip_side_pivot_plate(stl_t **stl, int j, nk_app_soic_clip_side_single_t *arg)
{
  float X = arg->number * arg->out_side;
  float DY;
  float Z;
  float bot_y = arg->pivot_bot_ht;
  float y = (arg->mid_height + bot_y) / 2.0f;
  float z = -arg->plate_thickness - arg->pivot_radius;

  j = nk_app_gen_rectoid(stl, j,

		    0,
		    0,
		    0,

		    X,
		    arg->mid_height,
		    -arg->plate_thickness,

		    RECTOID_ALL & ~(RECTOID_POS_Z|RECTOID_NEG_Z), false);

  for (int i=0; i<arg->pivot_seg_cutoff; i++) {
    float delta    = (0.5f / (float)arg->pivot_segments);
    float theta    = 2 * M_PI * i * delta;
    float theta_2  = 2 * M_PI * (i + 1) * delta;
    float mid_theta = (theta + theta_2) / 2.0f;
    float dz       = arg->pivot_radius * cosf(theta);
    float dz2      = arg->pivot_radius * cosf(theta_2);
    float dy       = arg->pivot_radius * sinf(theta);
    float dy2      = arg->pivot_radius * sinf(theta_2);
    /* TOP */
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, -sinf(mid_theta), -cosf(mid_theta));
      assign_pt(&(*stl)->tri[j].data[12], 0, y + dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], 0, y + dy2, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], X, y + dy2, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, -sinf(mid_theta), -cosf(mid_theta));
      assign_pt(&(*stl)->tri[j].data[12], 0, y + dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], X, y + dy2, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], X, y + dy, z + dz);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  -1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], 0, y + dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], 0, arg->mid_height, z + dz);
      assign_pt(&(*stl)->tri[j].data[36], 0, arg->mid_height, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  -1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], 0, y + dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], 0, arg->mid_height, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], 0, y + dy2, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], X, y + dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], X, arg->mid_height, z + dz);
      assign_pt(&(*stl)->tri[j].data[36], X, arg->mid_height, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], X, y + dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], X, arg->mid_height, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], X, y + dy2, z + dz2);
    }
    j++;
    /* BOT */
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, -sinf(-mid_theta), -cosf(-mid_theta));
      assign_pt(&(*stl)->tri[j].data[12], 0, y - dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], 0, y - dy2, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], X, y - dy2, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, -sinf(-mid_theta), -cosf(-mid_theta));
      assign_pt(&(*stl)->tri[j].data[12], 0, y - dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], X, y - dy2, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], X, y - dy, z + dz);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  -1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], 0, y - dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], 0, bot_y, z + dz);
      assign_pt(&(*stl)->tri[j].data[36], 0, bot_y, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  -1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], 0, y - dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], 0, bot_y, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], 0, y - dy2, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], X, y - dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], X, bot_y, z + dz);
      assign_pt(&(*stl)->tri[j].data[36], X, bot_y, z + dz2);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  1.0f, 0, 0);
      assign_pt(&(*stl)->tri[j].data[12], X, y - dy, z + dz);
      assign_pt(&(*stl)->tri[j].data[24], X, bot_y, z + dz2);
      assign_pt(&(*stl)->tri[j].data[36], X, y - dy2, z + dz2);
    }
    j++;
    Z = z + dz2;
    DY = dy2;
  }
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, arg->mid_height, -arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[24], X, arg->mid_height, -arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[36], X, arg->mid_height, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, arg->mid_height, -arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[24], X, arg->mid_height, Z);
    assign_pt(&(*stl)->tri[j].data[36], 0, arg->mid_height, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, -1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, bot_y, -arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[24], X, bot_y, -arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[36], X, bot_y, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, -1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, bot_y, -arg->plate_thickness);
    assign_pt(&(*stl)->tri[j].data[24], X, bot_y, Z);
    assign_pt(&(*stl)->tri[j].data[36], 0, bot_y, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, -1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0, arg->mid_height, Z);
    assign_pt(&(*stl)->tri[j].data[24], X, arg->mid_height, Z);
    assign_pt(&(*stl)->tri[j].data[36], X, y + DY, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, -1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0, arg->mid_height, Z);
    assign_pt(&(*stl)->tri[j].data[24], X, y + DY, Z);
    assign_pt(&(*stl)->tri[j].data[36], 0, y + DY, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, -1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0, bot_y, Z);
    assign_pt(&(*stl)->tri[j].data[24], X, bot_y, Z);
    assign_pt(&(*stl)->tri[j].data[36], X, y - DY, Z);
  }
  j++;
  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  0, 0, -1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0, bot_y, Z);
    assign_pt(&(*stl)->tri[j].data[24], X, y - DY, Z);
    assign_pt(&(*stl)->tri[j].data[36], 0, y - DY, Z);
  }
  j++;

  if (bot_y > 0.0f) {
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, 0, -1.0f);
      assign_pt(&(*stl)->tri[j].data[12], 0, bot_y, -arg->plate_thickness);
      assign_pt(&(*stl)->tri[j].data[24], X, bot_y, -arg->plate_thickness);
      assign_pt(&(*stl)->tri[j].data[36], X, 0, -arg->plate_thickness);
    }
    j++;
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0, 0, -1.0f);
      assign_pt(&(*stl)->tri[j].data[12], 0, bot_y, -arg->plate_thickness);
      assign_pt(&(*stl)->tri[j].data[24], X, 0, -arg->plate_thickness);
      assign_pt(&(*stl)->tri[j].data[36], 0, 0, -arg->plate_thickness);
    }
    j++;
  }

  return j;
}

int nk_app_gen_soic_clip_side_top(stl_t **stl, int j, nk_app_soic_clip_side_single_t *arg)
{
  float X = arg->number * arg->out_side;
  float Y = arg->mid_height + 16.0f * arg->out_side;
  float Z = arg->out_side;
	
  j = nk_app_gen_rectoid(stl, j,

		    0,
		    Y,
		    Z,

		    X,
		    Y + arg->top_ht,
		    Z + arg->plate_thickness,

		    RECTOID_ALL, false);

  j = nk_app_gen_rectoid(stl, j,

		    X / 2.0f + arg->top_pin_space / 2.0f,
		    Y + arg->top_ht / 2.0f - arg->top_pin_side / 2.0f,
		    Z,

		    X / 2.0f + arg->top_pin_space / 2.0f + arg->top_pin_side,
		    Y + arg->top_ht / 2.0f + arg->top_pin_side / 2.0f,
		    Z - arg->top_pin_len,

		    RECTOID_ALL, false);

  j = nk_app_gen_rectoid(stl, j,

		    X / 2.0f - arg->top_pin_space / 2.0f,
		    Y + arg->top_ht / 2.0f - arg->top_pin_side / 2.0f,
		    Z,

		    X / 2.0f - arg->top_pin_space / 2.0f - arg->top_pin_side,
		    Y + arg->top_ht / 2.0f + arg->top_pin_side / 2.0f,
		    Z - arg->top_pin_len,

		    RECTOID_ALL, false);
  
  return j;
}


void nk_app_gen_soic_clip_side(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
{
  static nk_app_soic_clip_side_single_t arg = {
    .bot_height       = 1.0f,
    .mid_height       = 10.0f,
    .plate_thickness  = 1.0f,
    .in_side          = 1.0f,
    .out_side         = 2.0f,
    .catch_side       = 0.3f,
    .number           = 10,
    .pin_header_side  = 1.5f,
    .pivot_radius     = 5.0f,
    .pivot_segments   = 32,
    .pivot_seg_cutoff = 24,
    .pivot_bot_ht     = 0.0f,
    .top_ht           = 3.0f,
    .top_pin_side     = 1.0f,
    .top_pin_space    = 3.0f,
    .top_pin_len      = 1.0f,
  };

  static int   ntris = 0;
  static bool is_recompute_needed = true;
  int j = 0;
  uint32_t size = 0;
  bool is_realloc_needed = false;
  float tmp_f;
  int   tmp_i;

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Bot Ht", 0.01f, arg.bot_height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Mid Ht", 0.01f, arg.mid_height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "In Side", 0.01f, arg.in_side, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Out Side", 0.01f, arg.out_side, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Catch Side", 0.01f, arg.catch_side, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Pin Plt Thick", 0.01f, arg.plate_thickness, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Pin Hdr Side", 0.01f, arg.pin_header_side, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Pvt Radius", 0.01f, arg.pivot_radius, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Pvt Bot Ht", 0.00f, arg.pivot_bot_ht, arg.mid_height, 0.1f, 0.1f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "Pvt Segments", 8, arg.pivot_segments, 128, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "Pvt Seg Cutoff", 4, arg.pivot_seg_cutoff, arg.pivot_segments, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Ht", 1.0f, arg.top_ht, 100.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Pin Side", 1.0f, arg.top_pin_side, 100.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Pin Space", 1.0f, arg.top_pin_space, 100.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Pin Len", 1.0f, arg.top_pin_len, 100.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "number", 1, arg.number, 100, 1, 1.0f);

  if (is_recompute_needed == nk_false) {
    return;
  }

  ntris = arg.number * nk_app_gen_soic_clip_side_single(NULL, 0, 0.0f, &arg) + nk_app_gen_soic_clip_side_pin_header_plate(NULL, 0, &arg) + nk_app_gen_soic_clip_side_pivot_plate(NULL, 0, &arg) + nk_app_gen_soic_clip_side_top(NULL, 0, &arg);
  size = sizeof((*stl)->h) + sizeof((*stl)->tri[0]) * ntris;

  if (*stl == NULL) {
    is_realloc_needed = true;
  } else {
    size_t bufsize;
    bufsize = atof((*stl)->h.hdr);
    if (size > bufsize) {
      is_realloc_needed = true;
    }
  }

  if (is_realloc_needed) {
    *stl = realloc(*stl, size);
  }
  snprintf((*stl)->h.hdr, sizeof((*stl)->h.hdr), "%d", size);
  (*stl)->h.n = ntris;

  j = 0;
  for (int i=0; i<arg.number; i++) {
    j = nk_app_gen_soic_clip_side_single(stl, j, i * arg.out_side, &arg);
  }
  j = nk_app_gen_soic_clip_side_pin_header_plate(stl, j, &arg);
  j = nk_app_gen_soic_clip_side_pivot_plate(stl, j, &arg);
  j = nk_app_gen_soic_clip_side_top(stl, j, &arg);

  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
  is_recompute_needed = nk_false;
}


void nk_app_gen_soic_clip_side_old(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
{
  static float height = 5.0f;
  static float bot_height = 1.0f;
  static float top_height = 1.0f;
  static float OD = 2.0f;
  static float ID = 1.0f;
  static float top_plate_thickness = 0.5f;
  static float top_plate_width = 2.0f;
  static int   number = 10;
  static int   segments = 32;
  static int   ntris = 0;
  static bool is_recompute_needed = true;
  int j = 0;
  uint32_t size = 0;
  bool is_realloc_needed = false;
  float tmp_f;
  int   tmp_i;

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Height", 0.01f, height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Bot Ht", 0.01f, bot_height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Ht", 0.01f, top_height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Plt Thick", 0.01f, top_plate_thickness, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Top Plt Wd", 0.01f, top_plate_width, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "OD", 0.01f, OD, 100.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "ID", 0.01f, ID, OD, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "number", 1, number, 100, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "segments", 10, segments, 100, 1, 1.0f);

  if (is_recompute_needed == nk_false) {
    return;
  }

  ntris = segments * 7 * number + number * 8 + 12;
  size = sizeof((*stl)->h) + sizeof((*stl)->tri[0]) * ntris;

  if (*stl == NULL) {
    is_realloc_needed = true;
  } else {
    size_t bufsize;
    bufsize = atof((*stl)->h.hdr);
    if (size > bufsize) {
      is_realloc_needed = true;
    }
  }

  if (is_realloc_needed) {
    *stl = realloc(*stl, size);
  }
  snprintf((*stl)->h.hdr, sizeof((*stl)->h.hdr), "%d", size);
  (*stl)->h.n = ntris;

  j = 0;
  for (int k=0; k<number; k++) {
  for (int i=0; i<segments; i++) {
    float delta    = (1.0f / (float)segments);
    float theta    = 2 * M_PI * i * delta;
    float theta_2  = 2 * M_PI * (i + 1) * delta;
    float ox1       = (OD / 2.0f) * cosf(theta);
    float ox2       = (OD / 2.0f) * cosf(theta_2);
    float oy1       = (OD / 2.0f) * sinf(theta);
    float oy2       = (OD / 2.0f) * sinf(theta_2);
    float ix1       = (ID / 2.0f) * cosf(theta);
    float ix2       = (ID / 2.0f) * cosf(theta_2);
    float iy1       = (ID / 2.0f) * sinf(theta);
    float iy2       = (ID / 2.0f) * sinf(theta_2);
    float ht       = height;
    float n_x      = cosf((theta + theta_2) / 2.0f);
    float n_y      = sinf((theta + theta_2) / 2.0f);
    float x_off    = k * OD;
    float z        = 0.0f;
    float z_top    = 0.0f;

    /* FLATS */
    if (theta_2 <= M_PI) {
      z = -bot_height;
    } else {
      z_top = top_height + top_plate_thickness;
    }
    if (theta_2 <= M_PI && (theta_2 + delta) > M_PI) {
      assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , cosf(theta));
      assign_pt(&(*stl)->tri[j].data[12], x_off + ox2, z , oy2);
      assign_pt(&(*stl)->tri[j].data[24], x_off + ox2, 0, oy2);
      assign_pt(&(*stl)->tri[j].data[36], x_off + ix2, 0, iy2);
      j++;

      assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , cosf(theta));
      assign_pt(&(*stl)->tri[j].data[12], x_off + ox2, z , oy2);
      assign_pt(&(*stl)->tri[j].data[24], x_off + ix2, 0, iy2);
      assign_pt(&(*stl)->tri[j].data[36], x_off + ix2, z, iy2);
      j++;

      assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , -cosf(theta));
      assign_pt(&(*stl)->tri[j].data[12], x_off + ox2, ht + top_height , oy2);
      assign_pt(&(*stl)->tri[j].data[24], x_off + ox2, ht, oy2);
      assign_pt(&(*stl)->tri[j].data[36], x_off + ix2, ht, iy2);
      j++;

      assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , -cosf(theta));
      assign_pt(&(*stl)->tri[j].data[12], x_off + ox2, ht + top_height , oy2);
      assign_pt(&(*stl)->tri[j].data[24], x_off + ix2, ht, iy2);
      assign_pt(&(*stl)->tri[j].data[36], x_off + ix2, ht + top_height, iy2);
      j++;
    }

    if (i == 0) {
        assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , -cosf(theta));
        assign_pt(&(*stl)->tri[j].data[12], x_off + ox1, z , oy1);
        assign_pt(&(*stl)->tri[j].data[24], x_off + ox1, 0, oy1);
        assign_pt(&(*stl)->tri[j].data[36], x_off + ix1, 0, iy1);
        j++;

        assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , -cosf(theta));
        assign_pt(&(*stl)->tri[j].data[12], x_off + ox1, z , oy1);
        assign_pt(&(*stl)->tri[j].data[24], x_off + ix1, 0, iy1);
        assign_pt(&(*stl)->tri[j].data[36], x_off + ix1, z, iy1);
        j++;

        assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , cosf(theta));
        assign_pt(&(*stl)->tri[j].data[12], x_off + ox1, ht + top_height , oy1);
        assign_pt(&(*stl)->tri[j].data[24], x_off + ox1, ht, oy1);
        assign_pt(&(*stl)->tri[j].data[36], x_off + ix1, ht, iy1);
        j++;

        assign_pt(&(*stl)->tri[j].data[0],    sinf(theta) , 0  , cosf(theta));
        assign_pt(&(*stl)->tri[j].data[12], x_off + ox1, ht + top_height , oy1);
        assign_pt(&(*stl)->tri[j].data[24], x_off + ix1, ht, iy1);
        assign_pt(&(*stl)->tri[j].data[36], x_off + ix1, ht + top_height, iy1);
        j++;
    }

    /* BOT */
    assign_pt(&(*stl)->tri[j].data[0],    0 , -1.0f  ,0);
    assign_pt(&(*stl)->tri[j].data[12], x_off + ix1, z , iy1);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ox2, z, oy2);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ox1, z, oy1);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    0 , -1.0f  ,0);
    assign_pt(&(*stl)->tri[j].data[12], x_off + ix2, z , iy2);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ox2, z, oy2);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ix1, z, iy1);
    j++;

    /* TOP */
    assign_pt(&(*stl)->tri[j].data[0],    0 , 1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x_off + 0 , ht + z_top, 0);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ox1, ht + z_top, oy1);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ox2, ht + z_top, oy2);
    j++;

    /* OUTSIDE */
    assign_pt(&(*stl)->tri[j].data[0],    n_x , 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x_off + ox1, ht + z_top, oy1);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ox2, z, oy2);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ox2, ht + z_top, oy2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x_off + ox1, ht + z_top, oy1);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ox1, z, oy1);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ox2, z, oy2);
    j++;

    /* INSIDE */
    assign_pt(&(*stl)->tri[j].data[0],    -n_x , 0, -n_y);
    assign_pt(&(*stl)->tri[j].data[12], x_off + ix1, ht + z_top, iy1);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ix2, z, iy2);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ix2, ht + z_top, iy2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    -n_x , 0, -n_y);
    assign_pt(&(*stl)->tri[j].data[12], x_off + ix1, ht + z_top, iy1);
    assign_pt(&(*stl)->tri[j].data[24], x_off + ix1, z, iy1);
    assign_pt(&(*stl)->tri[j].data[36], x_off + ix2, z, iy2);
    j++;
  }
  }
  /* TOP PLATE */
  {
    float x1 = -OD / 2.0f;
    float x2 = number * OD - OD / 2.0f;
    float y1 = -OD / 2.0f;
    float y2 = top_plate_width - OD / 2.0f;
    float ht1 = height + top_height;
    float ht2 = height + top_height + top_plate_thickness;
    /* TOP */
    assign_pt(&(*stl)->tri[j].data[0],    0 , 1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht2, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, ht2, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht2, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    0 , 1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht2, 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, ht2, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht2, 0);
    j++;

    /* BOT */
    assign_pt(&(*stl)->tri[j].data[0],    0 , -1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht1, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht1, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    0 , -1.0f  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht1, 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht1, 0);
    j++;

    /* SIDE1 */
    assign_pt(&(*stl)->tri[j].data[0],   -1.0f, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht1, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[36], x1, ht2, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],   -1.0f, 0  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht1, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, ht2, y2);
    assign_pt(&(*stl)->tri[j].data[36], x1, ht2, 0);
    j++;

    /* SIDE2 */
    assign_pt(&(*stl)->tri[j].data[0],   1.0f, 0, 0);
    assign_pt(&(*stl)->tri[j].data[12], x2, ht1, 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht2, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],   1.0f, 0  , 0);
    assign_pt(&(*stl)->tri[j].data[12], x2, ht1, 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, ht2, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht2, 0);
    j++;

    /* SIDE-END */
    assign_pt(&(*stl)->tri[j].data[0],   0, 0, 1.0f);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[24], x2, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, ht2, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],   0, 0  , 1.0f);
    assign_pt(&(*stl)->tri[j].data[12], x1, ht1, y2);
    assign_pt(&(*stl)->tri[j].data[24], x2, ht2, y2);
    assign_pt(&(*stl)->tri[j].data[36], x1, ht2, y2);
    j++;
  }
  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
  is_recompute_needed = nk_false;
}



void nk_app_parameters(struct nk_context *ctx, int width, int height, generator_t gen_id, stl_t **stl)
{
  if (nk_group_begin(ctx, "parameters", 0)) {
    switch (gen_id) {
      case GENERATOR_GREEK_COLUMNS: nk_app_parameters_greek_columns(ctx, width, height, stl); break;
      case GENERATOR_GREEK_CORINTHIAN_COLUMN: nk_app_corinthian_column(ctx, width, height, stl); break;
      case GEN_COLUMN_ADORN_CROSS: nk_app_gen_column_adorn_cross(ctx, width, height, stl); break;
      case GEN_COLUMN_ADORN_ACANTHUS: nk_app_gen_column_adorn_acanthus(ctx, width, height, stl); break;
      case GEN_SOIC_CLIP_SIDE: nk_app_gen_soic_clip_side(ctx, width, height, stl); break;
    }
    nk_group_end(ctx);
  }
  return;
}

void nk_app_viewer(struct nk_context *ctx, int width, int height, generator_t gen_id, stl_t *stl)
{
  static nk_bool is_mid_btn_dragging = nk_false;
  static nk_bool is_initialized = nk_false;
  static struct nk_image stl_viewer_img = { 0 };
  struct nk_rect header = nk_rect(NAV_WIDTH, NAV_HEIGHT, width - NAV_WIDTH, height - NAV_HEIGHT);
  static int last_x;
  static int last_y;
  static int dy;
  static int dx;

  if (!is_initialized) {
    stl_viewer_img = nk_image_ptr("stlviewer.glsl");
    is_initialized = nk_true;
  }
  if (nk_group_begin(ctx, "viewer", 0)) {
    if (is_mid_btn_dragging && nk_input_has_mouse_click_down_in_rect(&ctx->input, NK_BUTTON_MIDDLE, header, nk_false)) {
      is_mid_btn_dragging = nk_false;
      printf("stlviewer click - done");
    }
    if (nk_input_has_mouse_click_down_in_rect(&ctx->input, NK_BUTTON_MIDDLE, header, nk_true)) {
      if (is_mid_btn_dragging) {
        dx = ctx->input.mouse.pos.x - last_x;
        dy = ctx->input.mouse.pos.y - last_y;
	stlviewer_rot((float)dx / header.w, (float)dy / header.h);
      }
      is_mid_btn_dragging = nk_true;
      last_x = ctx->input.mouse.pos.x;
      last_y = ctx->input.mouse.pos.y;
      printf("stlviewer click");
    } 
    dy = ctx->input.mouse.scroll_delta.y;
    if (nk_input_is_mouse_hovering_rect(&ctx->input, header) && dy) {
      printf("stlviewer scroll: %d\n", dy);
      ctx->input.mouse.scroll_delta.y = 0;
    }
    nk_layout_row_dynamic(ctx, height - 1.5 * NAV_HEIGHT, 1);
    nk_image(ctx, stl_viewer_img);
    nk_group_end(ctx);
  }
}


void nk_app_main(struct nk_context *ctx, int width, int height)
{
  static nk_bool is_initialized = nk_false;
  static int selection = 0;
  static generator_t gen_id = GENERATOR_GREEK_COLUMNS;
  static stl_t *stl = NULL;
  
  if (!is_initialized) {
      set_style_local(ctx);
      is_initialized = nk_true;
  }
  if (nk_begin(ctx, "cadstle", nk_rect(0, 0, width, height), NK_WINDOW_NO_SCROLLBAR)) {
    nk_app_nav(ctx, width, height, &gen_id, stl);
    float ratio[] = { (float)NAV_WIDTH / (float)width,
                      (width - (float)NAV_WIDTH) / (float)width };
    nk_layout_row(ctx, NK_DYNAMIC, height - NAV_HEIGHT, 2, ratio);
    nk_app_parameters(ctx, width, height, gen_id, &stl);
    nk_app_viewer(ctx, width, height, gen_id, stl);
  }
  nk_end(ctx);
  return;
}
