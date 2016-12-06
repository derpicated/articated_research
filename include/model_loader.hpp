#ifndef MODEL_OBJ_HPP
#define MODEL_OBJ_HPP

class model_obj {
    public:
    model_obj ();
    void calculateNormal (float* norm, float* coord1, float* coord2, float* coord3);
    bool Load (const char* filename); // Loads the model
    void Draw ();                     // Draws the model on the screen
    void Release ();                  // Release the model

    private:
    void calculate_scale ();
    float _scale_factor;
    float* normals;            // Stores the normals
    float* Faces_Triangles;    // Stores the triangles
    float* vertexBuffer;       // Stores the points which make the object
    long TotalConnectedPoints; // Stores the total number of connected verteces
    long TotalConnectedTriangles; // Stores the total number of connected
                                  // triangles
};

#endif // MODEL_OBJ_HPP
