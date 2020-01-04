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
 14;
 -0.12525;-0.00831;-7.63166;,
 -1.62341;15.35853;-7.43300;,
 65.96646;53.11779;-5.97703;,
 70.59597;46.54956;-7.86970;,
 0.18191;13.97481;3.24013;,
 66.90903;52.23285;7.86970;,
 1.75016;-1.44876;2.67376;,
 71.30469;45.52923;6.04774;,
 -0.12525;-0.00831;-7.63166;,
 70.59597;46.54956;-7.86970;,
 -0.12525;-0.00831;-7.63166;,
 1.75016;-1.44876;2.67376;,
 -1.62341;15.35853;-7.43300;,
 160.24329;75.78301;-0.67383;;
 
 9;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;10,11,4,12;,
 3;3,2,13;,
 3;2,5,13;,
 3;5,7,13;,
 3;7,9,13;;
 
 MeshMaterialList {
  1;
  9;
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
   TextureFilename {
    "tree000.jpg";
   }
  }
 }
 MeshNormals {
  13;
  -0.054555;0.112424;-0.992162;,
  -0.032752;0.191818;-0.980884;,
  -0.368112;0.923182;0.110586;,
  -0.491588;0.859353;0.140903;,
  0.076912;-0.155031;0.984911;,
  0.019576;-0.132302;0.991016;,
  -0.010723;0.269887;-0.962832;,
  0.549752;-0.821627;-0.150674;,
  0.436506;-0.891780;-0.119124;,
  -0.982069;-0.101797;0.158676;,
  -0.237186;0.968325;0.078031;,
  0.133953;-0.177165;0.975023;,
  0.315081;-0.945220;-0.085342;;
  9;
  4;0,0,1,1;,
  4;3,3,2,2;,
  4;5,5,4,4;,
  4;7,7,8,8;,
  4;9,9,9,9;,
  3;1,1,6;,
  3;2,2,10;,
  3;4,4,11;,
  3;8,8,12;;
 }
 MeshTextureCoords {
  14;
  0.250000;0.769940;,
  0.375000;0.769940;,
  0.437500;0.649730;,
  0.375000;0.649730;,
  0.500000;0.769940;,
  0.500000;0.649730;,
  0.625000;0.769940;,
  0.562500;0.649730;,
  0.750000;0.769940;,
  0.625000;0.649730;,
  0.500000;1.010350;,
  0.750000;0.890150;,
  0.250000;0.890150;,
  0.500000;0.529530;;
 }
}
