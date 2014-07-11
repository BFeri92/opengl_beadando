// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 130

out vec4 vFragColor;

uniform vec4      ambientColor;
uniform sampler2D colorMap;

smooth in vec2 vTexCoords;

void main(void)
    { 
    // Dot product gives us diffuse intensity
    vFragColor = ambientColor;

    // Modulate in the texture
    vFragColor *= texture(colorMap, vTexCoords);
    }
    
