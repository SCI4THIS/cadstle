let draw_quad = function(arg)
{
  arg.gl.drawArrays(arg.gl.TRIANGLE_STRIP, 0, 4);
}

let draw = function(name, x, y, w, h)
{
  if (this.prog[name] == undefined) {
    console.error("draw called with unknown: " + name);
    return;
  }

  this.gl.activeTexture(this.gl.TEXTURE0);
  this.gl.bindTexture(this.gl.TEXTURE_2D, this.noise_tex);

  this.m.vbo.set(0, 0, x);
  this.m.vbo.set(1, 0, y);

  this.m.vbo.set(0, 1, x + w);
  this.m.vbo.set(1, 1, y);

  this.m.vbo.set(0, 2, x);
  this.m.vbo.set(1, 2, y + h);

  this.m.vbo.set(0, 3, x + w);
  this.m.vbo.set(1, 3, y + h);

  this.vbo.reload();

  this.prag[name].vars.t[1] = (Date.now() % 100000) / 100000.0;

  this.prag[name].run(this.prog[name], draw_quad, { gl: this.gl })
  this.g.nuklear.queue_display();
}

function create_prag_title_text(gl, caM_data, vbo)
{
  return this.g.Prag({
    gl: gl,
    vars: {
      coord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 0 ],
      texCoord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 2 * 4 ],
      caM: [ 'uniformMatrix4fv', false, caM_data ],
      tex: [ 'uniform1i', 0 ],
      t: [ 'uniform1f', 0 ],
    },
    vbo: {
      coord: vbo,
      texCoord: vbo
    }
  });
}

function create_prog_title_text(gl)
{
  let options = {
    gl: gl,
    src: { },
    location_fx: {
      coord: 'getAttribLocation',
      texCoord: 'getAttribLocation',
      caM: 'getUniformLocation',
      t: 'getUniformLocation',
    },
    enable_fx: {
      coord: 'enableVertexAttribArray',
      texCoord: 'enableVertexAttribArray',
    }
  }
  options.src[gl.VERTEX_SHADER] = `
precision highp float;
attribute vec2  coord;
attribute vec2  texCoord;
varying   vec2  st;
uniform   mat4  caM;

void main() {
  st = texCoord;
  gl_Position = caM * vec4(coord.x, coord.y, 0.0, 1.0);
}
`;

  options.src[gl.FRAGMENT_SHADER] = `
precision highp float;
uniform sampler2D tex;
uniform  float  t;
varying vec2 st;
void main() {
  vec4 n = texture2D(tex, vec2(fract(st.x + t), st.y));
  float intensity = (n[0] + n[1] + n[2] + n[3] + 0.03125) * 1.5;
  vec3 color = mix(vec3(0.0,0.0,0.8),vec3(0.8,0.8,0.8), intensity);
  gl_FragColor = vec4(color, 1.0);
}
`;
  return this.g.Program(options);
}

function create_prog_cloud(gl)
{
  let options = {
    gl: gl,
    src: { },
    location_fx: {
      coord: 'getAttribLocation',
      texCoord: 'getAttribLocation',
      caM: 'getUniformLocation',
      t: 'getUniformLocation',
    },
    enable_fx: {
      coord: 'enableVertexAttribArray',
      texCoord: 'enableVertexAttribArray',
    }
  }
  options.src[gl.VERTEX_SHADER] = `
precision highp float;
attribute vec2  coord;
attribute vec2  texCoord;
varying   vec2  st;
uniform   mat4  caM;

void main() {
  st = texCoord;
  gl_Position = caM * vec4(coord.x, coord.y, 0.0, 1.0);
}
`;

  options.src[gl.FRAGMENT_SHADER] = `
precision highp float;
uniform sampler2D tex;
uniform  float  t;
varying vec2 st;
void main() {
  vec4 n = texture2D(tex, vec2(fract(st.x + t), st.y));
  float intensity = (n[0] + n[1] + n[2] + n[3] + 0.03125) * 1.5;
  vec3 color = mix(vec3(0.0,0.0,0.8),vec3(0.8,0.8,0.8), intensity);
  gl_FragColor = vec4(color, 1.0);
}
`;
  return this.g.Program(options);
}

