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
 18;
 1.49755;-1.25390;2.50000;,
 1.30555;1.02250;2.50000;,
 -4.49755;-1.24750;2.50000;,
 -1.49760;1.00000;2.50000;,
 -4.49275;3.25390;2.50000;,
 1.49755;-1.25390;-2.50000;,
 -4.49755;-1.24750;-2.50000;,
 1.30555;1.02250;-2.50000;,
 -1.49760;1.00000;-2.50000;,
 -4.49275;3.25390;-2.50000;,
 1.49755;-1.25390;2.50000;,
 -4.49755;-1.24750;2.50000;,
 -4.49275;3.25390;-2.50000;,
 -4.49755;-1.24750;-2.50000;,
 -1.49760;1.00000;-2.50000;,
 -4.49275;3.25390;-2.50000;,
 1.30555;1.02250;-2.50000;,
 1.49755;-1.25390;-2.50000;;
 
 11;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;5,6,7;,
 3;7,6,8;,
 3;8,6,9;,
 4;5,10,11,6;,
 4;2,4,12,13;,
 4;14,15,4,3;,
 4;16,14,3,1;,
 4;17,16,1,0;;
 
 MeshMaterialList {
  1;
  11;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  16;
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.001068;-0.999999;0.000000;,
  -0.999999;0.001066;0.000000;,
  0.313182;0.949693;-0.000000;,
  0.601286;0.799034;-0.000000;,
  -0.008026;0.999968;0.000000;,
  0.996462;0.084045;-0.000000;;
  11;
  3;0,9,1;,
  3;9,7,1;,
  3;1,7,2;,
  3;4,5,8;,
  3;8,5,6;,
  3;6,5,3;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,13,13,12;,
  4;14,12,12,14;,
  4;15,15,15,15;;
 }
 MeshTextureCoords {
  18;
  0.375000;1.000000;,
  0.442710;0.932290;,
  0.625000;1.000000;,
  0.510410;0.864580;,
  0.645830;0.729170;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.437500;0.312500;,
  0.500000;0.375000;,
  0.624990;0.500000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.880200;0.744800;,
  0.875000;1.000000;,
  0.260400;0.864580;,
  0.395800;0.729150;,
  0.192700;0.932290;,
  0.125000;1.000000;;
 }
}
