#include "headers/GameObject.hpp"
#include "headers/ShaderProgram.hpp"

GameObject::GameObject() {
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),vertices.data(),GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(3*sizeof(float)));

}

GameObject::~GameObject() {
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}

void GameObject::draw(ShaderProgram &shaderProgram) {
    glBindVertexArray(VAO);
    shaderProgram.use();
    glDrawArrays(GL_TRIANGLES,0,vertices.size());
}
