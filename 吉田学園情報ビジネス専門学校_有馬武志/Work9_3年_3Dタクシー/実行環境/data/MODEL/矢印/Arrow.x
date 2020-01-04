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
 60;
 -7.90595;0.06840;38.90404;,
 -5.60996;4.60807;38.76216;,
 -3.14920;1.33764;-39.73091;,
 -4.48232;-0.06840;-39.58902;,
 -0.06780;6.48846;38.90405;,
 0.06874;1.92005;-39.58901;,
 5.47401;4.60807;39.24653;,
 3.28648;1.33764;-39.24653;,
 7.76916;0.06840;39.58903;,
 4.61911;-0.06840;-38.90401;,
 3.20657;-4.47127;39.73090;,
 3.28599;-1.47444;-38.76214;,
 -0.01138;-6.35167;39.58903;,
 0.06805;-2.05684;-38.90401;,
 -3.22911;-4.47127;39.24653;,
 -3.14969;-1.47444;-39.24653;,
 -7.90595;0.06840;38.90404;,
 -4.48232;-0.06840;-39.58902;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 -0.06840;0.06840;39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.06840;-0.06840;-39.24653;,
 0.00000;-5.65311;-22.55995;,
 0.00000;-0.92959;-57.14647;,
 12.18764;-4.07680;-22.86056;,
 0.00000;-0.92959;-57.14647;,
 17.23591;-0.27125;-23.58630;,
 0.00000;-0.92959;-57.14647;,
 12.18764;3.53430;-24.31201;,
 0.00000;-0.92959;-57.14647;,
 -0.00000;5.11060;-24.61258;,
 0.00000;-0.92959;-57.14647;,
 -12.18764;3.53430;-24.31201;,
 0.00000;-0.92959;-57.14647;,
 -17.23591;-0.27125;-23.58631;,
 0.00000;-0.92959;-57.14647;,
 -12.18764;-4.07680;-22.86058;,
 0.00000;-0.92959;-57.14647;,
 0.00000;-5.65311;-22.55995;,
 0.00000;-0.27125;-23.58630;,
 0.00000;-5.65311;-22.55995;,
 12.18764;-4.07680;-22.86056;,
 17.23591;-0.27125;-23.58630;,
 12.18764;3.53430;-24.31201;,
 -0.00000;5.11060;-24.61258;,
 -12.18764;3.53430;-24.31201;,
 -17.23591;-0.27125;-23.58631;,
 -12.18764;-4.07680;-22.86058;;
 
 40;
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
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;42,43,44;,
 3;44,45,46;,
 3;46,47,48;,
 3;48,49,50;,
 3;51,52,53;,
 3;51,53,54;,
 3;51,54,55;,
 3;51,55,56;,
 3;51,56,57;,
 3;51,57,58;,
 3;51,58,59;,
 3;51,59,52;;
 
 MeshMaterialList {
  1;
  40;
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
  49;
  -0.051440;0.052894;0.997274;,
  -0.818186;0.573112;-0.045982;,
  -0.568501;0.821051;-0.051793;,
  0.003050;0.998553;-0.053684;,
  0.572409;0.818377;-0.051058;,
  0.820163;0.570503;-0.043110;,
  0.544344;-0.838078;-0.036254;,
  0.003024;-0.998919;-0.046396;,
  -0.538332;-0.841911;-0.037213;,
  0.073969;-0.169296;-0.982786;,
  0.714396;-0.699216;-0.027108;,
  -0.708599;-0.705006;-0.029207;,
  -0.043598;0.053226;0.997630;,
  -0.043620;0.041807;0.998173;,
  -0.043597;0.053224;0.997630;,
  -0.043595;0.053225;0.997630;,
  -0.043568;0.064061;0.996994;,
  -0.059059;0.063687;0.996221;,
  -0.074950;0.052458;0.995807;,
  -0.059500;0.041425;0.997368;,
  0.073965;-0.169297;-0.982786;,
  0.073969;-0.169294;-0.982786;,
  0.073969;-0.169285;-0.982788;,
  0.073968;-0.169291;-0.982786;,
  0.073971;-0.169300;-0.982785;,
  0.073971;-0.169302;-0.982784;,
  0.073971;-0.169302;-0.982785;,
  0.073967;-0.169296;-0.982786;,
  0.000000;-0.990803;-0.135315;,
  0.350040;-0.913290;-0.208263;,
  0.554697;-0.787219;-0.269440;,
  0.379139;0.887648;-0.261408;,
  -0.000000;0.983199;-0.182539;,
  -0.379139;0.887648;-0.261407;,
  -0.598977;0.733171;-0.322006;,
  -0.350040;-0.913290;-0.208263;,
  0.000000;-0.974972;-0.222328;,
  -0.000000;0.187324;0.982298;,
  0.598977;0.733170;-0.322006;,
  0.000000;0.959268;-0.282499;,
  -0.554697;-0.787219;-0.269440;,
  -0.000001;0.187328;0.982297;,
  -0.000000;0.187329;0.982297;,
  0.000000;0.187325;0.982298;,
  0.000001;0.187320;0.982299;,
  -0.000000;0.187318;0.982299;,
  -0.000001;0.187319;0.982299;,
  -0.000001;0.187323;0.982298;,
  -0.000001;0.187327;0.982298;;
  40;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;10,6,6,10;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,11,11,8;,
  3;0,12,13;,
  3;0,14,12;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,18,17;,
  3;0,19,18;,
  3;0,13,19;,
  3;9,20,21;,
  3;9,21,22;,
  3;9,22,23;,
  3;9,23,24;,
  3;9,24,25;,
  3;9,25,26;,
  3;9,26,27;,
  3;9,27,20;,
  3;28,36,29;,
  3;29,36,30;,
  3;38,39,31;,
  3;31,39,32;,
  3;32,39,33;,
  3;33,39,34;,
  3;40,36,35;,
  3;35,36,28;,
  3;37,41,42;,
  3;37,42,43;,
  3;37,43,44;,
  3;37,44,45;,
  3;37,45,46;,
  3;37,46,47;,
  3;37,47,48;,
  3;37,48,41;;
 }
 MeshTextureCoords {
  60;
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
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
