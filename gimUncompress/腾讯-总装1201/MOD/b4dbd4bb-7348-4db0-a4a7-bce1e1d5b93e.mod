<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="112" Type="simple" Visible="false">
      <Cuboid L="100" W="8" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,50,-4,0,1" />
    </Entity>
    <Entity ID="113" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,43.5,0,75,1" />
    </Entity>
    <Entity ID="114" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="112" Entity2="113" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="115" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,40,0,75,1" />
    </Entity>
    <Entity ID="116" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="114" Entity2="115" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="117" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,56.5000000000002,0,75,1" />
    </Entity>
    <Entity ID="118" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="116" Entity2="117" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="119" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,60.0000000000002,0,75,1" />
    </Entity>
    <Entity ID="120" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="118" Entity2="119" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="121" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,50,0,46,1" />
    </Entity>
    <Entity ID="122" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="120" Entity2="121" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="123" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.894427190999916,0,-0.447213595499958,0,0.447213595499958,0,0.894427190999916,0,0,-1,0,0,60.6896123066542,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="124" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="122" Entity2="123" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="125" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.894427190999916,0,-0.447213595499958,0,-0.447213595499958,0,0.894427190999916,0,0,-1,0,0,39.3103877007962,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="126" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="124" Entity2="125" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="127" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-50,50,50,1" />
    </Entity>
    <Entity ID="128" Type="simple" Visible="false">
      <Cuboid L="100" W="8" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-50,-4,0,1" />
    </Entity>
    <Entity ID="129" Type="simple" Visible="false">
      <Cuboid L="2" W="10" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-50,0,65,1" />
    </Entity>
    <Entity ID="130" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="128" Entity2="129" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="131" Type="simple" Visible="false">
      <Cuboid L="2" W="10" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-35,0,40,1" />
    </Entity>
    <Entity ID="132" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="130" Entity2="131" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="133" Type="simple" Visible="false">
      <Cuboid L="2" W="10" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-65,0,40,1" />
    </Entity>
    <Entity ID="134" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="132" Entity2="133" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="135" Type="simple" Visible="false">
      <Cuboid L="2" W="10" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1.83697019872103E-16,0,1,0,1,0,1.83697019872103E-16,0,0,-1,0,0,-50,0,31,1" />
    </Entity>
    <Entity ID="136" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="134" Entity2="135" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="137" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,50,50,50,1" />
    </Entity>
  </Entities>
</Device>