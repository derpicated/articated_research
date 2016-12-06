#include "model_loader.hpp"

#include <GL/gl.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

model_obj::model_obj () {
    this->TotalConnectedTriangles = 0;
    this->TotalConnectedPoints    = 0;
    _is_loaded                    = false;
}

void model_obj::calculate_normal (float* norm, float* coord1, float* coord2, float* coord3) {
    /* calculate Vector1 and Vector2 */
    float va[3], vb[3], vr[3], val;
    va[0] = coord1[0] - coord2[0];
    va[1] = coord1[1] - coord2[1];
    va[2] = coord1[2] - coord2[2];

    vb[0] = coord1[0] - coord3[0];
    vb[1] = coord1[1] - coord3[1];
    vb[2] = coord1[2] - coord3[2];

    /* cross product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    /* normalization factor */
    val = sqrt (vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

    norm[0] = vr[0] / val;
    norm[1] = vr[1] / val;
    norm[2] = vr[2] / val;
}

void model_obj::calculate_scale () {
    float max_val = 0;
    for (int i = TotalConnectedPoints - 1; i >= 0; --i) {
        float abs_val = fabs (vertexBuffer[i]);
        if (max_val < abs_val) {
            max_val = abs_val;
        }
    }
    _scale_factor =
    (1 / max_val); // ensure that every vertex fits in range -1 to 1
}

bool model_obj::load (const char* filename) {

    bool status = true;
    std::string line;

    if (_is_loaded) {
        release ();
    }

    std::ifstream objFile (filename);
    if (objFile.is_open ()) // If obj file is open, continue
    {
        objFile.seekg (0, std::ios::end); // Go to end of the file,
        long fileSize = objFile.tellg (); // get file size
        objFile.seekg (0, std::ios::beg); // we'll use this to register
                                          // memory for our 3d model

        vertexBuffer =
        (float*)malloc (fileSize); // Allocate memory for the verteces
        Faces_Triangles = (float*)malloc (
        fileSize * sizeof (float)); // Allocate memory for the triangles
        normals = (float*)malloc (
        fileSize * sizeof (float)); // Allocate memory for the normals

        int triangle_index = 0; // Set triangle index to zero
        int normal_index   = 0; // Set normal index to zero

        while (!objFile.eof ()) {
            getline (objFile, line);

            if (line.c_str ()[0] == 'v') // geometry: vertex
            {
                line[0] = ' '; // Set first character to 0. This will allow us
                               // to use sscanf

                sscanf (line.c_str (),
                "%f %f %f ", // Read floats from the line: v X Y Z
                &vertexBuffer[TotalConnectedPoints],
                &vertexBuffer[TotalConnectedPoints + 1],
                &vertexBuffer[TotalConnectedPoints + 2]);

                TotalConnectedPoints +=
                POINTS_PER_VERTEX; // Add 3 to the total connected points
            }
            if (line.c_str ()[0] == 'f') // geometry: face
            {
                line[0] = ' '; // Set first character to 0. This will allow us
                               // to use sscanf


                unsigned int vertexIndex[4]  = { 0 };
                unsigned int textureIndex[4] = { 0 };
                unsigned int normalIndex[4]  = { 0 };
                int matches;
                matches = sscanf (line.c_str (),
                "%i%i%i", // Read integers from the line:  f x y z
                &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
                if (matches != POINTS_PER_VERTEX) { // other format
                    matches =
                    sscanf (line.c_str (), "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &textureIndex[0], &normalIndex[0],
                    &vertexIndex[1], &textureIndex[1], &normalIndex[1],
                    &vertexIndex[2], &textureIndex[2], &normalIndex[2]);
                    if (matches != POINTS_PER_VERTEX * 3) { // other format
                        matches =
                        sscanf (line.c_str (), "%d//%d %d//%d %d//%d\n",
                        &vertexIndex[0], &normalIndex[0], &vertexIndex[1],
                        &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                        if (matches != POINTS_PER_VERTEX * 2) {
                            matches = sscanf (line.c_str (), "%d %d %d %d\n",
                            &vertexIndex[0], &vertexIndex[1], &vertexIndex[2],
                            &vertexIndex[3]);
                            if (matches != POINTS_PER_VERTEX * 4) {
                                status = false;
                            }
                        }
                    }
                }

                vertexIndex[0] -= 1; // OBJ file starts counting from 1
                vertexIndex[1] -= 1; // OBJ file starts counting from 1
                vertexIndex[2] -= 1; // OBJ file starts counting from 1


                /********************************************************************
                 * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y
                 * Z)
                 * (v X Y Z).
                 * The vertexBuffer contains all verteces
                 * The triangles will be created using the verteces we read
                 * previously
                 */

                int tCounter = 0;
                for (int i = 0; i < POINTS_PER_VERTEX; i++) {
                    Faces_Triangles[triangle_index + tCounter] =
                    vertexBuffer[3 * vertexIndex[i]];
                    Faces_Triangles[triangle_index + tCounter + 1] =
                    vertexBuffer[3 * vertexIndex[i] + 1];
                    Faces_Triangles[triangle_index + tCounter + 2] =
                    vertexBuffer[3 * vertexIndex[i] + 2];
                    tCounter += POINTS_PER_VERTEX;
                }

                /*********************************************************************
                 * Calculate all normals, used for lighting
                 */
                float coord1[3] = { Faces_Triangles[triangle_index],
                    Faces_Triangles[triangle_index + 1],
                    Faces_Triangles[triangle_index + 2] };
                float coord2[3] = { Faces_Triangles[triangle_index + 3],
                    Faces_Triangles[triangle_index + 4],
                    Faces_Triangles[triangle_index + 5] };
                float coord3[3] = { Faces_Triangles[triangle_index + 6],
                    Faces_Triangles[triangle_index + 7],
                    Faces_Triangles[triangle_index + 8] };
                float norm[3];
                calculate_normal (norm, coord1, coord2, coord3);

                tCounter = 0;
                for (int i = 0; i < POINTS_PER_VERTEX; i++) {
                    normals[normal_index + tCounter]     = norm[0];
                    normals[normal_index + tCounter + 1] = norm[1];
                    normals[normal_index + tCounter + 2] = norm[2];
                    tCounter += POINTS_PER_VERTEX;
                }

                triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
                normal_index += TOTAL_FLOATS_IN_TRIANGLE;
                TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;
            }
        }
        objFile.close (); // Close OBJ file
    } else {
        status = false;
    }

    calculate_scale ();

    return status;
}

void model_obj::release () {
    _is_loaded = false;
    free (Faces_Triangles);
    free (normals);
    free (vertexBuffer);
}

void model_obj::draw () {
    glEnableClientState (GL_VERTEX_ARRAY); // Enable vertex arrays
    glEnableClientState (GL_NORMAL_ARRAY); // Enable normal arrays
    glVertexPointer (
    3, GL_FLOAT, 0, Faces_Triangles);       // Vertex Pointer to triangle array
    glNormalPointer (GL_FLOAT, 0, normals); // Normal pointer to normal array
    glScalef (
    _scale_factor, _scale_factor, _scale_factor); // scale to fit in screen
    glDrawArrays (
    GL_TRIANGLES, 0, TotalConnectedTriangles); // Draw the triangles
    glDisableClientState (GL_VERTEX_ARRAY);    // Disable vertex arrays
    glDisableClientState (GL_NORMAL_ARRAY);    // Disable normal arrays
}
