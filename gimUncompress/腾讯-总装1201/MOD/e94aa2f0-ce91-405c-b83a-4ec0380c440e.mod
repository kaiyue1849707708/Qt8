<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="18" Type="simple" Visible="false">
      <Cuboid L="700" W="180" H="500" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,350,90,0,1" />
    </Entity>
    <Entity ID="19" Type="simple" Visible="false">
      <Cuboid L="600" W="190" H="440" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,350,85,30,1" />
    </Entity>
    <Entity ID="20" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="18" Entity2="19" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="21" Type="simple" Visible="false">
      <Cylinder R="10" H="10" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,110,-10,250,1" />
    </Entity>
    <Entity ID="22" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="20" Entity2="21" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="23" Type="simple" Visible="false">
      <Cylinder R="20" H="10" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,110,-20,250,1" />
    </Entity>
    <Entity ID="24" Type="boolean" Visible="true">
      <Boolean Type="Union" Entity1="22" Entity2="23" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>