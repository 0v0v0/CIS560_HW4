#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>

#include <scene/cube.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>





//Class of Scene Graph
//场景图
//
class SceneGraph
{

public:
    //name
    QString name;
    //vectors of childrens
    std::vector<SceneGraph *> children;
    //
    int num_children;//number of children

    //pointer to the object
    Drawable* obj;//Type is Drawable

    //
    bool isdrawn;//see if the obj is drawn or not


    //color of the object
    glm::vec4 color;
    //transformation matrix
    glm::mat4 trans;

    //virtual functions
    SceneGraph();//Constructor
    //
    void Init_Graph();//initialize a new graph;
    //
    void rotate(glm::vec4 info);//{x, y, z, rotate angle}
    void translate(glm::vec4 info);//{x,y,z,whatever}
    void scale(glm::vec4 info);//{x,y,z,whatever}

};
//END of Scene Graph


//inheritated classes of Scene Graph
//场景图的继承类

class RotateNode: public SceneGraph
{
    RotateNode(glm::vec4 info);//x,y,z,angle
    //void rotate(glm::vec4 angle);
};

class TranslateNode: public SceneGraph
{
    TranslateNode(glm::vec4 info);//dx,dy,dz,anything
    //void translate(glm::vec4 direction);
};

class ScaleNode: public SceneGraph
{
    ScaleNode(glm::vec4 info);//x,y,z,anything
    //void scale(glm::vec4 scaling);
};

//END of Inheritated Classes





//下面的才是原来的……




class MyGL
    : public GLWidget277
{
private:
    Cylinder geom_cylinder;// The instance of a unit cylinder we can use to render any cylinder
    Sphere geom_sphere;// The instance of a unit sphere we can use to render any sphere

    Cube geom_cube;//The unit CUBE

    ShaderProgram prog_lambert;// A shader program that uses lambertian reflection
    ShaderProgram prog_flat;// A shader program that uses "flat" reflection (no shadowing at all)

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.


public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    //在此添加场景图的root节点
    SceneGraph root;
    void readnode(SceneGraph* parent, glm::mat4 T);
    //

protected:
    void keyPressEvent(QKeyEvent *e);
};








#endif // MYGL_H
