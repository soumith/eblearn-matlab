/***************************************************************************
 *   Copyright (C) 2011 by Soumith Chintala
 *   soumith@gmail.com
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Redistribution under a license not approved by the Open Source
 *       Initiative (http://www.opensource.org) must display the
 *       following acknowledgement in all advertising material:
 *        This product includes software developed at the Courant
 *        Institute of Mathematical Sciences (http://cims.nyu.edu).
 *     * The names of the authors may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ThE AUTHORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***************************************************************************/

#ifndef EBL_MATWRAPPER
#define EBL_MATWRAPPER_HPP

namespace ebl {

  template <typename T>
  idx<T> matlab::load_matrix(char *name) {
#ifdef __MATLAB__
    mat = Mat_Open(filename,MAT_ACC_RDONLY);
    if (mat == NULL) eblthrow("null file pointer");  
    // get variable corresponding to name
    matvar_t *matvar = Mat_VarRead(mat, name);
    if (matvar == NULL)
      eblthrow("variable \"" << name << "\" not found in matlab object");
    int ndims = matvar->rank;
    if (ndims > MAXDIMS)
      eblthrow("cannot load matrix with " << ndims 
	       << " dimensions, libidx was compiled to support " << MAXDIMS 
	       << " at most. Modify MAXDIMS and recompile.");
    int *dims = matvar->dims;
    // allocate matrix
    idxdim d;
    intg nelements = 1;
    for (uint i = 0; i < ndims; ++i)
      d.insert_dim(i, dims[ndims-i-1]);
    idx<T> m(d);
    // load data
    int type = matvar->class_type;
    switch (type) {
    case MAT_C_CELL: eblthrow("cannot load matrix from type cell"); break ;
    case MAT_C_STRUCT: eblthrow("cannot load matrix from type struct"); break ;
    case MAT_C_OBJECT: eblthrow("cannot load matrix from type object"); break ;
    case MAT_C_FUNCTION: eblthrow("cannot load matrix from type function"); break ;
    case MAT_C_INT8:
    case MAT_C_UINT8:
    case MAT_C_CHAR: read_cast_matrix<ubyte>(matvar, m); break ;
    case MAT_C_INT16: read_cast_matrix<int16>(matvar, m); break ;
    case MAT_C_UINT16: read_cast_matrix<uint16>(matvar, m); break ;
    case MAT_C_INT32: read_cast_matrix<uint32>(matvar, m); break ;
    case MAT_C_UINT32: read_cast_matrix<uint32>(matvar, m); break ;
    case MAT_C_INT64: read_cast_matrix<int64_t>(matvar, m); break ;
    case MAT_C_UINT64: read_cast_matrix<uint64_t>(matvar, m); break ;
    case MAT_C_SINGLE: read_cast_matrix<float>(matvar, m); break ;
    case MAT_C_DOUBLE: read_cast_matrix<double>(matvar, m); break ;
    }
    // delete array
    if (matvar) Mat_VarFree(matvar);
    Mat_Close(mat);
#else
    idx<T> m;
#endif
    return m;
  }

  template <typename Tmatlab, typename T>
  void matlab::read_cast_matrix(matvar_t *var, idx<T> &m) {
#ifdef __MATLAB__
    // allocate a temporary matrix with same type as original matrix type
    idx<Tmatlab> tmp(m.get_idxdim());
    // copy to idx 
    memcpy(tmp.idx_ptr(), (Tmatlab*) var->data, m.nelements() * sizeof (Tmatlab));
    // copy-cast
    idx_copy(tmp, m);
    //transpose for dimension correction
    int num_dims = m.order();
    if(num_dims>1) {
	    int *transpose_p = (int*)malloc(sizeof(int) * num_dims); 
	    for(int i=0;i<num_dims;i++)
		transpose_p[i]=num_dims-i-1;
	    m = m.transpose(transpose_p);
    }
#endif
  }

} // namespace ebl

#endif /* MATLAB_HPP_ */
