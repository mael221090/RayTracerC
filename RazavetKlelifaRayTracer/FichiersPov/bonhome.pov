camera {
        location <0,0,20>
        look_at <0,0,0>
}

background{
    color rgb <0,0,0>
}

light_source {
       <5,5,5>
        rgb <1,1,1>
}


plane {
        z,
        0
        pigment { rgb <0.5,0.5,1> }
}

sphere {
        <0,0,0>,
        0.2
        pigment { rgb <0.7,0.7,0.7> }
}

sphere {
        <6,0,0>,
        1
        pigment { rgb <1,0,0> }
}

sphere {
        <0,6,0>,
        3
        pigment { rgb <0,1,0> }
}

sphere {
        <0,0,6>,
        0.2
        pigment { rgb <0,0,1> }
}

cylinder{   

<0,3,0>,
<0,-3,0>,
        1.2
        pigment { color rgb  <1,0.5,0.15> }
}

cylinder{
       
        <5,1,0>,
<0,2,0>,
        0.5
        pigment { rgb <1,1,1> }
}

cylinder{
       
        <0,0,0>,
<2,-2,0>,
        0.5
        pigment { color rgb <1,1,1> }
}

cylinder{
       
        <0,-3,2>,
	<0,-8,2>,
        0.5
        pigment { rgb <0.2,0,0.2> }
}

cylinder{
        <-1,-8,0>,
        <0,-3,0>,
        0.5
        pigment { rgb <0.2,0,0.2> }
}


