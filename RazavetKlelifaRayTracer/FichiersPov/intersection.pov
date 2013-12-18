camera {
    location <0,0,-3>
    look_at <0,0,0>
}

light_source {
    <0,4,-3>
    color rgb <255,255,255>
}

intersection {

box {<-0.5,-0.5,-0.5>,< 0.5,0.5,0.5>
     pigment{color rgb<1,0.65,0>}

    }
sphere{<0,0,0>,0.66
     pigment{color rgb<1,1,0.65>}
 
}


}


