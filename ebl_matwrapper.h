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

#ifndef EBL_MATWRAPPER_H
#define EBL_MATWRAPPER_H

#include <eblearn/idx.h>
#include <eblearn/idxIO.h>

#define __MATLAB__

#ifdef __MATLAB__

// TODO: temporary dependency
#include <matio.h> // libmatio-dev

#endif

namespace ebl {
  
  //! A class to directly import Matlab variables from Matlab .mat files into idx tensors
  class matlab {
  public:
    //! Constructs a matlab object by loading all headers but does not actually load the data.
    //! \param filename name of the .mat (matlab format) file to be read.
    matlab(const char *filename);
    //! Close file handle.
    virtual ~matlab();
    //! Loads data of element with name 'name' and returns a matrix of type T
    template <typename T> idx<T> load_matrix(char *name);
  protected:
    //! Load and cast data from matlab 'var' with type 'Tmatlab' into 'm' with type 'T'.
    template <typename Tmatlab, typename T>
    void read_cast_matrix(matvar_t *var, idx<T> &m);
    const char* filename; //!< Loaded filename.
    mat_t *mat; //!< pointer to the opened mat.
  };  
  
}

#include "ebl_matwrapper.hpp"

#endif // MATLAB_H
