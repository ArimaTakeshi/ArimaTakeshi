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
 73;
 -4.32415;-0.09404;-4.11774;,
 -0.05947;0.99122;-4.05751;,
 -0.26026;-1.31361;-4.22035;,
 0.35582;4.51115;-0.14194;,
 -4.21922;3.30688;-3.77365;,
 -3.72910;4.61337;-0.31341;,
 0.35582;4.51115;-0.14194;,
 0.38238;3.22298;-2.93272;,
 -3.93307;3.11174;2.32366;,
 0.35582;4.51115;-0.14194;,
 -3.72910;4.61337;-0.31341;,
 0.33720;3.66843;2.21516;,
 -0.06169;-1.13319;3.79884;,
 0.04002;0.19548;3.69541;,
 -11.34598;-2.40824;2.79518;,
 0.34790;-3.29863;0.89288;,
 0.11628;-2.22837;3.23908;,
 -11.29834;-3.47340;0.26450;,
 -10.96574;0.08485;3.68865;,
 -0.06169;-1.13319;3.79884;,
 -10.63114;2.54424;2.46040;,
 -7.12365;3.15300;2.81452;,
 -10.51581;3.97089;0.08178;,
 -6.89376;4.28604;-0.10623;,
 -3.72910;4.61337;-0.31341;,
 -14.39644;2.49683;2.33936;,
 -14.25123;3.36114;0.10225;,
 -14.46341;0.41745;3.33794;,
 -14.73026;-1.89123;2.55280;,
 -14.84514;-3.13004;0.25029;,
 -10.86776;-2.26881;-2.60711;,
 -7.10585;0.22067;-4.12166;,
 -7.81611;-2.24279;-2.18487;,
 -10.51232;0.29266;-3.91312;,
 -0.52368;-2.59580;-2.20505;,
 -11.29834;-3.47340;0.26450;,
 0.34790;-3.29863;0.89288;,
 -11.29834;-3.47340;0.26450;,
 0.34790;-3.29863;0.89288;,
 -10.48298;2.97999;-2.81981;,
 -6.89376;4.28604;-0.10623;,
 -7.49753;3.00063;-3.16273;,
 -6.89376;4.28604;-0.10623;,
 -10.51581;3.97089;0.08178;,
 -6.89376;4.28604;-0.10623;,
 -14.28472;2.62397;-2.38233;,
 -10.51581;3.97089;0.08178;,
 -10.51581;3.97089;0.08178;,
 -14.25123;3.36114;0.10225;,
 -14.38487;0.06053;-3.53602;,
 -14.48442;-2.39211;-2.31191;,
 -11.29834;-3.47340;0.26450;,
 -14.84514;-3.13004;0.25029;,
 -11.29834;-3.47340;0.26450;,
 -12.06778;2.17068;1.65133;,
 -13.82566;2.76086;-0.35825;,
 -14.00621;2.19083;1.63886;,
 -11.82690;2.80746;-0.40055;,
 -12.44223;0.42879;2.88804;,
 -14.34143;0.42766;2.70519;,
 -12.66410;-1.63616;2.12258;,
 -14.52909;-1.65177;1.92637;,
 -12.52510;-2.43608;-0.28959;,
 -14.50558;-2.44929;-0.41799;,
 -11.69097;1.98656;-2.22089;,
 -13.77162;1.83078;-2.19068;,
 -11.74037;0.24378;-3.17649;,
 -13.90632;0.17862;-3.15089;,
 -12.01437;-1.68992;-2.58850;,
 -14.50558;-2.44929;-0.41799;,
 -14.18003;-1.68908;-2.59481;,
 -14.50558;-2.44929;-0.41799;,
 -12.52510;-2.43608;-0.28959;;
 
 68;
 3;0,1,2;,
 3;3,4,5;,
 3;4,6,7;,
 3;1,4,7;,
 3;4,1,0;,
 3;8,9,10;,
 3;9,8,11;,
 3;12,11,8;,
 3;11,12,13;,
 3;14,15,16;,
 3;15,14,17;,
 3;18,16,19;,
 3;16,18,14;,
 3;20,19,21;,
 3;19,20,18;,
 3;21,12,8;,
 3;22,21,23;,
 3;21,22,20;,
 3;23,8,24;,
 3;8,23,21;,
 3;25,22,26;,
 3;22,25,20;,
 3;27,20,25;,
 3;20,27,18;,
 3;28,18,27;,
 3;18,28,14;,
 3;29,14,28;,
 3;14,29,17;,
 3;30,31,32;,
 3;31,30,33;,
 3;32,0,34;,
 3;0,32,31;,
 3;35,32,36;,
 3;32,37,30;,
 3;34,38,32;,
 3;39,40,41;,
 3;42,39,43;,
 3;41,5,4;,
 3;5,41,44;,
 3;33,41,31;,
 3;41,33,39;,
 3;31,4,0;,
 3;4,31,41;,
 3;45,46,39;,
 3;47,45,48;,
 3;49,39,33;,
 3;39,49,45;,
 3;50,51,52;,
 3;53,50,30;,
 3;49,30,50;,
 3;30,49,33;,
 3;2,34,0;,
 3;54,55,56;,
 3;55,54,57;,
 3;58,56,59;,
 3;56,58,54;,
 3;60,59,61;,
 3;59,60,58;,
 3;62,61,63;,
 3;61,62,60;,
 3;64,55,57;,
 3;55,64,65;,
 3;66,65,64;,
 3;65,66,67;,
 3;68,69,70;,
 3;71,68,72;,
 3;66,70,67;,
 3;70,66,68;;
 
 MeshMaterialList {
  1;
  68;
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
   0.721600;0.300800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  68;
  -0.996902;0.074305;-0.025807;,
  -0.056584;0.907346;0.416560;,
  -0.072601;0.696123;0.714242;,
  0.052635;0.199441;-0.978495;,
  0.140225;0.703052;-0.697177;,
  -0.003931;0.070816;-0.997482;,
  -0.066090;-0.327809;-0.942430;,
  -0.076845;0.932717;-0.352327;,
  -0.007714;0.598851;-0.800823;,
  0.004146;0.777605;0.628740;,
  -0.000773;0.167111;0.985938;,
  -0.033218;-0.604958;0.795564;,
  -0.074213;-0.767161;0.637147;,
  -0.048820;-0.920916;0.386692;,
  -0.004442;-0.915897;0.401390;,
  -0.061050;-0.095337;0.993571;,
  -0.035422;0.716983;0.696190;,
  -0.066401;0.547465;0.834190;,
  -0.017460;0.913735;0.405936;,
  -0.109639;0.895501;0.431343;,
  -0.149179;0.925581;0.347916;,
  -0.074269;0.780768;0.620391;,
  -0.072996;0.206280;0.975766;,
  -0.144013;-0.528863;0.836400;,
  -0.128522;-0.893561;0.430153;,
  0.010276;-0.815928;-0.578062;,
  -0.001875;-0.671634;-0.740880;,
  -0.086187;0.038622;-0.995530;,
  -0.047971;-0.179166;-0.982649;,
  -0.116528;-0.840646;-0.528900;,
  -0.124647;0.691685;-0.711362;,
  -0.115534;0.720456;-0.683809;,
  -0.152431;0.827238;-0.540779;,
  -0.102589;-0.028759;-0.994308;,
  -0.053187;-0.827216;-0.559360;,
  -0.025676;0.729577;0.683416;,
  -0.029734;0.996399;-0.079402;,
  -0.097713;-0.055616;0.993659;,
  -0.049357;-0.817550;0.573738;,
  -0.014554;-0.946663;0.321897;,
  -0.050984;0.648943;-0.759127;,
  -0.015320;0.119268;-0.992744;,
  0.000190;-0.560772;-0.827970;,
  -0.019788;-0.948005;0.317638;,
  -0.077020;-0.595765;0.799457;,
  -0.062979;0.282978;0.957056;,
  -0.002470;0.874336;0.485315;,
  -0.024602;0.997700;-0.063168;,
  -0.020173;0.111194;-0.993594;,
  0.010831;-0.808962;-0.587760;,
  -0.052840;0.793668;-0.606052;,
  0.038363;0.933039;-0.357723;,
  0.092615;0.904377;-0.416563;,
  0.000970;0.868957;0.494887;,
  -0.057809;0.869453;0.490622;,
  0.035689;-0.912426;-0.407683;,
  0.060240;-0.923669;-0.378428;,
  -0.047868;-0.976921;-0.208167;,
  -0.049897;0.924136;-0.378791;,
  -0.098655;0.941380;-0.322600;,
  -0.119389;0.923415;-0.364761;,
  -0.124929;0.938491;-0.321911;,
  -0.156192;0.947499;-0.279017;,
  -0.091150;-0.953454;-0.287432;,
  -0.000137;-0.922146;-0.386842;,
  0.000595;-0.944112;-0.329623;,
  0.026023;-0.952515;-0.303377;,
  -0.253979;-0.800669;-0.542608;;
  68;
  3;6,3,5;,
  3;51,8,7;,
  3;8,52,4;,
  3;3,8,4;,
  3;8,3,6;,
  3;9,1,53;,
  3;1,9,2;,
  3;10,2,9;,
  3;0,0,0;,
  3;12,14,11;,
  3;14,12,13;,
  3;15,11,10;,
  3;11,15,12;,
  3;17,10,16;,
  3;10,17,15;,
  3;16,10,9;,
  3;19,16,18;,
  3;16,19,17;,
  3;18,9,54;,
  3;9,18,16;,
  3;21,19,20;,
  3;19,21,17;,
  3;22,17,21;,
  3;17,22,15;,
  3;23,15,22;,
  3;15,23,12;,
  3;24,12,23;,
  3;12,24,13;,
  3;26,28,25;,
  3;28,26,27;,
  3;25,6,29;,
  3;6,25,28;,
  3;55,25,55;,
  3;25,56,26;,
  3;29,57,25;,
  3;31,58,30;,
  3;59,31,59;,
  3;30,7,8;,
  3;7,30,60;,
  3;27,30,28;,
  3;30,27,31;,
  3;28,8,6;,
  3;8,28,30;,
  3;32,61,31;,
  3;62,32,62;,
  3;33,31,27;,
  3;31,33,32;,
  3;34,63,63;,
  3;64,34,26;,
  3;33,26,34;,
  3;26,33,27;,
  3;67,29,6;,
  3;46,36,35;,
  3;36,46,47;,
  3;45,35,37;,
  3;35,45,46;,
  3;44,37,38;,
  3;37,44,45;,
  3;43,38,39;,
  3;38,43,44;,
  3;50,36,47;,
  3;36,50,40;,
  3;48,40,50;,
  3;40,48,41;,
  3;49,65,42;,
  3;66,49,66;,
  3;48,42,41;,
  3;42,48,49;;
 }
 MeshTextureCoords {
  73;
  0.540500;0.085600;,
  0.525600;0.063700;,
  0.525500;0.087700;,
  0.550200;0.048700;,
  0.563000;0.078200;,
  0.570400;0.076400;,
  0.550200;0.048700;,
  0.544700;0.051600;,
  0.670000;0.085200;,
  0.686400;0.055000;,
  0.665000;0.081900;,
  0.690500;0.057500;,
  0.683600;0.093500;,
  0.703900;0.064500;,
  0.673300;0.143000;,
  0.696600;0.122100;,
  0.689400;0.119900;,
  0.680300;0.145500;,
  0.658200;0.135200;,
  0.674000;0.111100;,
  0.645600;0.127700;,
  0.661000;0.103000;,
  0.641800;0.124600;,
  0.656300;0.099400;,
  0.665000;0.081900;,
  0.625600;0.153900;,
  0.622700;0.151700;,
  0.637700;0.160300;,
  0.653700;0.167500;,
  0.662300;0.171000;,
  0.558100;0.136200;,
  0.555400;0.101900;,
  0.541800;0.110000;,
  0.571600;0.128700;,
  0.531800;0.098500;,
  0.553500;0.140700;,
  0.538100;0.116600;,
  0.553500;0.140700;,
  0.538100;0.116600;,
  0.584800;0.122600;,
  0.578500;0.094300;,
  0.571500;0.096000;,
  0.578500;0.094300;,
  0.591900;0.120200;,
  0.578500;0.094300;,
  0.602900;0.150400;,
  0.591900;0.120200;,
  0.591900;0.120200;,
  0.609900;0.147900;,
  0.590000;0.156400;,
  0.575800;0.163600;,
  0.553500;0.140700;,
  0.570500;0.166900;,
  0.553500;0.140700;,
  0.200130;0.523910;,
  0.181250;0.543330;,
  0.200300;0.545110;,
  0.179740;0.520530;,
  0.220200;0.530890;,
  0.219250;0.551370;,
  0.240480;0.538230;,
  0.239870;0.558010;,
  0.264580;0.549640;,
  0.261520;0.570320;,
  0.161040;0.520350;,
  0.160180;0.543820;,
  0.139940;0.526800;,
  0.143060;0.549830;,
  0.121180;0.535600;,
  0.100880;0.569010;,
  0.123680;0.557090;,
  0.100880;0.569010;,
  0.099870;0.547050;;
 }
}
