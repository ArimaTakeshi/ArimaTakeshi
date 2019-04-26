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
 24;
 -5.20680;-0.08825;-5.43645;,
 -5.20680;-0.08825;5.43645;,
 5.20680;-0.08825;5.43645;,
 5.20680;-0.08825;-5.43645;,
 5.20680;-0.20560;5.55380;,
 -5.20680;-0.20560;5.55380;,
 -5.20680;-7.79440;5.55380;,
 5.20680;-7.79440;5.55380;,
 -5.32415;-7.79440;5.43645;,
 -5.32415;-0.20560;5.43645;,
 -5.32415;-0.20560;-5.43645;,
 -5.32415;-7.79440;-5.43645;,
 5.32415;-0.20560;-5.43645;,
 5.32415;-0.20560;5.43645;,
 5.32415;-7.79440;5.43645;,
 5.32415;-7.79440;-5.43645;,
 5.20680;-7.91175;-5.43645;,
 5.20680;-7.91175;5.43645;,
 -5.20680;-7.91175;5.43645;,
 -5.20680;-7.91175;-5.43645;,
 5.20680;-7.79440;-5.55380;,
 -5.20680;-7.79440;-5.55380;,
 -5.20680;-0.20560;-5.55380;,
 5.20680;-0.20560;-5.55380;;
 
 26;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;1,0,10,9;,
 4;5,4,2,1;,
 4;9,8,6,5;,
 4;13,12,3,2;,
 4;4,7,14,13;,
 4;17,16,15,14;,
 4;7,6,18,17;,
 4;8,11,19,18;,
 4;21,20,16,19;,
 4;11,10,22,21;,
 4;0,3,23,22;,
 4;12,15,20,23;,
 3;9,5,1;,
 3;2,4,13;,
 3;14,7,17;,
 3;18,6,8;,
 3;19,11,21;,
 3;22,10,0;,
 3;23,3,12;,
 3;15,16,20;;
 
 MeshMaterialList {
  1;
  26;
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
  24;
  -0.854763;0.367001;0.367001;,
  -0.367001;0.854764;0.367001;,
  -0.367001;0.367001;0.854763;,
  0.367001;0.854764;0.367001;,
  0.854763;0.367001;0.367001;,
  0.367001;0.367001;0.854763;,
  0.854763;-0.367002;0.367001;,
  0.367000;-0.854764;0.367000;,
  0.367001;-0.367002;0.854763;,
  -0.367000;-0.854764;0.367000;,
  -0.854763;-0.367002;0.367001;,
  -0.367001;-0.367002;0.854763;,
  -0.367000;-0.854764;-0.367000;,
  -0.367001;-0.367002;-0.854763;,
  -0.854763;-0.367002;-0.367001;,
  -0.367001;0.367001;-0.854763;,
  -0.367001;0.854764;-0.367001;,
  -0.854763;0.367001;-0.367001;,
  0.367001;0.367001;-0.854763;,
  0.854763;0.367001;-0.367001;,
  0.367001;0.854764;-0.367001;,
  0.854763;-0.367002;-0.367001;,
  0.367001;-0.367002;-0.854763;,
  0.367000;-0.854764;-0.367000;;
  26;
  4;16,1,3,20;,
  4;5,2,11,8;,
  4;10,0,17,14;,
  4;19,4,6,21;,
  4;23,7,9,12;,
  4;22,13,15,18;,
  4;1,16,17,0;,
  4;2,5,3,1;,
  4;0,10,11,2;,
  4;4,19,20,3;,
  4;5,8,6,4;,
  4;7,23,21,6;,
  4;8,11,9,7;,
  4;10,14,12,9;,
  4;13,22,23,12;,
  4;14,17,15,13;,
  4;16,20,18,15;,
  4;19,21,22,18;,
  3;0,2,1;,
  3;3,5,4;,
  3;6,8,7;,
  3;9,11,10;,
  3;12,14,13;,
  3;15,17,16;,
  3;18,20,19;,
  3;21,23,22;;
 }
 MeshTextureCoords {
  24;
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;;
 }
}
