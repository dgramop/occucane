// cm
$fn = 100;
difference() {
    cube([3.0, 2.5, 4], center=true);
    cylinder(h=4.1,r=1.6/2, center=true);
    
    translate([1,0,0]) cube([2,1,4.1], center=true);
    
    translate([(0.8+1.5)/2 - 0.1,0,-1]) rotate([90,0,0]) cylinder(h=2.6, r=0.62/2, center=true);

    translate([(0.8+1.5)/2 - 0.1,0,1]) rotate([90,0,0]) cylinder(h=2.6, r=0.62/2, center=true);
}


