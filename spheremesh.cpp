#include "SphereMesh.h"
#include "DebugApplication.h"

//void copyPlane2Buffer(Vertex * & vertexBuffer, GLuint * & elementBuffer, unsigned int & elementStartIndex,
//                      const Vertex & a, const Vertex & b, const Vertex & c/*, const Vertex & d*/);


SphereMesh::SphereMesh(float radius, int sectors, int stacks)
{
    this->radius = radius;
    this->sectors = sectors;
    this->stacks = stacks;
    const float PI = acos(-1);

    // clear memory of prev arrays
    clearArrays();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stacks; ++i)
        {
            stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
            xy = radius * cosf(stackAngle);             // r * cos(u)
            z = radius * sinf(stackAngle);              // r * sin(u)

            // add (sectorCount+1) vertices per stack
            // the first and last vertices have same position and normal, but different tex coords
            for(int j = 0; j <= sectors; ++j)
            {
                sectorAngle = j * sectorStep;           // starting from 0 to 2pi

                // vertex position
                x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
                m_vertices.push_back(QVector3D(x, y, z));

                // normalized vertex normal
                nx = x * lengthInv;
                ny = y * lengthInv;
                nz = z * lengthInv;
                m_normals.push_back(QVector3D(nx, ny, nz));

                // vertex tex coord between [0, 1]
                s = (float)j / sectors;
                t = (float)i / stacks;
                m_textures.push_back(QVector2D(s, t));
            }
        }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < stacks; ++i)
    {
        k1 = i * (sectors + 1);     // beginning of current stack
        k2 = k1 + sectors + 1;      // beginning of next stack

        for(int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }

            if(i != (stacks-1))
            {
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }

            // vertical lines for all stacks
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if(i != 0)  // horizontal lines except 1st stack
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }

    // generate interleaved vertex array as well
    //buildInterleavedVertices();



}

void SphereMesh::transform(const QMatrix4x4 & transform){
    for (QVector3D & v : m_vertices)
        v = transform * v;
}


void SphereMesh::addIndices(unsigned int i1, unsigned int i2, unsigned int i3){
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);

}

//void SphereMesh::buildInterleavedVertices(){}

void SphereMesh::clearArrays(){
    std::vector<QVector3D>().swap(m_vertices);
    std::vector<QVector3D>().swap(m_normals);
    std::vector<QVector2D>().swap(m_textures);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);
}

void SphereMesh::copy2Buffer(Vertex *& vertexBuffer, GLuint *& elementBuffer,
                             unsigned int & vertexStartIndex,
                             unsigned int & elementStartIndex) const {
    std::vector<QColor> cols;
    Q_ASSERT(!m_colors.empty());
    // three ways to store vertex colors
    if (m_colors.size() == 1) {
        cols = std::vector<QColor>(6, m_colors[0]);
    }
    else {
        Q_ASSERT(m_colors.size() == 6);
        cols = m_colors;
    }


    // now we populate the vertex buffer for all planes

    int sSize = m_vertices.size();
    //  plane: a, b, c,  vertexes (0, 1, 2)
//    for (int i = 0; i < sSize; i+=3){
//    copyPlane2Buffer(vertexBuffer, elementBuffer, elementStartIndex,
//            Vertex(m_vertices[i], cols[i%6]),
//            Vertex(m_vertices[i+1], cols[i%6]),
//            Vertex(m_vertices[i+2], cols[i%6]),
//            QVector3D(indices[i],indices[i+1],indices[i+2]),
//            QVector3D(indices[i+3],indices[i+4],indices[i+5])
//            //Vertex(m_vertices[3], cols[0])
//        );
//    }

    for (int i = vertexStartIndex, j = 0; j < sSize; i++, j++){
        vertexBuffer[i] = Vertex(m_vertices[j], cols[j%6]);
    }

    int sInd = indices.size();
    for (int i = elementStartIndex, j = 0; j < sInd; i++, j++){
        elementBuffer[i] = (unsigned int)indices[j] + vertexStartIndex;
    }
    vertexStartIndex += sSize;
    elementStartIndex += sInd;

}


//void copyPlane2Buffer(Vertex * & vertexBuffer, GLuint * & elementBuffer, unsigned int & elementStartIndex,
//                      const Vertex & a, const Vertex & b, const Vertex & c/*, const Vertex & d*/)
//{
//    // first store the vertex data (a,b,c,d in counter-clockwise order)

//    vertexBuffer[0] = a;
//    vertexBuffer[1] = b;
//    vertexBuffer[2] = c;
//    //vertexBuffer[3] = d;

//    // tweak the colors of the bottom left and bottom right nodes
////    if (a.y < c.y) {
////        vertexBuffer[0].r *= 0.5;
////        vertexBuffer[1].r *= 0.5;
////        vertexBuffer[0].g *= 0.5;
////        vertexBuffer[1].g *= 0.5;
////        vertexBuffer[0].b *= 0.5;
////        vertexBuffer[1].b *= 0.5;
////    }

//    // advance vertexBuffer
//    vertexBuffer += 3;
//    //vertexBuffer += 4;

//    // we generate data for two triangles: a, b, d  and b, c, d

////    elementBuffer[0] = ind1[0];
////    elementBuffer[1] = ind1[1];
////    elementBuffer[2] = ind1[2];
////    elementBuffer[3] = ind2[0];
////    elementBuffer[4] = ind2[1];
////    elementBuffer[5] = ind2[2];
////    elementBuffer[0] = elementStartIndex;
////    elementBuffer[1] = elementStartIndex+1;
////    elementBuffer[2] = elementStartIndex+2;
////    elementBuffer[2] = elementStartIndex+3;
////    elementBuffer[3] = elementStartIndex+1;
////    elementBuffer[4] = elementStartIndex+2;
////    elementBuffer[5] = elementStartIndex+3;

//    // advance elementBuffer
//    elementBuffer += 3;
//    //elementBuffer += 6;
//    // 4 vertices have been added, so increase start number for next plane
//    elementStartIndex += 3;
//    //elementStartIndex += 4;
//}

//void SphereMesh::draw(){


//}
