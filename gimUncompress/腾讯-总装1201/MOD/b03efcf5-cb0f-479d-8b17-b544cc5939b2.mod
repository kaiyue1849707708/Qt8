<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
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
    <Entity ID="6383" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.707106781186547,-0.707106781186548,0,0,0.707106781186548,-0.707106781186547,0,0,0,0,1,0,-0.0169913992284982,0.0122291967273043,-20,1" />
    </Entity>
    <Entity ID="6384" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6382" Entity2="6383" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6385" Type="simple" Visible="false">
      <OffsetRectangularTable TL="120" TW="25" LL="120" LW="30" H="10" XOFF="0" YOFF="0" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-20,1" />
    </Entity>
    <Entity ID="6386" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6384" Entity2="6385" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6387" Type="simple" Visible="false">
      <Cylinder R="35" H="10" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,-29,1" />
    </Entity>
    <Entity ID="6388" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="6386" Entity2="6387" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6389" Type="simple" Visible="true">
      <TruncatedCone BR="32" TR="30" H="28" />
      <Color R="105" G="105" B="105" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,7.105427357601E-15,-5,1" />
    </Entity>
    <Entity ID="6390" Type="simple" Visible="false">
      <Cylinder R="50" H="25" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,1.77635683940025E-15,1" />
    </Entity>
    <Entity ID="6391" Type="simple" Visible="false">
      <Cylinder R="35" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,7.105427357601E-15,5,1" />
    </Entity>
    <Entity ID="6392" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6390" Entity2="6391" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,1.22464679914735E-16,0,0,-1.22464679914735E-16,-1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6393" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-9.99999999999995,15,-5,1" />
    </Entity>
    <Entity ID="6394" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6392" Entity2="6393" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6395" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,20,15,-5,1" />
    </Entity>
    <Entity ID="6396" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6394" Entity2="6395" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6397" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-9.99999999999995,-15,-5,1" />
    </Entity>
    <Entity ID="6398" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="6396" Entity2="6397" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6399" Type="simple" Visible="false">
      <Cylinder R="5" H="7" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,20,-15,-5,1" />
    </Entity>
    <Entity ID="6400" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="6398" Entity2="6399" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>