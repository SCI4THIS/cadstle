#include <string.h>
#include <stdbool.h>

#define NAV_WIDTH (300)

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

#define NK_IMPLEMENTATION
#include "nuklear.h"

typedef struct nk_glfont_st {
  float width;
} *nk_glfont_t;

extern float nk_glfont_width_calc_js(float height, const char *text, int len);

float nk_glfont_width_calc(nk_handle handle, float height, const char *text, int len)
{
  float wd;
  unsigned char buf[4];
  unsigned char buf2[4];
  int i;
  float test_val;
  //struct nk_glfont_st glfont;
  //memcpy(&glfont, handle.ptr, sizeof(glfont));
  //test_val = (float)len * (1.8) * 10.657f;
  float char_width = 1.2 * height;
  float spacing = 0.0f;
  if (len > 1) {
    spacing = 0.5 * (len - 1) * char_width;
  }
  return len * char_width - spacing;
  //wd = nk_glfont_width_calc_js(height, text, len);
  return wd;

  /*
  memcpy(buf, &wd, 8);
  for (i=0; i<8; i++) {
    buf2[i] = buf[7-i];
  }
  memcpy(&wd, buf2, 8);
  printf("wd: %x %x %x %x %x %x %x %x, %f\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], wd);
  */
  test_val = (float)len * (1.8) * 10.657f;
  if (wd != test_val) {
    memcpy(buf, &wd, 4);
    memcpy(buf2, &test_val, 4);
    printf("mismatch! %x %x %x %x != %x %x %x %x\n", buf[0], buf[1], buf[2], buf[3], buf2[0], buf2[1], buf2[2], buf2[3]);
    return test_val;
  }
  return wd;
}

struct nk_user_font * alloc_nk_glfont(float height, float width)
{
  struct nk_user_font *font = malloc(sizeof(struct nk_user_font) + sizeof(struct nk_glfont_st));
  struct nk_glfont_st glfont;
  font->userdata.ptr = font + sizeof(struct nk_user_font);
  font->height = height;
  font->width = nk_glfont_width_calc;
  glfont.width = width;
  memcpy(font->userdata.ptr, &glfont, sizeof(glfont));
  return font;
}

extern void nk_wasm_command_scissor(short x, short y, unsigned short w, unsigned short h);

extern void nk_wasm_command_line(unsigned short line_thickness, short x0, short y0, short x1, short y1, const struct nk_color *color);

extern void nk_wasm_command_curve(const struct nk_command_curve *q);

extern void nk_wasm_command_rect(unsigned short rounding, unsigned short line_thickness, short x, short y, unsigned short w, unsigned short h, const struct nk_color *color);

extern void nk_wasm_command_rect_filled(unsigned short rounding, short x, short y, unsigned short w, unsigned short h, const struct nk_color *color);

extern void nk_wasm_command_rect_multi_color(short x, short y, unsigned short w, unsigned short h, const struct nk_color *left, const struct nk_color *top, const struct nk_color *bottom, const struct nk_color *right);

extern void nk_wasm_command_circle(const struct nk_command_circle *c);

/*
    short x, y;
    unsigned short w, h;
    struct nk_color color;
*/
extern void nk_wasm_command_circle_filled(short x, short y, unsigned short w, unsigned short h, const struct nk_color *color);

extern void nk_wasm_command_arc(const struct nk_command_arc *c);
extern void nk_wasm_command_arc_filled(const struct nk_command_arc_filled *c);
extern void nk_wasm_command_triangle(const struct nk_command_triangle *t);

/*
    struct nk_vec2i a; //struct nk_vec2i {short x, y;};
    struct nk_vec2i b;
    struct nk_vec2i c;
    struct nk_color color;
*/
extern void nk_wasm_command_triangle_filled(short x0, short y0, short x1, short y1, short x2, short y2, const struct nk_color *color);

