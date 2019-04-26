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
 116;
 -14.83244;-0.14282;-3.16454;,
 -15.31934;0.16681;-1.47251;,
 -15.22979;-0.95580;-3.10127;,
 -15.76138;-0.60689;-0.32735;,
 -14.16769;0.82767;-3.31860;,
 -14.69677;1.16314;-1.51398;,
 -0.30394;-2.40471;2.47847;,
 -5.34584;-2.43533;1.62021;,
 -0.37009;-2.91695;1.74671;,
 -4.84116;-2.63144;-0.39693;,
 -9.63537;-2.11704;-1.41591;,
 -0.34407;-2.93249;-0.60541;,
 -4.84116;-2.63144;-0.39693;,
 -0.28334;-2.42025;-1.34964;,
 -4.63452;-2.23031;-1.06970;,
 -0.20190;-1.58445;-2.00994;,
 -4.43482;-1.53903;-1.70643;,
 0.01192;-0.27944;-2.43073;,
 -4.14358;-0.42269;-2.16351;,
 0.16673;1.00769;-2.01129;,
 -4.08610;0.74149;-1.89972;,
 0.24239;1.73604;-1.30356;,
 -4.14594;1.44718;-1.34750;,
 0.25821;2.10857;-0.60762;,
 -4.26315;1.82096;-0.78307;,
 0.23098;2.11217;1.74450;,
 -4.76124;2.00434;1.23011;,
 -9.63537;-2.11704;-1.41591;,
 -9.45956;-1.77309;-1.99983;,
 -9.27376;-1.16481;-2.56265;,
 -9.02255;-0.18916;-2.96090;,
 -8.96729;0.83050;-2.72588;,
 -9.02630;1.43962;-2.24823;,
 -9.13043;1.76381;-1.74930;,
 -9.55091;1.93931;0.01145;,
 -13.91944;-1.62924;-2.22331;,
 -13.77163;-1.32301;-2.90605;,
 -13.75483;-0.69934;-3.29929;,
 -13.65666;0.19741;-3.61739;,
 -13.76537;0.97027;-3.47397;,
 -13.88563;1.44341;-3.20807;,
 -14.07791;1.75134;-2.61255;,
 -14.40447;1.86057;-1.38143;,
 -12.36957;-1.92973;-2.13306;,
 -15.08263;-1.71734;-2.51718;,
 -12.20705;-1.79217;-2.73810;,
 -14.93497;-1.38786;-3.23965;,
 -12.06442;-1.13744;-3.32681;,
 -14.90604;-0.72908;-3.66260;,
 -11.86622;-0.08851;-3.74862;,
 -14.81532;0.21564;-3.99755;,
 -11.87285;1.00467;-3.50186;,
 -14.91209;1.02425;-3.84708;,
 -11.97269;1.63321;-3.00068;,
 -15.04419;1.52221;-3.56568;,
 -12.10016;1.97462;-2.47821;,
 -15.25435;1.85556;-2.93040;,
 -12.55164;2.12498;-0.61154;,
 -15.59532;1.96681;-1.61912;,
 -15.39739;0.19297;-2.14086;,
 -15.43200;-1.60579;-1.22063;,
 -15.58897;-1.17843;-0.58445;,
 -15.71788;-0.46448;-0.32965;,
 -15.73552;0.50917;-0.17205;,
 -15.73596;1.27731;-0.51727;,
 -15.69820;1.73164;-0.91046;,
 -12.39059;0.11289;-1.44416;,
 -12.82105;-1.77937;-0.26639;,
 -12.36957;-1.92973;-2.13306;,
 -12.20705;-1.79217;-2.73810;,
 -12.06442;-1.13744;-3.32681;,
 -11.86622;-0.08851;-3.74862;,
 -11.87285;1.00467;-3.50186;,
 -11.97269;1.63321;-3.00068;,
 -12.10016;1.97462;-2.47821;,
 -12.55164;2.12498;-0.61154;,
 -12.67886;1.86595;-0.02298;,
 -12.83420;1.30779;0.58690;,
 -12.98443;0.28102;1.01806;,
 -13.02528;-0.82232;0.76194;,
 -12.93621;-1.54650;0.29611;,
 -10.05938;-1.95325;0.35661;,
 -5.41551;-1.93365;2.22027;,
 -10.13044;-1.51176;0.87196;,
 -5.47291;-1.14380;2.71905;,
 -10.17408;-0.96671;1.31427;,
 -5.34700;0.03764;2.98924;,
 -10.06959;0.07214;1.55863;,
 -5.11780;1.14813;2.52274;,
 -9.86640;1.18748;1.15103;,
 -4.91457;1.74258;1.86576;,
 -9.68554;1.69977;0.56471;,
 -4.76124;2.00434;1.23011;,
 -9.55091;1.93931;0.01145;,
 -14.49963;1.63637;-0.70112;,
 -14.53015;1.20536;-0.32441;,
 -14.53665;0.48519;-0.00175;,
 -14.51913;-0.45226;-0.14972;,
 -14.39927;-1.11751;-0.38967;,
 -14.24600;-1.52000;-0.99217;,
 -13.91944;-1.62924;-2.22331;,
 -15.69820;1.73164;-0.91046;,
 -15.73596;1.27731;-0.51727;,
 -15.73552;0.50917;-0.17205;,
 -15.71788;-0.46448;-0.32965;,
 -15.58897;-1.17843;-0.58445;,
 -15.43200;-1.60579;-1.22063;,
 -15.08263;-1.71734;-2.51718;,
 -0.21768;-1.56891;3.13816;,
 -0.00073;-0.26389;3.56937;,
 0.15095;1.02323;3.13680;,
 0.22149;1.75158;2.44054;,
 0.23098;2.11217;1.74450;,
 -0.34407;-2.93249;-0.60541;,
 -14.40447;1.86057;-1.38143;,
 -15.59532;1.96681;-1.61912;;
 
 144;
 3;0,1,2;,
 3;2,1,3;,
 3;4,5,0;,
 3;0,5,1;,
 3;6,7,8;,
 3;8,7,9;,
 3;7,10,9;,
 3;11,12,13;,
 3;12,14,13;,
 3;13,14,15;,
 3;14,16,15;,
 3;15,16,17;,
 3;16,18,17;,
 3;17,18,19;,
 3;18,20,19;,
 3;19,20,21;,
 3;20,22,21;,
 3;21,22,23;,
 3;22,24,23;,
 3;23,24,25;,
 3;24,26,25;,
 3;12,27,14;,
 3;27,28,14;,
 3;14,28,16;,
 3;28,29,16;,
 3;16,29,18;,
 3;29,30,18;,
 3;18,30,20;,
 3;30,31,20;,
 3;20,31,22;,
 3;31,32,22;,
 3;22,32,24;,
 3;32,33,24;,
 3;24,33,26;,
 3;33,34,26;,
 3;27,35,28;,
 3;35,36,28;,
 3;28,36,29;,
 3;36,37,29;,
 3;29,37,30;,
 3;37,38,30;,
 3;30,38,31;,
 3;38,39,31;,
 3;31,39,32;,
 3;39,40,32;,
 3;32,40,33;,
 3;40,41,33;,
 3;33,41,34;,
 3;41,42,34;,
 3;43,44,45;,
 3;44,46,45;,
 3;45,46,47;,
 3;46,48,47;,
 3;47,48,49;,
 3;48,50,49;,
 3;49,50,51;,
 3;50,52,51;,
 3;51,52,53;,
 3;52,54,53;,
 3;53,54,55;,
 3;54,56,55;,
 3;55,56,57;,
 3;56,58,57;,
 3;59,58,56;,
 3;59,56,54;,
 3;59,54,52;,
 3;59,52,50;,
 3;59,50,48;,
 3;59,48,46;,
 3;59,46,44;,
 3;59,44,60;,
 3;59,60,61;,
 3;59,61,62;,
 3;59,62,63;,
 3;59,63,64;,
 3;59,64,65;,
 3;59,65,58;,
 3;66,67,68;,
 3;66,68,69;,
 3;66,69,70;,
 3;66,70,71;,
 3;66,71,72;,
 3;66,72,73;,
 3;66,73,74;,
 3;66,74,75;,
 3;66,75,76;,
 3;66,76,77;,
 3;66,77,78;,
 3;66,78,79;,
 3;66,79,80;,
 3;66,80,67;,
 3;10,7,81;,
 3;7,82,81;,
 3;81,82,83;,
 3;82,84,83;,
 3;83,84,85;,
 3;84,86,85;,
 3;85,86,87;,
 3;86,88,87;,
 3;87,88,89;,
 3;88,90,89;,
 3;89,90,91;,
 3;90,92,91;,
 3;91,92,93;,
 3;93,94,91;,
 3;94,95,91;,
 3;91,95,89;,
 3;95,96,89;,
 3;89,96,87;,
 3;96,97,87;,
 3;87,97,85;,
 3;97,98,85;,
 3;85,98,83;,
 3;98,99,83;,
 3;83,99,81;,
 3;99,100,81;,
 3;81,100,10;,
 3;75,101,76;,
 3;101,102,76;,
 3;76,102,77;,
 3;102,103,77;,
 3;77,103,78;,
 3;103,104,78;,
 3;78,104,79;,
 3;104,105,79;,
 3;79,105,80;,
 3;105,106,80;,
 3;80,106,67;,
 3;106,107,67;,
 3;67,107,68;,
 3;7,6,82;,
 3;6,108,82;,
 3;82,108,84;,
 3;108,109,84;,
 3;84,109,86;,
 3;109,110,86;,
 3;86,110,88;,
 3;110,111,88;,
 3;88,111,90;,
 3;111,112,90;,
 3;90,112,92;,
 3;113,8,9;,
 3;114,94,93;,
 3;115,101,75;;
 
 MeshMaterialList {
  1;
  144;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.000000;0.417600;0.624000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  132;
  0.910735;-0.314947;0.267150;,
  0.825276;-0.462506;0.324051;,
  0.880980;-0.376036;0.287179;,
  0.949942;-0.230390;0.211025;,
  0.805767;-0.494877;0.325325;,
  0.802858;-0.497873;0.327934;,
  -0.098071;-0.736093;0.669739;,
  -0.089185;-0.969910;0.226540;,
  -0.134720;-0.926482;0.351400;,
  -0.094991;-0.994318;0.048049;,
  -0.121019;-0.990602;0.063735;,
  -0.081159;-0.817922;-0.569577;,
  -0.077378;-0.768613;-0.635017;,
  -0.045507;-0.843169;-0.535720;,
  -0.017479;-0.767395;-0.640936;,
  -0.071003;-0.534676;-0.842069;,
  0.016775;-0.530293;-0.847649;,
  -0.066646;-0.121421;-0.990361;,
  0.047284;-0.075431;-0.996029;,
  -0.059592;0.424921;-0.903267;,
  0.059069;0.444869;-0.893645;,
  -0.050199;0.742904;-0.667513;,
  0.044908;0.747985;-0.662195;,
  -0.050968;0.933634;-0.354585;,
  0.015889;0.950054;-0.311680;,
  -0.037678;0.998136;-0.048006;,
  0.001740;0.995651;-0.093144;,
  0.009571;-0.861967;-0.506875;,
  0.039163;-0.794617;-0.605847;,
  0.101618;-0.526261;-0.844229;,
  0.144908;-0.088792;-0.985453;,
  0.154036;0.425091;-0.891947;,
  0.126290;0.726777;-0.675163;,
  0.052148;0.951466;-0.303304;,
  0.011273;0.995618;-0.092833;,
  -0.005580;-0.887835;-0.460128;,
  0.052711;-0.733473;-0.677672;,
  0.098694;-0.426760;-0.898963;,
  0.143237;0.025144;-0.989369;,
  0.156906;0.453993;-0.877081;,
  0.118757;0.774831;-0.620914;,
  0.032865;0.977115;-0.210159;,
  0.008553;0.996248;-0.086123;,
  -0.043149;-0.971639;-0.232498;,
  -0.021681;-0.876894;-0.480195;,
  -0.049874;-0.942723;-0.329828;,
  0.000615;-0.726320;-0.687357;,
  0.037754;-0.536959;-0.842763;,
  0.040342;-0.421979;-0.905707;,
  0.070499;-0.173170;-0.982365;,
  0.090079;0.026463;-0.995583;,
  0.105316;0.356810;-0.928222;,
  0.115986;0.455849;-0.882468;,
  0.100737;0.674947;-0.730957;,
  0.081301;0.771660;-0.630818;,
  0.025362;0.929885;-0.366974;,
  -0.005182;0.976715;-0.214476;,
  -0.023555;0.995820;-0.088245;,
  -0.021894;0.995686;-0.090166;,
  -0.970487;-0.066971;-0.231669;,
  -0.971073;-0.093682;-0.219640;,
  -0.975899;-0.089532;-0.199012;,
  -0.980693;-0.045735;-0.190130;,
  -0.985917;-0.030846;-0.164367;,
  -0.984706;-0.066088;-0.161204;,
  -0.984541;-0.061264;-0.164089;,
  0.971546;-0.047999;0.231936;,
  0.967723;-0.071542;0.241650;,
  0.969118;-0.074057;0.235215;,
  0.974086;-0.055139;0.219352;,
  0.975144;-0.064699;0.211916;,
  0.971505;-0.068128;0.227018;,
  0.972821;-0.037584;0.228486;,
  0.970814;-0.022381;0.238789;,
  0.970301;-0.017355;0.241278;,
  0.974876;-0.013966;0.222312;,
  0.975987;-0.015645;0.217266;,
  0.972213;-0.033003;0.231759;,
  0.968894;-0.066946;0.238251;,
  0.966127;-0.069227;0.248607;,
  0.967740;-0.062128;0.244170;,
  -0.195645;-0.915875;0.350567;,
  -0.180398;-0.667934;0.722026;,
  -0.258943;-0.692022;0.673836;,
  -0.193788;-0.405124;0.893488;,
  -0.300832;-0.371137;0.878498;,
  -0.198069;0.098364;0.975240;,
  -0.303972;0.110713;0.946226;,
  -0.158797;0.579904;0.799059;,
  -0.231067;0.589039;0.774365;,
  -0.108339;0.846744;0.520852;,
  -0.150864;0.841221;0.519218;,
  -0.090356;0.926199;0.366048;,
  -0.106243;0.931392;0.348168;,
  -0.141240;0.865458;0.480660;,
  -0.226622;0.616787;0.753801;,
  -0.306579;0.212431;0.927837;,
  -0.337544;-0.237692;0.910805;,
  -0.287329;-0.628414;0.722868;,
  -0.213669;-0.890611;0.401444;,
  -0.122496;-0.990722;0.058855;,
  -0.184235;0.860089;0.475715;,
  -0.277089;0.603313;0.747820;,
  -0.369200;0.220832;0.902732;,
  -0.396753;-0.240812;0.885774;,
  -0.343846;-0.597940;0.724043;,
  -0.187964;-0.933977;0.303902;,
  -0.087436;-0.994334;0.060452;,
  -0.103129;-0.486914;0.867340;,
  -0.104287;-0.062570;0.992577;,
  -0.084004;0.482315;0.871960;,
  -0.065592;0.784337;0.616857;,
  -0.055506;0.908591;0.413983;,
  -0.066522;-0.997768;0.005856;,
  -0.101094;0.949002;0.298621;,
  -0.145925;0.945082;0.292448;,
  -0.977291;-0.048365;-0.206307;,
  -0.962295;-0.044630;-0.268321;,
  -0.952362;-0.066074;-0.297726;,
  -0.950412;-0.068019;-0.303464;,
  -0.953448;-0.036400;-0.299353;,
  -0.960363;-0.064017;-0.271303;,
  -0.963151;-0.111665;-0.244687;,
  -0.962434;-0.109652;-0.248389;,
  -0.147996;0.931596;0.332001;,
  -0.215660;0.783840;0.582311;,
  -0.309665;0.523649;0.793662;,
  -0.391226;0.020227;0.920072;,
  -0.375449;-0.372492;0.848698;,
  -0.273684;-0.787325;0.552464;,
  -0.121764;-0.980180;0.156274;,
  -0.086246;-0.994510;0.059252;;
  144;
  3;1,2,0;,
  3;0,2,3;,
  3;5,4,1;,
  3;1,4,2;,
  3;6,8,7;,
  3;7,8,9;,
  3;8,10,9;,
  3;11,13,12;,
  3;13,14,12;,
  3;12,14,15;,
  3;14,16,15;,
  3;15,16,17;,
  3;16,18,17;,
  3;17,18,19;,
  3;18,20,19;,
  3;19,20,21;,
  3;20,22,21;,
  3;21,22,23;,
  3;22,24,23;,
  3;23,24,25;,
  3;24,26,25;,
  3;13,27,14;,
  3;27,28,14;,
  3;14,28,16;,
  3;28,29,16;,
  3;16,29,18;,
  3;29,30,18;,
  3;18,30,20;,
  3;30,31,20;,
  3;20,31,22;,
  3;31,32,22;,
  3;22,32,24;,
  3;32,33,24;,
  3;24,33,26;,
  3;33,34,26;,
  3;27,35,28;,
  3;35,36,28;,
  3;28,36,29;,
  3;36,37,29;,
  3;29,37,30;,
  3;37,38,30;,
  3;30,38,31;,
  3;38,39,31;,
  3;31,39,32;,
  3;39,40,32;,
  3;32,40,33;,
  3;40,41,33;,
  3;33,41,34;,
  3;41,42,34;,
  3;43,45,44;,
  3;45,46,44;,
  3;44,46,47;,
  3;46,48,47;,
  3;47,48,49;,
  3;48,50,49;,
  3;49,50,51;,
  3;50,52,51;,
  3;51,52,53;,
  3;52,54,53;,
  3;53,54,55;,
  3;54,56,55;,
  3;55,56,57;,
  3;56,58,57;,
  3;59,116,117;,
  3;59,117,118;,
  3;59,118,119;,
  3;59,119,120;,
  3;59,120,121;,
  3;59,121,122;,
  3;59,122,123;,
  3;59,123,60;,
  3;59,60,61;,
  3;59,61,62;,
  3;59,62,63;,
  3;59,63,64;,
  3;59,64,65;,
  3;59,65,116;,
  3;66,68,67;,
  3;66,67,69;,
  3;66,69,70;,
  3;66,70,71;,
  3;66,71,72;,
  3;66,72,73;,
  3;66,73,74;,
  3;66,74,75;,
  3;66,75,76;,
  3;66,76,77;,
  3;66,77,78;,
  3;66,78,79;,
  3;66,79,80;,
  3;66,80,68;,
  3;10,8,81;,
  3;8,82,81;,
  3;81,82,83;,
  3;82,84,83;,
  3;83,84,85;,
  3;84,86,85;,
  3;85,86,87;,
  3;86,88,87;,
  3;87,88,89;,
  3;88,90,89;,
  3;89,90,91;,
  3;90,92,91;,
  3;91,92,93;,
  3;93,94,91;,
  3;94,95,91;,
  3;91,95,89;,
  3;95,96,89;,
  3;89,96,87;,
  3;96,97,87;,
  3;87,97,85;,
  3;97,98,85;,
  3;85,98,83;,
  3;98,99,83;,
  3;83,99,81;,
  3;99,100,81;,
  3;81,100,10;,
  3;124,101,125;,
  3;101,102,125;,
  3;125,102,126;,
  3;102,103,126;,
  3;126,103,127;,
  3;103,104,127;,
  3;127,104,128;,
  3;104,105,128;,
  3;128,105,129;,
  3;105,106,129;,
  3;129,106,130;,
  3;106,107,130;,
  3;130,107,131;,
  3;8,6,82;,
  3;6,108,82;,
  3;82,108,84;,
  3;108,109,84;,
  3;84,109,86;,
  3;109,110,86;,
  3;86,110,88;,
  3;110,111,88;,
  3;88,111,90;,
  3;111,112,90;,
  3;90,112,92;,
  3;113,7,9;,
  3;114,94,93;,
  3;115,101,124;;
 }
 MeshTextureCoords {
  116;
  0.308590;0.791020;,
  0.314450;0.603520;,
  0.292970;0.791020;,
  0.277340;0.494140;,
  0.320310;0.800780;,
  0.326170;0.601560;,
  0.701170;0.359380;,
  0.783200;0.433590;,
  0.697270;0.380860;,
  0.773440;0.433590;,
  0.857420;0.484380;,
  0.269530;0.384770;,
  0.197270;0.437500;,
  0.267580;0.361330;,
  0.199220;0.417970;,
  0.261720;0.326170;,
  0.197270;0.384770;,
  0.255860;0.267580;,
  0.193360;0.332030;,
  0.248050;0.208980;,
  0.183590;0.281250;,
  0.244140;0.177730;,
  0.177730;0.253910;,
  0.240230;0.162110;,
  0.173830;0.240230;,
  0.240230;0.162110;,
  0.164060;0.240230;,
  0.121090;0.488280;,
  0.123050;0.470700;,
  0.121090;0.441410;,
  0.117190;0.396480;,
  0.109380;0.351560;,
  0.103520;0.326170;,
  0.099610;0.314450;,
  0.091800;0.314450;,
  0.052730;0.533200;,
  0.052730;0.517580;,
  0.048830;0.490230;,
  0.044920;0.449220;,
  0.037110;0.417970;,
  0.033200;0.398440;,
  0.027340;0.388670;,
  0.021480;0.388670;,
  0.078120;0.523440;,
  0.035160;0.552730;,
  0.080080;0.515620;,
  0.035160;0.535160;,
  0.078120;0.486330;,
  0.031250;0.507810;,
  0.074220;0.437500;,
  0.027340;0.464840;,
  0.066410;0.390620;,
  0.019530;0.431640;,
  0.060550;0.365230;,
  0.013670;0.410160;,
  0.054690;0.351560;,
  0.007810;0.400390;,
  0.046880;0.351560;,
  0.001950;0.400390;,
  0.017580;0.474610;,
  0.029300;0.552730;,
  0.023440;0.535160;,
  0.015620;0.507810;,
  0.009770;0.464840;,
  0.003910;0.431640;,
  0.001950;0.410160;,
  0.919920;0.431640;,
  0.914060;0.519530;,
  0.906250;0.519530;,
  0.906250;0.511720;,
  0.908200;0.482420;,
  0.912110;0.433590;,
  0.919920;0.386720;,
  0.925780;0.361330;,
  0.931640;0.347660;,
  0.937500;0.347660;,
  0.937500;0.361330;,
  0.935550;0.386720;,
  0.931640;0.433590;,
  0.923830;0.480470;,
  0.917970;0.511720;,
  0.865230;0.484380;,
  0.789060;0.414060;,
  0.869140;0.466800;,
  0.796880;0.380860;,
  0.876950;0.437500;,
  0.804690;0.330080;,
  0.882810;0.392580;,
  0.810550;0.279300;,
  0.888670;0.349610;,
  0.810550;0.251950;,
  0.888670;0.324220;,
  0.810550;0.238280;,
  0.888670;0.312500;,
  0.966800;0.394530;,
  0.962890;0.414060;,
  0.958980;0.445310;,
  0.951170;0.486330;,
  0.945310;0.511720;,
  0.937500;0.527340;,
  0.933590;0.527340;,
  0.986330;0.408200;,
  0.984380;0.427730;,
  0.978520;0.460940;,
  0.970700;0.501950;,
  0.962890;0.531250;,
  0.957030;0.546880;,
  0.953120;0.546880;,
  0.707030;0.322270;,
  0.714840;0.263670;,
  0.722660;0.207030;,
  0.728520;0.175780;,
  0.730470;0.160160;,
  0.697270;0.380860;,
  0.964840;0.384770;,
  0.986330;0.396480;;
 }
}
