camera {
        location <0,1.5,-3>
        look_at <0,1,0>
}
 
light_source {
        <2,3,-3>
        rgb <1,1,1>
}
 
plane {
        y
        0
        pigment { rgb <1,1,1> }
}       
       
cylinder {
        <0,0,0>
        <0,2,0>
        0.2
        pigment { rgb <0.3,0.9,0.3> }
}
 
cylinder {
        <-0.5,1.5,-0.5>
        <0.5,1.5,0.5>
        0.1
        pigment { rgb <0.3,0.6,0.6> }
        rotate <90,0,0>
}

 
cylinder {
        <0.5,1.5,-0.5>
        <-0.5,1.5,0.5>
        0.1
        pigment { rgb <0.3,0.6,0.6> }
}

