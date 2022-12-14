/**************************************************
RTScene.cpp contains the implementation of the buildTriangleSoup command
*****************************************************/
#include <string>
#include <iostream>
#include "RTScene.h"
#include "RTCube.h"
#include "RTObj.h"

// The scene init definition 
 #include "RTScene.inl"


using namespace glm;

void display_4x4(std::string tag,glm::mat4 m4)
{
    std::cout<<tag<<'\n';
    for(int col = 0; col<4; ++col) {
        std::cout<<"| ";
        for(int row = 0; row<4; ++row) {
            std::cout<<m4[row][col]<<'\t';
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

/**
* IN WORLD COORDINATE
*/
void RTScene::buildTriangleSoup() {
    camera -> computeMatrices();
    triangle_soup.clear();
    
    // Define stacks for depth-first search (DFS)
    std::stack < RTNode* > dfs_stack;
    std::stack < mat4 >  matrix_stack;
    
    // Initialize the current state variable for DFS
    RTNode* cur = node["world"]; // root of the tree
    mat4 cur_VM = mat4(1.0f);

    dfs_stack.push(cur);
    matrix_stack.push(cur_VM);
    
    // Compute total number of connectivities in the graph; this would be an upper bound for
    // the stack size in the depth first search over the directed acyclic graph
    int total_number_of_edges = 0; 
    for ( const auto &n : node ) total_number_of_edges += n.second->childnodes.size();
    
    // If you want to print some statistics of your scene graph
    // std::cout << "total numb of nodes = " << node.size() << std::endl;
    // std::cout << "total number of edges = " << total_number_of_edges << std::endl;
    
    while( ! dfs_stack.empty() ){
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the number of edges in the graph.
        if ( dfs_stack.size() > total_number_of_edges ){
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }
        
        // top-pop the stacks
        cur = dfs_stack.top();  dfs_stack.pop();
        cur_VM = matrix_stack.top();  matrix_stack.pop();
        
        // apply transformation to all the models at the current node
        for ( size_t i = 0; i < cur -> models.size(); i++ ){
            mat4 modelview = cur_VM * cur -> modeltransforms[i];
            //display_4x4("modelview",modelview);

            // extract upper left 3*3
            mat3 A;
            for(int j = 0; j < 3; j++)
                A[j] = vec3(modelview[j][0],modelview[j][1],modelview[j][2]);
            A = inverse(transpose(A));

            // Prepare to draw the geometry. Assign the modelview and the material.
            for(Triangle old : (cur -> models[i] -> geometry -> elements)) {
                Triangle currTriangle;
                currTriangle.material = (cur -> models[i]) -> material;

                // loop through all 3 points of the triangle
                for(int j = 0; j < 3; j++){
                    // apply transformation to the normal
                    currTriangle.N.push_back(glm::normalize(A * old.N[j]));

                    // apply transformation to the old point
                    vec4 oldPoint = vec4(old.P[j], 1.0f);
                    oldPoint = modelview * oldPoint;
                    vec3 newPoint = vec3(oldPoint[0] / oldPoint[3],
                                         oldPoint[1] / oldPoint[3],
                                         oldPoint[2] / oldPoint[3]);
                    currTriangle.P.push_back(newPoint);
                }
                triangle_soup.push_back(currTriangle);
            }
        }
        
        // Continue the DFS: put all the child nodes of the current node in the stack
        for ( size_t i = 0; i < cur -> childnodes.size(); i++ ){
            dfs_stack.push( cur -> childnodes[i] );
            matrix_stack.push( cur_VM * cur -> childtransforms[i] );
        }
        
    }
}