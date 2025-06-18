let draw_tex_quad = function(arg)
{
  arg.gl.drawArrays(arg.gl.TRIANGLE_STRIP, 0, 4);
}

let draw_tex = function(name, x, y, w, h)
{
  if (this.lookup[name] == undefined) {
    console.error("draw_tex called with unknown: " + name);
    return;
  }
  const texture = this.lookup[name];
  this.gl.activeTexture(this.gl.TEXTURE0);
  this.gl.bindTexture(this.gl.TEXTURE_2D, texture);

  this.m.vbo.set(0, 0, x);
  this.m.vbo.set(1, 0, y);

  this.m.vbo.set(0, 1, x + w);
  this.m.vbo.set(1, 1, y);

  this.m.vbo.set(0, 2, x);
  this.m.vbo.set(1, 2, y + h);

  this.m.vbo.set(0, 3, x + w);
  this.m.vbo.set(1, 3, y + h);

  this.vbo.reload();

  this.prag.run(this.prog, draw_tex_quad, { gl: this.gl });
}

let isPowerOf2 = function(x)
{
  return (x && !(x & (x - 1)));
}

function create_prog(gl)
{
  let options = {
    gl: gl,
    src: { },
    location_fx: {
      coord: 'getAttribLocation',
      texCoord: 'getAttribLocation',
      caM: 'getUniformLocation',
      tex: 'getUniformLocation',
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
varying vec2 st;
uniform sampler2D tex;
void main() {
  gl_FragColor = texture2D(tex, st);
}
`;
  return this.g.Program(options);
}

function create_prag(gl, caM_data, vbo)
{
  return this.g.Prag({
    gl: gl,
    vars: {
      coord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 0 ],
      texCoord: [ 'vertexAttribPointer', 2, gl.FLOAT, false, 4 * 4, 2 * 4 ],
      caM: [ 'uniformMatrix4fv', false, caM_data ],
      tex: [ 'uniform1i', 0 ]
    },
    vbo: {
      coord: vbo,
      texCoord: vbo
    }
  });
}

let load_image_tex = function(name, dataurl)
{
  let texture;
  if (this.lookup[name] == undefined) {
    texture = this.gl.createTexture();
  } else {
    texture = this.lookup[name];
  }
  this.gl.bindTexture(this.gl.TEXTURE_2D, texture);

  const level = 0;
  const internalFormat = this.gl.RGBA;
  const width = 1;
  const height = 1;
  const border = 0;
  const srcFormat = this.gl.RGBA;
  const srcType = this.gl.UNSIGNED_BYTE;
  const pixel = new Uint8Array([255, 255, 255, 255]);
  this.gl.texImage2D(
    this.gl.TEXTURE_2D,
    level,
    internalFormat,
    width,
    height,
    border,
    srcFormat,
    srcType,
    pixel
  );
  const image = new Image();
  let obj = this;
  image.onload = function() {
    obj.gl.bindTexture(obj.gl.TEXTURE_2D, texture);
    obj.gl.texImage2D(
        obj.gl.TEXTURE_2D,
        level,
        internalFormat,
        srcFormat,
        srcType,
        image
    );
    if (isPowerOf2(image.width) && isPowerOf2(image.height)) {
      obj.gl.generateMipmap(obj.gl.TEXTURE_2D);
    } else {
      obj.gl.texParameteri(obj.gl.TEXTURE_2D, obj.gl.TEXTURE_WRAP_S, obj.gl.CLAMP_TO_EDGE);
      obj.gl.texParameteri(obj.gl.TEXTURE_2D, obj.gl.TEXTURE_WRAP_T, obj.gl.CLAMP_TO_EDGE);
      obj.gl.texParameteri(obj.gl.TEXTURE_2D, obj.gl.TEXTURE_MIN_FILTER, obj.gl.LINEAR);
    }
    obj.lookup_width[name] = image.width;
    obj.lookup_height[name] = image.height;
    obj.g.nuklear.queue_display()
  }
  image.src = dataurl;
  this.lookup[name] = texture;
}

let init = function()
{
  this.gl = this.g.gl.gl;

  this.m["caM"] = this.g.matrix(Float32Array, 4, 4);
  this.m["caM"].identity();

  this.prog         = this.create_prog(this.gl);
  this.m.vbo        = this.g.Matrix(Float32Array, 4, 4, [ 0, 0, 0, 0,
                                                          1, 0, 1, 0,
                                                          0, 1, 0, 1,
                                                          1, 1, 1, 1 ]);
  this.vbo          = this.g.VBO({gl: this.gl, m: this.m.vbo});

  this.prag         = this.create_prag(this.gl, this.m.caM._data, this.vbo);
}

function resize({width, height})
{
  this.m.caM.set(0, 0, 2 / width);
  this.m.caM.set(1, 1, -2 / height);
  this.m.caM.set(0, 3, -1.0);
  this.m.caM.set(1, 3, 1.0);
}

let tex = function(g)
{
  return {
    init: init,
    resize: resize,
    g: g,
    draw_tex: draw_tex,
    load_image_tex: load_image_tex,
    create_prog: create_prog,
    create_prag: create_prag,
    lookup: { },
    lookup_width: { },
    lookup_height: { },
    m: { },
  };
}

module.exports.tex = tex;
