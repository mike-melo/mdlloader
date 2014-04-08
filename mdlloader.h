#ifndef __mdlloader_h_
#define __mdlloader_h_

#define ML_INITIAL_NUM_OF_VERTICES  10

typedef struct MLVertex {
 double x;
 double y;
 double z;
 double w;
}MLVertex;

typedef struct MLModel {
 MLVertex **vertices;
 unsigned int numberOfVertices;
}MLModel;

MLModel *mlLoadObjFile(const char *objFileName);
void mlUnloadModel(MLModel *mlModel);

#endif
