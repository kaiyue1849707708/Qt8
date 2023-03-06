<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="38" Type="simple" Visible="false">
      <Cuboid L="435" W="155" H="165" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,217.5,-77.5,0,1" />
    </Entity>
    <Entity ID="39" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,372,-77.5,0,1" />
    </Entity>
    <Entity ID="40" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="38" Entity2="39" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="41" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,269,-77.5,0,1" />
    </Entity>
    <Entity ID="42" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="40" Entity2="41" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="43" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,166,-77.5,0,1" />
    </Entity>
    <Entity ID="44" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="42" Entity2="43" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="45" Type="simple" Visible="false">
      <Cylinder R="40" H="60" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,-1,0,0,0,0,-1,0,62.9999999999999,-77.5,0,1" />
    </Entity>
    <Entity ID="46" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="44" Entity2="45" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="47" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,62.9999999999999,-77.5,-60,1" />
    </Entity>
    <Entity ID="48" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="46" Entity2="47" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="49" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,166,-77.5,-60,1" />
    </Entity>
    <Entity ID="50" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="48" Entity2="49" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="51" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,269,-77.5,-60,1" />
    </Entity>
    <Entity ID="52" Type="boolean" Visible="false">
      <Boolean Type="Union" Entity1="50" Entity2="51" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="53" Type="simple" Visible="false">
      <TerminalBlock L="60" W="60" T="10" CL="1" CS="2" RS="2" R="15" CN="1" RN="1" BL="30" Phase="A" />
      <Color R="137" G="145" B="150" A="0" />
      <TransformMatrix Value="-1,0,1.22460635382238E-16,0,0,1,0,0,-1.22460635382238E-16,0,-1,0,372,-77.5,-60,1" />
    </Entity>
    <Entity ID="54" Type="boolean" Visible="true">
      <Boolean Type="Union" Entity1="52" Entity2="53" />
      <Color R="138" G="149" B="151" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
  </Entities>
</Device>