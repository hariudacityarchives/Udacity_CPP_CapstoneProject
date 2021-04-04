#version 130

in vec2 fragmentPostion;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main(){
    color = vec4(fragmentColor.r * (cos(fragmentPostion.x * 4.0 +time)+1.0) *0.5,
                 fragmentColor.g * (cos(fragmentPostion.y * 8.0 +time)+1.0) *0.5,
                 fragmentColor.b * (cos(fragmentPostion.x * 2.0 +time)+1.0) *0.5, 0.0);
}