extern void nk_wasm_command_polygon(const struct nk_command_polygon *p);
extern void nk_wasm_command_polygon_filled(const struct nk_command_polygon_filled *p);
extern void nk_wasm_command_polyline(const struct nk_command_polyline *p);

/*
    const struct nk_user_font *font;
    struct nk_color background;
    struct nk_color foreground;
    short x, y;
    unsigned short w, h;
    float height;
    int length;
    char string[1];
*/
extern void nk_wasm_command_text(const struct nk_user_font *font, const struct nk_color *background, const struct nk_color *foreground, short x, short y, unsigned short w, unsigned short h, float height, int length, const char *string);

extern void nk_wasm_command_image(short x, short y, short w, short h, const struct nk_image *img, const struct nk_color *col);
extern void nk_wasm_command_custom(const struct nk_command_custom *c);

nk_bool is_unique_ref_update = nk_false;
const char *unique_ref_update = NULL;

void nk_wasm_draw(struct nk_context *ctx)
{
  const struct nk_command *cmd = 0;
  int i;
  nk_foreach(cmd, ctx) {
    switch(cmd->type) {
      case NK_COMMAND_NOP: break;
      case NK_COMMAND_SCISSOR: {
          const struct nk_command_scissor *s = (const struct nk_command_scissor*)cmd;
          nk_wasm_command_scissor(s->x, s->y, s->w, s->h);
      } break;
      case NK_COMMAND_LINE: {
          const struct nk_command_line *l = (const struct nk_command_line*)cmd;
          nk_wasm_command_line(l->line_thickness, l->begin.x, l->begin.y, l->end.x, l->end.y, &l->color);
      } break;
      case NK_COMMAND_CURVE: {
          const struct nk_command_curve *q = (const struct nk_command_curve*)cmd;
          nk_wasm_command_curve(q);
      } break;
      case NK_COMMAND_RECT: {
          const struct nk_command_rect *r = (const struct nk_command_rect*)cmd;
	  nk_wasm_command_rect(r->rounding, r->line_thickness, r->x, r->y, r->w, r->h, &r->color);
      } break;
      case NK_COMMAND_RECT_FILLED: {
          const struct nk_command_rect_filled *r = (const struct nk_command_rect_filled*)cmd;
	  nk_wasm_command_rect_filled(r->rounding, r->x, r->y, r->w, r->h, &r->color);
      } break;
      case NK_COMMAND_RECT_MULTI_COLOR: {
          const struct nk_command_rect_multi_color *r = (const struct nk_command_rect_multi_color*)cmd;
           nk_wasm_command_rect_multi_color(r->x, r->y, r->w, r->h, &r->left, &r->top, &r->bottom, &r->right);
      } break;
      case NK_COMMAND_CIRCLE: {
          const struct nk_command_circle *c = (const struct nk_command_circle*)cmd;
          nk_wasm_command_circle(c);
      } break;
      case NK_COMMAND_CIRCLE_FILLED: {
          const struct nk_command_circle_filled *c = (const struct nk_command_circle_filled *)cmd;
          nk_wasm_command_circle_filled(c->x, c->y, c->w, c->h, &c->color);
      } break;
      case NK_COMMAND_ARC: {
          const struct nk_command_arc *c = (const struct nk_command_arc*)cmd;
	  nk_wasm_command_arc(c);
      } break;
      case NK_COMMAND_ARC_FILLED: {
          const struct nk_command_arc_filled *c = (const struct nk_command_arc_filled*)cmd;
	  nk_wasm_command_arc_filled(c);
      } break;
      case NK_COMMAND_TRIANGLE: {
          const struct nk_command_triangle *t = (const struct nk_command_triangle*)cmd;
          nk_wasm_command_triangle(t);
      } break;
      case NK_COMMAND_TRIANGLE_FILLED: {
          const struct nk_command_triangle_filled *t = (const struct nk_command_triangle_filled*)cmd;
          nk_wasm_command_triangle_filled(t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y, &t->color);
      } break;
      case NK_COMMAND_POLYGON: {
          const struct nk_command_polygon*p = (const struct nk_command_polygon*)cmd;
          nk_wasm_command_polygon(p);
      } break;
      case NK_COMMAND_POLYGON_FILLED: {
          const struct nk_command_polygon_filled *p = (const struct nk_command_polygon_filled*)cmd;
          nk_wasm_command_polygon_filled(p);
      } break;
      case NK_COMMAND_POLYLINE: {
          const struct nk_command_polyline *p = (const struct nk_command_polyline*)cmd;
	  nk_wasm_command_polyline(p);
      } break;
      case NK_COMMAND_TEXT: {
          const struct nk_command_text *t = (const struct nk_command_text*)cmd;
	  nk_wasm_command_text(t->font, &t->background, &t->foreground, t->x, t->y, t->w, t->h, t->height, t->length, t->string);
      } break;
      case NK_COMMAND_IMAGE: {
          const struct nk_command_image *i = (const struct nk_command_image*)cmd;
	  nk_wasm_command_image(i->x, i->y, i->w, i->h, &i->img, &i->col);
      } break;
      case NK_COMMAND_CUSTOM: {
          const struct nk_command_custom *c = (const struct nk_command_custom*)cmd;
	  nk_wasm_command_custom(c);
      } break;
      default: break;
    }
  }
  nk_clear(ctx);
}

