camera{
	location <0,0,5>
 	look_at <0,0,0>
}

background {
	rgb <0,0,0.2>
}

light_source{
	<0.5,1,-80>
	rgb <1,1,1>
}

plane {
    y,1.4
    pigment {
        rgb <1,1,0>
    }
}

triangle{
	<-2, -0.1, 0>
	<-1, 1, 0>
	<0, 0, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

triangle{
	<0, -2, 0>
	<-1, -1, 0>
	<0, 0, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

triangle{
	<1, -1, 0>
	<2, 0, 0>
	<-1, -1, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

triangle{
	<-1, 0, 0>
	<2, 0, 0>
	<-1, -1, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

sphere{
	<10,-98,-200>
	100
	rgb <1,0.75,0.14>
}


background {
	rgb <0,0,0.2>
}

light_source{
	<0.5,1,-80>
	rgb <1,1,1>
}

plane {
    y,0
    pigment {
        rgb <1,1,0>
    }
}

triangle{
	<-2, -0.1, 0>
	<-1, 1, 0>
	<0, 0, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

triangle{
	<0, -2, 0>
	<-1, -1, 0>
	<0, 0, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

triangle{
	<1, -1, 0>
	<2, 0, 0>
	<-1, -1, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}

triangle{
	<-1, 0, 0>
	<2, 0, 0>
	<-1, -1, 0>
	rgb <1,0,0>
	rotate <0,0,-45>
}


