<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="20" Type="simple" Visible="false">
      <Cuboid L="200" W="100" H="300" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-5.96046447753906E-08,-50,0,1" />
    </Entity>
    <Entity ID="21" Type="simple" Visible="false">
      <Cuboid L="150" W="5" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-5.96046447753906E-08,-97.5,155,1" />
    </Entity>
    <Entity ID="22" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="20" Entity2="21" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="23" Type="simple" Visible="false">
      <Cuboid L="80" W="5" H="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-35.0000000596046,-97.5,60,1" />
    </Entity>
    <Entity ID="24" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="22" Entity2="23" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="25" Type="simple" Visible="false">
      <Sphere R="6" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,64.9999999403954,-100,70,1" />
    </Entity>
    <Entity ID="26" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="24" Entity2="25" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="27" Type="simple" Visible="false">
      <Sphere R="6" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,44.9999999403954,-100,70,1" />
    </Entity>
    <Entity ID="28" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="26" Entity2="27" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="29" Type="simple" Visible="false">
      <Sphere R="6" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,24.9999999403954,-100,70,1" />
    </Entity>
    <Entity ID="30" Type="boolean" Visible="true">
      <Boolean Type="Union" Entity1="28" Entity2="29" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>