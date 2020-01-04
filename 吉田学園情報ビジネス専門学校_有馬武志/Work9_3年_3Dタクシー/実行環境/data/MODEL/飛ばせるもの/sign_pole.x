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
 102;
 0.00000;68.26797;-10.00000;,
 7.07107;68.26797;-7.07107;,
 7.07107;6.20766;-7.07107;,
 0.00000;6.20766;-10.00000;,
 10.00000;68.26797;0.00000;,
 10.00000;6.20766;0.00000;,
 7.07107;68.26797;7.07107;,
 7.07107;6.20766;7.07107;,
 -0.00000;68.26797;10.00000;,
 -0.00000;6.20766;10.00000;,
 -7.07107;68.26797;7.07107;,
 -7.07107;6.20766;7.07107;,
 -10.00000;68.26797;-0.00000;,
 -10.00000;6.20766;-0.00000;,
 -7.07107;68.26797;-7.07107;,
 -7.07107;6.20766;-7.07107;,
 0.00000;68.26797;-10.00000;,
 0.00000;6.20766;-10.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;68.26797;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;6.20766;0.00000;,
 0.00000;7.04694;-14.52000;,
 9.33381;7.04694;-10.26719;,
 9.33381;0.00000;-10.26719;,
 0.00000;0.00000;-14.52000;,
 13.20000;7.04694;0.00000;,
 13.20000;0.00000;0.00000;,
 9.33381;7.04694;10.26719;,
 9.33381;0.00000;10.26719;,
 -0.00000;7.04694;14.52000;,
 -0.00000;0.00000;14.52000;,
 -9.33381;7.04694;10.26719;,
 -9.33381;0.00000;10.26719;,
 -13.20000;7.04694;-0.00000;,
 -13.20000;0.00000;-0.00000;,
 -9.33381;7.04694;-10.26719;,
 -9.33381;0.00000;-10.26719;,
 0.00000;7.04694;-14.52000;,
 0.00000;0.00000;-14.52000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;7.04694;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;74.27697;-11.34000;,
 8.01859;74.27697;-8.01859;,
 8.01859;67.23003;-8.01859;,
 0.00000;67.23003;-11.34000;,
 11.34000;74.27697;0.00000;,
 11.34000;67.23003;0.00000;,
 8.01859;74.27697;8.01859;,
 8.01859;67.23003;8.01859;,
 -0.00000;74.27697;11.34000;,
 -0.00000;67.23003;11.34000;,
 -8.01859;74.27697;8.01859;,
 -8.01859;67.23003;8.01859;,
 -11.34000;74.27697;-0.00000;,
 -11.34000;67.23003;-0.00000;,
 -8.01859;74.27697;-8.01859;,
 -8.01859;67.23003;-8.01859;,
 0.00000;74.27697;-11.34000;,
 0.00000;67.23003;-11.34000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;74.27697;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;,
 0.00000;67.23003;0.00000;;
 
 72;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 3;86,69,68;,
 3;87,72,69;,
 3;88,74,72;,
 3;89,76,74;,
 3;90,78,76;,
 3;91,80,78;,
 3;92,82,80;,
 3;93,84,82;,
 3;94,71,70;,
 3;95,70,73;,
 3;96,73,75;,
 3;97,75,77;,
 3;98,77,79;,
 3;99,79,81;,
 3;100,81,83;,
 3;101,83,85;;
 
 MeshMaterialList {
  2;
  72;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/modeltex/sign_pole.jpg";
   }
  }
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.730528;0.000000;-0.682882;,
  1.000000;0.000000;0.000000;,
  0.730528;0.000000;0.682882;,
  -0.000000;0.000000;1.000000;,
  -0.730528;0.000000;0.682882;,
  -1.000000;0.000000;-0.000000;,
  -0.730528;0.000000;-0.682882;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;;
  72;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,10,10,17;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,4,4,20;,
  4;4,21,21,4;,
  4;21,6,6,21;,
  4;6,22,22,6;,
  4;22,23,23,22;,
  4;23,18,18,23;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
