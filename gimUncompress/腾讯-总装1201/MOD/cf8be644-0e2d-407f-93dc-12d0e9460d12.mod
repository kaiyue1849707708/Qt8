<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="34" Type="simple" Visible="true">
      <Cylinder R="10" H="270" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-1.77635683940025E-15,-315,2770,1" />
    </Entity>
    <Entity ID="35" Type="simple" Visible="true">
      <Cylinder R="125" H="5" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,1.22464679914735E-15,0,0,1" />
    </Entity>
    <Entity ID="36" Type="simple" Visible="true">
      <Cylinder R="20" H="300" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,0,2790,1" />
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
    <Entity ID="43" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="39" Entity2="42" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="44" Type="simple" Visible="true">
      <Cylinder R="50" H="2790" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="45" Type="simple" Visible="true">
      <Sphere R="50" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,2790,1" />
    </Entity>
    <Entity ID="46" Type="simple" Visible="true">
      <Cuboid L="30" W="120" H="5" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0,1,0,0,0,0,1,0,1,0,0,0,58,0,90,1" />
    </Entity>
    <Entity ID="47" Type="simple" Visible="true">
      <Cylinder R="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0,1,0,0,0,0,1,0,1,0,0,0,50,0,120,1" />
    </Entity>
    <Entity ID="48" Type="simple" Visible="true">
      <Cylinder R="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0,1,0,0,0,0,-1,0,1,0,0,0,50,0,60,1" />
    </Entity>
  </Entities>
</Device>