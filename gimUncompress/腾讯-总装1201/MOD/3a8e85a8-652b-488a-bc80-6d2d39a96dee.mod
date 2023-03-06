<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="26" Type="simple" Visible="false">
      <Cuboid L="700" W="180" H="500" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,350,90,0,1" />
    </Entity>
    <Entity ID="27" Type="simple" Visible="false">
      <Cuboid L="600" W="190" H="440" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,350,85,30,1" />
    </Entity>
    <Entity ID="28" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="26" Entity2="27" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="29" Type="simple" Visible="false">
      <Cylinder R="10" H="10" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,110,-10,250,1" />
    </Entity>
    <Entity ID="30" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="28" Entity2="29" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="31" Type="simple" Visible="false">
      <Cylinder R="20" H="10" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,110,-20,250,1" />
    </Entity>
    <Entity ID="32" Type="boolean" Visible="true">
      <Boolean Type="Union" Entity1="30" Entity2="31" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>