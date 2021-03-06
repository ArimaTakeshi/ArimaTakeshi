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
 54;
 -1.11599;0.89396;-7.84678;,
 -1.11599;2.66423;-7.84678;,
 2.09877;2.66423;-6.96095;,
 2.09877;0.89396;-6.96095;,
 -1.11599;2.66423;-7.84678;,
 -5.19626;2.66423;6.96095;,
 -1.98150;2.66423;7.84678;,
 2.09877;2.66423;-6.96095;,
 -5.19626;2.66423;6.96095;,
 -5.19626;0.89396;6.96095;,
 -1.98150;0.89396;7.84678;,
 -1.98150;2.66423;7.84678;,
 -1.11599;0.89396;-7.84678;,
 2.09877;0.89396;-6.96095;,
 -1.98150;2.66423;7.84678;,
 -1.98150;0.89396;7.84678;,
 -5.19626;0.89396;6.96095;,
 -5.19626;2.66423;6.96095;,
 -0.24717;-0.88513;-7.68547;,
 -0.24717;0.88513;-7.68547;,
 3.08576;0.88513;-7.78993;,
 3.08576;-0.88513;-7.78993;,
 -0.24717;0.88513;-7.68547;,
 0.23398;0.88513;7.66659;,
 3.56692;0.88513;7.56213;,
 3.08576;0.88513;-7.78993;,
 0.23398;0.88513;7.66659;,
 0.23398;-0.88513;7.66659;,
 3.56692;-0.88513;7.56213;,
 3.56692;0.88513;7.56213;,
 -0.24717;-0.88513;-7.68547;,
 3.08576;-0.88513;-7.78993;,
 3.56692;0.88513;7.56213;,
 3.56692;-0.88513;7.56213;,
 0.23398;-0.88513;7.66659;,
 0.23398;0.88513;7.66659;,
 -4.42792;-0.88513;-7.97646;,
 -4.42792;0.88513;-7.97646;,
 -1.10049;0.88513;-8.19472;,
 -1.10049;-0.88513;-8.19472;,
 -4.42792;0.88513;-7.97646;,
 -3.42257;0.88513;7.35020;,
 -0.09515;0.88513;7.13194;,
 -1.10049;0.88513;-8.19472;,
 -3.42257;0.88513;7.35020;,
 -3.42257;-0.88513;7.35020;,
 -0.09515;-0.88513;7.13194;,
 -0.09515;0.88513;7.13194;,
 -4.42792;-0.88513;-7.97646;,
 -1.10049;-0.88513;-8.19472;,
 -0.09515;0.88513;7.13194;,
 -0.09515;-0.88513;7.13194;,
 -3.42257;-0.88513;7.35020;,
 -3.42257;0.88513;7.35020;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;3,2,14,15;,
 4;16,17,1,0;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;21,20,32,33;,
 4;34,35,19,18;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;39,38,50,51;,
 4;52,53,37,36;;
 
 MeshMaterialList {
  1;
  18;
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
  0.265649;0.000000;-0.964070;,
  0.000000;1.000000;0.000000;,
  -0.265649;0.000000;0.964070;,
  -0.031326;0.000000;-0.999509;,
  0.031326;0.000000;0.999509;,
  -0.065454;0.000000;-0.997856;,
  0.065454;0.000000;0.997856;,
  0.000000;-1.000000;-0.000000;,
  0.964070;0.000000;0.265649;,
  -0.964070;0.000000;-0.265649;,
  0.999509;0.000000;-0.031326;,
  -0.999509;0.000000;0.031326;,
  0.997856;0.000000;-0.065454;,
  -0.997856;0.000000;0.065454;;
  18;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;12,12,12,12;,
  4;13,13,13,13;;
 }
 MeshTextureCoords {
  54;
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.592734;0.924128;,
  0.592734;0.023855;,
  0.842734;0.023855;,
  0.842734;0.924128;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.122559;0.698141;,
  0.869445;0.674241;,
  0.877441;0.924113;,
  0.130555;0.948013;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.094938;0.717756;,
  0.905048;0.717711;,
  0.905062;0.967711;,
  0.094952;0.967756;,
  0.375000;0.500000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.750000;;
 }
}
