camera {
    location <-5,5,-3>
    look_at <0,1,0>
}

light_source {
    <0,4,-3>
    color rgb <255,255,255>
}

difference {

 sphere {
<0,0,0>
1
pigment { rgb <1,0,0> }
}
box {
<-2,-2,-2>
<2,0,2>
pigment { rgb <1,0,0> }
}
  
}
