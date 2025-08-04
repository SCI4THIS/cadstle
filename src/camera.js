let init = function()
{
  for (let i=0; i<this.keys.length; i++) {
    let key = this.keys[i];
    this.m[key] = g.matrix(Float32Array, 4, 4);
    this.m[key].identity();
  }
  this.m['translate'] = g.matrix(Float32Array, 4, 4);
  this.m['rotate'] = g.matrix(Float32Array, 4, 4);
  this.m['tmp'] = g.matrix(Float32Array, 4, 4);
  this.m['caM'] = g.matrix(Float32Array, 4, 4);
}

let resize = function({width,height})
{
  this.aspectRatio = width / height;
  if (width > height) {
    this.m['aspect'].set(0, 0, height / width);
    this.m['aspect'].set(1, 1, 1);
  } else {
    this.m['aspect'].set(0, 0, 1);
    this.m['aspect'].set(1, 1, width / height);
  }
  this.glhPerspectivef2_helper();
}

let caM = function()
{
  let is_recompute_needed = false;
  let keys = [ 'perspective', 'modelview', 'aspect' ];
  for (let i=0; i<this.keys.length; i++) {
    let key = this.keys[i];
    if (this.versions[key] != this.m[key].version) {
      is_recompute_needed = true;
      this.versions[key] = this.m[key].version;
    }
  }
  console.log({is_recompute_needed})
  if (is_recompute_needed) {
  //  this.m['tmp'].mul(this.m['modelview'], this.m['perspective']);
    this.m['tmp'].mul(this.m['perspective'], this.m['modelview']);
    this.m['caM'].mul(this.m['aspect'], this.m['tmp']);
  }
  return this.m['caM']
}

let glhFrustumf2 = function(left, right, bottom, top, znear, zfar)
{
  let temp = 2.0 * znear;
  let temp2 = right - left;
  let temp3 = top - bottom;
  let temp4 = zfar - znear;

  this.m['perspective'].set(0, temp / temp2);
  this.m['perspective'].set(1, 0);
  this.m['perspective'].set(2, 0);
  this.m['perspective'].set(3, 0);

  this.m['perspective'].set(4, 0);
  this.m['perspective'].set(5, temp / temp3);
  this.m['perspective'].set(6, 0);
  this.m['perspective'].set(7, 0);

  this.m['perspective'].set(8, 0);
  this.m['perspective'].set(9, (right + left) / temp2);
  this.m['perspective'].set(10, (top + bottom) / temp3);
  this.m['perspective'].set(11, (-zfar - znear) / temp4);

  this.m['perspective'].set(12, 0);
  this.m['perspective'].set(13, 0);
  this.m['perspective'].set(14, (-temp * zfar) / temp4);
  this.m['perspective'].set(15, 0);
}

let glhPerspectivef2 = function(fovyInDegrees, aspectRatio, znear, zfar)
{
  let ymax = znear * Math.tan(fovyInDegrees * (Math.PI / 360.0));
  let xmax = ymax * aspectRatio;
  //this.glhFrustumf2(-xmax, xmax, -ymax, ymax, znear, zfar)
  this.glFrustum(-xmax, xmax, -ymax, ymax, znear, zfar)
}

let glFrustum = function(left, right, bottom, top, znear, zfar)
{
  let A = (right + left) / (right - left);
  let B = (top + bottom) / (top - bottom);
  let C = - (zfar + znear) / (zfar - znear);
  let D = - (2 * zfar * znear) / (zfar - znear);

  this.m['perspective'].set(0, 0, 2 * znear / (right - left));
  this.m['perspective'].set(0, 1, 0);
  this.m['perspective'].set(0, 2, A);
  this.m['perspective'].set(0, 3, 0);

  this.m['perspective'].set(1, 0, 0);
  this.m['perspective'].set(1, 1, 2 * znear / (top - bottom));
  this.m['perspective'].set(1, 2, B);
  this.m['perspective'].set(1, 3, 0);

  this.m['perspective'].set(2, 0, 0);
  this.m['perspective'].set(2, 1, 0);
  this.m['perspective'].set(2, 2, C);
  this.m['perspective'].set(2, 3, D);

  this.m['perspective'].set(3, 0, 0);
  this.m['perspective'].set(3, 1, 0);
  this.m['perspective'].set(3, 2, -1);
  this.m['perspective'].set(3, 3, 0);
}

