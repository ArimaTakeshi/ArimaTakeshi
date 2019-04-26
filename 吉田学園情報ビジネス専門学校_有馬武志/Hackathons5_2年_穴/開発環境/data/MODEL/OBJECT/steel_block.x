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
 126;
 -23.76940;64.38325;-17.38250;,
 -22.14335;75.48680;-7.35845;,
 0.95540;84.50105;-21.08935;,
 -0.67065;73.39835;-31.11425;,
 -22.14335;75.48680;-7.35845;,
 52.19255;-2.23040;66.66380;,
 75.29130;6.78385;52.93205;,
 0.95540;84.50105;-21.08935;,
 52.19255;-2.23040;66.66380;,
 50.56650;-13.33395;56.63890;,
 73.66525;-4.31885;42.90715;,
 75.29130;6.78385;52.93205;,
 -23.76940;64.38325;-17.38250;,
 -0.67065;73.39835;-31.11425;,
 75.29130;6.78385;52.93205;,
 73.66525;-4.31885;42.90715;,
 50.56650;-13.33395;56.63890;,
 52.19255;-2.23040;66.66380;,
 -2.10120;-7.52335;-65.32675;,
 -2.10120;7.52335;-65.32675;,
 26.22930;7.52335;-66.21415;,
 26.22930;-7.52335;-66.21415;,
 -2.10120;7.52335;-65.32675;,
 1.98900;7.52335;65.16610;,
 30.31865;7.52335;64.27785;,
 26.22930;7.52335;-66.21415;,
 1.98900;7.52335;65.16610;,
 1.98900;-7.52335;65.16610;,
 30.31865;-7.52335;64.27785;,
 30.31865;7.52335;64.27785;,
 -2.10120;-7.52335;-65.32675;,
 26.22930;-7.52335;-66.21415;,
 30.31865;7.52335;64.27785;,
 30.31865;-7.52335;64.27785;,
 1.98900;-7.52335;65.16610;,
 1.98900;7.52335;65.16610;,
 -63.09550;-0.93160;36.89170;,
 -65.79765;13.87030;36.79480;,
 -73.62530;12.26380;9.60075;,
 -70.92315;-2.53895;9.69765;,
 -65.79765;13.87030;36.79480;,
 57.47105;36.13605;-0.00340;,
 49.64255;34.52955;-27.19745;,
 -73.62530;12.26380;9.60075;,
 57.47105;36.13605;-0.00340;,
 60.17320;21.33415;0.09265;,
 52.34555;19.72680;-27.10140;,
 49.64255;34.52955;-27.19745;,
 -63.09550;-0.93160;36.89170;,
 -70.92315;-2.53895;9.69765;,
 49.64255;34.52955;-27.19745;,
 52.34555;19.72680;-27.10140;,
 60.17320;21.33415;0.09265;,
 57.47105;36.13605;-0.00340;,
 -70.14880;-2.35450;-32.19970;,
 -72.85180;12.44740;-32.29575;,
 -71.60910;12.48990;-60.61265;,
 -68.90695;-2.31285;-60.51575;,
 -72.85180;12.44740;-32.29575;,
 55.45400;35.91080;-26.63220;,
 56.69670;35.95245;-54.94825;,
 -71.60910;12.48990;-60.61265;,
 55.45400;35.91080;-26.63220;,
 58.15700;21.10805;-26.53530;,
 59.39970;21.14970;-54.85220;,
 56.69670;35.95245;-54.94825;,
 -70.14880;-2.35450;-32.19970;,
 -68.90695;-2.31285;-60.51575;,
 56.69670;35.95245;-54.94825;,
 59.39970;21.14970;-54.85220;,
 58.15700;21.10805;-26.53530;,
 55.45400;35.91080;-26.63220;,
 -1.64985;27.30455;-45.19365;,
 -4.20325;42.09200;-44.08695;,
 19.48965;45.03980;-28.81160;,
 22.04305;30.25150;-29.91830;,
 -4.20325;42.09200;-44.08695;,
 -72.35200;22.13060;65.46785;,
 -48.65910;25.07755;80.74320;,
 19.48965;45.03980;-28.81160;,
 -72.35200;22.13060;65.46785;,
 -69.79860;7.34230;64.36115;,
 -46.10570;10.29010;79.63650;,
 -48.65910;25.07755;80.74320;,
 -1.64985;27.30455;-45.19365;,
 22.04305;30.25150;-29.91830;,
 -48.65910;25.07755;80.74320;,
 -46.10570;10.29010;79.63650;,
 -69.79860;7.34230;64.36115;,
 -72.35200;22.13060;65.46785;,
 -12.26125;107.32950;6.47700;,
 -24.96535;112.53575;0.31790;,
 -38.69285;107.84545;24.66785;,
 -25.98960;102.63920;30.82695;,
 -24.96535;112.53575;0.31790;,
 -54.92870;-8.03760;-39.79700;,
 -68.65620;-12.72790;-15.44705;,
 -38.69285;107.84545;24.66785;,
 -54.92870;-8.03760;-39.79700;,
 -42.22545;-13.24385;-33.63790;,
 -55.95295;-17.93415;-9.28795;,
 -68.65620;-12.72790;-15.44705;,
 -12.26125;107.32950;6.47700;,
 -25.98960;102.63920;30.82695;,
 -68.65620;-12.72790;-15.44705;,
 -55.95295;-17.93415;-9.28795;,
 -42.22545;-13.24385;-33.63790;,
 -54.92870;-8.03760;-39.79700;,
 -16.75010;81.43255;-19.05020;,
 -16.72375;92.73415;-9.11540;,
 11.61950;92.71375;-9.16555;,
 11.59400;81.41215;-19.10035;,
 -16.72375;92.73415;-9.11540;,
 -16.61325;6.53310;88.93805;,
 11.73085;6.51270;88.88790;,
 11.61950;92.71375;-9.16555;,
 -16.61325;6.53310;88.93805;,
 -16.63875;-4.76765;79.00325;,
 11.70535;-4.78805;78.95310;,
 11.73085;6.51270;88.88790;,
 -16.75010;81.43255;-19.05020;,
 11.59400;81.41215;-19.10035;,
 11.73085;6.51270;88.88790;,
 11.70535;-4.78805;78.95310;,
 -16.63875;-4.76765;79.00325;,
 -16.61325;6.53310;88.93805;;
 
 42;
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
 4;52,53,37,36;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;57,56,68,69;,
 4;70,71,55,54;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;81,84,85,82;,
 4;75,74,86,87;,
 4;88,89,73,72;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;99,102,103,100;,
 4;93,92,104,105;,
 4;106,107,91,90;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;117,120,121,118;,
 4;111,110,122,123;,
 4;124,125,109,108;;
 
 MeshMaterialList {
  1;
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
  42;
  -0.569365;0.595281;-0.566978;,
  0.108071;0.737897;0.666205;,
  0.569370;-0.595290;0.566963;,
  -0.031308;0.000000;-0.999510;,
  0.000000;1.000000;0.000000;,
  0.031339;0.000000;0.999509;,
  -0.944184;-0.170515;0.281854;,
  -0.179602;0.983718;-0.006413;,
  0.944172;0.170556;-0.281868;,
  -0.982762;-0.179713;-0.043382;,
  -0.179607;0.983718;-0.006421;,
  0.982757;0.179736;0.043394;,
  0.521984;0.152930;-0.839134;,
  -0.169660;0.982756;0.073529;,
  -0.521984;-0.152929;0.839134;,
  0.229505;0.923529;0.307280;,
  -0.844252;0.345981;-0.409311;,
  -0.229512;-0.923528;-0.307280;,
  -0.000854;0.660231;-0.751062;,
  0.001709;0.751040;0.660255;,
  0.000854;-0.660259;0.751037;,
  -0.108062;-0.737891;-0.666212;,
  0.814945;0.318072;-0.484454;,
  -0.814942;-0.318048;0.484474;,
  0.000000;-1.000000;-0.000000;,
  0.999509;0.000000;-0.031323;,
  -0.999509;0.000000;0.031329;,
  0.179610;-0.983717;0.006444;,
  -0.276178;-0.056675;-0.959434;,
  0.276178;0.056671;0.959434;,
  0.179602;-0.983718;0.006432;,
  0.043829;0.001491;-0.999038;,
  -0.043829;-0.001492;0.999038;,
  0.169660;-0.982756;-0.073529;,
  0.835907;0.104002;0.538927;,
  -0.835907;-0.104002;-0.538928;,
  0.844245;-0.345986;0.409321;,
  -0.484338;-0.165460;0.859093;,
  0.484326;0.165463;-0.859099;,
  -0.001709;-0.751043;-0.660251;,
  0.999998;-0.000710;-0.001759;,
  -0.999998;0.000733;0.001776;;
  42;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;;
 }
 MeshTextureCoords {
  126;
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.592730;0.924130;,
  0.592730;0.023850;,
  0.842730;0.023850;,
  0.842730;0.924130;,
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
  0.122560;0.698140;,
  0.869450;0.674240;,
  0.877440;0.924110;,
  0.130560;0.948010;,
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
  0.094940;0.717760;,
  0.905050;0.717710;,
  0.905060;0.967710;,
  0.094950;0.967760;,
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
  0.094940;0.717760;,
  0.905050;0.717710;,
  0.905060;0.967710;,
  0.094950;0.967760;,
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
  0.592730;0.924130;,
  0.592730;0.023850;,
  0.842730;0.023850;,
  0.842730;0.924130;,
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
  0.592730;0.924130;,
  0.592730;0.023850;,
  0.842730;0.023850;,
  0.842730;0.924130;,
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
  0.592730;0.924130;,
  0.592730;0.023850;,
  0.842730;0.023850;,
  0.842730;0.924130;,
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
