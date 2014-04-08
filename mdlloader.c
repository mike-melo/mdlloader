#include <stdio.h>
#include <stdlib.h>
#include "mdlloader.h"

MLModel *mlLoadObjFile(const char *objFileName) {
 FILE *stream;
 char line[256];
 MLVertex *mlVertex;
 MLModel *mlModel;
 unsigned int newSize = ML_INITIAL_NUM_OF_VERTICES;

 stream = fopen(objFileName, "r");
 
 if(stream == NULL) {
  return NULL;
 }
 
 mlModel = (MLModel *)calloc(1, sizeof(MLModel));
 mlModel->vertices = (MLVertex **)malloc(sizeof(MLVertex *) * newSize);
 
 do {
  if(line[0] == 'v' && line[1] == ' ') {
   mlVertex = (MLVertex *)calloc(1, sizeof(MLVertex));
   sscanf(line, "v %lf %lf %lf", &mlVertex->x, &mlVertex->y, &mlVertex->z);
   mlVertex->w = 1;
   mlModel->vertices[mlModel->numberOfVertices] = mlVertex;
   mlModel->numberOfVertices++;
   if(mlModel->numberOfVertices == newSize) {
    newSize += ML_INITIAL_NUM_OF_VERTICES;
    mlModel->vertices = (MLVertex **)realloc(mlModel->vertices, sizeof(MLVertex *) * newSize);
   }
  }   
 } while(fgets(line, 256, stream) != NULL);
 
 fclose(stream);
 
 return mlModel;
}

void mlUnloadModel(MLModel *mlModel) {
     free(mlModel->vertices);
     free(mlModel);
}

int main(int argc, char *argv[]) {
 MLModel *mlModel = mlLoadObjFile("simple.obj");
 unsigned int i = 0;
 
 for(i=0; i<mlModel->numberOfVertices; i++) {
   printf("x=%lf y=%lf z=%lf, w=%lf\n", mlModel->vertices[i]->x, mlModel->vertices[i]->y, mlModel->vertices[i]->z, mlModel->vertices[i]->w);
 }
 mlUnloadModel(mlModel);
 system("pause");
}
