#include <Matrix.h>

float array1[4][4] = {{16,19,2,7},{5,34,77,1},{23,37,38,7},{9,33,10,0}};
float array2[4][1] = {{5},{6},{7},{8}};
//create float type matrices
Matrix<float> A(4,4,(float*)array1);
Matrix<float> B(4,1,(float*)array2);

void setup() {
    Serial.begin(115200);

    Matrix<float> C = A*B;
    Matrix<float> D(4,4,'I');  //create identity matrix
    Serial.println("C: ");
    C.show();
    Serial.println("A transpose: ");
    Matrix<float>::transpose(A).show(4);
    Serial.println("A inverse: ");
    Matrix<float>::inv(A).show(4);
    Serial.println("D: ");
    D.show();
}

void loop() {

}
