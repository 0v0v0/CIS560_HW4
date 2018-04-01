#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>

//this is pie
#define pi 3.14159f
//
//TEST
extern int draws;
extern SceneGraph * leg1;
extern SceneGraph * leg2;
extern SceneGraph * leg3;
extern SceneGraph * leg4;
extern SceneGraph * bodys;
//


MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent),
      geom_cylinder(this), geom_sphere(this), //TODO: When you make your Cube instance, add it to this init list
      geom_cube(this),
      prog_lambert(this), prog_flat(this)
{
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    geom_cylinder.destroy();
    geom_sphere.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    geom_cylinder.create();

    geom_sphere.create();

    geom_cube.create();//create CUBE

    // Create and set up the diffuse shader
    prog_lambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    prog_flat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    // Set a color with which to draw geometry since you won't have one
    // defined until you implement the Node classes.
    // This makes your geometry render green.
    prog_lambert.setGeometryColor(glm::vec4(0,1,0,1));

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
//    vao.bind();
    glBindVertexArray(vao);


{
    //I revised at here
    //我在此进行了修改

    root.Init_Graph();
    root.name="root";

    //create a centaur From HERE
    SceneGraph* tmp;
    SceneGraph* tmp1;
    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();

    //create horse body
    tmp->name="body";
    tmp->obj=&geom_cylinder;
    tmp->color={3,0,0,0};
    //
    tmp->rotate({0,0,1,90.0f});
    tmp->scale({2,4,2,0});
    //
    tmp->children.clear();
    (root.children).push_back(tmp);//ADD tmp to the root
    root.num_children++;
    tmp1=tmp;
    //


    /********/
    //Create The Four Legs
    //because legs have no child junctions, so create them first
    /********/
    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a leg beneath the horse body
    tmp->name="leg1";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->rotate({0,0,1,90.0f});
    tmp->translate({-2,1,1,0});
    tmp->scale({1,0.5,0.5,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //
    leg1=tmp;

    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a leg beneath the horse body
    tmp->name="leg2";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->rotate({0,0,1,90.0f});
    tmp->translate({-2,-1,1,0});
    tmp->scale({1,0.5,0.5,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //
    leg2=tmp;

    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a leg beneath the horse body
    tmp->name="leg3";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->rotate({0,0,1,90.0f});
    tmp->translate({-2,1,-1,0});
    tmp->scale({1,0.5,0.5,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //
    leg3=tmp;

    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a leg beneath the horse body
    tmp->name="leg4";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->rotate({0,0,1,90.0f});
    tmp->translate({-2,-1,-1,0});
    tmp->scale({1,0.5,0.5,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //
    leg4=tmp;

    //A centaur has a human body, and a human head, and two human arms
    //create the Human Body on Top of the horse body
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create human body on the top of horse body
    tmp->name="human body";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->translate({-2,2,0,0});
    tmp->rotate({0,0,1,90.0f});
    tmp->scale({0.7,0.5,0.5,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //
    bodys=tmp;

    //
    tmp1=tmp;//Ready to create children nodes of the human body
    //


    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a arm on the human body
    tmp->name="arm1";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->translate({-2.3,1.5,-4,0});
    tmp->rotate({0,1,0,90.0f});
    tmp->scale({3,1,1,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //


    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a arm on the human body
    tmp->name="arm2";
    tmp->obj=&geom_cylinder;
    tmp->color={0,1,0,0};
    //
    tmp->translate({-2.3,1.5,-7.3,0});
    tmp->rotate({0,1,0,90.0f});
    tmp->scale({3,1,1,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //


    //create a part
    tmp=new(SceneGraph);
    tmp->Init_Graph();
    //create a cubic head on the human body
    tmp->name="head";
    tmp->obj=&geom_cube;
    tmp->color={0,1,0,0};
    //
    tmp->translate({0.7,1,2,0});
    tmp->scale({2,2,2,0});
    //
    tmp->children.clear();
    //
    (tmp1->children).push_back(tmp);//ADD tmp to the children list
    tmp1->num_children++;
    //
}



}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    glm::vec4 c1(1.1933f, 0, 1.1933f, 0);
    glm::vec4 c2(0.9856f, 1.9712f, -0.9856f, 0);
    glm::vec4 c3(0.5785f, -0.5785f, -0.5785f, 11.9484f);
    glm::vec4 c4(0.5774f, -0.5774f, -0.5774f, 12.1244f);
    glm::mat4 viewproj(c1, c2, c3, c4);
    //Transpose since GLM is column major and I wrote out the rows of the matrix
    viewproj = glm::transpose(viewproj);

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    prog_lambert.setViewProjMatrix(viewproj);
    prog_flat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
//DO NOT CONSTRUCT YOUR SCENE GRAPH IN THIS FUNCTION!
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


/*
    //VVV CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL VVV///////////////////
#define NOPE
#ifdef NOPE
    //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(3,3,3));
    //Send the geometry's transformation matrix to the shader
    prog_lambert.setModelMatrix(model);
    //Draw the example sphere using our lambert shader
    prog_lambert.draw(geom_sphere);

    //Now do the same to render the cylinder
    //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,0,1));
    prog_lambert.setModelMatrix(model);
    prog_lambert.draw(geom_cylinder);
#endif
    //^^^ CLEAR THIS CODE WHEN YOU IMPLEMENT SCENE GRAPH TRAVERSAL ^^^/////////////////

*/


    //Here is a good spot to call your scene graph traversal function.
    readnode(&root,glm::mat4(1.0f));



}


void MyGL::keyPressEvent(QKeyEvent *e)
{
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    }
}

//Implementation of SceneGraph classes

//constructor
SceneGraph::SceneGraph()
{
    obj=NULL;
    color={0,0,0,0};
    trans={
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    name="unknown";
    children.clear();
}
//
void SceneGraph::Init_Graph()
{
    obj=NULL;
    color={0,0,0,0};
    trans={
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    name="unknown";
    children.clear();
    num_children=0;

    isdrawn=0;
}


//inplement of functions
//I get help from:
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/

void SceneGraph::rotate(glm::vec4 info)//use {x, y, z, rotate angle}
{


    glm::mat4 tmp={
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    glm::mat4 push;
    float qx=info[0];
    float qy=info[1];
    float qz=info[2];
    float angle=info[3];

    //use glm::rotate
    tmp=glm::rotate( glm::mat4(1.0f), glm::radians(angle), glm::vec3(qx,qy,qz) );
    //
    push=trans*tmp;
    trans=push;


}

void SceneGraph::translate(glm::vec4 info)
{
    glm::mat4 tmp={
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };

    tmp[3][0]=info[0];
    tmp[3][1]=info[1];
    tmp[3][2]=info[2];

    glm::mat4 push;
    push=trans*tmp;
    trans=push;

}

void SceneGraph::scale(glm::vec4 info)
{
    glm::mat4 tmp={
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };

    tmp[0][0]=info[0];
    tmp[1][1]=info[1];
    tmp[2][2]=info[2];

    glm::mat4 push;
    push=trans*tmp;
    trans=push;
}




//Scene Graph Traversal
//the recursive function

void MyGL::readnode( SceneGraph* parent,glm::mat4 T)
{
    int length=parent->num_children;
    int i;
    SceneGraph* pchild;//tmp pointer to children
    glm::mat4 mattmp;

    //paint geometry

    mattmp=parent->trans * T;

    if( (parent->obj != NULL) )
    {


        prog_lambert.setModelMatrix( mattmp );
        prog_lambert.draw( *(parent->obj) ); //if exists, then draw?

        parent->isdrawn=1;

        draws++;
    }
    //

    //revise childrens
    for(i=0;i<length;i++)
    {
        pchild=(parent->children).at(i);

        readnode( pchild, parent->trans);//visit childrens from left to right 左子树遍历
    }
    //
}


