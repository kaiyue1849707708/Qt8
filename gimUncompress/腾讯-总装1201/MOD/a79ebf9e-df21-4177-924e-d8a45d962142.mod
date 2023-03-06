<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="2" Type="simple" Visible="true">
      <Cylinder R="100" H="2500" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,100,380,-460,1" />
    </Entity>
    <Entity ID="3" Type="simple" Visible="false">
      <Cuboid L="100" W="1200" H="20" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,100,380,2040,1" />
    </Entity>
    <Entity ID="4" Type="simple" Visible="false">
      <Cylinder R="9" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,100,880,2076,1" />
    </Entity>
    <Entity ID="5" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="3" Entity2="4" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="6" Type="simple" Visible="false">
      <Cylinder R="9" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,100,880,2005,1" />
    </Entity>
    <Entity ID="7" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="5" Entity2="6" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="8" Type="simple" Visible="false">
      <Cylinder R="9" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,100,380,2005,1" />
    </Entity>
    <Entity ID="9" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="7" Entity2="8" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="10" Type="simple" Visible="false">
      <Cylinder R="9" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,100,-120,2005,1" />
    </Entity>
    <Entity ID="11" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="9" Entity2="10" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>