float nk_image_w  (const struct nk_image *img) { return (float)img->w; }
float nk_image_h  (const struct nk_image *img) { return (float)img->h; }
float nk_image_rx (const struct nk_image *img) { return (float)img->region[0]; }
float nk_image_ry (const struct nk_image *img) { return (float)img->region[1]; }
float nk_image_rw (const struct nk_image *img) { return (float)img->region[2]; }
float nk_image_rh (const struct nk_image *img) { return (float)img->region[3]; }
void *nk_image_getptr(const struct nk_image *img) { return img->handle.ptr; }

float nk_color_r(const struct nk_color *color) { return (float)color->r/255.0f; }
float nk_color_g(const struct nk_color *color) { return (float)color->g/255.0f; }
float nk_color_b(const struct nk_color *color) { return (float)color->b/255.0f; }
float nk_color_a(const struct nk_color *color) { return (float)color->a/255.0f; }

void  nk_input_scroll_xy(struct nk_context *ctx, float x, float y) {
  struct nk_vec2 vec2 = { x, y };
  nk_input_scroll(ctx, vec2);
}

extern void nk_queue_display();

int nk_key_lookup(const char *s)
{
#define ENTRY(key) \
  if (strcmp(#key, s) == 0) { \
    return key; \
  }
  ENTRY(NK_KEY_BACKSPACE)
  ENTRY(NK_KEY_COPY)
  ENTRY(NK_KEY_CUT)
  ENTRY(NK_KEY_DEL)
  ENTRY(NK_KEY_DOWN)
  ENTRY(NK_KEY_ENTER)
  ENTRY(NK_KEY_LEFT)
  ENTRY(NK_KEY_PASTE)
  ENTRY(NK_KEY_RIGHT)
  ENTRY(NK_KEY_SCROLL_DOWN)
  ENTRY(NK_KEY_SCROLL_END)
  ENTRY(NK_KEY_SCROLL_START)
  ENTRY(NK_KEY_SCROLL_UP)
  ENTRY(NK_KEY_SHIFT)
  ENTRY(NK_KEY_TAB)
  ENTRY(NK_KEY_TEXT_END)
  ENTRY(NK_KEY_TEXT_LINE_END)
  ENTRY(NK_KEY_TEXT_LINE_START)
  ENTRY(NK_KEY_TEXT_REDO)
  ENTRY(NK_KEY_TEXT_START)
  ENTRY(NK_KEY_TEXT_UNDO)
  ENTRY(NK_KEY_TEXT_WORD_LEFT)
  ENTRY(NK_KEY_TEXT_WORD_RIGHT)
  ENTRY(NK_KEY_UP)
#undef ENTRY
  return 0;
}

