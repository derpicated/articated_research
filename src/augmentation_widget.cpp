// augmentation_widget.cpp

#include "augmentation_widget.h"

#include <GL/gl.h>
#include <QVector2D>
#include <QVector3D>

// clang-format off
#define MATRIX_INITVAL  1, 0, 0, 0,\
                        0, 1, 0, 0,\
                        0, 0, 1, 0,\
                        0, 0, 0, 1
// clang-format on

augmentation_widget::augmentation_widget (QWidget* parent)
: QOpenGLWidget (parent)
, _scale_factor (1.0f)
, _x_pos (0.0f)
, _y_pos (0.0f)
, _x_persp_mat{ MATRIX_INITVAL }
, _y_persp_mat{ MATRIX_INITVAL }
, _z_persp_mat{ MATRIX_INITVAL } {
}

augmentation_widget::~augmentation_widget () {
}

QSize augmentation_widget::minimumSizeHint () const {
    return QSize (100, 100);
}

QSize augmentation_widget::sizeHint () const {
    return QSize (500, 500);
}

bool augmentation_widget::loadObject (std::string path) {
    std::vector<QVector3D> vertices;
    std::vector<QVector2D> uvs;
    std::vector<QVector3D> normals; // Won't be used at the moment.
    bool res = parseObject (path.c_str (), vertices, uvs, normals);

    if (res == true) {
        GLuint vertexbuffer;
        glGenBuffers (1, &vertexbuffer);
        glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData (GL_ARRAY_BUFFER, vertices.size () * sizeof (QVector3D),
        &vertices[0], GL_STATIC_DRAW);

        GLuint uvbuffer;
        glGenBuffers (1, &uvbuffer);
        glBindBuffer (GL_ARRAY_BUFFER, uvbuffer);
        glBufferData (GL_ARRAY_BUFFER, uvs.size () * sizeof (QVector2D), &uvs[0], GL_STATIC_DRAW);
    }
    return res;
}

void augmentation_widget::setBackground (GLvoid* image, GLsizei width, GLsizei height) {
    // create background texture
    glBindTexture (GL_TEXTURE_2D, _texture_background);
    // TODO: maybe move these to init?
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
}

void augmentation_widget::setScale (const float scale) {
    _scale_factor = scale;
}

void augmentation_widget::setXPosition (const float location) {
    _x_pos = location;
}

void augmentation_widget::setYPosition (const float location) {
    _y_pos = location;
}

void augmentation_widget::setXRotation (const GLfloat persp_mat[16]) {
    for (int i = 0; i < 16; i++) {
        _x_persp_mat[i] = persp_mat[i];
    }
}

void augmentation_widget::setYRotation (const GLfloat persp_mat[16]) {
    for (int i = 0; i < 16; i++) {
        _y_persp_mat[i] = persp_mat[i];
    }
}

void augmentation_widget::setZRotation (const GLfloat persp_mat[16]) {
    for (int i = 0; i < 16; i++) {
        _z_persp_mat[i] = persp_mat[i];
    }
}

