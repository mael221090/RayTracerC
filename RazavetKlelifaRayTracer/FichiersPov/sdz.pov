camera {
        location <0,1.5,-3>
        look_at <0,1,0>
}
 
light_source {
        <2,3,-3>
        rgb <0.5,0.5,0.5>
}
 light_source {
        <-2,3,-3>
        rgb <0.5,0.5,0.5>
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
 
sphere {
        <0,2,0>
        0.2
        pigment { rgb <0.3,0.9,0.3> }
}
 

 

sphere {
        <0,1.5,0>
        0.35
        pigment { rgb <0.7,0.2,0.7> }
}
 
cylinder {
        <-0.5,1.5,-0.5>
        <0.5,1.5,0.5>
        0.1
        pigment { rgb <0.3,0.6,0.6> }
}
 
cylinder {
        <0.5,1.5,-0.5>
        <-0.5,1.5,0.5>
        0.1
        pigment { rgb <0.3,0.6,0.6> }
}
 
sphere {
        <0.5,1.5,0.5>
        0.15
        pigment { rgb <0.6,0.9,0.9> }
}
sphere {
        <.5,1.5,-.5>
        0.15
        pigment { rgb <0.6,0.9,0.9> }
}
sphere {
        <-.5,1.5,.5>
        0.15
        pigment { rgb <0.6,0.9,0.9> }
}
sphere {
        <-.5,1.5,-.5>
        0.15
        pigment { rgb <0.6,0.9,0.9> }
}
 

 
cylinder {
        <0,0.7,0>
        <0,0.9,0>
        0.3
        pigment { rgb <0.4,0.95,0.6> }
}
 
box {
        <-0.05,0.75,-0.6>
        <0.05,0.85,0.6>
        pigment { rgb <0.7,0.98,0.75> }
}
 
box {
        <0.6,0.75,-0.05>
        <-0.6,0.85,0.05>
        pigment { rgb <0.7,0.98,0.75> }
}

