/*
Claude4:

Can you make me a C function that makes a parametric model of composed triangles, for a Corinthian style Greek column?  Let me attach an example C function that creates a plain column.  Follow a style like that.

Attached (claude-column.c)

-----

Looking at your example code, I can see you're using a GUI framework (Nuklear) to create parametric 3D models and storing them in STL format. I'll create a Corinthian column function that follows the same pattern but adds the characteristic features of Corinthian columns: a fluted shaft, decorative base, and an ornate capital with acanthus leaves and volutes.

I've created a Corinthian column generator that follows the same style as your example. Here are the key features I've added to make it authentically Corinthian:

Key Features:

    Three-part structure: Base, fluted shaft, and ornate capital
    Fluted shaft: Configurable number of concave flutes with adjustable depth
    Corinthian capital: Features acanthus leaf variations and volute scrollwork
    Parametric controls: All major dimensions are adjustable through the GUI

GUI Parameters:

    Total height, base radius, shaft radius, capital radius
    Number of segments (affects smoothness)
    Number of flutes and flute depth
    Base height and capital height

Architectural Details:

    Base: Circular platform foundation
    Shaft: Fluted column with concave grooves running vertically
    Capital: Three-tier ornate top with:
        Acanthus leaf variations (sinusoidal radius modulation)
        Volute scrollwork (cosine variations at the top)
        Abacus (flat crown section)

The function generates significantly more triangles than the plain column due to the complex fluted geometry and ornate capital, but maintains the same memory management and STL generation pattern as your original code.

*/


