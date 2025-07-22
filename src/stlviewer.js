function create_prag_bg(gl, caM_data, vbo)
{
  return this.g.Prag({
    gl: gl,
    vars: {
      coord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 0 ],
    },
    vbo: {
      coord: vbo,
    }
  });
}

function create_prog_bg(gl)
{
  let options = {
    gl: gl,
    src: { },
    location_fx: {
      coord: 'getAttribLocation',
    },
    enable_fx: {
      coord: 'enableVertexAttribArray',
    }
  }
  options.src[gl.VERTEX_SHADER] = `
precision highp float;
attribute vec2  coord;

void main() {
  gl_Position = vec4(coord.x, coord.y, -1.0, 1.0);
}
`;

  options.src[gl.FRAGMENT_SHADER] = `
precision highp float;
void main() {
  gl_FragColor = vec4(0.6, 0.6, 0.6, 1.0);
}
`;
  return this.g.Program(options);
}

function create_prag_stl(gl, caM_data, vbo)
{
  return this.g.Prag({
    gl: gl,
    vars: {
      norm: [ 'vertexAttribPointer', 3, gl.FLOAT, false, 6 * 4, 0 * 4],
      pos: [  'vertexAttribPointer', 3, gl.FLOAT, false, 6 * 4, 3 * 4],
      caM: [ 'uniformMatrix4fv', false, caM_data ],
    },
    vbo: {
      norm: vbo,
      pos: vbo,
    }
  });
}

function create_prog_stl(gl)
{
  let options = {
    gl: gl,
    src: { },
    location_fx: {
      norm: 'getAttribLocation',
      pos: 'getAttribLocation',
      caM: 'getUniformLocation',
    },
    enable_fx: {
      norm: 'enableVertexAttribArray',
      pos: 'enableVertexAttribArray',
    }
  }
  options.src[gl.VERTEX_SHADER] = `
precision highp float;
attribute vec3  pos;
attribute vec3  norm;
varying   vec3  norm_varying;
uniform   mat4  caM;

void main() {
  norm_varying = norm;
  gl_Position = caM * vec4(pos.x, pos.y, pos.z, 1.0);
}
`;

  options.src[gl.FRAGMENT_SHADER] = `
precision highp float;
varying vec3 norm_varying;
void main() {
  gl_FragColor = vec4(0.8, 0.8, 0.8, 1.0);
}
`;
  return this.g.Program(options);
}

let init = function()
{
  this.gl = this.g.gl.gl;

  this.m["caM"] = this.g.matrix(Float32Array, 4, 4);
  this.m["caM"].identity();

  this.m["bg"] = this.g.Matrix(Float32Array, 4, 4, [ -1, -1, 0, 0,
                                                     1, -1, 1, 0,
                                                     -1, 1, 0, 1,
                                                     1, 1, 1, 1 ]);
  this.vbo["bg"] = this.g.VBO({gl: this.gl, m: this.m["bg"]});
  this.prog["bg"] = this.create_prog_bg(this.gl);
  this.prag["bg"] = this.create_prag_bg(this.gl, this.m.caM._data, this.vbo["bg"]);

  this.cam.init();
  this.cam.glFrustum(-10, 10, -10, 10, 5, 100);
  this.cam.gluLookAt(-5, 3, -20, 0, 3, 0, 0, 1, 0);

  this.m["stl"] = this.g.matrix(Float32Array, 6, 0);
  this.vbo["stl"] = this.g.VBO({gl: this.gl, m: this.m["stl"]});
  this.prog["stl"] = this.create_prog_stl(this.gl);
  this.prag["stl"] = this.create_prag_stl(this.gl, this.cam.caM()._data, this.vbo["stl"]);
  this.arrbuf = new ArrayBuffer(4);
  this.dataview = new DataView(this.arrbuf);
}

let resize = function({width, height})
{
  if (width > height) {
    this.m.caM.set(0, 0, height / width);
    this.m.caM.set(1, 1, 1);
  } else {
    this.m.caM.set(0, 0, 1);
    this.m.caM.set(1, 1, width / height);
  }
  this.height = height;
  this.width = width;
  this.cam.resize({width, height})
}

let draw_quad = function(arg)
{
  arg.gl.drawArrays(arg.gl.TRIANGLE_STRIP, 0, 4);
}

let draw_stl = function(arg)
{
  arg.gl.drawArrays(arg.gl.TRIANGLES, 0, arg.n);
}

let draw = function(x, y, w, h)
{
  this.win_bounds[0] = x;
  this.win_bounds[1] = y;
  this.win_bounds[2] = w;
  this.win_bounds[3] = h;
  this.gl.viewport(x, this.height - h - y, w, h);
  this.vbo["bg"].reload();
  this.prag["bg"].run(this.prog["bg"], draw_quad, { gl: this.gl })

  this.prag["stl"].run(this.prog["stl"], draw_stl, { gl: this.gl, n: this.m["stl"]._m })
  this.gl.viewport(0, 0, this.width, this.height);
}

let u8a2f32 = function(arr, i)
{
  for (let j=0; j<4; j++) {
    this.dataview.setUint8(j, arr[i+(3 - j)]);
  }
  return this.dataview.getFloat32(0);
}

let set_stl = function(arr)
{
  let n = (arr.length - 84) / 50;
  if (n <= 0) {
    return;
  }
  this.m["stl"] = new g.matrix(Float32Array, 6, 3 * n);
  for (i=0; i<n; i++) {
    let norm_x = this.u8a2f32(arr, 84 + (50 * i) + 0);
    let norm_y = this.u8a2f32(arr, 84 + (50 * i) + 4);
    let norm_z = this.u8a2f32(arr, 84 + (50 * i) + 8);
    for (j=0; j<3; j++) {
      let pos_x =  this.u8a2f32(arr, 84 + (50 * i) + 12 + (12 * j) + 0);
      let pos_y =  this.u8a2f32(arr, 84 + (50 * i) + 12 + (12 * j) + 4);
      let pos_z =  this.u8a2f32(arr, 84 + (50 * i) + 12 + (12 * j) + 8);
      this.m["stl"].set(0, 3 * i + j, norm_x);
      this.m["stl"].set(1, 3 * i + j, norm_y);
      this.m["stl"].set(2, 3 * i + j, norm_z);
      this.m["stl"].set(3, 3 * i + j, pos_x);
      this.m["stl"].set(4, 3 * i + j, pos_y);
      this.m["stl"].set(5, 3 * i + j, pos_z);
    }
  }
  this.vbo["stl"].m = this.m["stl"];
  this.vbo["stl"].reload();
}

let input = function(input_arr)
{
}

let stlviewer = function(g)
{
  return {
    init: init,
    resize: resize,
    g: g,
    draw: draw,
    n: 0,
    tris: null,
    prog: { },
    prag: { },
    m: { },
    vbo: { },
    set_stl: set_stl,
    u8a2f32: u8a2f32,
    width: 0,
    height: 0,
    win_bounds: [ 0, 0, 0, 0 ],
    input: input,
    create_prag_stl: create_prag_stl,
    create_prog_stl: create_prog_stl,
    create_prag_bg: create_prag_bg,
    create_prog_bg: create_prog_bg,
    cam: g.camera(g), 
  };
}

module.exports.stlviewer = stlviewer;
