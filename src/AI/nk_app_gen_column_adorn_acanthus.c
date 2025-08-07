/* Claude4

Can you make me a C function and sub-function to adorn a Corinthian column with acanthus leaves?  Attached is an example C function and sub-function of a column adorned with crosses.

Attached (claude-column2.c)

-----

Looking at your code, I can see the structure for generating 3D geometry for column adornments. I'll create a similar function for Corinthian acanthus leaves. Acanthus leaves are characterized by their deeply lobed, serrated edges and flowing, organic curves.

I've created a C function pair for generating Corinthian acanthus leaves to adorn a column. Here are the key features of this implementation:

Acanthus Leaf Characteristics:

    Deeply lobed edges: The leaf profile uses predefined lobe points that create the characteristic serrated, indented edges
    Natural curve: Leaves curve outward from the column using a sine-based curve function
    Organic shape: Multiple segments create smooth transitions between the lobes
    3D thickness: Leaves have both top and bottom surfaces with proper edge geometry

Customizable Parameters:

    Leaf Len: Length of each acanthus leaf
    Leaf Width: Maximum width of the leaves
    Thickness: How thick the leaves are (important for realistic appearance)
    Curve: How much the leaves curve outward from the column
    Lobes: Intensity of the characteristic acanthus serrations/indentations

Structure:

    nk_app_gen_column_adorn_acanthus_arg_t: Holds all the leaf parameters
    nk_app_gen_column_adorn_acanthus_sub(): Generates the geometry for a single acanthus leaf
    nk_app_gen_column_adorn_acanthus(): Main function with UI controls and coordinates the generation

The leaves are positioned around the column at a specified height and spacing, creating the classic Corinthian capital appearance. Each leaf has proper surface normals for lighting and is constructed with multiple triangular segments to achieve the flowing, organic curves characteristic of acanthus foliage.

You can adjust the number of leaves, their size, curvature, and the intensity of the lobed edges to create different variations of Corinthian ornamentation.

*/
typedef struct {
  float radius;
  float y;
  float angle;
  float leaf_length;
  float leaf_width;
  float leaf_thickness;
  float curve_depth;
  float lobe_intensity;
} nk_app_gen_column_adorn_acanthus_arg_t;

