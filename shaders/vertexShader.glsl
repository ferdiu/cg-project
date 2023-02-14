/**
 * @author: MANZELLA Federico
 * @badge-number: 170612
 * @assignment: 5
 */

#version 460 core

// ATTRIBUTES
layout(location=0) in vec4 posCoords;
layout(location=1) in vec3 normalCoords;
layout(location=2) in vec2 texCoords;

// UNIFORMS MATRICES
uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

// PASSED TO FRAGMENT
out vec3 fragcoord;
out vec2 texcoord;
out vec3 normalcoord;

// ----------------------------------------------------------------------

void main(void) {
   fragcoord = (modelMat * vec4(posCoords)).xyz;
   normalcoord = mat3(transpose(inverse(modelMat))) * normalCoords;
   texcoord = texCoords;

   gl_Position = projMat * viewMat * vec4(fragcoord, 1.0);
}
