#version 330 core

layout (location = 0) in vec3 input_pos;
layout (location = 1) in vec2 input_tex_coords;
layout (location = 2) in float input_selected;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 tex_coords;
out float sel;

void main() {
    gl_Position = projection * view * model * vec4(input_pos, 1.0);
    tex_coords = input_tex_coords;
    sel = input_selected;
}