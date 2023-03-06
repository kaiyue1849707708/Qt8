<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="22" Type="simple" Visible="false">
      <Cuboid L="390" W="11" H="320" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,-5.50000000745058,-50,1" />
    </Entity>
    <Entity ID="23" Type="simple" Visible="false">
      <Cuboid L="290" W="110" H="220" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,-7.45058059692383E-09,0,1" />
    </Entity>
    <Entity ID="24" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="22" Entity2="23" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="16" Type="simple" Visible="true">
      <RotationalEllipsoid LR="1500" WR="615" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="6.12323399573677E-17,0,-1,0,1,0,6.12323399573677E-17,0,0,-1,0,0,5.50670620214078E-15,0,1380,1" />
    </Entity>
    <Entity ID="4" Type="simple" Visible="true">
      <EccentricTruncatedCone TR="45" BR="50" H="5" TOPXOFF="0" TOPYOFF="0" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,189,1" />
    </Entity>
    <Entity ID="16" Type="simple" Visible="true">
      <OffsetRectangularTable TL="10" TW="2" LL="10" LW="2" H="45" XOFF="80" YOFF="0" />
      <Color R="49" G="127" B="67" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,0,1,0,0,-1.22464679914735E-16,0,1,0,-75,-41,30,1" />
    </Entity>
    <Entity ID="40" Type="simple" Visible="false">
      <Cylinder R="100" H="240" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,-330,2705,1" />
    </Entity>
    <Entity ID="41" Type="simple" Visible="false">
      <Cuboid L="500" W="500" H="500" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0,1,0,0,0,0,1,0,1,0,0,0,-250,-550,2455,1" />
    </Entity>
    <Entity ID="42" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="40" Entity2="41" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="1164" Type="simple" Visible="false">
      <Cuboid L="8" W="20" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,0,0,0,0,1,0,0,1,0,0,164,605,2154.5,1" />
    </Entity>
    <Entity ID="1165" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="1163" Entity2="1164" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="67" Type="simple" Visible="true">
      <StretchedBody L="7.25358562539478" Normal="0,304.8,0" Array="322.105721633723,-799.999999999994,504.071650908495;322.105721633723,-799.999999999994,304.071650908495;277.105721633723,-799.999999999994,304.071650908495;277.105721633723,-799.999999999994,504.071650908495" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,1172.21802657794,0,1" />
    </Entity>
    <Entity ID="19" Type="simple" Visible="false">
      <Cuboid L="100" W="8" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-1.49011611938477E-08,-4,0,1" />
    </Entity>
    <Entity ID="20" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-6.50000001490116,0,75,1" />
    </Entity>
    <Entity ID="21" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="19" Entity2="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="22" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-10.0000000149012,0,75,1" />
    </Entity>
    <Entity ID="23" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="21" Entity2="22" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="24" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,6.49999998509884,0,75,1" />
    </Entity>
    <Entity ID="25" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="23" Entity2="24" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="26" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,9.99999998509884,0,75,1" />
    </Entity>
    <Entity ID="27" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="25" Entity2="26" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="28" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-1.49011611938477E-08,0,46,1" />
    </Entity>
    <Entity ID="29" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="27" Entity2="28" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="30" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.894427190999916,0,-0.447213595499958,0,0.447213595499958,0,0.894427190999916,0,0,-1,0,0,10.6896122917533,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="31" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="29" Entity2="30" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="32" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.894427190999916,0,-0.447213595499958,0,-0.447213595499958,0,0.894427190999916,0,0,-1,0,0,-10.689612314105,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="33" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="31" Entity2="32" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="34" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-1.49011611938477E-08,50,50,1" />
    </Entity>
    <Entity ID="155" Type="simple" Visible="true">
      <SquareGasket L1="400" W1="400" L2="340" W2="340" H="20" CT="1" Rad="0.5" CL="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,0,200,1" />
    </Entity>
    <Entity ID="37" Type="simple" Visible="false">
      <Cylinder R="100" H="300" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,-300,2750,1" />
    </Entity>
    <Entity ID="38" Type="simple" Visible="false">
      <Cuboid L="500" W="500" H="500" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0,1,0,0,0,0,1,0,1,0,0,0,-250,-550,2500,1" />
    </Entity>
    <Entity ID="39" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="37" Entity2="38" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="5" Type="simple" Visible="true">
      <Cable StartCoord="48961.1523752777,23697.7700691435,1833.49993577494" EndCoord="48961.1523752777,23697.7700691435,4161.56984044418" InflectionCoordArray="48961.1523752777,23697.7700691435,2798.32651297768" IRArray="2000" D="64" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="5" Type="simple" Visible="true">
      <Wire D="34" Sag="1" StartVector="0,0,0" EndVector="0,0,0" FitCoordArray="31702.0482792815,20745,4973;31702.0241755888,20745,4946.17;31702.0000718961,20745,4919.74;31701.9759682034,20745,4893.71;31701.9518645107,20745,4868.08;31701.927760818,20745,4842.85;31701.9036571252,20745,4818.02;31701.8795534325,20745,4793.59;31701.8554497398,20745,4769.56;31701.8313460471,20745,4745.93;31701.8072423544,20745,4722.7;31701.7831386617,20745,4699.87;31701.7590349689,20745,4677.44;31701.7349312762,20745,4655.41;31701.7108275835,20745,4633.78;31701.6867238908,20745,4612.55;31701.6626201981,20745,4591.72;31701.6385165054,20745,4571.29;31701.6144128127,20745,4551.26;31701.5903091199,20745,4531.63;31701.5662054272,20745,4512.4;31701.5421017345,20745,4493.57;31701.5179980418,20745,4475.14;31701.4938943491,20745,4457.11;31701.4697906564,20745,4439.48;31701.4456869636,20745,4422.25;31701.4215832709,20745,4405.42;31701.3974795782,20745,4388.99;31701.3733758855,20745,4372.96;31701.3492721928,20745,4357.33;31701.3251685001,20745,4342.1;31701.3010648074,20745,4327.27;31701.2769611146,20745,4312.84;31701.2528574219,20745,4298.81;31701.2287537292,20745,4285.18;31701.2046500365,20745,4271.95;31701.1805463438,20745,4259.12;31701.1564426511,20745,4246.69;31701.1323389584,20745,4234.66;31701.1082352656,20745,4223.03;31701.0841315729,20745,4211.8;31701.0600278802,20745,4200.97;31701.0359241875,20745,4190.54;31701.0118204948,20745,4180.51;31700.9877168021,20745,4170.88;31700.9636131093,20745,4161.65;31700.9395094166,20745,4152.82;31700.9154057239,20745,4144.39;31700.8913020312,20745,4136.36;31700.8671983385,20745,4128.73;31700.8430946458,20745,4121.5;31700.8189909531,20745,4114.67;31700.7948872603,20745,4108.24;31700.7707835676,20745,4102.21;31700.7466798749,20745,4096.58;31700.7225761822,20745,4091.35;31700.6984724895,20745,4086.52;31700.6743687968,20745,4082.09;31700.650265104,20745,4078.06;31700.6261614113,20745,4074.43;31700.6020577186,20745,4071.2;31700.5779540259,20745,4068.37;31700.5538503332,20745,4065.94;31700.5297466405,20745,4063.91;31700.5056429478,20745,4062.28;31700.481539255,20745,4061.05;31700.4574355623,20745,4060.22;31700.4333318696,20745,4059.79;31700.4092281769,20745,4059.76;31700.3851244842,20745,4060.13;31700.3610207915,20745,4060.9;31700.3369170987,20745,4062.07;31700.312813406,20745,4063.64;31700.2887097133,20745,4065.61;31700.2646060206,20745,4067.98;31700.2405023279,20745,4070.75;31700.2163986352,20745,4073.92;31700.1922949425,20745,4077.49;31700.1681912497,20745,4081.46;31700.144087557,20745,4085.83;31700.1199838643,20745,4090.6;31700.0958801716,20745,4095.77;31700.0717764789,20745,4101.34;31700.0476727862,20745,4107.31;31700.0235690935,20745,4113.68;31699.9994654007,20745,4120.45;31699.975361708,20745,4127.62;31699.9512580153,20745,4135.19;31699.9271543226,20745,4143.16;31699.9030506299,20745,4151.53;31699.8789469372,20745,4160.3;31699.8548432444,20745,4169.47;31699.8307395517,20745,4179.04;31699.806635859,20745,4189.01;31699.7825321663,20745,4199.38;31699.7584284736,20745,4210.15;31699.7343247809,20745,4221.32;31699.7102210881,20745,4232.89;31699.6861173954,20745,4244.86;31699.6620137027,20745,4257.23;31699.63791001,20745,4270" StartCoord="31702.0482792815,20745,4973" EndCoord="31699.63791001,20745,4270" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="5" Type="simple" Visible="true">
      <TerminalBlock L="30" W="20" T="6" CL="5" CS="1" RS="1" R="1" CN="2" RN="2" BL="20" Phase="A" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="0,0,-1,0,0,1,0,0,1,0,0,0,369.999999999994,89.9999999999754,-609.999999999992,1" />
    </Entity>
    <Entity ID="44" Type="simple" Visible="true">
      <CircularGasket OR="70" IR="25" H="18" Rad="6.28318530717959" />
      <Color R="30" G="30" B="30" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-418,0,172.25126265847,1" />
    </Entity>
    <Entity ID="155" Type="simple" Visible="true">
      <SquareGasket L1="400" W1="400" L2="340" W2="340" H="20" CT="1" Rad="0.5" CL="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,0,200,1" />
    </Entity>
    <Entity ID="882" Type="simple" Visible="false">
      <TruncatedCone BR="114" TR="174" H="103" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0.40267614929016,0.915342514468135,0,0,-0.915342514468135,0.40267614929016,0,-0.388682633321611,61.9101884621173,223.730814802436,1" />
    </Entity>
    <Entity ID="883" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="881" Entity2="882" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="0.999998550154763,0.000147567541722022,0.00169644103700349,0,-0.00115085891016269,0.79284007806978,0.609428655488134,0,-0.00125507455567328,-0.609429724275184,0.792839098403789,0,0,0,0,1" />
    </Entity>
    <Entity ID="6378" Type="simple" Visible="false">
      <TruncatedCone BR="50" TR="35" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-25,1" />
    </Entity>
    <Entity ID="6379" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.707106781186548,-0.707106781186547,0,0,0.707106781186547,0.707106781186548,0,0,0,0,1,0,-0.0217536017297988,-0.0178567022084906,-20,1" />
    </Entity>
    <Entity ID="6380" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6378" Entity2="6379" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6381" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="6.12323399573677E-17,-1,0,0,1,6.12323399573677E-17,0,0,0,0,1,0,0,7.105427357601E-15,-20,1" />
    </Entity>
    <Entity ID="6382" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6380" Entity2="6381" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="21" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="19" Entity2="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="22" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-10.0000000149012,0,75,1" />
    </Entity>
    <Entity ID="23" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="21" Entity2="22" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="127" Type="simple" Visible="false">
      <StretchedBody L="2300" Normal="0,0,304.8" Array="500.000000000001,650.000000000003,0;500.000000000001,-1150,0;-499.999999999999,-1150,0;-499.999999999999,650.000000000003,0" />
      <Color R="215" G="215" B="215" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="128" Type="simple" Visible="false">
      <StretchedBody L="250" Normal="0,0,304.8" Array="449.999999999999,-836.246666870868,0;449.999999999999,-1015,0;346.835627380688,-1015,0;346.835627380688,-836.246666870868,0" />
      <Color R="128" G="128" B="128" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="129" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="127" Entity2="128" />
      <Color R="215" G="215" B="215" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>

  </Entities>
</Device>