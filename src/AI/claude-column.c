void nk_app_column(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
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
  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
}