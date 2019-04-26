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
 77;
 0.00001;187.58578;2.09830;,
 -3.60036;185.19629;1.76306;,
 -0.00001;184.20651;1.62443;,
 0.00001;187.58578;2.09830;,
 -5.09169;187.58578;2.09831;,
 0.00001;187.58578;2.09830;,
 -3.60038;189.97534;2.43364;,
 0.00001;187.58578;2.09830;,
 -0.00002;190.96513;2.57215;,
 0.00001;187.58578;2.09830;,
 3.60036;189.97534;2.43361;,
 0.00001;187.58578;2.09830;,
 5.09168;187.58578;2.09832;,
 0.00001;187.58578;2.09830;,
 3.60036;185.19629;1.76306;,
 0.00001;187.58578;2.09830;,
 -0.00001;184.20651;1.62443;,
 -3.60036;185.58295;-26.69138;,
 0.00000;184.58838;-26.47575;,
 -5.09168;187.97426;-26.48743;,
 -3.60037;190.36157;-25.98318;,
 0.00001;191.34625;-25.47449;,
 3.60036;190.35168;-25.25877;,
 5.09168;187.96039;-25.46281;,
 3.60036;185.57312;-25.96681;,
 0.00000;184.58838;-26.47575;,
 -5.76961;178.82852;-52.48391;,
 -5.76961;173.06970;-54.64576;,
 0.00000;173.06970;-51.46292;,
 -0.00000;178.52399;-49.30450;,
 -7.26094;180.07365;-64.53051;,
 -11.40360;173.06970;-67.80588;,
 -3.60037;181.53001;-70.64320;,
 -7.41511;173.06970;-78.19070;,
 0.00000;182.34451;-70.05953;,
 -0.00000;173.06970;-78.67261;,
 3.60037;182.04002;-69.53811;,
 3.60036;173.06970;-75.48971;,
 5.09169;180.79491;-62.96768;,
 9.47747;173.06970;-67.80589;,
 3.60037;179.33849;-51.37887;,
 6.85689;173.06970;-54.64578;,
 -0.00000;178.52399;-49.30450;,
 0.00000;173.06970;-51.46292;,
 0.00000;183.48920;-41.05647;,
 -3.60037;184.27943;-43.08476;,
 -5.09169;186.37636;-46.78904;,
 -3.60036;188.55153;-49.99967;,
 -0.00000;189.53096;-50.83569;,
 3.60036;188.74065;-48.80740;,
 5.09167;186.64384;-45.10313;,
 3.60035;184.46860;-41.89256;,
 0.00000;183.48920;-41.05647;,
 -4.53462;172.54347;-61.51682;,
 -0.00000;164.58092;-67.80588;,
 0.00000;172.46115;-56.63341;,
 -8.03531;172.70328;-67.80588;,
 -0.00000;164.58092;-67.80588;,
 -4.53462;172.54347;-61.51682;,
 -6.27205;172.77412;-74.69395;,
 -0.00000;164.58092;-67.80588;,
 -8.03531;172.70328;-67.80588;,
 -0.00000;172.65843;-74.86549;,
 -0.00000;164.58092;-67.80588;,
 -6.27205;172.77412;-74.69395;,
 3.68416;172.57260;-72.72002;,
 -0.00000;164.58092;-67.80588;,
 -0.00000;172.65843;-74.86549;,
 5.88706;172.41660;-67.80588;,
 -0.00000;164.58092;-67.80588;,
 3.68416;172.57260;-72.72002;,
 4.23671;172.38869;-60.42646;,
 -0.00000;164.58092;-67.80588;,
 5.88706;172.41660;-67.80588;,
 0.00000;172.46115;-56.63341;,
 -0.00000;164.58092;-67.80588;,
 4.23671;172.38869;-60.42646;;
 
 56;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;17,18,2,1;,
 4;19,17,1,4;,
 4;20,19,4,6;,
 4;21,20,6,8;,
 4;22,21,8,10;,
 4;23,22,10,12;,
 4;24,23,12,14;,
 4;25,24,14,16;,
 4;26,27,28,29;,
 4;30,31,27,26;,
 4;32,33,31,30;,
 4;34,35,33,32;,
 4;36,37,35,34;,
 4;38,39,37,36;,
 4;40,41,39,38;,
 4;42,43,41,40;,
 4;44,18,17,45;,
 4;44,45,26,29;,
 4;45,17,19,46;,
 4;45,46,30,26;,
 4;46,19,20,47;,
 4;46,47,32,30;,
 4;47,20,21,48;,
 4;47,48,34,32;,
 4;48,21,22,49;,
 4;48,49,36,34;,
 4;49,22,23,50;,
 4;49,50,38,36;,
 4;50,23,24,51;,
 4;50,51,40,38;,
 4;51,24,25,52;,
 4;51,52,42,40;,
 3;53,54,55;,
 4;53,55,28,27;,
 3;56,57,58;,
 4;56,58,27,31;,
 3;59,60,61;,
 4;59,61,31,33;,
 3;62,63,64;,
 4;62,64,33,35;,
 3;65,66,67;,
 4;65,67,35,37;,
 3;68,69,70;,
 4;68,70,37,39;,
 3;71,72,73;,
 4;71,73,39,41;,
 3;74,75,76;,
 4;74,76,41,43;;
 
 MeshMaterialList {
  2;
  56;
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
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1;;
  Material {
   0.508235;0.787451;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.241600;0.241600;0.241600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  74;
  0.000000;-0.138908;0.990305;,
  -0.000000;-0.138868;0.990311;,
  -0.000021;-0.138903;0.990306;,
  0.000002;-0.138955;0.990299;,
  0.000040;-0.138916;0.990304;,
  0.000004;-0.138861;0.990312;,
  -0.000037;-0.138908;0.990305;,
  -0.000005;-0.138949;0.990300;,
  0.000020;-0.138905;0.990306;,
  0.002544;-0.338700;0.940891;,
  -0.793065;-0.093368;0.601939;,
  -0.916566;0.399092;-0.025146;,
  -0.435212;0.698711;-0.567797;,
  0.164412;0.639220;-0.751243;,
  0.619078;0.546683;-0.563808;,
  0.890816;0.446191;-0.085794;,
  0.903706;0.391999;0.172201;,
  -0.663753;-0.712202;0.228475;,
  0.000711;-0.999531;0.030602;,
  -0.597127;-0.801731;0.025833;,
  -0.848050;-0.529631;0.017387;,
  -0.597737;0.801318;-0.024493;,
  -0.001296;0.999578;-0.029026;,
  0.596019;0.802659;-0.022355;,
  0.847189;0.531095;-0.014467;,
  0.597310;-0.801681;0.022980;,
  0.000672;-0.639396;0.768877;,
  -0.803478;-0.294473;0.517405;,
  -0.938484;0.345311;0.002800;,
  -0.496132;0.763091;-0.414179;,
  0.086961;0.821249;-0.563904;,
  0.638041;0.646823;-0.417760;,
  0.965129;0.258271;-0.042693;,
  0.985103;0.042926;0.166524;,
  0.000144;-0.954013;0.299764;,
  -0.704466;-0.669258;0.236266;,
  -0.988220;0.152131;0.016673;,
  -0.570981;0.805483;-0.158673;,
  -0.000109;0.978905;-0.204316;,
  0.617811;0.771507;-0.151943;,
  0.973942;0.226566;-0.010204;,
  0.668978;-0.717585;0.193752;,
  -0.028666;-0.943380;0.330472;,
  -0.372113;-0.890999;0.260103;,
  -0.430681;-0.901332;0.045995;,
  -0.237608;-0.924566;-0.297859;,
  0.117224;-0.881510;-0.457382;,
  0.388528;-0.847293;-0.362133;,
  0.524229;-0.847928;-0.078746;,
  0.397391;-0.890060;0.223323;,
  0.000001;-0.999908;-0.013588;,
  -0.598155;-0.801307;-0.010889;,
  -0.848768;-0.528717;-0.007185;,
  -0.848074;0.529610;-0.016840;,
  -0.848776;0.528703;0.007185;,
  -0.598159;0.801303;0.010890;,
  0.000003;0.999908;0.013589;,
  0.598157;0.801305;0.010890;,
  0.848770;0.528713;0.007186;,
  0.847562;-0.530497;0.014553;,
  0.848769;-0.528715;-0.007185;,
  0.598157;-0.801305;-0.010890;,
  0.468735;-0.280441;0.837639;,
  0.449226;-0.572816;0.685622;,
  0.845950;-0.532027;0.036284;,
  -0.007915;-0.995345;0.096052;,
  -0.095345;-0.993215;0.066579;,
  -0.114842;-0.993383;0.001297;,
  -0.063264;-0.995652;-0.068376;,
  0.574224;-0.772081;-0.272320;,
  0.037329;-0.992186;-0.119050;,
  0.147144;-0.978567;-0.144069;,
  0.192875;-0.979695;-0.054741;,
  0.118562;-0.990514;0.069458;;
  56;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;19,18,50,51;,
  4;20,19,51,52;,
  4;21,53,54,55;,
  4;22,21,55,56;,
  4;23,22,56,57;,
  4;24,23,57,58;,
  4;25,59,60,61;,
  4;18,25,61,50;,
  4;27,10,9,26;,
  4;28,11,10,27;,
  4;29,12,11,28;,
  4;30,13,12,29;,
  4;31,14,13,30;,
  4;32,15,14,31;,
  4;33,16,15,32;,
  4;26,9,62,63;,
  4;34,18,19,35;,
  4;34,35,27,26;,
  4;35,19,20,36;,
  4;35,36,28,27;,
  4;36,53,21,37;,
  4;36,37,29,28;,
  4;37,21,22,38;,
  4;37,38,30,29;,
  4;38,22,23,39;,
  4;38,39,31,30;,
  4;39,23,24,40;,
  4;39,40,32,31;,
  4;64,59,25,41;,
  4;40,41,33,32;,
  4;41,25,18,34;,
  4;41,34,26,63;,
  3;43,17,42;,
  4;43,42,65,66;,
  3;44,17,43;,
  4;44,43,66,67;,
  3;45,17,44;,
  4;45,44,67,68;,
  3;46,69,45;,
  4;46,45,68,70;,
  3;47,69,46;,
  4;47,46,70,71;,
  3;48,69,47;,
  4;48,47,71,72;,
  3;49,69,48;,
  4;49,48,72,73;,
  3;42,69,49;,
  4;42,49,73,65;;
 }
 MeshTextureCoords {
  77;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.125000;0.299417;,
  0.000000;0.295688;,
  0.250000;0.300798;,
  0.375000;0.299021;,
  0.500000;0.295127;,
  0.625000;0.291397;,
  0.750000;0.290016;,
  0.875000;0.291794;,
  1.000000;0.295688;,
  0.125000;0.695423;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.685260;,
  0.250000;0.699185;,
  0.250000;1.000000;,
  0.375000;0.694342;,
  0.375000;1.000000;,
  0.500000;0.683731;,
  0.500000;1.000000;,
  0.625000;0.673567;,
  0.625000;1.000000;,
  0.750000;0.669805;,
  0.750000;1.000000;,
  0.875000;0.674648;,
  0.875000;1.000000;,
  1.000000;0.685260;,
  1.000000;1.000000;,
  0.000000;0.486534;,
  0.125000;0.493416;,
  0.250000;0.495963;,
  0.375000;0.492684;,
  0.500000;0.485499;,
  0.625000;0.478617;,
  0.750000;0.476070;,
  0.875000;0.479349;,
  1.000000;0.486534;,
  0.102257;1.000000;,
  0.062500;1.000000;,
  0.023349;1.000000;,
  0.228433;1.000000;,
  0.187500;1.000000;,
  0.147743;1.000000;,
  0.353955;1.000000;,
  0.312500;1.000000;,
  0.271567;1.000000;,
  0.478103;1.000000;,
  0.437500;1.000000;,
  0.396045;1.000000;,
  0.602471;1.000000;,
  0.562500;1.000000;,
  0.521897;1.000000;,
  0.726323;1.000000;,
  0.687500;1.000000;,
  0.647529;1.000000;,
  0.851117;1.000000;,
  0.812500;1.000000;,
  0.773677;1.000000;,
  0.976651;1.000000;,
  0.937500;1.000000;,
  0.898883;1.000000;;
 }
}
