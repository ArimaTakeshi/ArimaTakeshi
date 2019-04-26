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
 70;
 31.15350;14.79567;-65.49839;,
 -33.71834;14.79567;-65.49839;,
 -33.71834;21.66989;-65.49839;,
 31.15350;21.66989;-65.49839;,
 -33.71834;14.79567;63.43111;,
 -33.71834;21.66989;63.43111;,
 31.15350;14.79567;63.43111;,
 31.15350;21.66989;63.43111;,
 -32.79588;0.11543;-66.47267;,
 -35.51884;0.11543;-66.47267;,
 -35.51884;40.99691;-66.47267;,
 -32.79588;40.99691;-66.47267;,
 -35.51884;0.11543;-63.74967;,
 -35.51884;40.99691;-63.74967;,
 -32.79588;0.11543;-63.74967;,
 -32.79588;40.99691;-63.74967;,
 32.69238;0.11543;-66.47267;,
 29.96942;0.11543;-66.47267;,
 29.96942;40.99691;-66.47267;,
 32.69238;40.99691;-66.47267;,
 29.96942;0.11543;-63.74967;,
 29.96942;40.99691;-63.74967;,
 32.69238;0.11543;-63.74967;,
 32.69238;40.99691;-63.74967;,
 32.69238;0.11543;61.20298;,
 29.96943;0.11543;61.20298;,
 29.96943;40.99691;61.20298;,
 32.69238;40.99691;61.20298;,
 29.96943;0.11543;63.92599;,
 29.96943;40.99691;63.92599;,
 32.69238;0.11543;63.92599;,
 32.69238;40.99691;63.92599;,
 -32.79588;0.11543;61.20298;,
 -35.51883;0.11543;61.20298;,
 -35.51883;40.99691;61.20298;,
 -32.79588;40.99691;61.20298;,
 -35.51883;0.11543;63.92599;,
 -35.51883;40.99691;63.92599;,
 -32.79588;0.11543;63.92599;,
 -32.79588;40.99691;63.92599;,
 -23.53624;23.48732;65.30003;,
 -22.31395;11.57209;66.40549;,
 14.50916;21.68283;65.32062;,
 33.74163;23.41806;60.71686;,
 35.33367;11.65936;58.69768;,
 37.79066;23.41806;26.83816;,
 29.01808;24.55442;-56.55672;,
 -34.65696;23.88222;-37.84036;,
 -36.18051;9.23099;-34.71901;,
 -34.35736;23.72242;16.31267;,
 -22.55209;21.63416;-60.27094;,
 10.39382;22.06605;-54.43251;,
 9.49247;17.55993;-54.17241;,
 -22.49242;18.08181;-59.36250;,
 10.39382;22.06605;-54.43251;,
 9.17837;22.82173;-42.74202;,
 8.27672;18.47212;-42.48389;,
 9.49247;17.55993;-54.17241;,
 9.17837;22.82173;-42.74202;,
 -22.88308;23.30905;-48.75060;,
 -22.82341;20.39701;-47.84216;,
 8.27672;18.47212;-42.48389;,
 -22.88308;23.30905;-48.75060;,
 -22.55209;21.63416;-60.27094;,
 -22.49242;18.08181;-59.36250;,
 -22.82341;20.39701;-47.84216;,
 10.39382;22.06605;-54.43251;,
 -22.55209;21.63416;-60.27094;,
 -22.49242;18.08181;-59.36250;,
 9.49247;17.55993;-54.17241;;
 
 42;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,0,3,7;,
 4;1,0,6,4;,
 4;5,7,3,2;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,14,15,13;,
 4;14,8,11,15;,
 4;9,8,14,12;,
 4;13,15,11,10;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;22,16,19,23;,
 4;17,16,22,20;,
 4;21,23,19,18;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;30,24,27,31;,
 4;25,24,30,28;,
 4;29,31,27,26;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;38,32,35,39;,
 4;33,32,38,36;,
 4;37,39,35,34;,
 3;40,41,42;,
 3;43,44,45;,
 4;43,45,46,40;,
 3;43,40,42;,
 3;47,48,49;,
 4;47,49,40,46;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;62,55,66,67;,
 4;68,69,56,65;;
 
 MeshMaterialList {
  4;
  42;
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
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.194510;0.194510;0.194510;1.000000;;
   1.000000;
   0.000000;0.000000;0.000000;;
   0.121569;0.121569;0.121569;;
  }
  Material {
   0.649412;0.643137;0.674510;1.000000;;
   1.000000;
   0.000000;0.000000;0.000000;;
   0.405882;0.401961;0.421569;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game103\\Pictures\\�l����\\si-tu.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  45;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.994492;0.104653;0.005811;,
  -0.001361;0.999984;0.005490;,
  0.986537;0.113324;0.117907;,
  0.003861;0.092773;0.995680;,
  0.014931;0.794436;0.607165;,
  0.025179;0.540460;0.840993;,
  0.023778;0.965199;0.260433;,
  0.005148;0.999966;0.006408;,
  -0.007871;0.999959;0.004572;,
  0.163718;-0.167539;-0.972177;,
  0.974673;-0.191766;0.115059;,
  -0.168633;0.192157;0.966767;,
  -0.999381;-0.025482;-0.024238;,
  0.019612;0.994519;-0.102702;,
  -0.060793;-0.989249;0.133009;;
  42;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  3;34,33,35;,
  3;32,32,32;,
  4;36,37,31,37;,
  3;36,34,35;,
  3;30,30,30;,
  4;38,38,34,31;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;;
 }
 MeshTextureCoords {
  70;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.127885;,
  0.000000;0.000000;,
  0.685284;0.000000;,
  0.912550;0.000000;,
  1.000000;0.000000;,
  1.000000;0.276428;,
  1.000000;1.000000;,
  0.142934;1.000000;,
  0.000000;1.000000;,
  0.000000;0.561984;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
