/**************************************************
Scene.inl contains the definition of the scene graph
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Plane.h"
#include "Obj.h"

using namespace glm;
void Scene::init(void){
    /*geometry["plane"] = new Plane;
    geometry["plane"] -> init();
    geometry["cube"] = new Cube;
    geometry["cube"] -> init();

    material["woodR"] = new Material;
    material["woodR"]->ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["woodR"]->diffuse = vec4(1.0f,0.0f,0.0f,1.0f);
    material["woodR"]->specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["woodR"]->shininess = 50.0f;

    material["woodG"] = new Material;
    material["woodG"]->ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["woodG"]->diffuse = vec4(0.0f,1.0f,0.0f,1.0f);
    material["woodG"]->specular = vec4(0.15f,0.3f,0.1f,1.0f);
    material["woodG"]->shininess = 50.0f;

    material["woodW"] = new Material;
    material["woodW"]->ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["woodW"]->diffuse = vec4(1.0f,1.0f,1.0f,1.0f);
    material["woodW"]->specular = vec4(0.3f,0.3f,0.3f,1.0f);
    material["woodW"]->shininess = 50.0f;

    material["silver"] = new Material;
    material["silver"]->ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["silver"]->diffuse = vec4(0.9f,0.9f,0.9f,1.0f);
    material["silver"]->specular = vec4(0.9f,0.9f,0.9f,1.0f);
    material["silver"]->shininess = 50.0f;

    material["bulb"] = new Material;
    material["bulb"]->ambient = vec4(0.0f,0.0f,0.0f,1.0f);
    material["bulb"]->diffuse = vec4(0.0f,0.0f,0.0f,1.0f);
    material["bulb"]->specular = vec4(1.0f,1.0f,1.0f,1.0f);
    material["bulb"]->emision = vec4(1.0f,1.0f,1.0f,1.0f);
    material["bulb"]->shininess = 200.0f;

    model["wallR"] = new Model;
    model["wallR"]->geometry = geometry["plane"];
    model["wallR"]->material = material["woodR"];
    model["wallG"] = new Model;
    model["wallG"]->geometry = geometry["plane"];
    model["wallG"]->material = material["woodG"];
    model["wallW"] = new Model;
    model["wallW"]->geometry = geometry["plane"];
    model["wallW"]->material = material["woodW"];
    model["box"] = new Model;
    model["box"]->geometry = geometry["cube"];
    model["box"]->material = material["silver"];
    model["bulb"] = new Model;
    model["bulb"]->geometry = geometry["plane"];
    model["bulb"]->material = material["bulb"];

    light["bulb"] = new Light;
    light["bulb"]->position = vec4(0.0f,1.8f,-0.25f,1.0f);
    light["bulb"]->color = 1.5f*vec4(1.0f,1.0f,1.0f,1.0f);

    node["room"] = new Node;
    // left
    node["room"]->models.push_back(model["wallR"]);
    node["room"]->modeltransforms.push_back(translate(vec3(-0.5f,0.5f,0.0f))*rotate(float(M_PI)/2.0f,vec3(0.0f,1.0f,0.0f)));
    // right
    node["room"]->models.push_back(model["wallG"]);
    node["room"]->modeltransforms.push_back(translate(vec3(0.5f,0.5f,0.0f))*rotate(float(M_PI)/-2.0f,vec3(0.0f,1.0f,0.0f)));
    // bottom
    node["room"]->models.push_back(model["wallW"]);
    node["room"]->modeltransforms.push_back(rotate(float(M_PI)/2.0f,vec3(-1.0f,0.0f,0.0f)));
    // top
    node["room"]->models.push_back(model["wallW"]);
    node["room"]->modeltransforms.push_back(translate(vec3(0.0f,1.0f,0.0f))*rotate(float(M_PI)/-2.0f,vec3(-1.0f,0.0f,0.0f)));
    // back
    node["room"]->models.push_back(model["wallW"]);
    node["room"]->modeltransforms.push_back(translate(vec3(0.0f,0.5f,-0.5f)));
    // box
    node["room"]->models.push_back(model["box"]);
    node["room"]->modeltransforms.push_back(rotate(float(M_PI/4.0f),vec3(0.0f,1.0f,0.0f))*scale(vec3(0.3f))*translate(vec3(0.0f,0.5f,-0.5f)));
    // bulb
    node["room"]->models.push_back(model["bulb"]);
    node["room"]->modeltransforms.push_back(scale(vec3(0.5f))*translate(vec3(0.0f,1.9f,0.0f))*rotate(float(M_PI)/-2.0f,vec3(-1.0f,0.0f,0.0f)));

    node["world"]->childnodes.push_back(node["room"]);
    node["world"]->childtransforms.push_back(scale(vec3(1.5f)));
    */
    
    // Create a geometry palette
    geometry["cube"] = new Cube;
    geometry["teapot"] = new Obj;
    geometry["bunny"] = new Obj;
    geometry["cube"] -> init();
    geometry["teapot"] -> init("models/teapot.obj");
    geometry["bunny"] -> init("models/bunny.obj");
    
    // Create a material palette
    material["wood"] = new Material;
    material["wood"] -> ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["wood"] -> diffuse = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> shininess = 100.0f;
    
    material["ceramic"] = new Material;
    material["ceramic"] -> ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    material["ceramic"] -> diffuse = vec4(0.1f, 0.25f, 0.7f, 1.0f);
    material["ceramic"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["ceramic"] -> shininess = 150.0f;
 
    material["silver"] = new Material;
    material["silver"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["silver"] -> diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    material["silver"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["silver"] -> shininess = 50.0f;
    
    material["turquoise"] = new Material;
    material["turquoise"] -> ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    material["turquoise"] -> diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    material["turquoise"] -> specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    material["turquoise"] -> shininess = 100.0f;
    
    material["bulb"] = new Material;
    material["bulb"] -> ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material["bulb"] -> emision = vec4(1.0f,0.2f,0.1f,1.0f);
    material["bulb"] -> shininess = 200.0f;
    
    // Create a model palette
    model["teapot1"] = new Model;
    model["teapot1"] -> geometry = geometry["teapot"];
    model["teapot1"] -> material = material["silver"];
    model["teapot2"] = new Model;
    model["teapot2"] -> geometry = geometry["teapot"];
    model["teapot2"] -> material = material["ceramic"];
    model["table piece"] = new Model;
    model["table piece"] -> geometry = geometry["cube"];
    model["table piece"] -> material = material["wood"];
    model["bunny"] = new Model;
    model["bunny"] -> geometry = geometry["bunny"];
    model["bunny"] -> material = material["turquoise"];
    model["bulb"] = new Model;
    model["bulb"] -> geometry = geometry["cube"];
    model["bulb"] -> material = material["bulb"];
    
    // Create a light palette
    light["sun"] = new Light;
    light["sun"] -> position = vec4(3.0f,2.0f,1.0f,0.0f);
    light["sun"] -> color = 1.0f*vec4(1.0f,1.0f,1.0f,1.0f);
    
    light["bulb"] = new Light;
    light["bulb"] -> position = vec4(0.0f,2.0f,0.0f,0.0f);
    light["bulb"] -> color = 1.5f * vec4(1.0f,0.2f,0.1f,1.0f);
    
    // Build the scene graph
    node["table"] = new Node;
    node["table top"] = new Node;
    node["table leg"] = new Node;
    node["teapot1"] = new Node;
    node["teapot2"] = new Node;
    node["bunny"] = new Node;
    
    
    node["table"] -> childnodes.push_back( node["table top"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.0f,1.2f,0.0f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-0.9f,0.0f,-0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-0.9f,0.0f,0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.9f,0.0f,0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.9f,0.0f,-0.4f)) );
    
    node["table leg"] -> models.push_back( model["table piece"] );
    node["table leg"] -> modeltransforms.push_back( translate(vec3(0.0f,0.5f,0.0f)) * scale(vec3(0.2f,1.0f,0.2f)) );
    
    node["table top"] -> models.push_back( model["table piece"] );
    node["table top"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.1f,0.0f)) * scale(vec3(2.0f,0.2f,1.0f)) );
    //node["table top"] -> childnodes.push_back( node["teapot1"] );
    //node["table top"] -> childtransforms.push_back( translate(vec3(-0.5f,0.0f,0.0f)) );
    //node["table top"] -> childnodes.push_back( node["teapot2"] );
    //node["table top"] -> childtransforms.push_back( translate(vec3( 0.5f,0.0f,0.0f)) * rotate( -120.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    
    node["teapot1"] -> models.push_back( model["teapot1"] );
    node["teapot1"] -> modeltransforms.push_back( scale(vec3(0.5f)) );
    node["teapot2"] -> models.push_back( model["teapot2"] );
    node["teapot2"] -> modeltransforms.push_back( scale(vec3(1.0f,1.5f,1.0f)) * scale(vec3(0.5f)) );
    
    node["bunny"] -> models.push_back( model["bunny"] );
    node["bunny"] -> modeltransforms.push_back( scale(vec3(0.8f)) * translate(vec3(0.0f,1.0f,0.0f)) );
    
    node["world"] -> childnodes.push_back( node["table"] );
    node["world"] -> childtransforms.push_back( mat4(1.0f) );
    //node["world"] -> childnodes.push_back( node["bunny"] );
    //node["world"] -> childtransforms.push_back( translate(vec3(-1.8f,0.0f,0.0f)) * rotate( 90.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ));
    node["world"] -> models.push_back( model["bulb"] );
    node["world"]->modeltransforms.push_back(translate(vec3(0.0f,2.0f,0.0f))* scale(vec3(0.1f)));
    

    // Put a camera
    camera = new Camera;
    camera -> target_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> eye_default = vec3( 0.0f, 1.0f, 5.0f );
    camera -> up_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> reset();
    
    // Initialize shader
    shader = new SurfaceShader;
    shader -> read_source( "shaders/projective.vert", "shaders/lighting.frag" );
    shader -> compile();
    glUseProgram(shader -> program);
    shader -> initUniforms();
}