void nk_app_corinthian_column(struct nk_context *ctx, int win_wd, int win_ht, stl_t **stl)
{
  static float    height            = 20.0f;
  static float    base_radius       = 2.0f;
  static float    shaft_radius      = 1.8f;
  static float    capital_radius    = 2.2f;
  static int      segments          = 32;
  static int      flutes            = 20;
  static float    flute_depth       = 0.1f;
  static float    base_height       = 1.5f;
  static float    capital_height    = 3.0f;
  uint32_t        size              = 0;
  nk_bool         is_realloc_needed = false;
  int             j                 = 0;
  float           shaft_height;

  // GUI controls
  nk_layout_row_dynamic(ctx, 40, 1);
  nk_property_float(ctx, "Total Height:", 5.0f, &height, 50.0f, 1.0f, 0.5f);

  nk_layout_row_dynamic(ctx, 40, 2);
  nk_property_float(ctx, "Base Radius:", 0.5f, &base_radius, 10.0f, 0.1f, 0.05f);
  nk_property_float(ctx, "Shaft Radius:", 0.5f, &shaft_radius, 10.0f, 0.1f, 0.05f);

  nk_layout_row_dynamic(ctx, 40, 2);
  nk_property_float(ctx, "Capital Radius:", 0.5f, &capital_radius, 10.0f, 0.1f, 0.05f);
  nk_property_int(ctx, "Segments:", 16, &segments, 64, 1, 1.0f);

  nk_layout_row_dynamic(ctx, 40, 2);
  nk_property_int(ctx, "Flutes:", 12, &flutes, 32, 1, 1.0f);
  nk_property_float(ctx, "Flute Depth:", 0.01f, &flute_depth, 0.5f, 0.01f, 0.01f);

  nk_layout_row_dynamic(ctx, 40, 2);
  nk_property_float(ctx, "Base Height:", 0.5f, &base_height, 5.0f, 0.1f, 0.1f);
  nk_property_float(ctx, "Capital Height:", 1.0f, &capital_height, 8.0f, 0.1f, 0.1f);

  shaft_height = height - base_height - capital_height;
  if (shaft_height < 1.0f) shaft_height = 1.0f;

  // Calculate required triangles
  // Base: segments*2 (top and bottom) + segments*2 (sides)
  // Shaft: flutes*segments*4 (fluted surface)
  // Capital: segments*6 (ornate capital with acanthus leaves)
  int total_triangles = segments * 4 + flutes * segments * 4 + segments * 6;
  
  size = sizeof((*stl)->h) + sizeof((*stl)->tri[0]) * total_triangles;

  if (*stl == NULL) {
    is_realloc_needed = true;
  } else {
    size_t bufsize = atof((*stl)->h.hdr);
    if (size > bufsize) {
      is_realloc_needed = true;
    }
  }

  if (is_realloc_needed) {
    *stl = realloc(*stl, size);
  }
  
  snprintf((*stl)->h.hdr, sizeof((*stl)->h.hdr), "%d", size);
  (*stl)->h.n = total_triangles;

  // Generate base (circular platform)
  for (int i = 0; i < segments; i++) {
    float delta = (1.0f / (float)segments);
    float theta = 2 * M_PI * i * delta;
    float theta_2 = 2 * M_PI * (i + 1) * delta;
    float x1 = base_radius * cosf(theta);
    float x2 = base_radius * cosf(theta_2);
    float y1 = base_radius * sinf(theta);
    float y2 = base_radius * sinf(theta_2);

    // Base bottom
    assign_pt(&(*stl)->tri[j].data[0], 0, -1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, 0, 0);
    assign_pt(&(*stl)->tri[j].data[24], x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36], x1, 0, y1);
    j++;

    // Base top
    assign_pt(&(*stl)->tri[j].data[0], 0, 1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, base_height, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1, base_height, y1);
    assign_pt(&(*stl)->tri[j].data[36], x2, base_height, y2);
    j++;

    // Base sides (2 triangles per segment)
    float n_x = cosf((theta + theta_2) / 2.0f);
    float n_y = sinf((theta + theta_2) / 2.0f);
    
    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1, base_height, y1);
    assign_pt(&(*stl)->tri[j].data[24], x2, 0, y2);
    assign_pt(&(*stl)->tri[j].data[36], x2, base_height, y2);
    j++;

    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1, base_height, y1);
    assign_pt(&(*stl)->tri[j].data[24], x1, 0, y1);
    assign_pt(&(*stl)->tri[j].data[36], x2, 0, y2);
    j++;
  }

  // Generate fluted shaft
  float shaft_start = base_height;
  float shaft_end = base_height + shaft_height;
  
  for (int f = 0; f < flutes; f++) {
    float flute_angle_start = (2 * M_PI * f) / flutes;
    float flute_angle_end = (2 * M_PI * (f + 1)) / flutes;
    float flute_angle_mid = (flute_angle_start + flute_angle_end) / 2.0f;
    
    for (int i = 0; i < segments; i++) {
      float h1 = shaft_start + (shaft_height * i) / segments;
      float h2 = shaft_start + (shaft_height * (i + 1)) / segments;
      
      // Flute geometry - create concave surface
      float r_edge = shaft_radius;
      float r_center = shaft_radius - flute_depth;
      
      float x1_start = r_edge * cosf(flute_angle_start);
      float y1_start = r_edge * sinf(flute_angle_start);
      float x1_mid = r_center * cosf(flute_angle_mid);
      float y1_mid = r_center * sinf(flute_angle_mid);
      float x1_end = r_edge * cosf(flute_angle_end);
      float y1_end = r_edge * sinf(flute_angle_end);
      
      // Normal for flute surface
      float n_x = cosf(flute_angle_mid);
      float n_y = sinf(flute_angle_mid);
      
      // Flute triangles (4 per segment per flute)
      // Triangle 1: start-mid-start_next
      assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
      assign_pt(&(*stl)->tri[j].data[12], x1_start, h1, y1_start);
      assign_pt(&(*stl)->tri[j].data[24], x1_mid, h1, y1_mid);
      assign_pt(&(*stl)->tri[j].data[36], x1_start, h2, y1_start);
      j++;
      
      // Triangle 2: mid-mid_next-start_next
      assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
      assign_pt(&(*stl)->tri[j].data[12], x1_mid, h1, y1_mid);
      assign_pt(&(*stl)->tri[j].data[24], x1_mid, h2, y1_mid);
      assign_pt(&(*stl)->tri[j].data[36], x1_start, h2, y1_start);
      j++;
      
      // Triangle 3: mid-end-mid_next
      assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
      assign_pt(&(*stl)->tri[j].data[12], x1_mid, h1, y1_mid);
      assign_pt(&(*stl)->tri[j].data[24], x1_end, h1, y1_end);
      assign_pt(&(*stl)->tri[j].data[36], x1_mid, h2, y1_mid);
      j++;
      
      // Triangle 4: end-end_next-mid_next
      assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
      assign_pt(&(*stl)->tri[j].data[12], x1_end, h1, y1_end);
      assign_pt(&(*stl)->tri[j].data[24], x1_end, h2, y1_end);
      assign_pt(&(*stl)->tri[j].data[36], x1_mid, h2, y1_mid);
      j++;
    }
  }

  // Generate Corinthian capital with acanthus leaves
  float capital_start = shaft_end;
  float capital_end = height;
  
  for (int i = 0; i < segments; i++) {
    float delta = (1.0f / (float)segments);
    float theta = 2 * M_PI * i * delta;
    float theta_2 = 2 * M_PI * (i + 1) * delta;
    
    // Create ornate capital with varying radius for acanthus leaf effect
    float leaf_variation = 0.3f * sinf(8 * theta); // 8 leaves around
    float scroll_variation = 0.2f * cosf(4 * theta); // 4 volutes
    
    float r1_base = capital_radius + leaf_variation;
    float r2_base = capital_radius + leaf_variation * cosf(theta_2 - theta);
    float r1_top = capital_radius * 1.1f + scroll_variation;
    float r2_top = capital_radius * 1.1f + scroll_variation * cosf(theta_2 - theta);
    
    float x1_base = r1_base * cosf(theta);
    float x2_base = r2_base * cosf(theta_2);
    float y1_base = r1_base * sinf(theta);
    float y2_base = r2_base * sinf(theta_2);
    
    float x1_top = r1_top * cosf(theta);
    float x2_top = r2_top * cosf(theta_2);
    float y1_top = r1_top * sinf(theta);
    float y2_top = r2_top * sinf(theta_2);
    
    float n_x = cosf((theta + theta_2) / 2.0f);
    float n_y = sinf((theta + theta_2) / 2.0f);
    
    // Capital base connection to shaft
    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], shaft_radius * cosf(theta), capital_start, shaft_radius * sinf(theta));
    assign_pt(&(*stl)->tri[j].data[24], x1_base, capital_start + capital_height * 0.2f, y1_base);
    assign_pt(&(*stl)->tri[j].data[36], x2_base, capital_start + capital_height * 0.2f, y2_base);
    j++;
    
    // Capital middle (acanthus leaves)
    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1_base, capital_start + capital_height * 0.2f, y1_base);
    assign_pt(&(*stl)->tri[j].data[24], x1_base, capital_start + capital_height * 0.6f, y1_base);
    assign_pt(&(*stl)->tri[j].data[36], x2_base, capital_start + capital_height * 0.6f, y2_base);
    j++;
    
    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1_base, capital_start + capital_height * 0.2f, y1_base);
    assign_pt(&(*stl)->tri[j].data[24], x2_base, capital_start + capital_height * 0.2f, y2_base);
    assign_pt(&(*stl)->tri[j].data[36], x2_base, capital_start + capital_height * 0.6f, y2_base);
    j++;
    
    // Capital top (volutes and abacus)
    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1_base, capital_start + capital_height * 0.6f, y1_base);
    assign_pt(&(*stl)->tri[j].data[24], x1_top, capital_start + capital_height * 0.9f, y1_top);
    assign_pt(&(*stl)->tri[j].data[36], x2_top, capital_start + capital_height * 0.9f, y2_top);
    j++;
    
    assign_pt(&(*stl)->tri[j].data[0], n_x, 0, n_y);
    assign_pt(&(*stl)->tri[j].data[12], x1_base, capital_start + capital_height * 0.6f, y1_base);
    assign_pt(&(*stl)->tri[j].data[24], x2_base, capital_start + capital_height * 0.6f, y2_base);
    assign_pt(&(*stl)->tri[j].data[36], x2_top, capital_start + capital_height * 0.9f, y2_top);
    j++;
    
    // Capital crown/abacus (top flat section)
    assign_pt(&(*stl)->tri[j].data[0], 0, 1.0f, 0);
    assign_pt(&(*stl)->tri[j].data[12], 0, capital_end, 0);
    assign_pt(&(*stl)->tri[j].data[24], x1_top, capital_end, y1_top);
    assign_pt(&(*stl)->tri[j].data[36], x2_top, capital_end, y2_top);
    j++;
  }

  cadstle_set_stl_gl(*stl, sizeof((*stl)->h) + (*stl)->h.n * sizeof((*stl)->tri[0]));
}