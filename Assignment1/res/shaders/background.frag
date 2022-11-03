#version 420 core

out vec4 color;

uniform float time;
uniform vec2 res;

#define PI 3.1415
#define TWO_PI (2.0 * 3.1415)
 
//Colors
const vec3  BACKGROUND_COLOR = vec3( 34,  30,  38)/256.0;
const vec3  RING1_COLOR      = vec3( 10, 205, 203)/256.0;
const vec3  RING2_COLOR      = vec3( 46,  72,  82)/256.0;
const vec3  RING3_COLOR      = vec3( 54, 147, 147)/256.0;

void main(){
	vec2 scaled = (gl_FragCoord.xy * 2.0 - res.xy) / res.y * 0.6;
    float t = 2.0 / res.y;

    //Info
    float len = length(scaled);
    float angle  = atan(scaled.y, scaled.x) + PI; //[-Pi,Pi]->[0,2Pi]
    float wave = mod(time * 2.0, TWO_PI); //[0,2Pi]

    // //Background
	vec3 tmp_color = BACKGROUND_COLOR;  
    
    //Calculating
    float angle_difference = abs(wave-angle);
    float distance_to_wave  = min(angle_difference, TWO_PI - angle_difference);
    float final_multiplier = pow(max(1.0, distance_to_wave), -4.0);

    float ring1 = 0.50  + 0.03 * cos(angle * 7.0               ) * final_multiplier;
    float ring2 = 0.485 + 0.03 * cos(angle * 7.0 + TWO_PI / 3.0) * final_multiplier;
    float ring3 = 0.47  + 0.03 * cos(angle * 7.0 - TWO_PI / 3.0) * final_multiplier;
    
    //Drawing
    
    tmp_color = mix(tmp_color, RING1_COLOR, smoothstep(0.01 + t, 0.01, abs(ring1 - len)));
    tmp_color = mix(tmp_color, RING2_COLOR, smoothstep(0.01 + t, 0.01, abs(ring2 - len)));
    tmp_color = mix(tmp_color, RING3_COLOR, smoothstep(0.01 + t, 0.01, abs(ring3 - len)));

    //Final
	color = vec4(tmp_color,1.0);
}