int nk_app_gen_column_adorn_acanthus_sub(struct nk_context *ctx, stl_t **stl, nk_app_gen_column_adorn_acanthus_arg_t *arg, int j)
{
  float len = arg->leaf_length;
  float width = arg->leaf_width;
  float thickness = arg->leaf_thickness;
  float curve = arg->curve_depth;
  float lobe = arg->lobe_intensity;
  float w2 = width / 2.0f;
  float t2 = thickness / 2.0f;
  
  // Define key points along the leaf length for natural curve
  float base_y = arg->y;
  float mid_y = arg->y + len * 0.6f;
  float tip_y = arg->y + len;
  
  // Leaf profile points with lobes (acanthus characteristic serrations)
  float lobe_points_x[] = {
    0.0f,           // base center
    w2 * 0.3f,      // first small lobe
    w2 * 0.8f,      // main lobe
    w2 * 1.0f,      // widest point
    w2 * 0.9f,      // taper start
    w2 * 0.6f,      // second lobe
    w2 * 0.4f,      // minor lobe
    0.0f            // tip
  };
  
  float lobe_points_z[] = {
    0.0f,           // base
    len * 0.15f,    // first lobe position
    len * 0.35f,    // main lobe
    len * 0.5f,     // widest section
    len * 0.65f,    // taper
    len * 0.8f,     // upper lobe
    len * 0.9f,     // final lobe
    len * 1.0f      // tip
  };

#define ROT_X(X,Z) ((arg->radius + X) * cosf(arg->angle) - Z * sinf(arg->angle))
#define ROT_Z(X,Z) ((arg->radius + X) * sinf(arg->angle) + Z * cosf(arg->angle))
#define CURVE_X(base_x, z_progress) (base_x * (1.0f + curve * sinf(z_progress * M_PI)))

  // Generate leaf geometry with multiple segments for organic shape
  int num_segments = 6;
  
  for (int seg = 0; seg < num_segments; seg++) {
    float t1 = (float)seg / (float)num_segments;
    float t2 = (float)(seg + 1) / (float)num_segments;
    
    // Interpolate between lobe points
    int idx1 = (int)(t1 * 6);
    int idx2 = (int)(t2 * 6);
    idx1 = (idx1 > 6) ? 6 : idx1;
    idx2 = (idx2 > 6) ? 6 : idx2;
    
    float x1_pos = lobe_points_x[idx1] * (1.0f + lobe * 0.2f * sinf(t1 * M_PI * 3));
    float x1_neg = -x1_pos;
    float z1 = base_y + lobe_points_z[idx1];
    
    float x2_pos = lobe_points_x[idx2] * (1.0f + lobe * 0.2f * sinf(t2 * M_PI * 3));
    float x2_neg = -x2_pos;
    float z2 = base_y + lobe_points_z[idx2];
    
    // Apply natural curve
    x1_pos = CURVE_X(x1_pos, t1);
    x1_neg = CURVE_X(x1_neg, t1);
    x2_pos = CURVE_X(x2_pos, t2);
    x2_neg = CURVE_X(x2_neg, t2);
    
    // Top surface of leaf (positive side)
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0.0f, 0.0f, 1.0f);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_pos, t2), z1, ROT_Z(x1_pos, t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x2_pos, t2), z2, ROT_Z(x2_pos, t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x1_neg, t2), z1, ROT_Z(x1_neg, t2));
    }
    j++;
    
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0.0f, 0.0f, 1.0f);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_neg, t2), z1, ROT_Z(x1_neg, t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x2_pos, t2), z2, ROT_Z(x2_pos, t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x2_neg, t2), z2, ROT_Z(x2_neg, t2));
    }
    j++;
    
    // Bottom surface of leaf (negative side)
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0.0f, 0.0f, -1.0f);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_pos, -t2), z1, ROT_Z(x1_pos, -t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x1_neg, -t2), z1, ROT_Z(x1_neg, -t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x2_pos, -t2), z2, ROT_Z(x2_pos, -t2));
    }
    j++;
    
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  0.0f, 0.0f, -1.0f);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_neg, -t2), z1, ROT_Z(x1_neg, -t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x2_neg, -t2), z2, ROT_Z(x2_neg, -t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x2_pos, -t2), z2, ROT_Z(x2_pos, -t2));
    }
    j++;
    
    // Side edges of leaf - positive edge
    float norm_x = x2_pos - x1_pos;
    float norm_z = z2 - z1;
    float norm_len = sqrtf(norm_x * norm_x + norm_z * norm_z);
    if (norm_len > 0.001f) {
      norm_x /= norm_len;
      norm_z /= norm_len;
    }
    
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  norm_x, 0.0f, norm_z);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_pos, t2), z1, ROT_Z(x1_pos, t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x2_pos, t2), z2, ROT_Z(x2_pos, t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x1_pos, -t2), z1, ROT_Z(x1_pos, -t2));
    }
    j++;
    
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  norm_x, 0.0f, norm_z);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_pos, -t2), z1, ROT_Z(x1_pos, -t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x2_pos, t2), z2, ROT_Z(x2_pos, t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x2_pos, -t2), z2, ROT_Z(x2_pos, -t2));
    }
    j++;
    
    // Side edges of leaf - negative edge
    norm_x = x1_neg - x2_neg;
    
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  -norm_x, 0.0f, norm_z);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_neg, t2), z1, ROT_Z(x1_neg, t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x1_neg, -t2), z1, ROT_Z(x1_neg, -t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x2_neg, t2), z2, ROT_Z(x2_neg, t2));
    }
    j++;
    
    if (stl != NULL) {
      assign_pt(&(*stl)->tri[j].data[0],  -norm_x, 0.0f, norm_z);
      assign_pt(&(*stl)->tri[j].data[12], ROT_X(x1_neg, -t2), z1, ROT_Z(x1_neg, -t2));
      assign_pt(&(*stl)->tri[j].data[24], ROT_X(x2_neg, -t2), z2, ROT_Z(x2_neg, -t2));
      assign_pt(&(*stl)->tri[j].data[36], ROT_X(x2_neg, t2), z2, ROT_Z(x2_neg, t2));
    }
    j++;
  }
  
  return j;
}

