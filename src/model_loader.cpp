#include "model_loader.hpp"

#ifdef OPENGL_ES
#include <GLES/gl.h>
#else
#include <GL/gl.h>
#endif // OPENGL_ES

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
#include <vector>

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

model_obj::model_obj ()
: _is_loaded (false)
, _scale_factor (1.0f)
, _current_rgba{ 1, 1, 1, 1 } {
}

void model_obj::release () {
    _is_loaded = false;
    _faces.clear ();
    _normals.clear ();
    _colors.clear ();
    _current_rgba = { 1, 1, 1, 1 };
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
    // ensure that every vertex fits into range -1 to 1
    float max_val = 0.0f;
    for (float val : _vertices) {
        float abs_val = std::fabs (val);
        if (max_val < abs_val) {
            max_val = abs_val;
        }
    }
    _scale_factor = (1 / max_val);
}

void model_obj::draw () {
    if (_is_loaded) {
        GLsizei face_count = _faces.size () / 3; // 3 points per face

        glEnableClientState (GL_VERTEX_ARRAY); // Enable vertex arrays
        glEnableClientState (GL_NORMAL_ARRAY); // Enable normal arrays
        glEnableClientState (GL_COLOR_ARRAY);  // Enable color arrays

        glScalef (_scale_factor, _scale_factor, _scale_factor);

        glVertexPointer (3, GL_FLOAT, 0, _faces.data ());
        glNormalPointer (GL_FLOAT, 0, _normals.data ());
        glColorPointer (4, GL_FLOAT, 0, _colors.data ());
        glDrawArrays (GL_TRIANGLES, 0, face_count);

        glDisableClientState (GL_VERTEX_ARRAY); // Disable vertex arrays
        glDisableClientState (GL_NORMAL_ARRAY); // Disable normal arrays
        glDisableClientState (GL_COLOR_ARRAY);  // Disable color arrays
    }
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
        while ((!objFile.eof ()) && status) {
            getline (objFile, line);
            if (!line.empty ()) {
                status = parse_line (line);
            }
        }
        objFile.close (); // Close OBJ file
    } else {
        status = false;
    }


    if (status == true) {
        calculate_scale ();
        _is_loaded = true;
    }

    return status;
}

bool model_obj::parse_line (std::string line) {
    bool status = true;

    size_t split_pos    = line.find (' ');
    std::string keyword = line.substr (0, split_pos);
    std::string value   = line.substr (split_pos);

    if (keyword == "#" || keyword.empty ()) {
        ; // comment line, ignore
    } else if (keyword == "v") {
        status = parse_vertex (value);
    } else if (keyword == "f") {
        status = parse_face (value);
    } else if (keyword == "usemtl") {
        status = parse_usemtl (value); // should be usemtl
    } else {
        if (_unknown_options.find (keyword) == _unknown_options.end ()) {
            std::cout << "unsupporterd keyword: " << keyword << std::endl;
            _unknown_options.insert (keyword);
        }
    }
    return status;
}

bool model_obj::parse_vertex (std::string value) {
    bool status = true; // TODO: check status
    float x, y, z;

    int matches = sscanf (value.c_str (), " %f %f %f", &x, &y, &z);
    if (matches == 3) {
        _vertices.push_back (x);
        _vertices.push_back (y);
        _vertices.push_back (z);
    } else {
        status = false;
    }
    return status;
}

