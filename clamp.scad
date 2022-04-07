// cm
$fn = 100;
$cane_thickness = 1.6; //TODO: properly parameterize
$tab_height = 1;
$clamp_height = 2.5;
$bolt_space = 1.0;
$clamp_material_padding = 0.5;
$clamp_width = $cane_thickness+$clamp_material_padding*2;
$cane_padding = 0.075;
$joint_distance = 1;
$hole_diameter = $cane_padding + $cane_thickness;
$hole_radius = $hole_diameter/2;

difference() {
    union() {
        //clamp part
        difference() {
            cube([$clamp_width, $clamp_width, $clamp_height], center=true);
            
            // the cane is 16mm thick
            translate([0,0,0]) cylinder(h=$clamp_height+0.01,r=($hole_diameter)/2, center=true);
            
            //translate([1,0,0]) cube([2,1,4.1], center=true);
            
            
        }

        // block containing bolts
        translate([$clamp_width/2 ,0,0]) difference() {
            translate([$bolt_space/2, 0, 0]) cube([$bolt_space,$clamp_width,$clamp_height], center=true);
            
            translate([$bolt_space/2,0,-$clamp_height/2 + 0.6]) rotate([90,0,0]) {
                // bore hole
                cylinder(h=$clamp_width+0.01, r=0.62/2, center=true);
                
                // TODO: wider holes for nut & screw head
                /*cylinder(h=$clamp_width+0.01, r=0.62/2, center=true);
                cylinder(h=$clamp_width+0.01, r=0.62/2, center=true);*/
            }

            translate([$bolt_space/2,0,$clamp_height/2 - 0.6]) rotate([90,0,0]) cylinder(h=$clamp_width+0.01, r=0.62/2, center=true);
        }
    }
    
$opening_ratio = 1.5;
$hole_shift = sqrt($hole_radius^2 - ($hole_radius/$opening_ratio)^2 ) - $hole_radius;
$polyhedron_x = $bolt_space + $clamp_material_padding - $hole_shift;
translate([($polyhedron_x+$hole_diameter )/2 + $hole_shift, 0, 0]) 
    hull() polyhedron( points=[ 
        [$polyhedron_x/2, $hole_radius, 0.01+$clamp_height/2],  //0
        [$polyhedron_x/2, $hole_radius, -0.01-$clamp_height/2], //1
        [$polyhedron_x/2, -$hole_radius, 0.01+$clamp_height/2], //2
        [$polyhedron_x/2, -$hole_radius, -0.01-$clamp_height/2],//3
        [-$polyhedron_x/2, $hole_diameter/(2*$opening_ratio), 0.01+$clamp_height/2], //4
        [-$polyhedron_x/2, $hole_diameter/(2*$opening_ratio), -0.01+-$clamp_height/2],//5
        [-$polyhedron_x/2, -$hole_diameter/(2*$opening_ratio), 0.01+$clamp_height/2],//6
        [-$polyhedron_x/2, -$hole_diameter/(2*$opening_ratio), -0.01+-$clamp_height/2]//7
    ], faces=[
        [0, 2, 3, 1],
        [4, 5 ,7, 6],
        [6, 2, 0, 4],
        [0, 1, 5, 4],
        [2, 3, 7, 6],
        [1, 3, 7, 5]
    ]);
}

// joint
translate([-$clamp_width/2 - $joint_distance+0.01,0,0]) 
difference() {
    cube([$joint_distance*2,0.5,$tab_height], center=true);
    
    translate([-$joint_distance + 0.62/2 + 0.3, 0, 0]) rotate([90,0,0]) cylinder(h=0.6,r=0.62/2, center=true);
    
}
