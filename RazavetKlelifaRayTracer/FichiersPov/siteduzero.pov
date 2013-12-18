camera {
    location <1,1.5,-3>
    look_at <0,1,0>
}

light_source {
    <0,4,-3>
    color rgb <1,1,1>
}


plane {
    y,0
    pigment {
        rgb <1,1,0>
    }
}

box {
    <-0.5,0,-0.5>
    <0.5,1,0.5>
    pigment {
      rgb <1,0,0>
    }
}

sphere {
    <0,1.3,0>,0.3
    pigment {
        rgb <0,0,1>
    }
}

torus {
    1
    0.1
    pigment { rgb <0,1,1> }
}
