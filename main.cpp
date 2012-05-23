// EXAMPLE USAGE

#include <iostream>
#include "ebl_matwrapper.h"
#include <eblearn/libidx.h>
#include <matio.h>

int main(int argc, char **argv) {
    
    const char *matFileName = "testMATLAB.mat";
    const char* varName = "var_a";
     ebl::matlab matWrapper(matFileName);
     ebl::idx<double> varToGet=matWrapper.load_matrix<double>(varName);
     for(int i=0;i<10;i++) {
	for(int j=0;j<10;j++) {
	     cout<<varToGet.get(i,j)<<" ";
	}
	cout<<endl;
}
cout<<"Tensor dimensions"<<varToGet.order()<<endl;
     int err = 0;
     mat_t *mat;
     matvar_t *matvar;
cout<<"------------------------------------------"<<endl;
     mat = Mat_Open(matFileName,MAT_ACC_RDONLY);
     if ( mat ) {
         matvar = Mat_VarRead(mat,varName);
         if ( matvar == NULL ) {
             err = 1;
 	    cout<<"no var"<<endl;
         } else {
		for ( int i = 0; i  <10 ; i++ ) {
     for ( int j = 0; j <10; j++ ) {
             printf("%f ", ((double*)matvar->data)[matvar->dims[0]*j+i]);
}
                 printf("\n");
 }

             Mat_VarFree(matvar);
         }
         Mat_Close(mat);
     } else {
         err = 1;
     }


    
    return 0;
}