void nk_app_gen_column_adorn_acanthus(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
{
  static float    height            = 10.0f;
  static float    radius            = 1.0f;
  static int      segments          = 32;
  static int      nleaves           = 8;
  static float    mount_space       = 0.05f;
  static float    mount_height      = 2.0f;
  static nk_app_gen_column_adorn_acanthus_arg_t arg = {
    0.0f,           // radius (set dynamically)
    0.0f,           // y (set dynamically)
    0.0f,           // angle (set dynamically)
    2.5f,           // leaf_length
    0.8f,           // leaf_width
    0.08f,          // leaf_thickness
    0.3f,           // curve_depth
    0.4f,           // lobe_intensity
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

  // UI Controls
  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Height:", 0.01f, height, 10000.0f, 1.0f, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Radius:", 0.01f, radius, 100.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "Segments:", 10, segments, 256, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_INT(ctx, "Leaves:", 1, nleaves, 24, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Mt Space:", 0.0f, mount_space, 2.0f, 1.0f, 0.01f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Mt Ht:", 0.0f, mount_height, height, 1.0f, 0.1f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Leaf Len:", 0.1f, arg.leaf_length, 5.0f, 1.0f, 0.1f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Leaf Width:", 0.05f, arg.leaf_width, 2.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Thickness:", 0.01f, arg.leaf_thickness, 0.5f, 1.0f, 0.01f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Curve:", 0.0f, arg.curve_depth, 1.0f, 1.0f, 0.05f);

  nk_layout_row_dynamic(ctx, 50, 1);
  NK_PROP_FLOAT(ctx, "Lobes:", 0.0f, arg.lobe_intensity, 1.0f, 1.0f, 0.05f);

  if (is_recompute_needed == nk_false) {
    return;
  }

  mount_radius = radius + mount_space;

  // Calculate triangle count: column + leaves
  int tris_per_leaf = nk_app_gen_column_adorn_acanthus_sub(ctx, NULL, &arg, 0);
  ntris = segments * 4 + nleaves * tris_per_leaf;
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

  // Generate column cylinder
  for (int i = 0; i < segments; i++) {
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

    // Bottom cap
    assign_pt(&(*stl)->tri[j].data[0],    0, -1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12],   0, 0, 0);
    assign_pt(&(*stl)->tri[j].data[24],   x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36],   x1, 0, y1);
    j++;

    // Top cap
    assign_pt(&(*stl)->tri[j].data[0],    0, 1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12],   0, ht, 0);
    assign_pt(&(*stl)->tri[j].data[24],   x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[36],   x2, ht, y2);
    j++;

    // Side faces
    assign_pt(&(*stl)->tri[j].data[0],    n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12],   x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[24],   x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36],   x2, ht, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0],    n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12],   x1, ht, y1);
    assign_pt(&(*stl)->tri[j].data[24],   x1, 0, y1);
    assign_pt(&(*stl)->tri[j].data[36],   x2, 0, y2);
    j++;
  }

  // Generate acanthus leaves
  for (int i = 0; i < nleaves; i++) {
    arg.angle = (2.0f * M_PI * (float)i) / (float)nleaves;
    arg.radius = mount_radius;
    arg.y = mount_height;
    j = nk_app_gen_column_adorn_acanthus_sub(ctx, stl, &arg, j);
  }

  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
  is_recompute_needed = nk_false;
}