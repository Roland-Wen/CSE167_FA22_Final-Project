#version 330 core

in vec4 position; // raw position in the model coord
in vec3 normal;   // raw normal in the model coord

uniform mat4 modelview; // from model coord to eye coord
uniform mat4 view;      // from world coord to eye coord

// Material parameters
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emision;
uniform float shininess;

// Light source parameters
const int maximal_allowed_lights = 10;
uniform bool enablelighting;
uniform int nlights;
uniform vec4 lightpositions[ maximal_allowed_lights ]; // in the world coord
uniform vec4 lightcolors[ maximal_allowed_lights ];

// Output the frag color
out vec4 fragColor;


void main (void){
    if (!enablelighting){
        // Default normal coloring (you don't need to modify anything here)
        vec3 N = normalize(normal);
        fragColor = vec4(0.5f*N + 0.5f , 1.0f);
    } else {
        
        // HW3: You will compute the lighting here.
        // transform stuff to eye coordinate
        mat3 A;
        for(int i = 0; i < 3; i++) {
            A[i] = vec3(modelview[i][0], modelview[i][1], modelview[i][2]);
        }
        A = inverse(transpose(A));
        vec3 normalEYE = normalize(A * normal);
        vec4 positionEYE = modelview * position;

        vec4 lightpositionsEYE[maximal_allowed_lights];
        for(int i = 0; i < nlights; i++) {
            lightpositionsEYE[i] = view * lightpositions[i];
        }

        // light model
        fragColor = emision;
        for(int i = 0; i < nlights; i++) {
            vec4 delta = ambient;
            
            vec3 l;
            // l is the direction to the light = lightposition - position
            for(int j = 0; j < 3; j++){
                l[j] = lightpositionsEYE[i][j] * positionEYE.w - positionEYE[j] * lightpositionsEYE[i].w;
            }
            l = normalize(l);
            delta += diffuse * max(dot(normalEYE, l), 0);

            vec3 v,h;
            vec4 origin = vec4(0.0f, 0.0f, 0.0f, 1.0f);
            // v is the direction to the viewer = viwer(origin) - position
            for(int j = 0; j < 3; j++){
                v[j] = origin[j] * positionEYE.w - positionEYE[j] * origin.w;
            }
            v = normalize(v);
            h = normalize(v + l);
            delta += specular * pow(max(dot(normalEYE, h) , 0), shininess);

            delta *= lightcolors[i];
            fragColor += delta;
        }
    }
}
