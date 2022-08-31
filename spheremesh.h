#ifndef SPHEREMESH_H
#define SPHEREMESH_H

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QColor>
#include <vector>

#include <transform3d.h>
#include <Vertex.h>


class SphereMesh
{
public:
    //SphereMesh(float r = 0.7f, int sec = 18, int st = 12):
    SphereMesh(float radius, int sectors, int stacks);//{}
//    {
//        this->radius = radius;
//        this->sectors = sectors;
//        this->stacks = stacks;
//    }
    //~SphereMesh();




    void setColor(QColor c) { m_colors = std::vector<QColor>(1,c); }
    void setFaceColors(const std::vector<QColor> & c) { Q_ASSERT(c.size() == 6); m_colors = c; }

    void transform(const QMatrix4x4 & transform);

    void copy2Buffer(Vertex * & vertexBuffer,
                     GLuint * & elementBuffer,
                     unsigned int & vertexStartIndex,
                     unsigned int & elementStartIndex) const;

//    void setVertexCount(unsigned int count){VectexCount = count; }//?
//    void setIndexCount(unsigned int count){IndexCount = count; }
    unsigned int getVertexCount(){
        if(!VertexCount)
            //VertexCount =  2 + sectors * (stacks - 1);
            VertexCount =  (sectors + 1) * (stacks + 1);
        return VertexCount;
    }////
    unsigned int getIndexCount(){
        if(!IndexCount)
            IndexCount = 3 * 2 * sectors * (stacks - 1);
        return IndexCount;
    }//???
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    //void buildInterleavedVertices();
    void clearArrays();
    void draw();

protected:
    float radius;
    int sectors;                        // longitude, # of slices (долгота)
    int stacks;

private:
    std::vector<unsigned int> lineIndices;
    std::vector<unsigned int> indices;

    std::vector<QVector3D> m_vertices;
    std::vector<QVector3D> m_normals;
    std::vector<QVector2D> m_textures;
    std::vector<QColor> m_colors;

    unsigned int VertexCount = 0;//?
    unsigned int IndexCount = 0;

//    float radius;
//    int sectors;// longitude, # of slices
//    int stacks;
};

#endif // SPHEREMESH_H
