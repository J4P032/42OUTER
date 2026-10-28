//para Compilar: glslc shader.vert -o vert.spv
#version 460

layout(location = 0) in vec3 inPosition;

const vec3 colors[3] = vec3[]
(
    vec3(1.0, 0.0, 0.0), // Red
    vec3(0.0, 1.0, 0.0), // Green
    vec3(0.0, 0.0, 1.0)  // Blue
);

layout (location = 0) out vec3 outColor;

void main() {
    //gl_Position = vec4(inPosition, 1.0);
    gl_Position = vec4(
        inPosition.x / 20.0,
        (inPosition.y + inPosition.z) / 10.0,
        (inPosition.z - inPosition.y) / 10.0 + 0.5,
        1.0
    );
    outColor = vec3(0.8, 0.8, 0.8); //vertices color gris claro
}
