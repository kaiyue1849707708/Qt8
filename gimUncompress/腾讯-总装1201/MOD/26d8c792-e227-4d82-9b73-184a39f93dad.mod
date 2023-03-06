<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="10" Type="simple" Visible="false">
      <Cuboid L="700" W="180" H="500" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,350,90,0,1" />
    </Entity>
    <Entity ID="11" Type="simple" Visible="false">
      <Cuboid L="600" W="190" H="440" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,350,85,30,1" />
    </Entity>
    <Entity ID="12" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="10" Entity2="11" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="13" Type="simple" Visible="false">
      <Cylinder R="10" H="10" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,110,-10,250,1" />
    </Entity>
    <Entity ID="14" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="12" Entity2="13" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="15" Type="simple" Visible="false">
      <Cylinder R="20" H="10" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,110,-20,250,1" />
    </Entity>
    <Entity ID="16" Type="boolean" Visible="true">
      <Boolean Type="Union" Entity1="14" Entity2="15" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>