function create_prog_stlviewer(gl)
{
  let options = {
    gl: gl,
    src: { },
    location_fx: {
      coord: 'getAttribLocation',
      texCoord: 'getAttribLocation',
      caM: 'getUniformLocation',
      t: 'getUniformLocation',
    },
    enable_fx: {
      coord: 'enableVertexAttribArray',
      texCoord: 'enableVertexAttribArray',
    }
  }
  options.src[gl.VERTEX_SHADER] = `
precision highp float;
attribute vec2  coord;
attribute vec2  texCoord;
varying   vec2  st;
uniform   mat4  caM;

void main() {
  st = texCoord;
  gl_Position = caM * vec4(coord.x, coord.y, 0.0, 1.0);
}
`;

  options.src[gl.FRAGMENT_SHADER] = `
precision highp float;
uniform sampler2D tex;
uniform  float  t;
varying vec2 st;
void main() {
  vec4 n = texture2D(tex, vec2(fract(st.x + t), st.y));
  float intensity = (n[0] + n[1] + n[2] + n[3] + 0.03125) * 1.5;
  vec3 color = mix(vec3(0.0,0.0,0.8),vec3(0.8,0.8,0.8), intensity);
  gl_FragColor = vec4(0.6, 0.6, 0.6, 1.0);
}
`;
  return this.g.Program(options);
}

function create_prag_stlviewer(gl, caM_data, vbo)
{
  return this.g.Prag({
    gl: gl,
    vars: {
      coord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 0 ],
      texCoord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 2 * 4 ],
      caM: [ 'uniformMatrix4fv', false, caM_data ],
      tex: [ 'uniform1i', 0 ],
      t: [ 'uniform1f', 0 ],
    },
    vbo: {
      coord: vbo,
      texCoord: vbo
    }
  });
}

function create_prag_cloud(gl, caM_data, vbo)
{
  return this.g.Prag({
    gl: gl,
    vars: {
      coord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 0 ],
      texCoord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 2 * 4 ],
      caM: [ 'uniformMatrix4fv', false, caM_data ],
      tex: [ 'uniform1i', 0 ],
      t: [ 'uniform1f', 0 ],
    },
    vbo: {
      coord: vbo,
      texCoord: vbo
    }
  });
}

function build_noise_texture()
{
  let gl = this.gl;
  const wd = 128;
  const ht = 128;
  let texture = gl.createTexture();
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texParameterf(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.REPEAT);
  gl.texParameterf(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.REPEAT);
  gl.texParameterf(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
  gl.texParameterf(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  let noise_data = new Uint8Array(g.memory.buffer, this.noise_data_offset, wd * ht * 4);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, wd, ht, 0, gl.RGBA, gl.UNSIGNED_BYTE, noise_data);
  this.noise_tex = texture;
}

let init = function()
{
  this.gl = this.g.gl.gl;

  this.m["caM"] = this.g.matrix(Float32Array, 4, 4);
  this.m["caM"].identity();

  this.prog["clouds.glsl"] = this.create_prog_cloud(this.gl);
  this.m.vbo              = this.g.Matrix(Float32Array, 4, 4, [ 0, 0, 0, 0,
                                                                1, 0, 1, 0,
                                                                0, 1, 0, 1,
                                                                1, 1, 1, 1 ]);
  this.vbo                = this.g.VBO({gl: this.gl, m: this.m.vbo});
  this.prag["clouds.glsl"] = this.create_prag_cloud(this.gl, this.m.caM._data, this.vbo);
  this.g.nuklear.wasm.instance.exports.make3DNoiseTexture();
  this.prog["title_text.glsl"] = this.create_prog_title_text(this.gl);
  this.prag["title_text.glsl"] = this.create_prag_title_text(this.gl, this.m.caM._data, this.vbo);
  this.prog["stlviewer.glsl"] = this.create_prog_stlviewer(this.gl);
  this.prag["stlviewer.glsl"] = this.create_prag_stlviewer(this.gl, this.m.caM._data, this.vbo);
  this.noise_data_offset = this.g.nuklear.wasm.instance.exports.get_Noise3DTexPtr();
  this.build_noise_texture();
}

function resize({width, height})
{
  this.m.caM.set(0, 0, 2 / width);
  this.m.caM.set(1, 1, -2 / height);
  this.m.caM.set(0, 3, -1.0);
  this.m.caM.set(1, 3, 1.0);
}

let shader = function(g)
{
  return {
    init: init,
    resize: resize,
    g: g,
    draw: draw,
    create_prog_cloud: create_prog_cloud,
    create_prag_cloud: create_prag_cloud,
    create_prog_title_text: create_prog_title_text,
    create_prag_title_text: create_prag_title_text,
    create_prog_stlviewer: create_prog_stlviewer,
    create_prag_stlviewer: create_prag_stlviewer,
    build_noise_texture: build_noise_texture,
    prog: { },
    prag: { },
    m: { },
  };
}

module.exports.shader = shader;
