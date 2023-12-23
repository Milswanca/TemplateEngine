#pragma once
#include "Rendering/RHI/Resources/RHIVertexStateObject.h"
#include <glad/glad.h>
#include <unordered_map>

class OpenGLVertexStateObject : public RHIVertexStateObject
{
public:
    OpenGLVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes);
    ~OpenGLVertexStateObject();
    
    void Rebuild();

    void Bind();
    void Unbind();
    
protected:
    static std::unordered_map<VertexAttributeTypes, GLenum> s_VertexAttribTypeToOGL;
    
private:
    GLuint m_VertexArrayObject;
};