void augmentation_widget::initializeGL () {
    initializeOpenGLFunctions ();

    glClearColor (0, 0, 0, 1.0f);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glMatrixMode (GL_PROJECTION);
    glEnable (GL_TEXTURE_2D);
    glGenTextures (1, &_texture_background);
    glEnable (GL_COLOR_MATERIAL);

    glMatrixMode (GL_MODELVIEW);
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
    glLoadIdentity ();
    // gluPerspective (33.7, 1.3, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void augmentation_widget::resizeGL (int width, int height) {
    int side = qMin (width, height);
    glViewport ((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
#ifdef QT_OPENGL_ES_1
    glOrthof (-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho (-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode (GL_MODELVIEW);
}

void augmentation_widget::paintGL () {
    glMatrixMode (GL_MODELVIEW);
    // QOpenGLFunctions* f = QOpenGLContext::currentContext ()->functions
    // ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    // draw background
    glTranslatef (0.0, 0.0, -10.0);

    glBegin (GL_QUADS);
    glColor3f (1, 1, 1);
    glTexCoord2f (0.0, 1.0);
    glVertex3f (-4.0, -3.0, -2.0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f (4.0, -3.0, -2.0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f (4.0, 3.0, -2.0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f (-4.0, 3.0, -2.0);
    glEnd ();

    glPushMatrix ();

    glTranslatef (_x_pos, _y_pos, 0);
    glScalef (_scale_factor, _scale_factor, _scale_factor);
    glMultMatrixf (_x_persp_mat);
    glMultMatrixf (_y_persp_mat);
    glMultMatrixf (_z_persp_mat);

    drawObject ();

    glPopMatrix ();
}

void augmentation_widget::drawObject () {
    glBegin (GL_QUADS);
    glColor3f (0, 1, 1);
    glNormal3f (0, 0, -1);
    glVertex3f (-1, -1, 0);
    glVertex3f (-1, 1, 0);
    glVertex3f (1, 1, 0);
    glVertex3f (1, -1, 0);
    glEnd ();

    glBegin (GL_TRIANGLES);
    glColor3f (1, 0, 0);
    glNormal3f (0, -1, 0.707);
    glVertex3f (-1, -1, 0);
    glVertex3f (1, -1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glColor3f (0, 1, 0);
    glNormal3f (1, 0, 0.707);
    glVertex3f (1, -1, 0);
    glVertex3f (1, 1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glColor3f (0, 0, 1);
    glNormal3f (0, 1, 0.707);
    glVertex3f (1, 1, 0);
    glVertex3f (-1, 1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
    glBegin (GL_TRIANGLES);
    glColor3f (1, 1, 0);
    glNormal3f (-1, 0, 0.707);
    glVertex3f (-1, 1, 0);
    glVertex3f (-1, -1, 0);
    glVertex3f (0, 0, 1.2);
    glEnd ();
}

bool augmentation_widget::parseObject (const char* path,
std::vector<QVector3D>& out_vertices,
std::vector<QVector2D>& out_uvs,
std::vector<QVector3D>& out_normals) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<QVector3D> temp_vertices;
    std::vector<QVector2D> temp_uvs;
    std::vector<QVector3D> temp_normals;


    FILE* file = fopen (path, "r");
    if (file == NULL) {
        getchar ();
        return false;
    }

    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf (file, "%s", lineHeader);
        if (res == EOF) break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp (lineHeader, "v") == 0) {
            float x, y, z;
            QVector3D vertex;
            fscanf (file, "%f %f %f\n", &x, &y, &z);
            vertex.setX (x);
            vertex.setY (y);
            vertex.setZ (z);
            temp_vertices.push_back (vertex);
        } else if (strcmp (lineHeader, "vt") == 0) {
            float x, y;
            QVector2D uv;
            fscanf (file, "%f %f\n", &x, &y);

            uv.setX (x);
            uv.setY (-y); // Invert V coordinate since we will only use DDS
                          // texture, which are inverted. Remove if you want
                          // to use TGA or BMP loaders.
            temp_uvs.push_back (uv);
        } else if (strcmp (lineHeader, "vn") == 0) {
            float x, y, z;
            QVector3D normal;
            fscanf (file, "%f %f %f\n", &x, &y, &z);
            normal.setX (x);
            normal.setY (y);
            normal.setZ (z);
            temp_normals.push_back (normal);
        } else if (strcmp (lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf (file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
            &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1],
            &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf ("File can't be read by our simple parser :-( Try "
                        "exporting with other options\n");
                return false;
            }
            vertexIndices.push_back (vertexIndex[0]);
            vertexIndices.push_back (vertexIndex[1]);
            vertexIndices.push_back (vertexIndex[2]);
            uvIndices.push_back (uvIndex[0]);
            uvIndices.push_back (uvIndex[1]);
            uvIndices.push_back (uvIndex[2]);
            normalIndices.push_back (normalIndex[0]);
            normalIndices.push_back (normalIndex[1]);
            normalIndices.push_back (normalIndex[2]);
        } else {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets (stupidBuffer, 1000, file);
        }
    }

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size (); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex     = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        QVector3D vertex = temp_vertices[vertexIndex - 1];
        QVector2D uv     = temp_uvs[uvIndex - 1];
        QVector3D normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back (vertex);
        out_uvs.push_back (uv);
        out_normals.push_back (normal);
    }

    return true;
}
