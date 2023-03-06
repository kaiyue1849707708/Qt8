<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="6417" Type="simple" Visible="false">
      <TruncatedCone BR="50" TR="35" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-25,1" />
    </Entity>
    <Entity ID="6418" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.707106781186548,-0.707106781186547,0,0,0.707106781186547,0.707106781186548,0,0,0,0,1,0,-0.0217536017297988,-0.0178567022084906,-20,1" />
    </Entity>
    <Entity ID="6419" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6417" Entity2="6418" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6420" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="6.12323399573677E-17,-1,0,0,1,6.12323399573677E-17,0,0,0,0,1,0,0,7.105427357601E-15,-20,1" />
    </Entity>
    <Entity ID="6421" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6419" Entity2="6420" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6422" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.707106781186547,-0.707106781186548,0,0,0.707106781186548,-0.707106781186547,0,0,0,0,1,0,-0.0169913992284982,0.0122291967273043,-20,1" />
    </Entity>
    <Entity ID="6423" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6421" Entity2="6422" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6424" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-20,1" />
    </Entity>
    <Entity ID="6425" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6423" Entity2="6424" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6426" Type="simple" Visible="false">
      <Cylinder R="35" H="10" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-29,1" />
    </Entity>
    <Entity ID="6427" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="6425" Entity2="6426" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6428" Type="simple" Visible="true">
      <TruncatedCone BR="32" TR="30" H="28" />
      <Color R="105" G="105" B="105" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,7.105427357601E-15,-5,1" />
    </Entity>
    <Entity ID="6429" Type="simple" Visible="false">
      <Cylinder R="50" H="25" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,1.77635683940025E-15,1" />
    </Entity>
    <Entity ID="6430" Type="simple" Visible="false">
      <Cylinder R="35" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,5,1" />
    </Entity>
    <Entity ID="6431" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6429" Entity2="6430" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6432" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-9.99999999999995,15,-5,1" />
    </Entity>
    <Entity ID="6433" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6431" Entity2="6432" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6434" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,20,15,-5,1" />
    </Entity>
    <Entity ID="6435" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6433" Entity2="6434" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6436" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-9.99999999999995,-15,-5,1" />
    </Entity>
    <Entity ID="6437" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6435" Entity2="6436" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6438" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,20,-15,-5,1" />
    </Entity>
    <Entity ID="6439" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="6437" Entity2="6438" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6440" Type="simple" Visible="true">
      <Cylinder R="60" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,1.77635683939996E-16,0,0,1" />
    </Entity>
    <Entity ID="6441" Type="simple" Visible="true">
      <Cylinder R="5" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="3.74939945665465E-33,-6.12323399573677E-17,1,0,1,6.12323399573677E-17,0,0,-6.12323399573677E-17,1,6.12323399573677E-17,0,-2.1316282072803E-14,55,10,1" />
    </Entity>
    <Entity ID="6442" Type="simple" Visible="true">
      <Cylinder R="5" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="3.74939945665465E-33,-6.12323399573677E-17,1,0,1,6.12323399573677E-17,0,0,-6.12323399573677E-17,1,6.12323399573677E-17,0,-1.4210854715202E-14,-75.0000000000002,10,1" />
    </Entity>
    <Entity ID="6443" Type="simple" Visible="true">
      <Cylinder R="8" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="6.12323399573677E-17,0,1,0,0,1,0,0,-1,0,6.12323399573677E-17,0,75.0000000000002,0,10,1" />
    </Entity>
    <Entity ID="6444" Type="simple" Visible="true">
      <Cylinder R="8" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="6.12323399573677E-17,0,1,0,0,1,0,0,-1,0,6.12323399573677E-17,0,-54.9999999999999,0,10,1" />
    </Entity>
  </Entities>
</Device>