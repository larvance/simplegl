#pragma once
#include <glad/glad.h>

class Layout {
public:
    enum class Type {
        Byte          = GL_BYTE,
        UnsignedByte  = GL_UNSIGNED_BYTE,
        Short         = GL_SHORT,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Int           = GL_INT,
        UnsignedInt   = GL_UNSIGNED_INT,
        HalfFloat     = GL_HALF_FLOAT,
        Float         = GL_FLOAT,
        Double        = GL_DOUBLE,
        Fixed         = GL_FIXED
    };

    Type type;
    int count;
    int size;
    GLboolean normalized;

    Layout(Type type, int count, bool normalized = false) : type(type), count(count), normalized(normalized) {
        switch (type) {
        case Type::Byte:
        case Type::UnsignedByte:
            size = sizeof(GLbyte) * count;
            break;
        case Type::Short:
        case Type::UnsignedShort:
            size = sizeof(GLshort) * count;
            break;
        case Type::Int:
        case Type::UnsignedInt:
            size = sizeof(GLint) * count;
            break;
        case Type::HalfFloat:
            size = sizeof(GLhalf) * count;
            break;
        case Type::Float:
            size = sizeof(GLfloat) * count;
            break;
        case Type::Double:
            size = sizeof(GLdouble) * count;
            break;
        case Type::Fixed:
            size = sizeof(GLfixed) * count;
            break;
        }
    }
};
