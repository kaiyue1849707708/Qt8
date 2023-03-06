<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="33" Type="simple" Visible="true">
      <Cuboid L="100" W="8" H="100" />
      <Color R="246" G="246" B="246" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,1,0,0,-4,0,1" />
    </Entity>
    <Entity ID="34" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,50,50,1" />
    </Entity>
    <Entity ID="35" Type="simple" Visible="true">
      <Cylinder R="8" H="6" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-7.54951656745106E-15,-8,50,1" />
    </Entity>
    <Entity ID="36" Type="simple" Visible="false">
      <Cuboid L="100" W="100" H="10" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,-8,50,1" />
    </Entity>
    <Entity ID="37" Type="simple" Visible="false">
      <Cuboid L="100" W="40" H="10" />
      <Color R="255" G="255" B="255" A="50" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,0,-8,50,1" />
    </Entity>
    <Entity ID="38" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="36" Entity2="37" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="39" Type="simple" Visible="true">
      <Cuboid L="100" W="10" H="40" />
      <Color R="246" G="246" B="246" A="50" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,1,0,0,-13,30,1" />
    </Entity>
  </Entities>
</Device>