bool model_obj::parse_face (std::string value) {
    bool status  = true;
    bool is_quad = false;
    int v[4]     = { 0 }; // vertex indices
    int t[4]     = { 0 }; // texture point indices
    int n[4]     = { 0 }; // normal indices
    int matches;

    matches = sscanf (value.c_str (), "%d %d %d %d\n", &v[0], &v[1], &v[2], &v[3]);
    if (matches == 4) {
        is_quad = true;
    } else {
        matches = sscanf (value.c_str (), "%d %d %d", &v[0], &v[1], &v[2]);

        if (matches != 3) { // other format
            matches = sscanf (value.c_str (), "%d//%d %d//%d %d//%d\n", &v[0],
            &n[0], &v[1], &n[1], &v[2], &n[2]);

            if (matches != 6) {
                matches =
                sscanf (value.c_str (), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v[0],
                &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]);

                if (matches != 9) { // unsupported format
                    status = false;
                }
            }
        }
    }

    // OBJ file starts counting from 1, and every vertex consists of 3 floats
    v[0] = (v[0] - 1) * 3;
    v[1] = (v[1] - 1) * 3;
    v[2] = (v[2] - 1) * 3;
    v[3] = (v[3] - 1) * 3;
    t[0] = (t[0] - 1) * 3;
    t[1] = (t[1] - 1) * 3;
    t[2] = (t[2] - 1) * 3;
    t[3] = (t[3] - 1) * 3;
    n[0] = (n[0] - 1) * 3;
    n[1] = (n[1] - 1) * 3;
    n[2] = (n[2] - 1) * 3;
    n[3] = (n[3] - 1) * 3;

    float coord_a[3], coord_b[3], coord_c[3], coord_d[3];
    coord_a[0] = _vertices[v[0]];
    coord_a[1] = _vertices[v[0] + 1];
    coord_a[2] = _vertices[v[0] + 2];
    coord_b[0] = _vertices[v[1]];
    coord_b[1] = _vertices[v[1] + 1];
    coord_b[2] = _vertices[v[1] + 2];
    coord_c[0] = _vertices[v[2]];
    coord_c[1] = _vertices[v[2] + 1];
    coord_c[2] = _vertices[v[2] + 2];
    if (is_quad) {
        coord_d[0] = _vertices[v[3]];
        coord_d[1] = _vertices[v[3] + 1];
        coord_d[2] = _vertices[v[3] + 2];
    }
    /********************************************************************
     * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y
     * Z)
     * (v X Y Z).
     * The vertexBuffer contains all verteces
     * The triangles will be created using the verteces we read
     * previously
     */

    if (is_quad) { // its a quad with vertices abcd
        // first triangle with points abc
        _faces.push_back (coord_a[0]);
        _faces.push_back (coord_a[1]);
        _faces.push_back (coord_a[2]);
        _faces.push_back (coord_b[0]);
        _faces.push_back (coord_b[1]);
        _faces.push_back (coord_b[2]);
        _faces.push_back (coord_c[0]);
        _faces.push_back (coord_c[1]);
        _faces.push_back (coord_c[2]);
        // second triangle with vertices acd
        _faces.push_back (coord_a[0]);
        _faces.push_back (coord_a[1]);
        _faces.push_back (coord_a[2]);
        _faces.push_back (coord_c[0]);
        _faces.push_back (coord_c[1]);
        _faces.push_back (coord_c[2]);
        _faces.push_back (coord_d[0]);
        _faces.push_back (coord_d[1]);
        _faces.push_back (coord_d[2]);

    } else { // its a triangle with vertices abc
        _faces.push_back (coord_a[0]);
        _faces.push_back (coord_a[1]);
        _faces.push_back (coord_a[2]);
        _faces.push_back (coord_b[0]);
        _faces.push_back (coord_b[1]);
        _faces.push_back (coord_b[2]);
        _faces.push_back (coord_c[0]);
        _faces.push_back (coord_c[1]);
        _faces.push_back (coord_c[2]);
    }

    /*********************************************************************
     * Calculate all normals, used for lighting
     */
    float norm[3];
    if (is_quad) {
        calculate_normal (norm, coord_a, coord_b, coord_c);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        calculate_normal (norm, coord_a, coord_c, coord_d);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
    } else {
        calculate_normal (norm, coord_a, coord_b, coord_c);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
        _normals.push_back (norm[0]);
        _normals.push_back (norm[1]);
        _normals.push_back (norm[2]);
    }

    // add colors for each vertex

    if (is_quad) {
        // color for triangle 1
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        // color for triangle 2
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
    } else { // color for triangle
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
        _colors.insert (std::end (_colors), std::begin (_current_rgba),
        std::end (_current_rgba));
    }

    return status;
}

bool model_obj::parse_usemtl (std::string value) {
    bool status = true; // TODO: check status

    std::string mat = value.substr (value.find (" ")); // get from space
    mat             = trim_str (mat);

    if (mat == "black") { // shuttle materials
        _current_rgba = { 0.0, 0.0, 0.0, 1.0 };
    } else if (mat == "glass") {
        _current_rgba = { 0.5, 0.65, 0.75, 1.0 };
    } else if (mat == "bone") {
        _current_rgba = { 0.75, 0.75, 0.65, 1.0 };
    } else if (mat == "brass") {
        _current_rgba = { 0.45, 0.35, 0.12, 1.0 };
    } else if (mat == "dkdkgrey") {
        _current_rgba = { 0.30, 0.35, 0.35, 1.0 };
    } else if (mat == "fldkdkgrey") {
        _current_rgba = { 0.30, 0.35, 0.35, 1.0 };
    } else if (mat == "redbrick") {
        _current_rgba = { 0.61, 0.16, 0.0, 1.0 };
    } else if (mat == "Mat_1_-1") { // articated materials
        _current_rgba = { 0.0, 0.0, 1.0, 1.0 };
    } else if (mat == "Mat_2_-1") {
        _current_rgba = { 0.2, 1.0, 1.0, 0.4 };
    } else if (mat == "Mat_3_-1") {
        _current_rgba = { 1.0, 0.0, 0.0, 1.0 };
    } else if (mat == "Mat_4_-1") {
        _current_rgba = { 0.0, 1.0, 0.0, 1.0 };
    } else if (mat == "red") { // general collors
        _current_rgba = { 1.0, 0.0, 0.0, 1.0 };
    } else if (mat == "green") {
        _current_rgba = { 0.0, 1.0, 0.0, 1.0 };
    } else if (mat == "blue") {
        _current_rgba = { 0.0, 0.0, 1.0, 1.0 };
    } else if (mat == "cyan") {
        _current_rgba = { 0.0, 1.0, 1.0, 1.0 };
    } else if (mat == "yellow") {
        _current_rgba = { 1.0, 1.0, 0.0, 1.0 };
    } else {
        // default to dark purple
        _current_rgba = { 0.2, 0, 0.2, 1 };

        if (_unknown_options.find (mat) == _unknown_options.end ()) {
            std::cout << "unknown material: " << mat << std::endl;
            _unknown_options.insert (mat);
        }
    }
    return status;
}

inline std::string model_obj::trim_str (const std::string& s) {
    auto wsfront = std::find_if_not (
    s.begin (), s.end (), [](int c) { return std::isspace (c); });
    auto wsback = std::find_if_not (s.rbegin (), s.rend (), [](int c) {
        return std::isspace (c);
    }).base ();
    return (wsback <= wsfront ? std::string () : std::string (wsfront, wsback));
}
