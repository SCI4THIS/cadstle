let resize = function ({width, height}) {
  let el = document.getElementById(this.id);
  el.width = width;
  el.height = height;
  this.width = width;
  this.height = height;
  this.gl.viewport(0,0,width,height);
  this.publish("resize", {width, height})
  this.display();
}

let display = function()
{
  let gl = this.gl
  gl.clearColor(this.bg[0], this.bg[1], this.bg[2], 0);
  gl.clear(gl.COLOR_BUFFER_BIT + gl.DEPTH_BUFFER_BIT);
  this.publish("display", gl);
}

let init = function()
{
  let options = { alpha: true };
  let el      = document.getElementById(this.id);
  let gl_ctx;
  try { gl_ctx = el.getContext("webgl2", options) } catch (e) { }
  //try { gl_ctx = el.getContext("webgl", options) } catch (e) { }
  //try { gl_ctx = gl_ctx || canvas.getContext("experimental-webgl", options); } catch(e) { }
  if (gl_ctx == null) {
    console.log("couldn't create GL instance");
    return;
  }
  this.gl = gl_ctx;
  this.gl.blendFuncSeparate(this.gl.SRC_ALPHA, this.gl.ONE_MINUS_SRC_ALPHA, 0, 1);
  this.publish("init", this.gl);
  this.resize({ width: window.innerWidth, height: window.innerHeight});
}


let subscribe = function(object, tag)
{
  this.fxs.push({ object, tag });
}

let publish = function(tag, args)
{
  for (let i=0; i<this.fxs.length; i++) {
    if (this.fxs[i].tag == tag) {
      this.fxs[i].object[tag](args);
    }
  }
}

let bgcolor_set = function(hex6)
{
  let m = hex6.match(/^#([0-9a-fA-F]{6})$/i)[1];
  if (m) {
    this.bg[0] = parseInt(m.substr(0,2),16);
    this.bg[1] = parseInt(m.substr(2,2),16);
    this.bg[2] = parseInt(m.substr(4,2),16);
  }
}

let gl = function(id)
{
  return {
    id: id,
    init: init,
    resize: resize,
    display: display,
    subscribe: subscribe,
    publish: publish,
    width: 240,
    height: 120,
    bg: [ 11.0/255.0, 95.0/255.0, 164.0/255.0 ],
    bgcolor_set: bgcolor_set,
    fxs: [ ],
  };
}

module.exports.gl = gl;
