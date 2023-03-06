<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="20" Type="simple" Visible="false">
      <Cuboid L="435" W="155" H="165" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,217.5,-77.5,0,1" />
    </Entity>
    <Entity ID="21" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,372,-77.5,0,1" />
    </Entity>
    <Entity ID="22" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="20" Entity2="21" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="23" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,269,-77.5,0,1" />
    </Entity>
    <Entity ID="24" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="22" Entity2="23" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="25" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,166,-77.5,0,1" />
    </Entity>
    <Entity ID="26" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="24" Entity2="25" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="27" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,62.9999999999999,-77.5,0,1" />
    </Entity>
    <Entity ID="28" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="26" Entity2="27" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="29" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,62.9999999999999,-77.5,-60,1" />
    </Entity>
    <Entity ID="30" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="28" Entity2="29" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="31" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,166,-77.5,-60,1" />
    </Entity>
    <Entity ID="32" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="30" Entity2="31" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="33" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,269,-77.5,-60,1" />
    </Entity>
    <Entity ID="34" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="32" Entity2="33" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="35" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,372,-77.5,-60,1" />
    </Entity>
    <Entity ID="36" Type="boolean" Visible="true">
      <Boolean Type="Union" Entity1="34" Entity2="35" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>