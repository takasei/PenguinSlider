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
 308;
 -0.72145;-0.89527;0.03040;,
 0.89030;-0.86713;0.03040;,
 0.88603;-0.62257;0.62091;,
 -0.72572;-0.65071;0.62091;,
 0.87573;-0.03215;0.86551;,
 -0.73603;-0.06028;0.86551;,
 0.86542;0.55828;0.62091;,
 -0.74632;0.53014;0.62091;,
 0.86115;0.80284;0.03040;,
 -0.75060;0.77469;0.03040;,
 0.86542;0.55828;-0.56013;,
 -0.74632;0.53014;-0.56013;,
 0.87573;-0.03215;-0.80472;,
 -0.73603;-0.06028;-0.80472;,
 0.88603;-0.62257;-0.56012;,
 -0.72572;-0.65071;-0.56012;,
 0.89030;-0.86713;0.03040;,
 -0.72145;-0.89527;0.03040;,
 1.99783;-0.63560;0.62091;,
 1.98503;-0.87987;0.03040;,
 2.02873;-0.04590;0.86551;,
 2.05964;0.54380;0.62091;,
 2.07244;0.78807;0.03040;,
 2.05964;0.54380;-0.56013;,
 2.02873;-0.04590;-0.80472;,
 1.99783;-0.63560;-0.56012;,
 1.98503;-0.87987;0.03040;,
 2.69835;-0.62067;0.57291;,
 2.69444;-0.84535;0.03040;,
 2.70783;-0.07824;0.79762;,
 2.71729;0.46418;0.57291;,
 2.72121;0.68886;0.03040;,
 2.71729;0.46418;-0.51211;,
 2.70783;-0.07824;-0.73683;,
 2.69835;-0.62067;-0.51211;,
 2.69444;-0.84535;0.03040;,
 3.20702;-0.64241;0.53380;,
 3.19429;-0.85054;0.03040;,
 3.23775;-0.13994;0.74232;,
 3.26848;0.36253;0.53380;,
 3.28122;0.57065;0.03040;,
 3.26848;0.36253;-0.47301;,
 3.23775;-0.13994;-0.68153;,
 3.20702;-0.64241;-0.47301;,
 3.19429;-0.85054;0.03040;,
 4.47972;-0.58137;0.88451;,
 4.46699;-0.75017;0.03040;,
 4.51045;-0.17386;1.23831;,
 4.54118;0.23364;0.88451;,
 4.55391;0.40244;0.03040;,
 4.54118;0.23364;-0.82373;,
 4.51045;-0.17386;-1.17752;,
 4.47972;-0.58137;-0.82373;,
 4.46699;-0.75017;0.03040;,
 5.95089;-0.63048;1.32897;,
 5.93815;-0.77366;0.03039;,
 5.98162;-0.28481;1.76195;,
 6.01233;0.06085;1.32897;,
 6.02507;0.20403;0.03039;,
 6.01233;0.06085;-1.26819;,
 5.98162;-0.28481;-1.68881;,
 5.95088;-0.63048;-1.26818;,
 5.93815;-0.77366;0.03039;,
 6.19901;-0.60518;1.66170;,
 5.94707;-0.67343;0.93932;,
 6.27017;-0.65534;1.22404;,
 5.96046;-0.52264;0.92383;,
 6.30160;-0.54867;1.07070;,
 6.30160;-0.54867;1.07070;,
 5.96046;-0.52264;0.92383;,
 5.98162;-0.28481;0.89940;,
 6.33245;-0.33904;1.00733;,
 6.24567;-0.31662;1.86820;,
 6.33245;-0.33904;1.00733;,
 5.98162;-0.28481;0.89940;,
 6.00163;-0.05966;0.87627;,
 6.34724;-0.07812;1.06331;,
 6.26024;-0.10538;1.68736;,
 6.31897;0.14337;1.31914;,
 6.01696;0.11272;0.85856;,
 6.34724;-0.07812;1.06331;,
 6.00163;-0.05966;0.87627;,
 5.99689;-0.11298;-0.61512;,
 5.99838;0.00078;-0.67802;,
 6.01812;0.12591;-0.67812;,
 6.01886;0.13412;-0.60371;,
 5.98162;-0.28481;-0.62306;,
 5.98162;-0.28481;-0.67794;,
 5.99838;0.00078;-0.67802;,
 5.99689;-0.11298;-0.61512;,
 5.96595;-0.46091;-0.63119;,
 5.96484;-0.47333;-0.67786;,
 5.98162;-0.28481;-0.67794;,
 5.98162;-0.28481;-0.62306;,
 5.94475;-0.69949;-0.64220;,
 5.94508;-0.69557;-0.67775;,
 5.96484;-0.47333;-0.67786;,
 5.96595;-0.46091;-0.63119;,
 5.96294;-0.49485;0.81949;,
 5.94596;-0.68577;0.82744;,
 5.98162;-0.28481;0.81076;,
 5.96294;-0.49485;0.81949;,
 5.99988;-0.07936;0.80222;,
 5.98162;-0.28481;0.81076;,
 6.01758;0.11984;0.79393;,
 5.99988;-0.07936;0.80222;,
 6.34329;0.10526;-0.30757;,
 6.34951;0.24541;0.03039;,
 6.32132;-0.14183;-0.48396;,
 6.30605;-0.31364;-0.49043;,
 6.32132;-0.14183;-0.48396;,
 6.29039;-0.48976;-0.44477;,
 6.30605;-0.31364;-0.49043;,
 6.26259;-0.80249;0.03039;,
 6.26918;-0.72834;-0.29991;,
 6.29039;-0.48976;-0.44477;,
 6.27040;-0.71462;0.42529;,
 6.26259;-0.80249;0.03039;,
 6.28737;-0.52370;0.61518;,
 6.30605;-0.31364;0.67824;,
 6.28737;-0.52370;0.61518;,
 6.32431;-0.10821;0.61879;,
 6.30605;-0.31364;0.67824;,
 6.34202;0.09101;0.42892;,
 6.32431;-0.10821;0.61879;,
 6.30815;0.03455;-1.44122;,
 6.31394;0.16111;-1.15179;,
 6.29418;-0.04289;-0.87195;,
 6.29418;-0.04289;-0.87195;,
 6.27742;-0.31111;-0.74666;,
 6.27742;-0.31111;-1.74026;,
 6.27742;-0.31111;-0.74666;,
 6.26066;-0.49964;-0.82548;,
 6.24668;-0.65677;-1.44122;,
 6.24090;-0.72187;-0.97557;,
 6.26066;-0.49964;-0.82548;,
 6.80680;-0.62867;1.70987;,
 6.86974;-0.65877;1.42879;,
 6.89777;-0.58826;1.26306;,
 6.89777;-0.58826;1.26306;,
 6.93419;-0.41674;1.17396;,
 6.79867;-0.39799;1.87485;,
 6.93419;-0.41674;1.17396;,
 6.93756;-0.18290;1.25517;,
 6.85424;-0.05366;1.70250;,
 6.91353;0.04002;1.47422;,
 6.93756;-0.18290;1.25517;,
 6.91536;-0.01850;-0.23825;,
 6.92050;0.11910;0.04137;,
 6.89717;-0.22292;-0.38419;,
 6.88454;-0.36509;-0.38953;,
 6.89717;-0.22292;-0.38419;,
 6.87159;-0.58064;-0.35177;,
 6.88454;-0.36509;-0.38953;,
 6.84857;-0.80756;0.04137;,
 6.85403;-0.74697;-0.23192;,
 6.87159;-0.58064;-0.35177;,
 6.85504;-0.73645;0.36807;,
 6.84857;-0.80756;0.04137;,
 6.86909;-0.53887;0.52518;,
 6.88454;-0.36509;0.57736;,
 6.86909;-0.53887;0.52518;,
 6.89965;-0.19511;0.52817;,
 6.88454;-0.36509;0.57736;,
 6.91429;-0.03030;0.37108;,
 6.89965;-0.19511;0.52817;,
 6.79250;-0.05685;-1.52053;,
 6.84391;0.05593;-1.25953;,
 6.87101;-0.06090;-1.04770;,
 6.87101;-0.06090;-1.04770;,
 6.85584;-0.34379;-0.91974;,
 6.73301;-0.34379;-1.69531;,
 6.85584;-0.34379;-0.91974;,
 6.84069;-0.54696;-0.99589;,
 6.74630;-0.64927;-1.45727;,
 6.78368;-0.74315;-1.21473;,
 6.84069;-0.54696;-0.99589;,
 8.27711;-0.67885;0.00621;,
 7.50132;-0.30337;-0.12239;,
 7.50468;-0.11869;0.05969;,
 8.27844;-0.59304;0.08003;,
 8.27230;-0.73730;-0.03232;,
 7.48949;-0.45342;-0.21743;,
 8.26896;-0.77795;-0.03374;,
 7.48126;-0.55776;-0.22091;,
 7.48949;-0.45342;-0.21743;,
 8.27230;-0.73730;-0.03232;,
 8.26553;-0.81962;-0.02376;,
 7.47282;-0.66473;-0.19633;,
 7.48126;-0.55776;-0.22091;,
 8.26896;-0.77795;-0.03374;,
 8.25946;-0.89362;0.08003;,
 7.45785;-0.85465;0.05969;,
 7.46140;-0.80961;-0.11827;,
 8.26090;-0.87608;0.00788;,
 7.47282;-0.66473;-0.19633;,
 8.26553;-0.81962;-0.02376;,
 8.26117;-0.87283;0.16630;,
 7.46205;-0.80127;0.27245;,
 7.45785;-0.85465;0.05969;,
 8.25946;-0.89362;0.08003;,
 8.26488;-0.82766;0.20779;,
 7.47119;-0.68534;0.37476;,
 8.26896;-0.77796;0.22155;,
 7.48126;-0.55778;0.40872;,
 7.47119;-0.68534;0.37476;,
 8.26488;-0.82766;0.20779;,
 8.27295;-0.72935;0.20857;,
 7.49109;-0.43301;0.37670;,
 7.48126;-0.55778;0.40872;,
 8.26896;-0.77796;0.22155;,
 7.50063;-0.31204;0.32031;,
 8.27682;-0.68221;0.16710;,
 7.49109;-0.43301;0.37670;,
 8.27295;-0.72935;0.20857;,
 8.60324;-0.82551;0.06845;,
 8.60364;-0.82070;0.08988;,
 8.60187;-0.84248;0.05727;,
 8.60090;-0.85429;0.08988;,
 8.60090;-0.85428;0.05685;,
 8.60187;-0.84248;0.05727;,
 8.60090;-0.85429;0.08988;,
 8.59990;-0.86637;0.05975;,
 8.60090;-0.85428;0.05685;,
 8.60090;-0.85429;0.08988;,
 8.59813;-0.88785;0.08988;,
 8.59855;-0.88276;0.06894;,
 8.59990;-0.86637;0.05975;,
 8.60090;-0.85429;0.08988;,
 8.59862;-0.88181;0.11492;,
 8.59813;-0.88785;0.08988;,
 8.59970;-0.86870;0.12696;,
 8.60090;-0.85429;0.08988;,
 8.60090;-0.85429;0.13096;,
 8.59970;-0.86870;0.12696;,
 8.60090;-0.85429;0.08988;,
 8.60205;-0.84016;0.12720;,
 8.60090;-0.85429;0.13096;,
 8.60090;-0.85429;0.08988;,
 8.60317;-0.82649;0.11516;,
 8.60205;-0.84016;0.12720;,
 8.60090;-0.85429;0.08988;,
 7.86605;-0.45820;-1.54704;,
 7.32036;-0.24323;-1.53681;,
 7.35703;-0.08639;-1.35590;,
 7.88730;-0.36380;-1.44603;,
 7.37563;-0.18447;-1.21803;,
 7.89612;-0.38947;-1.39467;,
 7.89612;-0.38947;-1.39467;,
 7.37563;-0.18447;-1.21803;,
 7.36814;-0.45222;-1.06548;,
 7.88972;-0.58210;-1.27291;,
 7.84686;-0.58210;-1.58379;,
 7.28937;-0.45221;-1.65228;,
 7.88972;-0.58210;-1.27291;,
 7.36814;-0.45222;-1.06548;,
 7.34829;-0.60277;-1.20122;,
 7.87823;-0.64911;-1.38017;,
 7.84478;-0.66796;-1.54181;,
 7.28682;-0.63883;-1.49826;,
 7.85885;-0.70838;-1.46057;,
 7.31211;-0.74279;-1.34192;,
 7.87823;-0.64911;-1.38017;,
 7.34829;-0.60277;-1.20122;,
 8.30617;-0.64183;-1.51876;,
 8.30984;-0.63188;-1.50310;,
 8.31085;-0.64369;-1.48679;,
 8.31085;-0.64369;-1.48679;,
 8.31007;-0.65861;-1.48088;,
 8.30241;-0.66018;-1.52432;,
 8.31007;-0.65861;-1.48088;,
 8.30854;-0.67465;-1.48610;,
 8.30151;-0.67473;-1.52057;,
 8.30483;-0.68470;-1.50340;,
 8.30854;-0.67465;-1.48610;,
 7.75043;-0.60577;1.75747;,
 7.41399;-0.60704;1.75038;,
 7.45275;-0.62891;1.59254;,
 7.78151;-0.62024;1.75898;,
 7.46862;-0.60231;1.45791;,
 7.77927;-0.58199;1.67405;,
 7.77927;-0.58199;1.67405;,
 7.46862;-0.60231;1.45791;,
 7.49662;-0.52269;1.36388;,
 7.80348;-0.47600;1.50225;,
 7.75707;-0.45375;1.83279;,
 7.40862;-0.43779;1.83904;,
 7.80348;-0.47600;1.50225;,
 7.49662;-0.52269;1.36388;,
 7.49706;-0.34827;1.42268;,
 7.81088;-0.33059;1.54618;,
 7.78129;-0.34456;1.75820;,
 7.44341;-0.15537;1.74883;,
 7.80528;-0.29569;1.66608;,
 7.48228;-0.12943;1.58168;,
 7.81088;-0.33059;1.54618;,
 7.49706;-0.34827;1.42268;,
 8.17951;-0.55351;1.72740;,
 8.18576;-0.56372;1.71368;,
 8.18538;-0.55810;1.70247;,
 8.18538;-0.55810;1.70247;,
 8.18803;-0.54347;1.69216;,
 8.17889;-0.54055;1.73590;,
 8.18803;-0.54347;1.69216;,
 8.18892;-0.52969;1.69842;,
 8.18377;-0.52624;1.72539;,
 8.18708;-0.51994;1.71210;,
 8.18892;-0.52969;1.69842;;
 
 212;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;18,2,1,19;,
 4;20,4,2,18;,
 4;21,6,4,20;,
 4;22,8,6,21;,
 4;23,10,8,22;,
 4;24,12,10,23;,
 4;25,14,12,24;,
 4;26,16,14,25;,
 4;27,18,19,28;,
 4;29,20,18,27;,
 4;30,21,20,29;,
 4;31,22,21,30;,
 4;32,23,22,31;,
 4;33,24,23,32;,
 4;34,25,24,33;,
 4;35,26,25,34;,
 4;36,27,28,37;,
 4;38,29,27,36;,
 4;39,30,29,38;,
 4;40,31,30,39;,
 4;41,32,31,40;,
 4;42,33,32,41;,
 4;43,34,33,42;,
 4;44,35,34,43;,
 4;45,36,37,46;,
 4;47,38,36,45;,
 4;48,39,38,47;,
 4;49,40,39,48;,
 4;50,41,40,49;,
 4;51,42,41,50;,
 4;52,43,42,51;,
 4;53,44,43,52;,
 4;54,45,46,55;,
 4;56,47,45,54;,
 4;57,48,47,56;,
 4;58,49,48,57;,
 4;59,50,49,58;,
 4;60,51,50,59;,
 4;61,52,51,60;,
 4;62,53,52,61;,
 4;63,54,64,65;,
 4;65,64,66,67;,
 4;68,69,70,71;,
 4;72,56,54,63;,
 4;73,74,75,76;,
 4;77,57,56,72;,
 4;78,79,57,77;,
 4;80,81,79,78;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,66,64,99;,
 4;100,70,69,101;,
 4;102,75,74,103;,
 4;104,79,81,105;,
 4;106,85,58,107;,
 4;108,82,85,106;,
 4;109,86,89,110;,
 4;111,90,93,112;,
 4;113,62,94,114;,
 4;114,94,97,115;,
 4;116,99,55,117;,
 4;118,98,99,116;,
 4;119,100,101,120;,
 4;121,102,103,122;,
 4;107,58,104,123;,
 4;123,104,105,124;,
 4;125,59,84,126;,
 4;126,84,83,127;,
 4;128,88,87,129;,
 4;130,60,59,125;,
 4;131,92,91,132;,
 4;133,61,60,130;,
 4;134,95,61,133;,
 4;135,96,95,134;,
 4;136,63,65,137;,
 4;137,65,67,138;,
 4;139,68,71,140;,
 4;141,72,63,136;,
 4;142,73,76,143;,
 4;144,77,72,141;,
 4;145,78,77,144;,
 4;146,80,78,145;,
 4;147,106,107,148;,
 4;149,108,106,147;,
 4;150,109,110,151;,
 4;152,111,112,153;,
 4;154,113,114,155;,
 4;155,114,115,156;,
 4;157,116,117,158;,
 4;159,118,116,157;,
 4;160,119,120,161;,
 4;162,121,122,163;,
 4;148,107,123,164;,
 4;164,123,124,165;,
 4;166,125,126,167;,
 4;167,126,127,168;,
 4;169,128,129,170;,
 4;171,130,125,166;,
 4;172,131,132,173;,
 4;174,133,130,171;,
 4;175,134,133,174;,
 4;176,135,134,175;,
 4;177,178,179,180;,
 4;181,182,178,177;,
 4;183,184,185,186;,
 4;187,188,189,190;,
 4;191,192,193,194;,
 4;194,193,195,196;,
 4;197,198,199,200;,
 4;201,202,198,197;,
 4;203,204,205,206;,
 4;207,208,209,210;,
 4;180,179,211,212;,
 4;212,211,213,214;,
 4;215,177,180,216;,
 4;217,181,177,215;,
 4;217,215,216,218;,
 4;219,183,186,220;,
 3;219,220,221;,
 4;222,187,190,223;,
 3;222,223,224;,
 4;225,191,194,226;,
 4;226,194,196,227;,
 4;226,227,228,225;,
 4;229,197,200,230;,
 4;231,201,197,229;,
 4;231,229,230,232;,
 4;233,203,206,234;,
 3;233,234,235;,
 4;236,207,210,237;,
 3;236,237,238;,
 4;216,180,212,239;,
 4;239,212,214,240;,
 4;239,240,241,216;,
 4;242,243,244,245;,
 4;245,244,246,247;,
 4;248,249,250,251;,
 4;252,253,243,242;,
 4;254,255,256,257;,
 4;258,259,253,252;,
 4;260,261,259,258;,
 4;262,263,261,260;,
 4;264,242,245,265;,
 4;265,245,247,266;,
 3;265,266,264;,
 4;267,248,251,268;,
 4;269,252,242,264;,
 4;268,269,264,267;,
 4;270,254,257,271;,
 4;272,258,252,269;,
 4;271,272,269,270;,
 4;273,260,258,272;,
 4;274,262,260,273;,
 3;274,273,272;,
 4;275,276,277,278;,
 4;278,277,279,280;,
 4;281,282,283,284;,
 4;285,286,276,275;,
 4;287,288,289,290;,
 4;291,292,286,285;,
 4;293,294,292,291;,
 4;295,296,294,293;,
 4;297,275,278,298;,
 4;298,278,280,299;,
 3;298,299,297;,
 4;300,281,284,301;,
 4;302,285,275,297;,
 4;301,302,297,300;,
 4;303,287,290,304;,
 4;305,291,285,302;,
 4;304,305,302,303;,
 4;306,293,291,305;,
 4;307,295,293,306;,
 3;307,306,305;,
 4;137,277,276,136;,
 4;138,279,277,137;,
 4;140,283,282,139;,
 4;136,276,286,141;,
 4;143,289,288,142;,
 4;141,286,292,144;,
 4;144,292,294,145;,
 4;145,294,296,146;,
 4;148,179,178,147;,
 4;147,178,182,149;,
 4;151,185,184,150;,
 4;153,189,188,152;,
 4;155,193,192,154;,
 4;156,195,193,155;,
 4;158,199,198,157;,
 4;157,198,202,159;,
 4;161,205,204,160;,
 4;163,209,208,162;,
 4;164,211,179,148;,
 4;165,213,211,164;,
 4;167,244,243,166;,
 4;168,246,244,167;,
 4;170,250,249,169;,
 4;166,243,253,171;,
 4;173,256,255,172;,
 4;171,253,259,174;,
 4;174,259,261,175;,
 4;175,261,263,176;;
 
 MeshMaterialList {
  8;
  212;
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  1,
  0,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1;;
  Material {
   0.204000;0.533600;0.708800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.316800;0.304000;0.244800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.558400;0.545600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.496000;0.166400;0.156800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.075200;0.075200;0.075200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  288;
  0.017457;-0.999848;0.000003;,
  0.012343;-0.706999;0.707106;,
  0.000000;0.000000;1.000000;,
  -0.012345;0.707002;0.707104;,
  -0.017460;0.999848;0.000006;,
  -0.012345;0.707001;-0.707105;,
  0.000000;-0.000007;-1.000000;,
  0.012343;-0.707002;-0.707104;,
  0.002889;-0.999996;0.000003;,
  0.002027;-0.707144;0.707066;,
  0.000021;-0.000000;1.000000;,
  -0.001887;0.707144;0.707067;,
  -0.002650;0.999996;0.000006;,
  -0.001887;0.707143;-0.707068;,
  0.000021;-0.000008;-1.000000;,
  0.002027;-0.707146;-0.707065;,
  0.018729;-0.999825;0.000002;,
  0.027749;-0.707634;0.706034;,
  0.049777;-0.001865;0.998759;,
  0.072149;0.704195;0.706331;,
  0.081517;0.996672;0.000005;,
  0.072154;0.704195;-0.706331;,
  0.049782;-0.001871;-0.998758;,
  0.027752;-0.707637;-0.706031;,
  0.019249;-0.999815;0.000002;,
  0.043563;-0.707712;0.705157;,
  0.101027;-0.004431;0.994874;,
  0.156731;0.695278;0.701444;,
  0.179283;0.983798;0.000002;,
  0.156733;0.695281;-0.701441;,
  0.101028;-0.004433;-0.994874;,
  0.043561;-0.707716;-0.705153;,
  0.012506;-0.999922;0.000002;,
  -0.052599;-0.750582;0.658681;,
  -0.091070;0.005562;0.995829;,
  0.047654;0.752679;0.656661;,
  0.147065;0.989127;0.000002;,
  0.047649;0.752681;-0.656659;,
  -0.091078;0.005562;-0.995828;,
  -0.052604;-0.750583;-0.658679;,
  -0.003958;-0.999992;0.000002;,
  -0.144576;-0.839663;0.523511;,
  -0.267029;-0.593800;0.759010;,
  -0.053930;0.852259;0.520333;,
  0.098233;0.995163;0.000002;,
  -0.053837;0.851311;-0.521891;,
  -0.197394;0.622710;-0.757144;,
  -0.144324;-0.838732;-0.525071;,
  -0.033354;-0.999444;-0.000246;,
  -0.230976;-0.871413;0.432769;,
  -0.389254;-0.625728;0.675977;,
  -0.145831;0.868402;0.473932;,
  0.075767;0.997121;-0.002859;,
  -0.115684;0.878572;-0.463388;,
  -0.165936;0.712418;-0.681855;,
  -0.207487;-0.876569;-0.434253;,
  0.869500;-0.203639;0.450001;,
  0.927789;0.081495;0.364096;,
  0.894231;0.068215;0.442377;,
  0.996493;-0.081102;-0.020596;,
  0.940730;-0.166611;0.295413;,
  -0.041699;-0.993229;0.108430;,
  0.389042;-0.363266;-0.846572;,
  0.359654;-0.098748;-0.927846;,
  0.514675;0.149518;-0.844248;,
  -0.236336;0.916619;0.322419;,
  -0.190305;-0.863853;0.466413;,
  -0.308033;-0.578696;0.755133;,
  -0.133563;0.793314;0.593981;,
  0.012786;-0.996049;-0.087881;,
  0.295137;-0.526942;-0.797011;,
  0.324044;-0.090823;-0.941672;,
  0.428418;0.327763;-0.842039;,
  -0.126621;0.907088;0.401445;,
  0.842301;0.009066;-0.538931;,
  0.863110;0.056525;-0.501843;,
  0.946469;-0.149969;-0.285844;,
  0.882763;-0.178514;-0.434583;,
  0.902397;0.088279;0.421766;,
  0.867963;-0.182344;0.461942;,
  0.886471;-0.224223;0.404836;,
  0.996071;-0.088563;0.000020;,
  0.960475;0.025370;0.277206;,
  -0.017432;-0.999848;-0.000925;,
  0.137736;0.990425;-0.009282;,
  0.335880;0.207771;-0.918703;,
  0.166922;0.843431;-0.510648;,
  0.281894;-0.081086;-0.956013;,
  0.314985;-0.294796;-0.902153;,
  0.010750;-0.900953;-0.433783;,
  0.162468;0.872767;0.460306;,
  0.329594;-0.373536;0.867086;,
  0.013330;-0.919711;0.392369;,
  0.312559;-0.020648;0.949674;,
  0.379521;0.331810;0.863635;,
  -0.066353;0.824691;-0.561677;,
  -0.069864;0.655898;-0.751610;,
  -0.140159;-0.862619;-0.486050;,
  -0.116206;-0.975105;-0.188855;,
  0.043732;0.997639;-0.052954;,
  0.418174;0.435113;0.797375;,
  0.324378;-0.008703;0.945887;,
  0.336773;-0.389734;0.857141;,
  -0.036157;-0.851941;0.522387;,
  -0.028505;-0.270116;0.962406;,
  0.056792;0.732594;0.678293;,
  0.052278;-0.989701;-0.133260;,
  0.171750;-0.760290;-0.626467;,
  0.300121;-0.137059;-0.944003;,
  0.342892;0.482778;-0.805823;,
  0.086279;0.915422;0.393140;,
  -0.040705;-0.999170;-0.001415;,
  0.340266;0.940001;-0.024836;,
  0.278118;0.280222;-0.918763;,
  0.319914;0.688760;-0.650589;,
  0.200961;-0.099546;-0.974528;,
  0.135506;-0.386104;-0.912448;,
  0.031167;-0.820167;-0.571275;,
  0.299276;0.737297;0.605662;,
  0.109061;-0.482976;0.868815;,
  0.007060;-0.857912;0.513749;,
  0.214823;-0.025285;0.976326;,
  0.281351;0.422250;0.861712;,
  0.128641;0.721180;-0.680699;,
  0.096806;0.533947;-0.839958;,
  -0.039186;-0.809580;-0.585700;,
  -0.052274;-0.933617;-0.354439;,
  0.252122;0.967659;0.008451;,
  0.315185;0.636485;0.703949;,
  0.299368;-0.026838;0.953760;,
  0.210204;-0.583084;0.784747;,
  -0.060452;-0.998170;-0.001221;,
  0.403792;0.681841;-0.609955;,
  0.330450;0.258538;-0.907723;,
  0.396728;0.589066;-0.703995;,
  0.222903;-0.105945;-0.969067;,
  0.149385;-0.371224;-0.916448;,
  0.029978;-0.805011;-0.592502;,
  0.390255;0.627800;0.673475;,
  0.103826;-0.478498;0.871929;,
  -0.012404;-0.854962;0.518542;,
  0.241990;-0.027875;0.969878;,
  0.340967;0.363555;0.866931;,
  -0.015966;-0.999872;-0.000876;,
  0.431546;0.694755;-0.575399;,
  0.320013;0.259045;-0.911311;,
  0.404247;0.597573;-0.692453;,
  0.218276;-0.114872;-0.969103;,
  0.152945;-0.368476;-0.916969;,
  0.060973;-0.796594;-0.601432;,
  0.408013;0.644783;0.646359;,
  0.122172;-0.487310;0.864641;,
  0.022695;-0.860649;0.508693;,
  0.241061;-0.026846;0.970139;,
  0.338842;0.388894;0.856707;,
  0.017061;-0.999854;-0.000777;,
  0.498131;0.867035;-0.010776;,
  0.996633;-0.081987;0.000024;,
  0.329638;0.259829;-0.907649;,
  0.420394;0.640934;-0.642240;,
  0.236361;-0.116971;-0.964599;,
  0.175664;-0.371844;-0.911523;,
  0.091962;-0.797827;-0.595832;,
  0.411841;0.697581;0.586317;,
  0.147154;-0.490669;0.858830;,
  0.053731;-0.862231;0.503657;,
  0.257096;-0.028390;0.965969;,
  0.348328;0.418494;0.838767;,
  0.200846;0.601314;-0.773358;,
  0.057643;-0.096407;-0.993672;,
  -0.062532;-0.750550;-0.657848;,
  -0.058713;-0.879437;-0.472380;,
  0.229728;0.754942;-0.614237;,
  0.411147;0.642560;0.646587;,
  0.371863;0.129759;0.919174;,
  0.164700;-0.705934;0.688863;,
  0.241145;0.520295;-0.819233;,
  0.083790;-0.074360;-0.993705;,
  -0.024119;-0.692763;-0.720762;,
  -0.029996;-0.874883;-0.483406;,
  0.296972;0.699784;-0.649700;,
  0.490529;0.617242;0.615137;,
  0.447142;0.420943;0.789221;,
  0.133608;-0.755373;0.641530;,
  0.264487;0.502528;-0.823111;,
  0.110214;-0.048474;-0.992725;,
  0.023692;-0.656209;-0.754207;,
  0.002619;-0.880312;-0.474389;,
  0.337931;0.706035;-0.622348;,
  0.520845;0.589408;0.617510;,
  0.461946;0.386545;0.798241;,
  0.126180;-0.741574;0.658898;,
  -0.050721;-0.775129;0.629764;,
  0.025276;-0.049928;0.998433;,
  0.194661;0.701570;0.685498;,
  0.040277;-0.999188;0.000626;,
  0.223952;-0.856269;-0.465456;,
  0.283108;-0.725912;-0.626818;,
  0.378183;0.503984;-0.776516;,
  0.391161;0.906916;-0.156512;,
  0.015008;-0.564423;0.825349;,
  0.138835;-0.006462;0.990295;,
  0.309989;0.666201;0.678294;,
  0.040565;-0.994084;-0.100759;,
  0.191458;-0.855505;-0.481098;,
  0.234161;-0.771482;-0.591595;,
  0.466213;0.556692;-0.687560;,
  0.484703;0.874673;0.003172;,
  0.123879;-0.408590;0.904272;,
  0.118477;-0.493313;0.861745;,
  0.350214;0.653993;0.670555;,
  0.128165;-0.320183;0.938646;,
  0.091622;-0.825240;-0.557300;,
  0.098916;-0.733516;-0.672435;,
  0.535856;0.569871;-0.622981;,
  0.510378;0.855331;0.089012;,
  -0.197687;0.625349;0.754890;,
  -0.266344;-0.591224;-0.761259;,
  -0.214513;0.711125;0.669541;,
  -0.280423;-0.674903;-0.682546;,
  0.449577;-0.493654;-0.744437;,
  -0.133793;0.638470;0.757928;,
  0.903688;0.100730;-0.416176;,
  0.480296;0.508516;-0.714652;,
  0.996070;-0.088573;0.000029;,
  0.996072;-0.088549;0.000023;,
  0.996073;-0.088539;-0.000043;,
  0.035589;0.967766;-0.249323;,
  0.525115;0.218648;-0.822464;,
  0.402487;-0.061129;-0.913383;,
  0.425859;-0.127266;-0.895795;,
  -0.029785;-0.985825;-0.165114;,
  0.584502;-0.231103;-0.777784;,
  -0.019840;-0.986237;0.164141;,
  0.604635;-0.316333;0.730993;,
  0.444114;-0.020807;0.895729;,
  0.440296;0.103427;0.891876;,
  0.046510;0.970119;0.238129;,
  0.611994;0.245863;0.751675;,
  -0.216571;0.943349;-0.251375;,
  0.657171;0.264132;0.705946;,
  0.363288;-0.023307;0.931386;,
  0.311512;-0.206909;0.927442;,
  -0.149896;-0.660339;-0.735856;,
  -0.182293;-0.975398;-0.123969;,
  0.392634;-0.483725;0.782207;,
  0.011841;0.554820;0.831887;,
  0.333580;0.666976;-0.666234;,
  -0.023485;-0.630766;-0.775618;,
  0.193063;-0.701722;0.685793;,
  0.434729;0.732161;0.524357;,
  0.401277;0.740816;0.538673;,
  0.996659;-0.081675;-0.000018;,
  0.996683;-0.081386;-0.000011;,
  0.996683;-0.081388;-0.000012;,
  0.996618;-0.082179;-0.000025;,
  0.996617;-0.082188;0.000018;,
  0.996634;-0.081984;0.000060;,
  0.996631;-0.082011;0.000134;,
  0.996592;-0.082490;0.000103;,
  0.996629;-0.082037;0.000207;,
  0.996602;-0.082370;-0.000000;,
  0.996666;-0.081593;-0.000006;,
  0.996682;-0.081390;-0.000013;,
  0.499222;0.769938;0.397459;,
  0.399605;0.805570;0.437462;,
  0.139662;-0.698341;0.702008;,
  0.112761;-0.768264;0.630123;,
  0.168391;-0.753315;0.635736;,
  0.126647;-0.807014;0.576792;,
  0.539489;0.746718;0.389055;,
  0.980699;-0.124774;-0.150536;,
  0.979248;-0.130240;-0.155277;,
  0.979287;-0.105541;-0.172794;,
  0.165057;-0.620889;0.766325;,
  0.980163;-0.046526;-0.192657;,
  0.083819;-0.841779;0.533275;,
  0.979686;-0.017743;-0.199753;,
  0.407871;0.283250;-0.867992;,
  0.351437;0.288518;-0.890646;,
  0.082338;-0.899038;-0.430059;,
  0.920175;0.361594;0.150090;,
  0.969004;0.158197;0.189749;,
  0.970291;-0.110235;0.215370;,
  0.465926;0.288296;-0.836539;,
  0.290964;0.497258;0.817358;,
  0.970173;-0.131299;0.203778;,
  0.975604;-0.094689;0.198069;;
  212;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  4;17,9,8,16;,
  4;18,10,9,17;,
  4;19,11,10,18;,
  4;20,12,11,19;,
  4;21,13,12,20;,
  4;22,14,13,21;,
  4;23,15,14,22;,
  4;16,8,15,23;,
  4;25,17,16,24;,
  4;26,18,17,25;,
  4;27,19,18,26;,
  4;28,20,19,27;,
  4;29,21,20,28;,
  4;30,22,21,29;,
  4;31,23,22,30;,
  4;24,16,23,31;,
  4;33,25,24,32;,
  4;34,26,25,33;,
  4;35,27,26,34;,
  4;36,28,27,35;,
  4;37,29,28,36;,
  4;38,30,29,37;,
  4;39,31,30,38;,
  4;32,24,31,39;,
  4;41,33,32,40;,
  4;42,34,33,41;,
  4;43,35,34,216;,
  4;44,36,35,43;,
  4;45,37,36,44;,
  4;46,38,37,45;,
  4;47,39,38,217;,
  4;40,32,39,47;,
  4;49,41,40,48;,
  4;50,42,41,49;,
  4;51,43,216,218;,
  4;52,44,43,51;,
  4;53,45,44,52;,
  4;54,46,45,53;,
  4;55,47,217,219;,
  4;48,40,47,55;,
  4;66,49,61,69;,
  4;220,220,62,70;,
  4;70,62,63,71;,
  4;67,50,49,66;,
  4;71,63,64,72;,
  4;68,51,218,221;,
  4;73,65,51,68;,
  4;72,64,222,223;,
  4;74,58,57,75;,
  4;59,59,58,74;,
  4;76,60,59,59;,
  4;77,56,60,76;,
  4;79,224,225,80;,
  4;81,81,224,79;,
  4;82,226,81,81;,
  4;78,222,226,82;,
  4;86,227,52,84;,
  4;85,74,75,228;,
  4;87,229,74,85;,
  4;88,230,229,87;,
  4;83,48,231,89;,
  4;232,77,76,88;,
  4;92,233,48,83;,
  4;91,79,80,234;,
  4;93,235,79,91;,
  4;94,236,235,93;,
  4;84,52,237,90;,
  4;238,78,82,94;,
  4;95,53,239,99;,
  4;240,57,58,100;,
  4;100,58,241,101;,
  4;96,54,53,95;,
  4;101,241,242,102;,
  4;97,55,219,243;,
  4;98,244,55,97;,
  4;102,60,56,245;,
  4;103,66,69,106;,
  4;106,69,70,107;,
  4;107,70,71,108;,
  4;104,67,66,103;,
  4;108,71,72,109;,
  4;105,68,221,246;,
  4;110,73,68,105;,
  4;109,72,223,247;,
  4;114,86,84,112;,
  4;113,85,86,114;,
  4;115,87,85,113;,
  4;116,88,87,115;,
  4;111,83,89,117;,
  4;117,89,88,116;,
  4;120,92,83,111;,
  4;119,91,92,120;,
  4;121,93,91,119;,
  4;122,94,93,121;,
  4;112,84,90,118;,
  4;118,90,94,122;,
  4;123,95,99,127;,
  4;127,99,100,128;,
  4;128,100,101,129;,
  4;124,96,95,123;,
  4;129,101,102,130;,
  4;125,97,243,248;,
  4;126,98,97,125;,
  4;130,102,245,249;,
  4;146,134,132,144;,
  4;145,133,134,146;,
  4;147,135,133,145;,
  4;148,136,135,147;,
  4;143,131,137,149;,
  4;149,137,136,148;,
  4;152,140,131,143;,
  4;151,139,140,152;,
  4;153,141,139,151;,
  4;154,142,141,153;,
  4;250,251,138,150;,
  4;150,138,142,154;,
  4;159,146,144,156;,
  4;158,145,146,159;,
  4;252,253,254,157;,
  4;160,147,145,158;,
  3;255,252,157;,
  4;161,148,147,160;,
  3;256,255,157;,
  4;155,143,149,162;,
  4;162,149,148,161;,
  4;257,256,157,258;,
  4;165,152,143,155;,
  4;164,151,152,165;,
  4;259,260,258,157;,
  4;166,153,151,164;,
  3;261,259,157;,
  4;167,154,153,166;,
  3;262,261,157;,
  4;156,250,150,163;,
  4;163,150,154,167;,
  4;263,262,157,254;,
  4;176,168,172,180;,
  4;264,265,173,181;,
  4;181,173,174,182;,
  4;177,169,168,176;,
  4;266,267,175,183;,
  4;178,170,169,177;,
  4;179,171,170,178;,
  4;183,175,268,269;,
  4;184,176,180,188;,
  4;270,264,181,189;,
  3;271,272,272;,
  4;189,181,182,190;,
  4;185,177,176,184;,
  4;273,273,272,272;,
  4;274,266,183,191;,
  4;186,178,177,185;,
  4;275,275,273,273;,
  4;187,179,178,186;,
  4;191,183,269,276;,
  3;275,277,275;,
  4;200,192,195,203;,
  4;203,195,196,204;,
  4;204,196,197,205;,
  4;201,193,192,200;,
  4;278,279,198,206;,
  4;202,194,193,201;,
  4;207,199,194,202;,
  4;206,198,199,207;,
  4;208,200,211,211;,
  4;280,203,204,212;,
  3;281,282,282;,
  4;212,204,205,213;,
  4;209,201,200,208;,
  4;283,283,282,282;,
  4;284,278,206,214;,
  4;210,202,201,285;,
  4;286,286,283,283;,
  4;215,207,202,210;,
  4;214,206,207,215;,
  3;286,287,286;,
  4;106,195,192,103;,
  4;107,196,195,106;,
  4;108,197,196,107;,
  4;103,192,193,104;,
  4;109,198,279,108;,
  4;104,193,194,105;,
  4;105,194,199,110;,
  4;247,199,198,109;,
  4;112,132,134,114;,
  4;114,134,133,113;,
  4;113,133,135,115;,
  4;115,135,136,116;,
  4;117,137,131,111;,
  4;116,136,137,117;,
  4;111,131,140,120;,
  4;120,140,139,119;,
  4;119,139,141,121;,
  4;121,141,142,122;,
  4;118,138,251,112;,
  4;122,142,138,118;,
  4;127,172,168,123;,
  4;128,173,265,127;,
  4;129,174,173,128;,
  4;123,168,169,124;,
  4;130,175,174,129;,
  4;248,169,170,125;,
  4;125,170,171,126;,
  4;249,268,175,130;;
 }
 MeshTextureCoords {
  308;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.087490;1.000000;,
  0.087490;1.000000;,
  0.105500;1.000000;,
  0.105500;1.000000;,
  0.144500;1.000000;,
  0.144500;1.000000;,
  0.217070;1.000000;,
  0.217070;1.000000;,
  0.250000;1.000000;,
  0.282930;1.000000;,
  0.282930;1.000000;,
  0.353210;1.000000;,
  0.353210;1.000000;,
  0.375000;1.000000;,
  0.420280;1.000000;,
  0.420280;1.000000;,
  0.396790;1.000000;,
  0.396790;1.000000;,
  0.593570;1.000000;,
  0.596600;1.000000;,
  0.568200;1.000000;,
  0.561040;1.000000;,
  0.709740;1.000000;,
  0.711610;1.000000;,
  0.653400;1.000000;,
  0.656430;1.000000;,
  0.844340;1.000000;,
  0.846590;1.000000;,
  0.788390;1.000000;,
  0.790260;1.000000;,
  0.935260;1.000000;,
  0.931830;1.000000;,
  0.903410;1.000000;,
  0.905660;1.000000;,
  0.100480;1.000000;,
  0.076720;1.000000;,
  0.214060;1.000000;,
  0.149520;1.000000;,
  0.349650;1.000000;,
  0.285940;1.000000;,
  0.426500;1.000000;,
  0.400350;1.000000;,
  0.561040;1.000000;,
  0.500000;1.000000;,
  0.593570;1.000000;,
  0.709740;1.000000;,
  0.656430;1.000000;,
  0.844340;1.000000;,
  0.790260;1.000000;,
  1.000000;1.000000;,
  0.935260;1.000000;,
  0.905660;1.000000;,
  0.076720;1.000000;,
  0.000000;1.000000;,
  0.100480;1.000000;,
  0.214060;1.000000;,
  0.149520;1.000000;,
  0.349650;1.000000;,
  0.285940;1.000000;,
  0.426500;1.000000;,
  0.400350;1.000000;,
  0.625000;1.000000;,
  0.568200;1.000000;,
  0.596600;1.000000;,
  0.653400;1.000000;,
  0.711610;1.000000;,
  0.750000;1.000000;,
  0.788390;1.000000;,
  0.846590;1.000000;,
  0.875000;1.000000;,
  0.931830;1.000000;,
  0.903410;1.000000;,
  0.125000;1.000000;,
  0.087490;1.000000;,
  0.105500;1.000000;,
  0.144500;1.000000;,
  0.217070;1.000000;,
  0.250000;1.000000;,
  0.282930;1.000000;,
  0.353210;1.000000;,
  0.375000;1.000000;,
  0.420280;1.000000;,
  0.396790;1.000000;,
  0.561040;1.000000;,
  0.500000;1.000000;,
  0.593570;1.000000;,
  0.709740;1.000000;,
  0.656430;1.000000;,
  0.844340;1.000000;,
  0.790260;1.000000;,
  1.000000;1.000000;,
  0.935260;1.000000;,
  0.905660;1.000000;,
  0.076720;1.000000;,
  0.000000;1.000000;,
  0.100480;1.000000;,
  0.214060;1.000000;,
  0.149520;1.000000;,
  0.349650;1.000000;,
  0.285940;1.000000;,
  0.426500;1.000000;,
  0.400350;1.000000;,
  0.625000;1.000000;,
  0.568200;1.000000;,
  0.596600;1.000000;,
  0.653400;1.000000;,
  0.711610;1.000000;,
  0.750000;1.000000;,
  0.788390;1.000000;,
  0.846590;1.000000;,
  0.875000;1.000000;,
  0.931830;1.000000;,
  0.903410;1.000000;,
  0.561040;1.000000;,
  0.561040;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.593570;1.000000;,
  0.593570;1.000000;,
  0.709740;1.000000;,
  0.709740;1.000000;,
  0.656430;1.000000;,
  0.656430;1.000000;,
  0.844340;1.000000;,
  0.844340;1.000000;,
  0.790260;1.000000;,
  0.790260;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.935260;1.000000;,
  0.935260;1.000000;,
  0.905660;1.000000;,
  0.905660;1.000000;,
  0.076720;1.000000;,
  0.076720;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.100480;1.000000;,
  0.100480;1.000000;,
  0.214060;1.000000;,
  0.214060;1.000000;,
  0.149520;1.000000;,
  0.149520;1.000000;,
  0.349650;1.000000;,
  0.349650;1.000000;,
  0.285940;1.000000;,
  0.285940;1.000000;,
  0.426500;1.000000;,
  0.426500;1.000000;,
  0.400350;1.000000;,
  0.400350;1.000000;,
  0.561040;1.000000;,
  0.500000;1.000000;,
  0.593570;1.000000;,
  0.562500;1.000000;,
  0.709740;1.000000;,
  0.656430;1.000000;,
  0.687500;1.000000;,
  0.844340;1.000000;,
  0.790260;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.935260;1.000000;,
  0.905660;1.000000;,
  0.937500;1.000000;,
  0.076720;1.000000;,
  0.000000;1.000000;,
  0.100480;1.000000;,
  0.062500;1.000000;,
  0.214060;1.000000;,
  0.149520;1.000000;,
  0.187500;1.000000;,
  0.349650;1.000000;,
  0.285940;1.000000;,
  0.312500;1.000000;,
  0.426500;1.000000;,
  0.400350;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.568200;1.000000;,
  0.568200;1.000000;,
  0.596600;1.000000;,
  0.596600;1.000000;,
  0.653400;1.000000;,
  0.653400;1.000000;,
  0.711610;1.000000;,
  0.711610;1.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.788390;1.000000;,
  0.788390;1.000000;,
  0.846590;1.000000;,
  0.846590;1.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.931830;1.000000;,
  0.931830;1.000000;,
  0.903410;1.000000;,
  0.903410;1.000000;,
  0.625000;1.000000;,
  0.568200;1.000000;,
  0.596600;1.000000;,
  0.653400;1.000000;,
  0.711610;1.000000;,
  0.750000;1.000000;,
  0.788390;1.000000;,
  0.846590;1.000000;,
  0.875000;1.000000;,
  0.931830;1.000000;,
  0.903410;1.000000;,
  0.125000;1.000000;,
  0.125000;1.000000;,
  0.087490;1.000000;,
  0.087490;1.000000;,
  0.105500;1.000000;,
  0.105500;1.000000;,
  0.144500;1.000000;,
  0.144500;1.000000;,
  0.217070;1.000000;,
  0.217070;1.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.282930;1.000000;,
  0.282930;1.000000;,
  0.353210;1.000000;,
  0.353210;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.420280;1.000000;,
  0.420280;1.000000;,
  0.396790;1.000000;,
  0.396790;1.000000;,
  0.125000;1.000000;,
  0.087490;1.000000;,
  0.105500;1.000000;,
  0.144500;1.000000;,
  0.217070;1.000000;,
  0.250000;1.000000;,
  0.282930;1.000000;,
  0.353210;1.000000;,
  0.375000;1.000000;,
  0.420280;1.000000;,
  0.396790;1.000000;;
 }
}
