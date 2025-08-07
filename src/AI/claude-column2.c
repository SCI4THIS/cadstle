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
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d, d2), y_bot, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d,-d2), y_bot, ROT_Z(d,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, 1.0f), 0.0f, ROT_Z(0.0f, 1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(d,-d2), y_bot, ROT_Z(d,-d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(d, d2), y_top, ROT_Z(d, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(d,-d2), y_top, ROT_Z(d,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
    assign_pt(&(*stl)->tri[j].data[12], ROT_X(0, d2), y_bot, ROT_Z(0, d2));
    assign_pt(&(*stl)->tri[j].data[24], ROT_X(0, d2), y_top, ROT_Z(0, d2));
    assign_pt(&(*stl)->tri[j].data[36], ROT_X(0,-d2), y_bot, ROT_Z(0,-d2));
  }
  j++;

  if (stl != NULL) {
    assign_pt(&(*stl)->tri[j].data[0],  ROT_X(0.0f, -1.0f), 0.0f, ROT_Z(0.0f, -1.0f));
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