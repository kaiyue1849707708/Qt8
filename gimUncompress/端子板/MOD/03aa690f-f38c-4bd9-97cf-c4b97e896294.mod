<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="19" Type="simple" Visible="true">
      <TerminalBlock L="85" W="80" T="15" CL="5" CS="40" RS="40" R="7" CN="2" RN="2" BL="23" Phase="A" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-5396,2067.5,628.95659608841,1" />
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
    <Entity ID="39" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="37" Entity2="38" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    
  </Entities>
</Device>