xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 64;
 6.54111;34.12696;-29.84015;,
 3.69892;34.12696;-29.84015;,
 3.69892;67.20496;-29.84015;,
 6.54111;67.20496;-29.84015;,
 6.54111;34.12696;29.84015;,
 6.54111;34.12696;-29.84015;,
 6.54111;67.20496;-29.84015;,
 6.54111;67.20496;29.84015;,
 6.54111;67.20496;-29.84015;,
 3.69892;67.20496;-29.84015;,
 3.69892;67.20496;29.84015;,
 6.54111;67.20496;29.84015;,
 6.54111;67.20496;29.84015;,
 3.69892;67.20496;29.84015;,
 3.69892;34.12696;29.84015;,
 6.54111;34.12696;29.84015;,
 6.54111;34.12696;29.84015;,
 3.69892;34.12696;29.84015;,
 3.69892;34.12696;-29.84015;,
 6.54111;34.12696;-29.84015;,
 3.69892;34.12696;-29.84015;,
 3.69892;34.12696;29.84015;,
 3.69892;67.20496;29.84015;,
 3.69892;67.20496;-29.84015;,
 -2.53841;0.08193;2.57145;,
 0.01652;0.08193;3.62974;,
 0.01652;67.18847;3.62973;,
 -2.53841;67.18847;2.57145;,
 0.01652;0.08193;3.62974;,
 2.57145;0.08193;2.57145;,
 2.57145;67.18847;2.57145;,
 0.01652;67.18847;3.62973;,
 2.57145;0.08193;2.57145;,
 3.62973;0.08193;0.01652;,
 3.62973;67.18847;0.01652;,
 2.57145;67.18847;2.57145;,
 3.62973;0.08193;0.01652;,
 2.57145;0.08193;-2.53840;,
 2.57145;67.18847;-2.53841;,
 3.62973;67.18847;0.01652;,
 2.57145;0.08193;-2.53840;,
 0.01652;0.08193;-3.59669;,
 0.01652;67.18847;-3.59669;,
 2.57145;67.18847;-2.53841;,
 0.01652;0.08193;-3.59669;,
 -2.53841;0.08193;-2.53840;,
 -2.53841;67.18847;-2.53841;,
 0.01652;67.18847;-3.59669;,
 -2.53841;0.08193;-2.53840;,
 -3.59669;0.08193;0.01652;,
 -3.59669;67.18847;0.01652;,
 -2.53841;67.18847;-2.53841;,
 -3.59669;0.08193;0.01652;,
 -2.53841;0.08193;2.57145;,
 -2.53841;67.18847;2.57145;,
 -3.59669;67.18847;0.01652;,
 3.62973;67.18847;0.01652;,
 2.57145;67.18847;-2.53841;,
 2.57145;67.18847;2.57145;,
 0.01652;67.18847;-3.59669;,
 0.01652;67.18847;3.62973;,
 -2.53841;67.18847;-2.53841;,
 -2.53841;67.18847;2.57145;,
 -3.59669;67.18847;0.01652;;
 
 20;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 3;56,57,58;,
 3;57,59,58;,
 3;58,59,60;,
 3;59,61,60;,
 3;60,61,62;,
 3;61,63,62;;
 
 MeshMaterialList {
  1;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  0.707107;0.000000;0.707106;,
  1.000000;-0.000000;-0.000000;,
  0.707107;-0.000000;-0.707106;,
  0.000000;-0.000000;-1.000000;,
  -0.707107;-0.000000;-0.707106;,
  -1.000000;-0.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  20;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;5,4,4,5;,
  4;4,6,6,4;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,5,5,11;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;;
 }
 MeshTextureCoords {
  64;
  0.501511;0.999191;,
  0.999854;0.999191;,
  0.999854;0.500948;,
  0.501511;0.500948;,
  0.002285;0.499196;,
  0.499092;0.499196;,
  0.499092;0.005083;,
  0.002285;0.005083;,
  0.501476;0.998411;,
  1.000663;0.998411;,
  1.000663;0.500845;,
  0.501476;0.500845;,
  0.500966;1.000672;,
  0.999864;1.000672;,
  0.999864;0.502696;,
  0.500966;0.502696;,
  0.500456;0.999765;,
  1.001384;0.999765;,
  1.001384;0.500356;,
  0.500456;0.500356;,
  0.500951;0.999189;,
  1.000281;0.999189;,
  1.000281;0.500081;,
  0.500951;0.500081;,
  0.504300;0.488904;,
  0.999594;0.488904;,
  0.999594;0.003509;,
  0.504300;0.003509;,
  0.506686;0.485161;,
  0.998432;0.485161;,
  0.998432;0.003509;,
  0.506686;0.003509;,
  0.505583;0.489315;,
  0.996241;0.489315;,
  0.996241;0.002634;,
  0.505583;0.002634;,
  0.506653;0.485962;,
  0.993957;0.485962;,
  0.993957;0.004311;,
  0.506653;0.004311;,
  0.506046;0.485962;,
  0.993351;0.485962;,
  0.993351;0.002634;,
  0.506046;0.002634;,
  0.503762;0.487639;,
  0.994420;0.487639;,
  0.994420;0.000958;,
  0.503762;0.000958;,
  0.509862;0.482609;,
  0.992137;0.482609;,
  0.992137;0.005988;,
  0.509862;0.005988;,
  0.510932;0.490992;,
  0.996560;0.490992;,
  0.996560;0.004311;,
  0.510932;0.004311;,
  0.511976;0.072269;,
  0.512471;0.485501;,
  0.512471;0.006108;,
  0.882840;0.491109;,
  0.882840;0.003853;,
  0.993326;0.485501;,
  0.993326;0.006108;,
  0.993820;0.072269;;
 }
}
