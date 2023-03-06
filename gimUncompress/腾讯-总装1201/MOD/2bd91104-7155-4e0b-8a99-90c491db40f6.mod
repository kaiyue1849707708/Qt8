<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="19" Type="simple" Visible="false">
      <Cuboid L="100" W="8" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-1.49011611938477E-08,-4,0,1" />
    </Entity>
    <Entity ID="20" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-6.50000001490116,0,75,1" />
    </Entity>
    <Entity ID="21" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="19" Entity2="20" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="22" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-10.0000000149012,0,75,1" />
    </Entity>
    <Entity ID="23" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="21" Entity2="22" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="24" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,6.49999998509884,0,75,1" />
    </Entity>
    <Entity ID="25" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="23" Entity2="24" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="26" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,9.99999998509884,0,75,1" />
    </Entity>
    <Entity ID="27" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="25" Entity2="26" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="28" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-1.49011611938477E-08,0,46,1" />
    </Entity>
    <Entity ID="29" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="27" Entity2="28" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="30" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.894427190999916,0,-0.447213595499958,0,0.447213595499958,0,0.894427190999916,0,0,-1,0,0,10.6896122917533,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="31" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="29" Entity2="30" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="32" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.894427190999916,0,-0.447213595499958,0,-0.447213595499958,0,0.894427190999916,0,0,-1,0,0,-10.689612314105,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="33" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="31" Entity2="32" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="34" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-1.49011611938477E-08,50,50,1" />
    </Entity>
  </Entities>
</Device>