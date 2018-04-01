#include "cube.h"
#include<la.h>
#include <iostream>

static const int CUBE_IDX_COUNT = 36;//12 tris
static const int CUBE_VERT_COUNT = 24;//8 vertex

Cube::Cube(GLWidget277 *context) : Drawable(context)
{}

//These are functions that are only defined in this cpp file. They're used for organizational purposes
//when filling the arrays used to hold the vertex and index data.

//制造定点
void createCubeVertexPositions(glm::vec4 (&cube_vert_pos)[CUBE_VERT_COUNT])
{
    //Create Vertex on (1,1)~(0,0)
    glm::vec4 v;

    int i,j,k;
    int pos;

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            for(k = 0; k < 2; k++)
            {
                v = {i,j,k,1};//the fourth should be 1, NOT 0!!!!
                pos=i*4+j*2+k;
                cube_vert_pos[pos*3+0] = v;
                cube_vert_pos[pos*3+1] = v;
                cube_vert_pos[pos*3+2] = v;
            }
        }
    }
}

//制造顶点法线
void createCubeVertexNormals(glm::vec4 (&cube_vert_nor)[CUBE_VERT_COUNT])
{
    //for every cube vertex, there's 3 normals
    glm::vec4 v1,v2,v3;
    int i,j,k;//-1 or 1
    int pos=0;

    for(i = -1; i < 1; i++)
    {
        for(j = -1; j < 1; j++)
        {
            for(k=-1 ; k<1 ; k++)
            {
                v1={i+0.5,0,0,0};
                v2={0,j+0.5,0,0};
                v3={0,0,k+0.5,0};
                pos=(i+1)*4+(j+1)*2+(k+1);
                cube_vert_nor[pos*3+0] = v1;
                cube_vert_nor[pos*3+1] = v2;
                cube_vert_nor[pos*3+2] = v3;
            }
        }
    }
}

//创造index
void createCubeIndices(GLuint (&cube_idx)[CUBE_IDX_COUNT])
{

    int i,j,k;
    int count=0;

    cube_idx[0]=0;
    cube_idx[1]=1;
    cube_idx[2]=2;
    cube_idx[3]=0;
    cube_idx[4]=2;
    cube_idx[5]=4;
    cube_idx[6]=0;
    cube_idx[7]=1;
    cube_idx[8]=4;

    cube_idx[9]=3;
    cube_idx[10]=1;
    cube_idx[11]=2;
    cube_idx[12]=3;
    cube_idx[13]=1;
    cube_idx[14]=7;
    cube_idx[15]=3;
    cube_idx[16]=2;
    cube_idx[17]=7;

    cube_idx[18]=5;
    cube_idx[19]=1;
    cube_idx[20]=4;
    cube_idx[21]=5;
    cube_idx[22]=1;
    cube_idx[23]=7;
    cube_idx[24]=5;
    cube_idx[25]=4;
    cube_idx[26]=7;

    cube_idx[27]=6;
    cube_idx[28]=2;
    cube_idx[29]=7;
    cube_idx[30]=6;
    cube_idx[31]=2;
    cube_idx[32]=4;
    cube_idx[33]=6;
    cube_idx[34]=4;
    cube_idx[35]=7;

    for(i=0;i<12;i++)
    {
        cube_idx[i*3]=cube_idx[i*3] * 3;
        cube_idx[i*3+1]=cube_idx[i*3+1] * 3+1;
        cube_idx[i*3+2]=cube_idx[i*3+2] * 3+2;
    }

}

//创造形状
void Cube::create()
{
    GLuint cube_idx[CUBE_IDX_COUNT];
    glm::vec4 cube_vert_pos[CUBE_VERT_COUNT];
    glm::vec4 cube_vert_nor[CUBE_VERT_COUNT];

    createCubeVertexPositions(cube_vert_pos);
    createCubeVertexNormals(cube_vert_nor);
    createCubeIndices(cube_idx);

    count = CUBE_IDX_COUNT;

    // Create a VBO on our GPU and store its handle in bufIdx
    generateIdx();
    // Tell OpenGL that we want to perform subsequent operations on the VBO referred to by bufIdx
    // and that it will be treated as an element array buffer (since it will contain triangle indices)
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    // Pass the data stored in cube_idx into the bound buffer, reading a number of bytes equal to
    // CUBE_IDX_COUNT multiplied by the size of a GLuint. This data is sent to the GPU to be read by shader programs.
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, CUBE_IDX_COUNT * sizeof(GLuint), cube_idx, GL_STATIC_DRAW);

    // The next few sets of function calls are basically the same as above, except bufPos and bufNor are
    // array buffers rather than element array buffers, as they store vertex attributes like position.
    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, CUBE_VERT_COUNT * sizeof(glm::vec4), cube_vert_pos, GL_STATIC_DRAW);

    generateNor();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    context->glBufferData(GL_ARRAY_BUFFER, CUBE_VERT_COUNT * sizeof(glm::vec4), cube_vert_nor, GL_STATIC_DRAW);
}
