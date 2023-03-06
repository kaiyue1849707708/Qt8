<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="6402" Type="simple" Visible="false">
      <TruncatedCone BR="50" TR="35" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-25,1" />
    </Entity>
    <Entity ID="6403" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.707106781186548,-0.707106781186547,0,0,0.707106781186547,0.707106781186548,0,0,0,0,1,0,-0.0217536017297988,-0.0178567022084906,-20,1" />
    </Entity>
    <Entity ID="6404" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6402" Entity2="6403" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6405" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="6.12323399573677E-17,-1,0,0,1,6.12323399573677E-17,0,0,0,0,1,0,0,7.105427357601E-15,-20,1" />
    </Entity>
    <Entity ID="6406" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6404" Entity2="6405" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6407" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.707106781186547,-0.707106781186548,0,0,0.707106781186548,-0.707106781186547,0,0,0,0,1,0,-0.0169913992284982,0.0122291967273043,-20,1" />
    </Entity>
    <Entity ID="6408" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6406" Entity2="6407" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6409" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-20,1" />
    </Entity>
    <Entity ID="6410" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6408" Entity2="6409" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6411" Type="simple" Visible="false">
      <Cylinder R="35" H="10" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-29,1" />
    </Entity>
    <Entity ID="6412" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="6410" Entity2="6411" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6413" Type="simple" Visible="true">
      <TruncatedCone BR="32" TR="30" H="28" />
      <Color R="105" G="105" B="105" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,7.105427357601E-15,-5,1" />
    </Entity>
    <Entity ID="6414" Type="simple" Visible="false">
      <Cylinder R="50" H="25" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,1.77635683940025E-15,1" />
    </Entity>
    <Entity ID="6415" Type="simple" Visible="false">
      <Cylinder R="35" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,5,1" />
    </Entity>
    <Entity ID="6416" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6414" Entity2="6415" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6417" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-9.99999999999995,15,-5,1" />
    </Entity>
    <Entity ID="6418" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6416" Entity2="6417" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6419" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,20,15,-5,1" />
    </Entity>
    <Entity ID="6420" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6418" Entity2="6419" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6421" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-9.99999999999995,-15,-5,1" />
    </Entity>
    <Entity ID="6422" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6420" Entity2="6421" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6423" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,20,-15,-5,1" />
    </Entity>
    <Entity ID="6424" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="6422" Entity2="6423" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>