#ifndef MODEL_OBJ_HPP
#define MODEL_OBJ_HPP

class model_obj {
    public:
    model_obj ();
    bool load (const char* filename); // Loads the model
    void draw ();                     // Draws the model on the screen
    void release ();                  // Release the model

    private:
    void calculate_normal (float* norm, float* coord1, float* coord2, float* coord3);
    void calculate_scale ();

    bool _is_loaded;
    float _scale_factor;
    float* normals;            // Stores the normals
    float* Faces_Triangles;    // Stores the triangles
    float* vertexBuffer;       // Stores the points which make the object
    long TotalConnectedPoints; // Stores the total number of connected verteces
    long TotalConnectedTriangles; // Stores the total number of connected
                                  // triangles
};

#endif // MODEL_OBJ_HPP
