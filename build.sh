#!/bin/bash

mkdir -p tar-staging

for file in "prag.js" "vbo.js" "matrix.js" "nuklear.wasm" "sys.js" "gl.js" "program.js" "glf.js" "nuklear.js" "handler.js" "tex.js" "IntelOneMono-Regular.glf.js" "shader.js" "stlviewer.js"
do
  cp src/${file} tar-staging/${file}
done

tar -czvf src/manifest.tar.gzip -C tar-staging/ .

rm -f manifest.tar.gzip.part-*
split -a 4 -b 1m -d src/manifest.tar.gzip manifest.tar.gzip.part-

cp tarballjs/tarball.js src/tarball.js

FIRST=1
for FILE in `ls manifest.tar.gzip.part-* | sort`
do
  echo ${FILE}
  if [ $FIRST -eq 1 ];
  then
    echo "\"data:application/gzip;base64,`base64 --wrap=0 ${FILE}`\"" > manifest.tar.gzip.b64
    FIRST=0
  else
    echo "," >> manifest.tar.gzip.b64
    echo "\"data:application/gzip;base64,`base64 --wrap=0 ${FILE}`\"" >> manifest.tar.gzip.b64
  fi

done

echo "data:application/wasm;base64,`base64 --wrap=0 zlib-wasm/zlibaux.wasm`" > zlibaux.wasm.b64
gzip -f zlibaux.wasm.b64
echo "\"data:application/gzip;base64,`base64 --wrap=0 zlibaux.wasm.b64.gz`\"" > zlibaux.wasm.b64.gz.b64

sed -f amalgamate_tarballjs.sed src/index.html > tmp1.js
sed -f amalgamate_manifest.tar.gzip.sed tmp1.js > tmp2.js
sed -f amalgamate_zlibaux.sed tmp2.js > tmp3.js
sed s/is_staging\:\ true/is_staging\:\ false/g tmp3.js > tmp4.js

mv tmp4.js index.html
rm tmp3.js
rm tmp2.js
rm tmp1.js
rm manifest.tar.gzip.b64
rm manifest.tar.gzip.part-*
rm src/manifest.tar.gzip
rm zlibaux.wasm.b64
rm zlibaux.wasm.b64.gz.b64
