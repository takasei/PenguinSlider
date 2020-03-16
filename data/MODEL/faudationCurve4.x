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
 144;
 18.11020;-6.95302;-21.98573;,
 19.39137;-4.13978;-21.45505;,
 21.69271;-4.08289;-35.18429;,
 20.33263;-6.89613;-35.45483;,
 23.59907;0.01854;-19.71217;,
 21.99760;-8.69591;-20.37552;,
 24.45947;-8.63902;-34.63395;,
 25.63250;0.07543;-34.29578;,
 14.46172;-12.86322;-23.49698;,
 16.45943;-12.80633;-36.22526;,
 17.43703;-16.08365;-22.26457;,
 19.61799;-16.02676;-35.59698;,
 9.00142;-16.81229;-25.75871;,
 10.66280;-16.75540;-37.37828;,
 10.61164;-21.01999;-25.09174;,
 12.37220;-20.96310;-37.03825;,
 2.56055;-18.19902;-28.42662;,
 3.82521;-18.14213;-38.73836;,
 2.56055;-22.75340;-28.42662;,
 3.82521;-22.69651;-38.73836;,
 -3.88032;-16.81229;-31.09451;,
 -3.01238;-16.75540;-40.09845;,
 -5.49055;-21.01999;-31.76148;,
 -4.72179;-20.96310;-40.43846;,
 -9.34065;-12.86322;-33.35624;,
 -8.80904;-12.80633;-41.25147;,
 -12.31594;-16.08366;-34.58865;,
 -11.94411;-16.02677;-41.66150;,
 -11.94420;-6.94044;-33.33898;,
 -11.62519;-6.88355;-41.46896;,
 -15.83162;-8.68333;-34.94919;,
 -15.53833;-8.62644;-42.20083;,
 -13.22538;-4.12720;-33.86965;,
 -12.89843;-4.07031;-41.40282;,
 -17.43307;0.03112;-35.61254;,
 -17.23039;0.08801;-42.38611;,
 12.62742;-6.97156;-8.29951;,
 13.78045;-4.15832;-7.52908;,
 17.56729;0.00000;-4.99881;,
 16.12601;-8.71445;-5.96184;,
 9.34389;-12.88176;-10.49349;,
 12.02159;-16.10219;-8.70432;,
 4.42974;-16.83083;-13.77703;,
 5.87890;-21.03853;-12.80873;,
 -1.36689;-18.21756;-17.65021;,
 -1.36689;-22.77194;-17.65021;,
 -7.16353;-16.83083;-21.52340;,
 -8.61269;-21.03853;-22.49170;,
 -12.07768;-12.88176;-24.80695;,
 -14.75538;-16.10219;-26.59613;,
 -14.31631;-6.95898;-25.47243;,
 -17.81489;-8.70187;-27.81010;,
 -15.46934;-4.14574;-26.24285;,
 -19.25617;0.01258;-28.77313;,
 3.49324;-6.97156;4.17401;,
 4.47381;-4.15832;5.15457;,
 7.69424;0.00000;8.37500;,
 6.46853;-8.71445;7.14930;,
 0.70083;-12.88176;1.38159;,
 2.97802;-16.10220;3.65878;,
 -3.47832;-16.83083;-2.79756;,
 -2.24591;-21.03853;-1.56515;,
 -8.40795;-18.21756;-7.72718;,
 -8.40795;-22.77194;-7.72718;,
 -13.33757;-16.83083;-12.65681;,
 -14.56997;-21.03853;-13.88922;,
 -17.51672;-12.88176;-16.83595;,
 -19.79392;-16.10219;-19.11315;,
 -19.26423;-6.95897;-18.09986;,
 -22.23954;-8.70187;-21.07515;,
 -20.24482;-4.14574;-19.08043;,
 -23.46524;0.01258;-22.30087;,
 -8.70869;-6.97155;13.31145;,
 -7.93826;-4.15831;14.46447;,
 -5.40798;0.00001;18.25130;,
 -6.37102;-8.71445;16.81002;,
 -10.90268;-12.88176;10.02792;,
 -9.11349;-16.10220;12.70561;,
 -14.18621;-16.83083;5.11377;,
 -13.21791;-21.03853;6.56293;,
 -18.05941;-18.21756;-0.68287;,
 -18.05941;-22.77194;-0.68287;,
 -21.93260;-16.83083;-6.47950;,
 -22.90090;-21.03853;-7.92866;,
 -25.21616;-12.88176;-11.39366;,
 -27.00533;-16.10219;-14.07135;,
 -26.36524;-6.95898;-13.14868;,
 -28.70291;-8.70187;-16.64727;,
 -27.13567;-4.14574;-14.30172;,
 -29.66595;0.01258;-18.08855;,
 -22.54868;-6.95488;17.77231;,
 -22.01801;-4.14163;19.05346;,
 -20.27511;0.01669;23.26116;,
 -20.93846;-8.69777;21.65970;,
 -24.05992;-12.86510;14.12384;,
 -22.82752;-16.08553;17.09914;,
 -26.32166;-16.81416;8.66355;,
 -25.65469;-21.02186;10.27377;,
 -28.98957;-18.20089;2.22266;,
 -28.98957;-22.75527;2.22266;,
 -31.65747;-16.81416;-4.21822;,
 -32.32445;-21.02186;-5.82843;,
 -33.91921;-12.86509;-9.67854;,
 -35.15161;-16.08553;-12.65384;,
 -34.38556;-6.94231;-11.79851;,
 -35.99576;-8.68520;-15.68592;,
 -34.91623;-4.12907;-13.07968;,
 -36.65912;0.02925;-17.28738;,
 -36.20477;-6.97155;19.83810;,
 -35.93423;-4.15830;21.19818;,
 -35.04572;0.00002;25.66505;,
 -35.38389;-8.71444;23.96496;,
 -36.97520;-12.88177;15.96494;,
 -36.34692;-16.10220;19.12349;,
 -38.12822;-16.83083;10.16831;,
 -37.78820;-21.03853;11.87770;,
 -39.48831;-18.21756;3.33074;,
 -39.48831;-22.77194;3.33074;,
 -40.84839;-16.83084;-3.50686;,
 -41.18841;-21.03853;-5.21628;,
 -42.00142;-12.88177;-9.30353;,
 -42.62969;-16.10220;-12.46209;,
 -41.72694;-6.95898;-11.64822;,
 -42.54782;-8.70187;-15.77509;,
 -41.99748;-4.14575;-13.00832;,
 -42.88600;0.01258;-17.47519;,
 -49.84855;-6.97154;24.15365;,
 -49.84854;-4.15829;24.67986;,
 -49.84854;0.00003;25.54218;,
 -49.84855;-8.71444;23.80879;,
 -49.84854;-12.88177;15.65204;,
 -49.84854;-16.10220;18.87247;,
 -49.84854;-16.83083;9.74185;,
 -49.84854;-21.03853;11.48473;,
 -49.84855;-18.21756;2.77031;,
 -49.84855;-22.77194;2.77031;,
 -49.84855;-16.83084;-4.20126;,
 -49.84855;-21.03853;-5.94415;,
 -49.84855;-12.88177;-10.11148;,
 -49.84855;-16.10220;-13.33192;,
 -49.84855;-6.97156;-16.78490;,
 -49.84855;-8.71445;-16.44005;,
 -49.84855;-4.15832;-17.31110;,
 -49.84855;0.00001;-18.17345;;
 
 120;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,0,3,9;,
 4;5,10,11,6;,
 4;12,8,9,13;,
 4;10,14,15,11;,
 4;16,12,13,17;,
 4;14,18,19,15;,
 4;20,16,17,21;,
 4;18,22,23,19;,
 4;24,20,21,25;,
 4;22,26,27,23;,
 4;28,24,25,29;,
 4;26,30,31,27;,
 4;32,28,29,33;,
 4;30,34,35,31;,
 4;36,37,1,0;,
 4;38,39,5,4;,
 4;40,36,0,8;,
 4;39,41,10,5;,
 4;42,40,8,12;,
 4;41,43,14,10;,
 4;44,42,12,16;,
 4;43,45,18,14;,
 4;46,44,16,20;,
 4;45,47,22,18;,
 4;48,46,20,24;,
 4;47,49,26,22;,
 4;50,48,24,28;,
 4;49,51,30,26;,
 4;52,50,28,32;,
 4;51,53,34,30;,
 4;54,55,37,36;,
 4;56,57,39,38;,
 4;58,54,36,40;,
 4;57,59,41,39;,
 4;60,58,40,42;,
 4;59,61,43,41;,
 4;62,60,42,44;,
 4;61,63,45,43;,
 4;64,62,44,46;,
 4;63,65,47,45;,
 4;66,64,46,48;,
 4;65,67,49,47;,
 4;68,66,48,50;,
 4;67,69,51,49;,
 4;70,68,50,52;,
 4;69,71,53,51;,
 4;72,73,55,54;,
 4;74,75,57,56;,
 4;76,72,54,58;,
 4;75,77,59,57;,
 4;78,76,58,60;,
 4;77,79,61,59;,
 4;80,78,60,62;,
 4;79,81,63,61;,
 4;82,80,62,64;,
 4;81,83,65,63;,
 4;84,82,64,66;,
 4;83,85,67,65;,
 4;86,84,66,68;,
 4;85,87,69,67;,
 4;88,86,68,70;,
 4;87,89,71,69;,
 4;90,91,73,72;,
 4;92,93,75,74;,
 4;94,90,72,76;,
 4;93,95,77,75;,
 4;96,94,76,78;,
 4;95,97,79,77;,
 4;98,96,78,80;,
 4;97,99,81,79;,
 4;100,98,80,82;,
 4;99,101,83,81;,
 4;102,100,82,84;,
 4;101,103,85,83;,
 4;104,102,84,86;,
 4;103,105,87,85;,
 4;106,104,86,88;,
 4;105,107,89,87;,
 4;108,109,91,90;,
 4;110,111,93,92;,
 4;112,108,90,94;,
 4;111,113,95,93;,
 4;114,112,94,96;,
 4;113,115,97,95;,
 4;116,114,96,98;,
 4;115,117,99,97;,
 4;118,116,98,100;,
 4;117,119,101,99;,
 4;120,118,100,102;,
 4;119,121,103,101;,
 4;122,120,102,104;,
 4;121,123,105,103;,
 4;124,122,104,106;,
 4;123,125,107,105;,
 4;126,127,109,108;,
 4;128,129,111,110;,
 4;128,127,126,129;,
 4;130,126,108,112;,
 4;129,131,113,111;,
 4;129,126,130,131;,
 4;132,130,112,114;,
 4;131,133,115,113;,
 4;131,130,132,133;,
 4;134,132,114,116;,
 4;133,135,117,115;,
 4;133,132,134,135;,
 4;136,134,116,118;,
 4;135,137,119,117;,
 4;135,134,136,137;,
 4;138,136,118,120;,
 4;137,139,121,119;,
 4;137,136,138,139;,
 4;140,138,120,122;,
 4;139,141,123,121;,
 4;139,138,140,141;,
 4;142,140,122,124;,
 4;141,143,125,123;,
 4;141,140,142,143;;
 
 MeshMaterialList {
  3;
  120;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   1.000000;0.949000;0.200000;1.000000;;
   5.000000;
   0.450000;0.450000;0.450000;;
   0.550000;0.521950;0.110000;;
  }
  Material {
   0.571200;0.571200;0.571200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.341600;0.762400;0.800000;0.630000;;
   25.000000;
   0.120000;0.120000;0.120000;;
   0.260470;0.581330;0.610000;;
  }
 }
 MeshNormals {
  149;
  0.974834;-0.163538;0.151504;,
  0.919303;-0.365039;0.147067;,
  0.702849;-0.702539;0.111545;,
  0.384031;-0.921786;0.053203;,
  0.000755;-0.999996;-0.002544;,
  -0.388477;-0.920712;-0.037088;,
  -0.757485;-0.651143;-0.047216;,
  -0.948621;-0.313742;-0.041028;,
  -0.981624;-0.187389;-0.036063;,
  -0.887391;0.437369;-0.145757;,
  -0.857904;0.494829;-0.138366;,
  -0.703880;0.702211;-0.107015;,
  -0.384562;0.921668;-0.051392;,
  -0.000916;0.999995;0.003109;,
  0.387195;0.921115;0.040334;,
  0.762992;0.644196;0.053424;,
  0.908212;0.415986;0.045900;,
  0.908623;0.415641;0.040571;,
  0.947938;-0.179580;0.262991;,
  0.893223;-0.374403;0.248947;,
  0.683730;-0.705212;0.187589;,
  0.372715;-0.922975;0.095923;,
  0.000261;-0.999999;-0.001035;,
  -0.378664;-0.922065;-0.080060;,
  -0.747516;-0.650291;-0.135431;,
  -0.938413;-0.310827;-0.150891;,
  -0.970606;-0.189685;-0.148136;,
  -0.864981;0.439965;-0.241328;,
  -0.836070;0.497609;-0.231025;,
  -0.685022;0.704976;-0.183721;,
  -0.373310;0.922891;-0.094404;,
  -0.000441;0.999999;0.001514;,
  0.377417;0.922313;0.083042;,
  0.755195;0.639097;0.145721;,
  0.896978;0.413074;0.157483;,
  0.891583;0.427171;0.150345;,
  0.855246;-0.195016;0.480127;,
  0.806363;-0.382744;0.450871;,
  0.618899;-0.707155;0.341900;,
  0.336506;-0.923877;0.182252;,
  -0.000429;-1.000000;0.000630;,
  -0.343195;-0.923609;-0.170771;,
  -0.690080;-0.645055;-0.328168;,
  -0.866571;-0.302822;-0.396679;,
  -0.894794;-0.193629;-0.402307;,
  -0.784243;0.441917;-0.435513;,
  -0.757890;0.499720;-0.419383;,
  -0.620209;0.707084;-0.339665;,
  -0.337044;0.923849;-0.181396;,
  0.000266;1.000000;-0.000352;,
  0.342172;0.923634;0.172679;,
  0.699820;0.627164;0.341932;,
  0.826238;0.402817;0.393788;,
  0.812491;0.440045;0.382385;,
  0.696887;-0.195958;0.689890;,
  0.656128;-0.384392;0.649415;,
  0.501299;-0.709081;0.495886;,
  0.270762;-0.924702;0.267607;,
  0.000011;-1.000000;0.000135;,
  -0.270740;-0.925049;-0.266430;,
  -0.547079;-0.641448;-0.537819;,
  -0.681498;-0.296780;-0.668941;,
  -0.700071;-0.196963;-0.686372;,
  -0.636986;0.443879;-0.630253;,
  -0.614917;0.501830;-0.608312;,
  -0.501357;0.709149;-0.495730;,
  -0.270777;0.924717;-0.267540;,
  -0.000007;1.000000;-0.000106;,
  0.270772;0.924984;0.266623;,
  0.558842;0.620632;0.550011;,
  0.655132;0.394918;0.644081;,
  0.638834;0.445298;0.627376;,
  0.456540;-0.195240;0.868017;,
  0.428004;-0.383215;0.818510;,
  0.322907;-0.707654;0.628456;,
  0.170806;-0.924052;0.341983;,
  0.001293;-0.999999;-0.000748;,
  -0.153539;-0.923639;-0.351165;,
  -0.292147;-0.636368;-0.713922;,
  -0.345410;-0.290762;-0.892272;,
  -0.346179;-0.192872;-0.918129;,
  -0.412390;0.442312;-0.796426;,
  -0.396553;0.500141;-0.769808;,
  -0.319750;0.707557;-0.630177;,
  -0.169586;0.924012;-0.342698;,
  -0.000889;0.999999;0.000527;,
  0.156319;0.923688;0.349808;,
  0.309188;0.615892;0.724623;,
  0.350761;0.388065;0.852275;,
  0.336467;0.439129;0.833040;,
  0.234687;-0.192671;0.952785;,
  0.218535;-0.378679;0.899358;,
  0.161548;-0.702278;0.693331;,
  0.082516;-0.921698;0.379031;,
  0.003296;-0.999994;-0.001151;,
  -0.052037;-0.919567;-0.389473;,
  -0.074222;-0.628796;-0.774020;,
  -0.061620;-0.285966;-0.956256;,
  -0.049464;-0.183856;-0.981708;,
  -0.207288;0.436973;-0.875263;,
  -0.197839;0.494379;-0.846433;,
  -0.156468;0.701811;-0.694967;,
  -0.080570;0.921545;-0.379820;,
  -0.002635;0.999996;0.000897;,
  0.056694;0.919899;0.388036;,
  0.093651;0.611213;0.785906;,
  0.090415;0.383637;0.919047;,
  0.079873;0.424853;0.901732;,
  0.073747;-0.193492;0.978326;,
  0.067229;-0.380101;0.922498;,
  0.046280;-0.704041;0.708649;,
  0.020807;-0.922539;0.385344;,
  0.003626;-0.999993;-0.000764;,
  0.007604;-0.920842;-0.389863;,
  0.032313;-0.635535;-0.771396;,
  0.052342;-0.293963;-0.954382;,
  0.057940;-0.188001;-0.980458;,
  -0.197604;0.376052;-0.905283;,
  -0.151365;0.505634;-0.849366;,
  -0.066460;0.735144;-0.674646;,
  -0.019110;0.922434;-0.385682;,
  -0.003032;0.999995;0.000659;,
  -0.003378;0.921080;0.389359;,
  -0.061663;0.664670;0.744588;,
  -0.180170;0.407694;0.895167;,
  -0.248431;0.351345;0.902684;,
  -0.009368;-0.193123;0.981130;,
  -0.011016;-0.379442;0.925150;,
  -0.013531;-0.703382;0.710683;,
  -0.011643;-0.922307;0.386283;,
  0.002599;-0.999997;-0.000206;,
  0.036191;-0.921147;-0.387530;,
  0.080213;-0.636145;-0.767389;,
  0.095879;-0.295531;-0.950510;,
  0.093830;-0.190760;-0.977142;,
  -0.257383;0.312359;-0.914432;,
  -0.173704;0.516902;-0.838236;,
  -0.031990;0.765707;-0.642393;,
  0.013202;0.922225;-0.386429;,
  -0.002060;0.999998;0.000169;,
  -0.032364;0.921317;0.387462;,
  -0.153818;0.703247;0.694106;,
  -0.378048;0.407866;0.831098;,
  -0.491347;0.250178;0.834259;,
  -1.000000;-0.000083;0.000423;,
  -1.000000;-0.000042;0.000211;,
  -1.000000;-0.000000;-0.000001;,
  -1.000000;0.000000;0.000001;,
  -1.000000;0.000000;0.000000;;
  120;
  4;28,27,9,10;,
  4;18,19,1,0;,
  4;29,28,10,11;,
  4;19,20,2,1;,
  4;30,29,11,12;,
  4;20,21,3,2;,
  4;31,30,12,13;,
  4;21,22,4,3;,
  4;32,31,13,14;,
  4;22,23,5,4;,
  4;33,32,14,15;,
  4;23,24,6,5;,
  4;34,33,15,16;,
  4;24,25,7,6;,
  4;35,34,16,17;,
  4;25,26,8,7;,
  4;46,45,27,28;,
  4;36,37,19,18;,
  4;47,46,28,29;,
  4;37,38,20,19;,
  4;48,47,29,30;,
  4;38,39,21,20;,
  4;49,48,30,31;,
  4;39,40,22,21;,
  4;50,49,31,32;,
  4;40,41,23,22;,
  4;51,50,32,33;,
  4;41,42,24,23;,
  4;52,51,33,34;,
  4;42,43,25,24;,
  4;53,52,34,35;,
  4;43,44,26,25;,
  4;64,63,45,46;,
  4;54,55,37,36;,
  4;65,64,46,47;,
  4;55,56,38,37;,
  4;66,65,47,48;,
  4;56,57,39,38;,
  4;67,66,48,49;,
  4;57,58,40,39;,
  4;68,67,49,50;,
  4;58,59,41,40;,
  4;69,68,50,51;,
  4;59,60,42,41;,
  4;70,69,51,52;,
  4;60,61,43,42;,
  4;71,70,52,53;,
  4;61,62,44,43;,
  4;82,81,63,64;,
  4;72,73,55,54;,
  4;83,82,64,65;,
  4;73,74,56,55;,
  4;84,83,65,66;,
  4;74,75,57,56;,
  4;85,84,66,67;,
  4;75,76,58,57;,
  4;86,85,67,68;,
  4;76,77,59,58;,
  4;87,86,68,69;,
  4;77,78,60,59;,
  4;88,87,69,70;,
  4;78,79,61,60;,
  4;89,88,70,71;,
  4;79,80,62,61;,
  4;100,99,81,82;,
  4;90,91,73,72;,
  4;101,100,82,83;,
  4;91,92,74,73;,
  4;102,101,83,84;,
  4;92,93,75,74;,
  4;103,102,84,85;,
  4;93,94,76,75;,
  4;104,103,85,86;,
  4;94,95,77,76;,
  4;105,104,86,87;,
  4;95,96,78,77;,
  4;106,105,87,88;,
  4;96,97,79,78;,
  4;107,106,88,89;,
  4;97,98,80,79;,
  4;118,117,99,100;,
  4;108,109,91,90;,
  4;119,118,100,101;,
  4;109,110,92,91;,
  4;120,119,101,102;,
  4;110,111,93,92;,
  4;121,120,102,103;,
  4;111,112,94,93;,
  4;122,121,103,104;,
  4;112,113,95,94;,
  4;123,122,104,105;,
  4;113,114,96,95;,
  4;124,123,105,106;,
  4;114,115,97,96;,
  4;125,124,106,107;,
  4;115,116,98,97;,
  4;136,135,117,118;,
  4;126,127,109,108;,
  4;144,144,145,145;,
  4;137,136,118,119;,
  4;127,128,110,109;,
  4;145,145,146,146;,
  4;138,137,119,120;,
  4;128,129,111,110;,
  4;146,146,147,147;,
  4;139,138,120,121;,
  4;129,130,112,111;,
  4;147,147,147,147;,
  4;140,139,121,122;,
  4;130,131,113,112;,
  4;147,147,148,148;,
  4;141,140,122,123;,
  4;131,132,114,113;,
  4;148,148,148,148;,
  4;142,141,123,124;,
  4;132,133,115,114;,
  4;148,148,148,148;,
  4;143,142,124,125;,
  4;133,134,116,115;,
  4;148,148,148,148;;
 }
 MeshTextureCoords {
  144;
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
  0.000000;0.000000;;
 }
}
