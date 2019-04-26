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
 36;
 0.16257;-0.21153;-1.52691;,
 -2.00336;1.03346;-0.90213;,
 0.20504;1.05847;-1.55350;,
 1.57649;0.93464;3.26258;,
 1.51354;-0.42726;3.29710;,
 -0.87809;-0.42726;3.27427;,
 -2.05759;-0.23849;-0.87413;,
 -0.82872;0.93520;3.22959;,
 1.54505;-0.20945;-2.76224;,
 -9.75520;1.13842;-2.77107;,
 1.59784;1.13892;-2.79813;,
 1.63229;1.05078;-0.18812;,
 1.57770;-0.29505;-0.16382;,
 -9.78346;-0.30258;-0.11217;,
 -9.80799;-0.20996;-2.73518;,
 -9.72908;1.03423;-0.15084;,
 -9.24503;-0.03866;-2.40061;,
 -10.13312;0.93956;-2.41986;,
 -9.20207;0.94231;-2.41606;,
 -9.18623;0.90400;-1.42028;,
 -9.22737;-0.07949;-1.39324;,
 -10.15842;-0.08224;-1.39704;,
 -10.17425;-0.04393;-2.39283;,
 -10.11727;0.90126;-1.42407;,
 -0.76814;0.88055;1.00835;,
 -0.76676;0.87072;1.51554;,
 -0.81005;-0.23995;1.55231;,
 1.54609;-0.45494;3.22379;,
 -1.24266;0.89796;3.19931;,
 1.59728;0.90499;3.19069;,
 1.61517;0.87318;4.21243;,
 1.55222;-0.48872;4.24695;,
 -1.27598;-0.49379;4.25416;,
 -1.29546;-0.45041;3.23519;,
 -1.22478;0.86614;4.22105;,
 -0.81482;-0.21601;1.03633;;
 
 50;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;3,5,4;,
 3;4,5,0;,
 3;5,6,0;,
 3;0,6,1;,
 3;6,7,1;,
 3;1,7,3;,
 3;7,5,3;,
 3;8,9,10;,
 3;9,11,10;,
 3;10,11,12;,
 3;11,13,12;,
 3;12,13,8;,
 3;13,14,8;,
 3;8,14,9;,
 3;14,15,9;,
 3;9,15,11;,
 3;15,13,11;,
 3;16,17,18;,
 3;17,19,18;,
 3;18,19,20;,
 3;19,21,20;,
 3;20,21,16;,
 3;21,22,16;,
 3;16,22,17;,
 3;22,23,17;,
 3;17,23,19;,
 3;23,21,19;,
 3;24,25,26;,
 3;27,28,29;,
 3;28,30,29;,
 3;29,30,31;,
 3;30,32,31;,
 3;31,32,27;,
 3;32,33,27;,
 3;27,33,28;,
 3;33,34,28;,
 3;28,34,30;,
 3;34,32,30;,
 3;6,5,7;,
 3;2,4,0;,
 3;14,13,15;,
 3;10,12,8;,
 3;22,21,23;,
 3;18,20,16;,
 3;24,26,35;,
 3;33,32,34;,
 3;29,31,27;;
 
 MeshMaterialList {
  1;
  50;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  75;
  -0.282372;-0.009861;-0.959254;,
  -0.282775;-0.010626;-0.959127;,
  -0.001771;0.999680;0.025243;,
  0.961008;-0.044595;-0.272901;,
  -0.011622;0.029523;0.999497;,
  -0.001136;-0.998980;-0.045134;,
  -0.960477;0.045403;0.274631;,
  -0.002382;-0.026512;-0.999646;,
  -0.002382;-0.026512;-0.999646;,
  -0.000645;0.999324;0.036747;,
  0.999093;-0.040137;-0.014210;,
  0.003886;0.023327;0.999720;,
  -0.000040;-0.999377;-0.035288;,
  -0.999130;0.040189;0.011157;,
  -0.002048;-0.021528;-0.999766;,
  0.004126;-0.015925;-0.999865;,
  -0.003099;0.999254;0.038484;,
  0.998899;-0.043162;-0.018408;,
  -0.004160;0.027651;0.999609;,
  0.005353;-0.999243;-0.038519;,
  -0.998953;0.042269;0.017514;,
  0.999020;-0.042821;-0.011228;,
  0.999135;-0.040940;-0.007345;,
  0.999231;-0.039058;-0.003462;,
  -0.003513;-0.025331;-0.999673;,
  -0.002976;-0.024222;-0.999702;,
  -0.002382;0.999511;0.031165;,
  0.999023;-0.042219;-0.013086;,
  0.002739;0.024724;0.999691;,
  -0.001764;-0.999095;-0.042499;,
  -0.999050;0.038864;0.019720;,
  -0.003451;0.999638;0.026686;,
  0.960148;-0.051344;-0.274736;,
  -0.009544;0.025780;0.999622;,
  0.000428;-0.998996;-0.044796;,
  -0.000354;-0.998989;-0.044965;,
  -0.281968;-0.009096;-0.959381;,
  -0.960526;0.046987;0.274193;,
  -0.000091;0.999717;0.023799;,
  -0.013699;0.033266;0.999353;,
  0.000036;0.999430;0.033751;,
  0.999062;-0.040791;-0.014566;,
  0.004534;0.017869;0.999830;,
  0.000513;-0.999458;-0.032929;,
  0.000237;-0.999418;-0.034109;,
  -0.002381;-0.026511;-0.999646;,
  -0.999156;0.039425;0.011526;,
  -0.001325;0.999209;0.039743;,
  0.003238;0.028783;0.999580;,
  -0.003101;0.999254;0.038486;,
  0.998953;-0.042270;-0.017517;,
  -0.004160;0.027651;0.999609;,
  0.003110;-0.999172;-0.040557;,
  0.004232;-0.999209;-0.039538;,
  -0.008222;-0.027130;-0.999598;,
  -0.998953;0.042261;0.017522;,
  -0.003098;0.999255;0.038483;,
  -0.004159;0.027650;0.999609;,
  -0.002382;0.999511;0.031164;,
  0.998732;-0.046644;-0.018937;,
  0.002502;0.025224;0.999679;,
  0.001709;-0.999454;-0.033000;,
  -0.000027;-0.999287;-0.037750;,
  -0.004051;-0.026439;-0.999642;,
  -0.999040;0.039614;0.018719;,
  -0.002382;0.999511;0.031166;,
  0.002975;0.024224;0.999702;,
  -0.960425;0.043818;0.275069;,
  0.961820;-0.037844;-0.271052;,
  -0.999103;0.040953;0.010789;,
  0.999124;-0.039484;-0.013854;,
  -0.998953;0.042278;0.017506;,
  0.998843;-0.044053;-0.019300;,
  -0.999059;0.038115;0.020722;,
  0.999259;-0.037792;-0.007234;;
  50;
  3;0,0,1;,
  3;2,2,31;,
  3;3,32,3;,
  3;4,4,33;,
  3;34,35,35;,
  3;35,5,35;,
  3;0,36,0;,
  3;6,6,37;,
  3;2,38,2;,
  3;39,4,4;,
  3;7,7,8;,
  3;9,9,40;,
  3;10,41,10;,
  3;11,11,42;,
  3;43,44,44;,
  3;44,12,44;,
  3;7,45,7;,
  3;13,13,46;,
  3;9,47,9;,
  3;48,11,11;,
  3;14,14,15;,
  3;16,16,49;,
  3;17,50,17;,
  3;18,18,51;,
  3;52,53,53;,
  3;53,19,53;,
  3;14,54,14;,
  3;20,20,55;,
  3;16,56,16;,
  3;57,18,18;,
  3;22,23,22;,
  3;24,24,25;,
  3;26,26,58;,
  3;27,59,27;,
  3;28,28,60;,
  3;61,62,62;,
  3;62,29,62;,
  3;24,63,24;,
  3;30,30,64;,
  3;26,65,26;,
  3;66,28,28;,
  3;6,67,6;,
  3;3,3,68;,
  3;13,69,13;,
  3;10,10,70;,
  3;20,71,20;,
  3;17,17,72;,
  3;22,22,21;,
  3;30,73,30;,
  3;27,27,74;;
 }
 MeshTextureCoords {
  36;
  0.164060;0.091800;,
  0.195310;0.220700;,
  0.164060;0.091800;,
  0.431640;0.017580;,
  0.431640;0.017580;,
  0.427730;0.154300;,
  0.195310;0.220700;,
  0.427730;0.154300;,
  0.097660;0.011720;,
  0.076170;0.664060;,
  0.097660;0.011720;,
  0.242190;0.011720;,
  0.242190;0.011720;,
  0.220700;0.664060;,
  0.076170;0.664060;,
  0.220700;0.664060;,
  0.095700;0.630860;,
  0.093750;0.685550;,
  0.095700;0.630860;,
  0.150390;0.630860;,
  0.150390;0.630860;,
  0.148440;0.685550;,
  0.093750;0.685550;,
  0.148440;0.685550;,
  0.304690;0.150390;,
  0.332030;0.150390;,
  0.332030;0.150390;,
  0.431640;0.017580;,
  0.423830;0.179690;,
  0.431640;0.017580;,
  0.486330;0.015620;,
  0.486330;0.015620;,
  0.480470;0.179690;,
  0.423830;0.179690;,
  0.480470;0.179690;,
  0.304690;0.150390;;
 }
}
