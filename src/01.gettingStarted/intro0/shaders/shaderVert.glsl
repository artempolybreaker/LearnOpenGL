#ifdef CPP_GLSL_INCLUDE
std::string shader_vert = R"(
#endif

#version 330 core
uniform vec2 offset;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color;

void main() {
   color = vec3(aCol);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(offset, 0, 0);
}

// #version 330 core
// layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

// out vec4 vertexColor; // specify a color output to the fragment shader

// void main()
// {
//     gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
//     vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
// }

#ifdef CPP_GLSL_INCLUDE
)";
#endif