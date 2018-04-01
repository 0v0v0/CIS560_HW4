Q1:
Virtual Functions can be defined by both the parent class and the inherited classes. If we need to describe an object that has many sub-divisions which acts differently, then we will need to use virtual functions. (eg. class Animal, class Cat: public Animal, class Dog: public Animal, and virtual function talk() ). 

In this case, the function in the Derived class's func(). 

Q2:

These are not the actual data of vertices' positions or colors, these are the positions of the vertex data in the buffer. These attributes are given values from the index of vertices we created in the scene folder. 

Q3:

A uniform variable is like a constant variable in C language, it does not change during the procedure, so we could use it for some parameters that will not change, for example, a projection matrix. 

We can consider the "in" and "out" like the input and output in an electronic system, the only difference is that they are parallel  processed rather than one by one. In the vertex shader system and the fragment shader system, there both exists in and out variables. So we could use the "out" variables in the vertex shader to pass data to the fragment shader. 