let gluLookAt = function(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
{
  this.m['translate'].set(0, 0, 1);
  this.m['translate'].set(0, 1, 0);
  this.m['translate'].set(0, 2, 0);
  this.m['translate'].set(0, 3, -eyeX);

  this.m['translate'].set(1, 0, 0);
  this.m['translate'].set(1, 1, 1);
  this.m['translate'].set(1, 2, 0);
  this.m['translate'].set(1, 3, -eyeY);

  this.m['translate'].set(2, 0, 0);
  this.m['translate'].set(2, 1, 0);
  this.m['translate'].set(2, 2, 1);
  this.m['translate'].set(2, 3, -eyeZ);

  this.m['translate'].set(3, 0, 0);
  this.m['translate'].set(3, 1, 0);
  this.m['translate'].set(3, 2, 0);
  this.m['translate'].set(3, 3, 1);

  let Fx = eyeX - centerX;
  let Fy = eyeY - centerY;
  let Fz = eyeZ - centerZ;

  let Fmag = Math.sqrt(Fx * Fx + Fy * Fy + Fz * Fz);
  let fx = Fx / Fmag;
  let fy = Fy / Fmag;
  let fz = Fz / Fmag;

  // l = up x f
  let Lx = upY * fz - upZ * fy;
  let Ly = upZ * fx - upX * fz;
  let Lz = upX * fy - upY * fx;

  let Lmag = Math.sqrt(Lx * Lx + Ly * Ly + Lz * Lz);
  let lx = Lx / Lmag;
  let ly = Ly / Lmag;
  let lz = Lz / Lmag;

  // u = f x l
  let ux = fy * lz - fz * ly;
  let uy = fz * lx - fx * lz;
  let uz = fx * ly - fy * lx;

  this.m['rotate'].set(0, 0, lx);
  this.m['rotate'].set(0, 1, ly);
  this.m['rotate'].set(0, 2, lz);
  this.m['rotate'].set(0, 3, 0);

  this.m['rotate'].set(1, 0, ux);
  this.m['rotate'].set(1, 1, uy);
  this.m['rotate'].set(1, 2, uz);
  this.m['rotate'].set(1, 3, 0);

  this.m['rotate'].set(2, 0, fx);
  this.m['rotate'].set(2, 1, fy);
  this.m['rotate'].set(2, 2, fz);
  this.m['rotate'].set(2, 3, 0);
  /*
  this.m['rotate'].set(0, 0, lx);
  this.m['rotate'].set(0, 1, ux);
  this.m['rotate'].set(0, 2, -fx);
  this.m['rotate'].set(0, 3, 0);

  this.m['rotate'].set(1, 0, ly);
  this.m['rotate'].set(1, 1, uy);
  this.m['rotate'].set(1, 2, -fy);
  this.m['rotate'].set(1, 3, 0);

  this.m['rotate'].set(2, 0, lz);
  this.m['rotate'].set(2, 1, uy);
  this.m['rotate'].set(2, 2, -fz);
  this.m['rotate'].set(2, 3, 0);
  */

  this.m['rotate'].set(3, 0, 0);
  this.m['rotate'].set(3, 1, 0);
  this.m['rotate'].set(3, 2, 0);
  this.m['rotate'].set(3, 3, 1);

  this.m['modelview'].mul(this.m['rotate'], this.m['translate']);
}

let set_xyz = function(obj, x, y, z)
{
  obj.x = x;
  obj.y = y;
  obj.z = z;
}

let set_pos = function(x,y,z)
{
  set_xyz(this.pos, x, y, z);
}

let set_center = function(x,y,z)
{
  set_xyz(this.center, x, y, z);
}

let set_up = function(x,y,z)
{
  set_xyz(this.up, x, y, z);
}

let gluLookAt_helper = function()
{
  this.gluLookAt(this.pos.x, this.pos.y, this.pos.z,
                 this.center.x, this.center.y, this.center.z,
                 this.up.x, this.up.y, this.up.z);

}

let glhPerspectivef2_helper = function()
{
  this.glhPerspectivef2(this.fovyInDegrees, 1, this.znear, this.zfar)
}

let magnitude = function (x, y, z)
{
  return Math.sqrt(x*x + y*y + z*z)
}

let rot = function(dx, dy)
{
  let x = this.pos.x;
  let y = this.pos.y;
  let z = this.pos.z;
  let dtheta = dx * this.fovyInDegrees * Math.PI / 180.0;
  let dphi = dy * this.fovyInDegrees * Math.PI / 180.0;
  this.pos.x = Math.cos(dtheta) * x - Math.sin(dtheta) * z;
  this.pos.z = Math.sin(dtheta) * x + Math.cos(dtheta) * z;
  let mag = Math.sqrt(x * x + z * z);
  this.pos.y = Math.cos(dphi) * y - Math.sin(dphi) * mag;
  let mag2 = Math.sin(dphi) * y + Math.cos(dphi) * mag;
  this.pos.x = this.pos.x * (mag2 / mag);
  this.pos.y = this.pos.y * (mag2 / mag);
  this.gluLookAt_helper();
  this.caM();
}

let camera = function(g)
{
  return {
    init: init,
    resize: resize,
    keys: [ 'perspective', 'modelview', 'aspect' ],
    m: { },
    versions: { },
    glFrustum: glFrustum,
    gluLookAt: gluLookAt,
    gluLookAt_helper: gluLookAt_helper,
    set_pos: set_pos,
    set_center: set_center,
    set_up: set_up,
    fovyInDegrees: 60,
    zfar: 50,
    znear: 5,
    aspectRatio: 1,
    pos: { x: -5, y: 3, z: -20 },
    center: { x: 0, y: 3, z: 0 },
    up: { x: 0, y: 1, z: 0 },
    caM: caM,
    rot: rot,
    g: g,
    glhPerspectivef2: glhPerspectivef2,
    glhPerspectivef2_helper: glhPerspectivef2_helper,
    glhFrustumf2: glhFrustumf2,
  };
}

module.exports.camera = camera;
