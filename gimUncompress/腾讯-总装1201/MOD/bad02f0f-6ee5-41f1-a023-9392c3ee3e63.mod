<?xml version="1.0" encoding="utf-8"?>
<Device>
  <Entities>
    <Entity ID="55" Type="simple" Visible="false">
      <Cuboid L="100" W="8" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,-1.49011611938477E-08,-4,0,1" />
    </Entity>
    <Entity ID="56" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-6.50000001490116,0,75,1" />
    </Entity>
    <Entity ID="57" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="55" Entity2="56" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="58" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-10.0000000149012,0,75,1" />
    </Entity>
    <Entity ID="59" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="57" Entity2="58" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="60" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,6.49999998509884,0,75,1" />
    </Entity>
    <Entity ID="61" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="59" Entity2="60" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="62" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,9.99999998509884,0,75,1" />
    </Entity>
    <Entity ID="63" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="61" Entity2="62" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="64" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,-1.49011611938477E-08,0,46,1" />
    </Entity>
    <Entity ID="65" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="63" Entity2="64" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="66" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.894427190999916,0,-0.447213595499958,0,0.447213595499958,0,0.894427190999916,0,0,-1,0,0,10.6896122917533,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="67" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="65" Entity2="66" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="68" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.894427190999916,0,-0.447213595499958,0,-0.447213595499958,0,0.894427190999916,0,0,-1,0,0,-10.689612314105,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="69" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="67" Entity2="68" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="70" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-1.49011611938477E-08,50,50,1" />
    </Entity>
    <Entity ID="71" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="20" />
      <Color R="255" G="255" B="255" A="50" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,-1.49011611938477E-08,-8,50,1" />
    </Entity>
    <Entity ID="72" Type="simple" Visible="false">
      <Cuboid L="100" W="8" H="100" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,99.9999999850988,-4,0,1" />
    </Entity>
    <Entity ID="73" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,93.4999999850988,0,75,1" />
    </Entity>
    <Entity ID="74" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="72" Entity2="73" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="75" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,89.9999999850988,0,75,1" />
    </Entity>
    <Entity ID="76" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="74" Entity2="75" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="77" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,106.499999985099,0,75,1" />
    </Entity>
    <Entity ID="78" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="76" Entity2="77" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="79" Type="simple" Visible="false">
      <Cylinder R="3.5" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,109.999999985099,0,75,1" />
    </Entity>
    <Entity ID="80" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="78" Entity2="79" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="81" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-1,0,-1.22464679914735E-16,0,-1.22464679914735E-16,0,1,0,0,-1,0,0,99.9999999850988,0,46,1" />
    </Entity>
    <Entity ID="82" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="80" Entity2="81" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="83" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="0.894427190999916,0,-0.447213595499958,0,0.447213595499958,0,0.894427190999916,0,0,-1,0,0,110.689612291753,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="84" Type="boolean" Visible="false">
      <Boolean Type="Difference" Entity1="82" Entity2="83" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="85" Type="simple" Visible="false">
      <Cuboid L="2" W="8" H="8" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="-0.894427190999916,0,-0.447213595499958,0,-0.447213595499958,0,0.894427190999916,0,0,-1,0,0,89.310387685895,0,26.4222912378609,1" />
    </Entity>
    <Entity ID="86" Type="boolean" Visible="true">
      <Boolean Type="Difference" Entity1="84" Entity2="85" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1" />
    </Entity>
    <Entity ID="87" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="50" />
      <Color R="255" G="255" B="255" A="0" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,99.9999999850988,50,50,1" />
    </Entity>
    <Entity ID="88" Type="simple" Visible="true">
      <Cuboid L="100" W="100" H="20" />
      <Color R="255" G="255" B="255" A="50" />
      <TransformMatrix Value="1,0,0,0,0,0,1,0,0,-1,0,0,99.9999999850988,-8,50,1" />
    </Entity>
  </Entities>
</Device>