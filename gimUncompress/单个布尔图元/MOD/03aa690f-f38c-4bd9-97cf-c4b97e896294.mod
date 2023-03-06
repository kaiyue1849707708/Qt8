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
  </Entities>
</Device>