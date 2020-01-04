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
 87;
 -0.67318;-0.32538;-1.22420;,
 0.43235;-0.19205;-0.89194;,
 0.46316;-0.97925;-0.82866;,
 -0.03474;0.14673;1.53006;,
 -1.70914;0.43453;1.86318;,
 -0.04615;-0.59854;1.94526;,
 -2.33315;0.50915;1.80937;,
 0.13930;1.10319;0.75862;,
 -2.32183;1.56850;1.19750;,
 0.64691;0.73605;-1.04600;,
 -1.46446;0.94713;-2.02244;,
 -1.32755;-0.23643;-1.95140;,
 -2.10488;-0.09821;-2.16610;,
 -2.06329;-1.36778;-1.45923;,
 -2.80840;-1.00371;-1.70897;,
 -2.86972;-0.77593;1.56392;,
 -3.61482;-0.41185;1.31417;,
 -3.10331;0.63461;1.60942;,
 -3.80315;0.76508;1.42840;,
 -3.06103;1.65467;1.00707;,
 -4.19945;1.60003;0.76221;,
 -2.20366;1.03330;-2.21287;,
 -3.34207;0.97866;-2.45773;,
 -2.80592;0.02031;-2.34711;,
 -4.70951;0.39264;-2.42606;,
 -3.36156;-0.22482;-2.00562;,
 -4.16950;-0.34877;-2.15891;,
 -4.16799;0.36703;1.01752;,
 -4.97592;0.24308;0.86424;,
 -4.91410;0.97293;1.13371;,
 -5.53914;0.48040;0.67987;,
 -5.45440;1.12298;0.56005;,
 -4.73392;-0.12340;-2.34327;,
 -4.64919;0.51919;-2.46309;,
 -4.21099;0.92136;-2.45533;,
 -5.01742;1.51321;0.56782;,
 -5.71206;-0.86794;-1.41794;,
 -3.72858;0.33177;-1.23799;,
 -6.25203;-0.00266;0.68702;,
 -4.45818;0.96283;0.83470;,
 -5.03641;1.50309;0.58784;,
 -4.38684;0.90582;-0.31348;,
 -4.45771;1.04390;-1.55557;,
 -6.66318;-0.54344;-1.66021;,
 -6.22029;-1.74538;-1.34399;,
 -6.66127;-0.68502;0.74488;,
 -7.22374;-0.88181;0.67267;,
 -6.29454;-1.44527;0.95316;,
 -6.82124;-1.63359;0.89040;,
 -6.27981;-2.15978;-0.09203;,
 -6.39857;-2.98147;-1.14547;,
 -5.72451;-2.74765;-1.05650;,
 -6.51443;-0.62228;-2.67159;,
 -6.57316;-1.77391;-2.46794;,
 -6.74800;-0.45298;-1.89399;,
 -6.81825;-1.60346;-1.69349;,
 -5.90721;-1.86364;-1.46393;,
 -6.31129;-1.96838;-1.94361;,
 -5.66332;-2.04604;-2.23837;,
 -5.58994;-0.89590;-2.45044;,
 -5.18725;0.25740;-2.58577;,
 -5.43234;0.42786;-1.81132;,
 -4.91467;-0.41986;-1.54718;,
 -4.40311;1.05039;-1.61558;,
 -4.46533;-0.29375;-1.33273;,
 -4.32163;0.29408;-1.87032;,
 -4.25361;-0.44880;-2.11666;,
 -4.19139;0.89534;-2.39951;,
 -4.61806;-1.71544;-2.66425;,
 -3.22924;-2.32565;-2.75534;,
 -4.65234;-2.33966;-3.04123;,
 -4.63710;-2.88295;-2.33744;,
 -4.83946;-2.22359;-2.49826;,
 -4.60282;-2.25873;-1.96046;,
 -3.58238;-2.08358;-1.65153;,
 -3.59568;-1.55255;-2.36687;,
 -2.70940;-0.96572;-1.91954;,
 -1.52118;-1.19380;-1.91427;,
 -1.57295;-1.40446;-1.02674;,
 -0.54749;0.07216;-1.12688;,
 -1.04275;-0.20349;-1.01692;,
 -6.92294;-2.00043;-1.42767;,
 -6.99148;0.22828;0.50481;,
 -4.67077;-0.60226;-2.32161;,
 -5.83696;-0.71318;-1.66443;,
 -3.21280;-2.85700;-2.05156;,
 -2.76116;-1.17637;-1.03200;;
 
 151;
 3;0,1,2;,
 3;3,4,5;,
 3;5,4,6;,
 3;4,7,6;,
 3;6,7,8;,
 3;7,9,8;,
 3;8,9,10;,
 3;9,11,10;,
 3;10,11,12;,
 3;11,13,12;,
 3;12,13,14;,
 3;13,15,14;,
 3;14,15,16;,
 3;15,17,16;,
 3;16,17,18;,
 3;17,19,18;,
 3;18,19,20;,
 3;19,21,20;,
 3;20,21,22;,
 3;21,23,22;,
 3;22,23,24;,
 3;23,25,24;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;28,29,30;,
 3;29,31,30;,
 3;30,31,32;,
 3;31,33,32;,
 3;32,33,24;,
 3;33,34,24;,
 3;24,34,22;,
 3;34,35,22;,
 3;22,35,20;,
 3;35,29,20;,
 3;20,29,18;,
 3;29,27,18;,
 3;18,27,16;,
 3;27,25,16;,
 3;16,25,14;,
 3;25,23,14;,
 3;14,23,12;,
 3;23,21,12;,
 3;12,21,10;,
 3;21,19,10;,
 3;10,19,8;,
 3;19,17,8;,
 3;8,17,6;,
 3;17,15,6;,
 3;6,15,5;,
 3;15,13,5;,
 3;5,13,2;,
 3;13,11,2;,
 3;2,11,0;,
 3;11,9,0;,
 3;0,9,1;,
 3;7,4,3;,
 3;36,37,38;,
 3;37,39,38;,
 3;38,39,40;,
 3;39,41,40;,
 3;40,41,42;,
 3;41,37,42;,
 3;42,37,43;,
 3;37,36,43;,
 3;43,36,44;,
 3;36,38,44;,
 3;44,38,45;,
 3;38,46,45;,
 3;45,46,47;,
 3;46,48,47;,
 3;47,48,49;,
 3;48,50,49;,
 3;49,50,51;,
 3;50,44,51;,
 3;51,44,47;,
 3;44,45,47;,
 3;52,53,54;,
 3;53,55,54;,
 3;54,55,56;,
 3;55,57,56;,
 3;56,57,58;,
 3;57,53,58;,
 3;58,53,59;,
 3;53,52,59;,
 3;59,52,60;,
 3;52,54,60;,
 3;60,54,61;,
 3;54,62,61;,
 3;61,62,63;,
 3;62,64,63;,
 3;63,64,65;,
 3;64,66,65;,
 3;65,66,67;,
 3;66,60,67;,
 3;67,60,63;,
 3;60,61,63;,
 3;68,69,70;,
 3;69,71,70;,
 3;70,71,72;,
 3;71,73,72;,
 3;72,73,68;,
 3;73,74,68;,
 3;68,74,75;,
 3;74,76,75;,
 3;75,76,69;,
 3;76,77,69;,
 3;69,77,78;,
 3;77,79,78;,
 3;78,79,80;,
 3;44,50,81;,
 3;50,46,81;,
 3;81,46,43;,
 3;46,82,43;,
 3;43,82,40;,
 3;82,38,40;,
 3;60,66,83;,
 3;66,62,83;,
 3;83,62,59;,
 3;62,84,59;,
 3;59,84,56;,
 3;84,54,56;,
 3;71,69,85;,
 3;69,78,85;,
 3;85,78,74;,
 3;78,86,74;,
 3;74,86,76;,
 3;24,26,32;,
 3;26,28,32;,
 3;32,28,30;,
 3;29,35,31;,
 3;35,34,31;,
 3;31,34,33;,
 3;85,74,71;,
 3;74,73,71;,
 3;70,72,68;,
 3;79,77,76;,
 3;69,68,75;,
 3;44,81,43;,
 3;41,39,37;,
 3;47,49,51;,
 3;82,46,38;,
 3;42,43,40;,
 3;50,48,46;,
 3;60,83,59;,
 3;57,55,53;,
 3;63,65,67;,
 3;84,62,54;,
 3;58,59,56;,
 3;66,64,62;;
 
 MeshMaterialList {
  1;
  151;
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
   0.787200;0.749600;0.473600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  179;
  0.444462;0.165049;-0.880462;,
  0.296857;-0.307289;-0.904129;,
  0.300789;-0.145127;-0.942584;,
  0.251963;0.524798;0.813081;,
  0.010788;0.091535;0.995743;,
  0.123828;0.485761;0.865276;,
  -0.080915;0.148060;0.985663;,
  0.195783;0.798245;0.569625;,
  -0.020098;0.504238;0.863331;,
  0.160652;0.975635;-0.149425;,
  0.156177;0.976744;-0.146903;,
  0.353747;-0.346205;-0.868910;,
  0.188712;-0.267229;-0.944974;,
  0.164650;-0.499798;-0.850348;,
  -0.031432;-0.513859;-0.857298;,
  -0.299422;-0.948240;0.105771;,
  -0.697970;-0.714630;-0.046276;,
  -0.231177;0.213053;0.949297;,
  -0.313384;0.152875;0.937240;,
  -0.161954;0.522517;0.837106;,
  -0.180670;0.610147;0.771414;,
  0.046808;0.983053;-0.177242;,
  -0.042142;0.978683;-0.201005;,
  0.038951;-0.331793;-0.942548;,
  0.136366;-0.290814;-0.947012;,
  -0.062121;-0.495962;-0.866119;,
  0.228739;-0.178234;-0.957033;,
  -0.342645;-0.739200;0.579808;,
  -0.288956;-0.808271;0.513032;,
  -0.397090;0.151608;0.905171;,
  -0.569127;-0.034734;0.821516;,
  -0.611687;0.402100;0.681289;,
  -0.959630;0.076055;-0.270789;,
  -0.854513;0.416238;-0.310732;,
  0.214620;-0.254558;-0.942941;,
  -0.355518;0.923473;0.144238;,
  0.645764;-0.633584;0.426099;,
  0.637745;-0.646591;0.418571;,
  0.423521;-0.805071;0.415320;,
  0.410054;-0.822241;0.394684;,
  -0.186290;0.213562;0.959003;,
  0.684084;0.729061;0.022358;,
  0.696889;0.716071;0.039842;,
  0.189176;-0.189941;-0.963398;,
  0.184093;-0.184313;-0.965473;,
  0.977250;-0.010837;0.211811;,
  -0.184782;0.184835;0.965242;,
  -0.183070;0.179277;0.966615;,
  -0.180635;0.183159;0.966346;,
  0.202393;-0.796517;0.569735;,
  0.239307;-0.778488;0.580249;,
  0.151321;-0.802936;0.576537;,
  -0.824795;0.447799;-0.345239;,
  -0.822280;0.447502;-0.351566;,
  -0.927884;-0.299591;-0.221984;,
  -0.872515;-0.455866;-0.175795;,
  -0.191747;0.179851;0.964825;,
  -0.312454;-0.942360;0.119712;,
  -0.122393;-0.992453;-0.007565;,
  0.184211;-0.181631;-0.965959;,
  0.283519;-0.145128;-0.947921;,
  -0.476911;0.814562;-0.330218;,
  -0.277978;0.182726;0.943048;,
  -0.368311;0.170668;0.913903;,
  -0.467534;0.202703;0.860421;,
  0.965875;0.009723;0.258827;,
  0.967342;0.004546;0.253432;,
  0.967649;0.012180;0.252005;,
  0.165761;0.503818;-0.847756;,
  0.165445;0.503166;-0.848205;,
  0.135910;0.497639;-0.856670;,
  0.132202;-0.786428;-0.603369;,
  -0.997004;0.062337;0.045783;,
  -0.761950;0.394297;0.513773;,
  -0.524992;0.720854;0.452497;,
  -0.473936;0.702802;0.530523;,
  -0.719213;0.631256;0.290256;,
  0.096558;0.482923;-0.870323;,
  0.730851;-0.644481;-0.224725;,
  0.815343;-0.572211;-0.088260;,
  0.285092;-0.133618;0.949141;,
  0.181818;-0.183991;-0.965966;,
  -0.795853;0.522032;-0.306759;,
  0.322133;-0.095869;-0.941828;,
  0.255458;-0.920917;0.294368;,
  0.461814;-0.702659;-0.541292;,
  -0.099452;-0.498181;0.861351;,
  0.048101;0.816776;0.574946;,
  0.157792;0.976169;-0.148981;,
  0.449776;-0.290284;-0.844652;,
  0.310485;-0.017423;-0.950419;,
  -0.105744;-0.984284;0.141434;,
  -0.581199;-0.813750;0.004278;,
  -0.248415;-0.100227;0.963455;,
  -0.432025;-0.135871;0.891568;,
  0.099666;0.981598;-0.162887;,
  -0.022500;0.980504;-0.195205;,
  0.234885;-0.010750;-0.971964;,
  0.077795;-0.051772;-0.995624;,
  0.107339;-0.969912;0.218516;,
  -0.060596;-0.982491;0.176182;,
  -0.959628;0.076064;-0.270793;,
  -0.853180;0.419282;-0.310301;,
  0.291426;0.138075;0.946576;,
  0.409387;-0.430529;-0.804392;,
  -0.466743;0.835834;-0.289019;,
  -0.794336;-0.600099;-0.094404;,
  0.073352;-0.981247;0.178250;,
  0.112174;-0.981478;0.155300;,
  0.557962;0.719160;-0.414110;,
  0.558249;-0.597672;-0.575453;,
  -0.186402;0.201988;0.961486;,
  -0.198755;0.223313;0.954268;,
  0.670841;0.741585;0.004859;,
  0.693253;0.720350;0.022267;,
  0.674804;0.737656;0.022445;,
  0.202483;-0.218403;-0.954621;,
  0.195923;-0.193130;-0.961413;,
  0.185692;-0.177293;-0.966481;,
  0.977931;-0.005565;0.208852;,
  -0.188919;0.186139;0.964190;,
  0.165094;-0.813123;0.558189;,
  0.252892;-0.787956;0.561401;,
  0.185765;-0.181881;-0.965614;,
  0.190586;-0.182410;-0.964574;,
  0.899150;0.436744;-0.027992;,
  0.901190;0.432558;-0.027380;,
  -0.188751;0.186453;0.964162;,
  -0.191749;0.179850;0.964824;,
  -0.349981;-0.809408;0.471563;,
  -0.186970;-0.915079;0.357312;,
  -0.222243;-0.945107;-0.239544;,
  0.186507;-0.189648;-0.963975;,
  0.182302;-0.184904;-0.965700;,
  0.178732;-0.178175;-0.967630;,
  -0.484572;0.814167;-0.319877;,
  -0.225190;0.161858;0.960776;,
  0.964351;0.014900;0.264206;,
  0.964046;0.007266;0.265635;,
  0.378521;-0.110046;-0.919028;,
  0.307810;-0.209548;-0.928086;,
  -0.476384;0.829105;-0.292649;,
  -0.460144;0.832504;-0.308554;,
  0.425246;-0.771077;-0.473926;,
  0.129782;-0.783527;-0.607653;,
  -0.947172;-0.036185;-0.318678;,
  -0.958272;-0.275459;0.076403;,
  -0.483970;0.691599;0.536156;,
  0.139740;0.496666;-0.856619;,
  0.102138;0.484782;-0.868651;,
  0.714968;-0.688482;-0.121712;,
  0.029107;-0.388136;0.921142;,
  -0.889256;-0.444152;0.109331;,
  -0.986612;-0.154120;-0.053323;,
  -0.985257;-0.162073;-0.054787;,
  -0.807988;0.509447;-0.296006;,
  -0.522427;0.783879;-0.335564;,
  -0.177222;0.193835;0.964894;,
  0.181527;-0.948683;0.258937;,
  0.218009;-0.935679;0.277447;,
  0.228654;-0.929051;0.290829;,
  0.254064;-0.920962;0.295433;,
  0.953525;-0.005501;0.301263;,
  0.953598;-0.005766;0.301028;,
  -0.188696;0.189442;0.963590;,
  -0.130629;-0.504008;0.853764;,
  -0.132809;-0.502349;0.854405;,
  -0.771633;0.627520;0.103929;,
  0.246134;-0.164871;-0.955110;,
  -0.399230;-0.913836;0.074291;,
  -0.407531;-0.910249;0.073254;,
  -0.165162;-0.507646;0.845587;,
  -0.170349;-0.502536;0.847608;,
  -0.891346;0.269221;-0.364723;,
  0.094552;0.472331;-0.876335;,
  -0.544822;0.777664;-0.313700;,
  -0.889144;-0.444317;0.109572;,
  0.953452;-0.005237;0.301499;,
  0.158325;-0.959609;0.232559;;
  151;
  3;0,2,1;,
  3;3,5,4;,
  3;4,5,6;,
  3;5,7,87;,
  3;6,7,8;,
  3;7,9,88;,
  3;88,9,10;,
  3;89,11,90;,
  3;90,11,12;,
  3;11,13,12;,
  3;12,13,14;,
  3;91,15,92;,
  3;92,15,16;,
  3;93,17,94;,
  3;94,17,18;,
  3;17,19,18;,
  3;18,19,20;,
  3;95,21,96;,
  3;96,21,22;,
  3;97,23,98;,
  3;98,23,24;,
  3;23,25,24;,
  3;24,25,26;,
  3;99,27,100;,
  3;100,27,28;,
  3;27,29,28;,
  3;28,29,30;,
  3;29,31,30;,
  3;101,102,32;,
  3;102,33,32;,
  3;103,103,103;,
  3;104,34,24;,
  3;24,34,98;,
  3;105,35,22;,
  3;22,35,96;,
  3;35,29,20;,
  3;20,29,18;,
  3;29,27,18;,
  3;18,27,94;,
  3;27,106,16;,
  3;16,106,92;,
  3;25,23,14;,
  3;14,23,12;,
  3;23,97,12;,
  3;12,97,90;,
  3;21,95,10;,
  3;10,95,88;,
  3;19,17,8;,
  3;8,17,6;,
  3;17,93,6;,
  3;6,93,4;,
  3;15,91,107;,
  3;107,91,108;,
  3;13,11,1;,
  3;109,109,0;,
  3;11,89,110;,
  3;0,89,2;,
  3;7,5,3;,
  3;36,38,37;,
  3;38,39,37;,
  3;111,112,40;,
  3;113,41,114;,
  3;114,41,42;,
  3;41,115,42;,
  3;116,117,43;,
  3;117,118,43;,
  3;43,118,44;,
  3;36,37,119;,
  3;119,37,45;,
  3;111,46,120;,
  3;120,46,47;,
  3;46,48,47;,
  3;121,122,49;,
  3;122,50,49;,
  3;49,50,51;,
  3;123,44,124;,
  3;125,119,126;,
  3;119,45,126;,
  3;52,54,53;,
  3;54,55,53;,
  3;127,128,56;,
  3;129,57,130;,
  3;130,57,58;,
  3;57,131,58;,
  3;132,133,59;,
  3;133,134,59;,
  3;59,134,60;,
  3;52,53,135;,
  3;135,53,61;,
  3;127,62,136;,
  3;136,62,63;,
  3;62,64,63;,
  3;137,138,65;,
  3;138,66,65;,
  3;65,66,67;,
  3;139,60,140;,
  3;141,135,142;,
  3;135,61,142;,
  3;68,70,69;,
  3;143,71,144;,
  3;145,146,72;,
  3;146,73,72;,
  3;72,73,147;,
  3;73,74,147;,
  3;147,74,75;,
  3;74,76,75;,
  3;148,149,70;,
  3;149,77,70;,
  3;143,150,78;,
  3;150,79,78;,
  3;151,80,80;,
  3;44,123,81;,
  3;152,153,154;,
  3;154,153,155;,
  3;153,82,155;,
  3;155,82,156;,
  3;157,111,40;,
  3;60,139,83;,
  3;158,159,160;,
  3;160,159,161;,
  3;159,84,161;,
  3;162,163,162;,
  3;164,127,56;,
  3;71,143,85;,
  3;143,78,85;,
  3;165,151,166;,
  3;151,86,166;,
  3;74,167,76;,
  3;24,26,168;,
  3;100,28,169;,
  3;169,28,170;,
  3;29,35,31;,
  3;35,105,102;,
  3;102,105,33;,
  3;165,166,171;,
  3;166,172,171;,
  3;145,72,173;,
  3;174,77,149;,
  3;70,68,148;,
  3;44,81,43;,
  3;41,113,115;,
  3;121,49,51;,
  3;157,46,111;,
  3;175,155,156;,
  3;152,176,153;,
  3;60,83,59;,
  3;57,55,54;,
  3;137,65,67;,
  3;164,62,127;,
  3;177,162,162;,
  3;158,178,159;;
 }
 MeshTextureCoords {
  87;
  0.339840;0.814450;,
  0.308590;0.791020;,
  0.292970;0.791020;,
  0.314450;0.603520;,
  0.359380;0.453120;,
  0.277340;0.494140;,
  0.398440;0.453120;,
  0.326170;0.601560;,
  0.462890;0.492190;,
  0.320310;0.800780;,
  0.457030;0.847660;,
  0.390620;0.869140;,
  0.441410;0.869140;,
  0.365230;0.828120;,
  0.423830;0.828120;,
  0.369140;0.494140;,
  0.429690;0.494140;,
  0.447270;0.453120;,
  0.492190;0.453120;,
  0.507810;0.492190;,
  0.566410;0.490230;,
  0.501950;0.847660;,
  0.560550;0.847660;,
  0.486330;0.869140;,
  0.599610;0.826170;,
  0.494140;0.828120;,
  0.531250;0.828120;,
  0.500000;0.494140;,
  0.537110;0.494140;,
  0.562500;0.453120;,
  0.580080;0.494140;,
  0.609380;0.494140;,
  0.574220;0.828120;,
  0.603520;0.828120;,
  0.601560;0.828120;,
  0.605470;0.494140;,
  0.748050;0.851560;,
  0.703120;0.851560;,
  0.771480;0.607420;,
  0.726560;0.613280;,
  0.785160;0.613280;,
  0.742190;0.732420;,
  0.779300;0.851560;,
  0.814450;0.847660;,
  0.728520;0.851560;,
  0.757810;0.609380;,
  0.777340;0.607420;,
  0.699220;0.613280;,
  0.716800;0.611330;,
  0.685550;0.734380;,
  0.673830;0.855470;,
  0.650390;0.857420;,
  0.937500;0.935550;,
  0.880860;0.937500;,
  0.941410;0.847660;,
  0.884770;0.851560;,
  0.822270;0.853520;,
  0.847660;0.896480;,
  0.818360;0.941410;,
  0.873050;0.937500;,
  0.912110;0.935550;,
  0.916020;0.849610;,
  0.843750;0.853520;,
  0.777340;0.859380;,
  0.710940;0.859380;,
  0.744140;0.902340;,
  0.708980;0.945310;,
  0.777340;0.945310;,
  0.238280;0.837890;,
  0.142580;0.890620;,
  0.218750;0.888670;,
  0.177730;0.830080;,
  0.220700;0.828120;,
  0.197270;0.779300;,
  0.148440;0.767580;,
  0.189450;0.826170;,
  0.164060;0.789060;,
  0.093750;0.820310;,
  0.066410;0.736330;,
  0.089840;0.736330;,
  0.097660;0.720700;,
  0.753910;0.851560;,
  0.822270;0.605470;,
  0.839840;0.939450;,
  0.878910;0.851560;,
  0.101560;0.832030;,
  0.138670;0.705080;;
 }
}
