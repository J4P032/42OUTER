#version 460

layout(location = 0) in vec3 inPosition;

/*Esto leera la constante VkPushConstantRange, es decir la matriz 4x4 de transformacion
y se conecta automaticamente a ella por que en el codigo el .offset lo puse a 0 (podria haber
puesto layout(offset = N) vec4 mvp). Leera 16 por que mat4 le dice que es una matriz de 4x4
mvp es el nombre de la variable que se quiera poner, pero viene de Model-View-Projection*/
layout(push_constant) uniform Push {
    mat4 mvp;
} push;

layout (location = 0) out vec3 outColor;

void main() {
    gl_Position = push.mvp * vec4(inPosition, 1.0);
    outColor = vec3(0.8, 0.8, 0.8);
}


/* #version 460

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
} */
