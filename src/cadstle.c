#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
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

const char *generators[] = { "Greek Columns" };

void make3DNoiseTexture();
extern unsigned char *Noise3DTexPtr;
extern int Noise3DTexSize;
extern void cadstle_download(uint32_t size, stl_t *stl);
extern void cadstle_set_stl_gl(void *stl, uint32_t len);

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
  *gen_id = nk_combo(ctx, generators, NK_LEN(generators), *gen_id, NAV_HEIGHT, nk_vec2(width,200));
  if (nk_button_label(ctx, "download")) {
    if (stl != NULL) {
      uint32_t size = atof(stl->h.hdr);
      cadstle_download(size, stl);
    }
  }
}

void assign_pt(void *data, float x, float y, float z)
{
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
  float           tmp;

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

    assign_pt(&(*stl)->tri[j].data[0],    0 , 0  ,-1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0 , 0 , 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, y1, 0);
    assign_pt(&(*stl)->tri[j].data[36], x2, y2, 0);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    0 , 0  , 1.0f);
    assign_pt(&(*stl)->tri[j].data[12], 0 , 0 , ht);
    assign_pt(&(*stl)->tri[j].data[24], x1, y1, ht);
    assign_pt(&(*stl)->tri[j].data[36], x2, y2, ht);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , n_y, 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, y1, ht);
    assign_pt(&(*stl)->tri[j].data[24], x2, y2, 0);
    assign_pt(&(*stl)->tri[j].data[36], x2, y2, ht);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x , n_y, 0);
    assign_pt(&(*stl)->tri[j].data[12], x1, y1, ht);
    assign_pt(&(*stl)->tri[j].data[24], x2, y2, 0);
    assign_pt(&(*stl)->tri[j].data[36], x1, y1, 0);
    j++;
  }
  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
}

void nk_app_parameters(struct nk_context *ctx, int width, int height, generator_t gen_id, stl_t **stl)
{
  if (nk_group_begin(ctx, "parameters", 0)) {
    switch (gen_id) {
      case GENERATOR_GREEK_COLUMNS: nk_app_parameters_greek_columns(ctx, width, height, stl); break;
    }
    nk_group_end(ctx);
  }
  return;
}

void nk_app_viewer(struct nk_context *ctx, int width, int height, generator_t gen_id, stl_t *stl)
{
  static nk_bool is_initialized = nk_false;
  static struct nk_image stl_viewer_img = { 0 };

  if (!is_initialized) {
    stl_viewer_img = nk_image_ptr("stlviewer.glsl");
    is_initialized = nk_true;
  }
  if (nk_group_begin(ctx, "viewer", 0)) {
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
