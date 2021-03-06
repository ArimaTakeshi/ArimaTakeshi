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
 28;
 -3.86996;1.06524;2.16648;,
 -3.73376;0.25952;5.74496;,
 -6.90088;1.16988;3.25756;,
 -4.82224;-0.23952;6.38756;,
 -6.97316;-0.10344;6.96384;,
 -6.64276;1.18428;-0.55268;,
 -3.70636;0.94972;-1.24552;,
 -6.42312;1.56748;-1.94944;,
 -3.54180;1.28788;-2.71740;,
 -6.47548;1.93256;-0.47960;,
 -3.19448;1.97152;-1.08044;,
 -4.12440;2.51416;2.91732;,
 -2.34928;1.75380;3.05512;,
 -4.53312;0.33600;6.64788;,
 -3.42756;0.50672;5.89976;,
 -0.46036;0.27544;0.32240;,
 -0.30224;-0.18000;2.29036;,
 -0.34220;-0.15856;-1.13588;,
 -0.28796;0.10644;-1.94520;,
 -0.17620;0.30044;-1.08660;,
 -1.54052;1.70016;1.53196;,
 -2.44068;0.45984;4.85424;,
 -0.84112;0.38388;3.15960;,
 -0.10436;0.34892;2.37904;,
 -0.20224;0.88508;0.52984;,
 -6.42100;2.31936;3.55408;,
 -6.79632;0.53520;7.23736;,
 -5.14276;1.20564;5.44628;;
 
 40;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 4;2,5,6,0;,
 4;5,7,8,6;,
 4;7,9,10,8;,
 3;9,11,10;,
 3;12,13,14;,
 4;1,0,15,16;,
 4;0,6,17,15;,
 4;6,8,18,17;,
 4;8,10,19,18;,
 3;10,20,19;,
 3;12,21,22;,
 3;16,23,1;,
 3;23,22,1;,
 3;22,21,1;,
 3;21,14,1;,
 4;15,24,23,16;,
 3;12,14,21;,
 3;22,23,12;,
 3;12,23,20;,
 3;23,24,20;,
 4;25,26,13,27;,
 3;25,27,11;,
 3;9,25,11;,
 3;10,11,12;,
 3;10,12,20;,
 3;19,20,24;,
 4;11,27,13,12;,
 4;26,4,3,13;,
 4;3,1,14,13;,
 3;18,19,17;,
 3;17,19,15;,
 3;19,24,15;,
 3;4,26,2;,
 3;26,25,2;,
 3;2,25,5;,
 3;5,25,7;,
 3;25,9,7;;
 
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
  51;
  0.162333;0.865514;0.473850;,
  -0.145939;-0.934739;-0.323983;,
  -0.048700;-0.965570;-0.255543;,
  -0.103159;-0.986720;-0.125470;,
  -0.149470;-0.953898;-0.260265;,
  -0.061012;0.980960;-0.184376;,
  0.038522;0.953399;0.299244;,
  0.375027;0.788321;0.487754;,
  0.241796;-0.958105;0.153525;,
  -0.189931;-0.979586;-0.065858;,
  -0.191966;-0.976287;-0.100061;,
  -0.217063;-0.937819;-0.270884;,
  0.233102;0.956617;-0.174779;,
  0.421166;0.833342;0.357993;,
  0.747867;-0.556011;0.362694;,
  -0.317343;-0.928430;-0.193160;,
  -0.294961;-0.955077;-0.028749;,
  -0.280126;-0.957147;-0.073474;,
  -0.283584;-0.917108;-0.280165;,
  0.406603;0.865945;-0.291229;,
  0.921358;-0.388553;0.011272;,
  0.562445;0.657445;0.501420;,
  0.562443;0.657442;0.501427;,
  0.201653;0.855261;0.477352;,
  0.123725;0.980497;0.152703;,
  0.435941;0.899942;-0.007798;,
  -0.012744;-0.914891;-0.403501;,
  0.165292;0.857017;0.488058;,
  -0.034299;0.948886;-0.313749;,
  0.206080;0.918779;-0.336714;,
  0.434257;0.834265;-0.339741;,
  0.875061;-0.382468;0.296625;,
  0.640650;-0.353925;0.681399;,
  0.422434;-0.795529;0.434376;,
  0.422500;-0.795448;0.434460;,
  0.470218;-0.743333;0.475764;,
  0.923575;-0.377344;0.067973;,
  0.586535;0.741647;0.325477;,
  0.481569;0.873798;-0.067598;,
  0.194586;-0.456495;0.868187;,
  0.367830;-0.592558;0.716642;,
  0.940957;-0.335286;-0.046722;,
  0.921123;-0.375742;0.101738;,
  0.935993;-0.345659;0.066610;,
  -0.968467;0.240823;0.063849;,
  -0.949860;0.303931;0.073425;,
  -0.941310;0.336313;0.028802;,
  -0.976906;0.213629;0.004162;,
  -0.924260;0.377849;-0.054526;,
  -0.999623;0.027237;-0.003336;,
  -0.950970;-0.306386;0.042224;;
  40;
  3;9,8,2;,
  3;8,26,2;,
  3;26,1,2;,
  4;2,3,10,9;,
  4;3,4,11,10;,
  4;28,5,12,29;,
  3;5,24,12;,
  3;13,23,7;,
  4;8,9,16,15;,
  4;9,10,17,16;,
  4;10,11,18,17;,
  4;29,12,19,30;,
  3;12,25,19;,
  3;13,21,22;,
  3;31,14,32;,
  3;14,33,8;,
  3;33,34,8;,
  3;34,35,8;,
  4;36,20,14,31;,
  3;13,7,21;,
  3;22,37,13;,
  3;13,37,25;,
  3;37,38,25;,
  4;6,0,23,27;,
  3;6,27,24;,
  3;5,6,24;,
  3;12,24,13;,
  3;12,13,25;,
  3;19,25,38;,
  4;24,27,23,13;,
  4;39,39,40,40;,
  4;40,8,35,40;,
  3;41,42,43;,
  3;43,42,36;,
  3;42,20,36;,
  3;44,45,46;,
  3;45,47,46;,
  3;46,47,48;,
  3;48,47,49;,
  3;47,50,49;;
 }
 MeshTextureCoords {
  28;
  0.742240;0.741120;,
  0.708130;0.741120;,
  0.742240;0.616120;,
  0.708130;0.693550;,
  0.708130;0.616120;,
  0.776360;0.616120;,
  0.776360;0.741120;,
  0.810480;0.616120;,
  0.810480;0.741120;,
  0.844600;0.616120;,
  0.844600;0.741120;,
  0.878710;0.705560;,
  0.878710;0.741120;,
  0.912830;0.694440;,
  0.912830;0.741120;,
  0.742240;0.866120;,
  0.708130;0.866120;,
  0.776360;0.866120;,
  0.810480;0.866120;,
  0.844600;0.866120;,
  0.878710;0.807180;,
  0.912830;0.778240;,
  0.912830;0.838410;,
  0.912830;0.866120;,
  0.878710;0.866120;,
  0.878710;0.616120;,
  0.912830;0.616120;,
  0.899990;0.664960;;
 }
}
