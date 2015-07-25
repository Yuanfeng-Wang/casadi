/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


/** \brief This file is included from sparsity_interface.hpp and used for SWIG wrapping
    \author Joel Andersson
    \date 2015
*/

/** \brief Concatenate a list of matrices horizontally
 * Alternative terminology: horizontal stack, hstack, horizontal append, [a b]
 *
 *   horzcat(horzsplit(x, ...)) = x
 */
inline SWIG_FRIEND MatType horzcat(const std::vector<MatType> &v) {
  return MatType::zz_horzcat(v);
}

#ifndef SWIG

/** \brief Concatenate horizontally, two matrices */
inline SWIG_FRIEND MatType horzcat(const MatType &x, const MatType &y) {
  MatType v[] = {x, y};
  return horzcat(std::vector<MatType>(v, v+2));
}

/** \brief Concatenate horizontally, three matrices */
inline SWIG_FRIEND MatType horzcat(const MatType &x, const MatType &y, const MatType &z) {
  MatType v[] = {x, y, z};
  return horzcat(std::vector<MatType>(v, v+3));
}

/** \brief Concatenate horizontally, four matrices */
inline SWIG_FRIEND MatType horzcat(const MatType &x, const MatType &y, const MatType &z,
                              const MatType &w) {
  MatType v[] = {x, y, z, w};
  return horzcat(std::vector<MatType>(v, v+4));
}

#endif // SWIG

/** \brief Concatenate a list of matrices vertically
 * Alternative terminology: vertical stack, vstack, vertical append, [a;b]
 *
 *   vertcat(vertsplit(x, ...)) = x
 */
inline SWIG_FRIEND MatType vertcat(const std::vector<MatType> &v) {
  return MatType::zz_vertcat(v);
}

#ifndef SWIG

/** \brief Concatenate vertically, two matrices */
inline SWIG_FRIEND MatType vertcat(const MatType &x, const MatType &y) {
  MatType v[] = {x, y};
  return vertcat(std::vector<MatType>(v, v+2));
}

/** \brief Concatenate vertically, three matrices */
inline SWIG_FRIEND MatType vertcat(const MatType &x, const MatType &y, const MatType &z) {
  MatType v[] = {x, y, z};
  return vertcat(std::vector<MatType>(v, v+3));
}

/** \brief Concatenate vertically, four matrices */
inline SWIG_FRIEND MatType vertcat(const MatType &x, const MatType &y, const MatType &z,
                              const MatType &w) {
  MatType v[] = {x, y, z, w};
  return vertcat(std::vector<MatType>(v, v+4));
}

#endif // SWIG

/** \brief  split horizontally, retaining groups of columns
 * \param offset List of all start columns for each group
 *      the last column group will run to the end.
 *
 *   horzcat(horzsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector<MatType > horzsplit(const MatType &v,
                                              const std::vector<int>& offset) {
  return v.zz_horzsplit(offset);
}

/** \brief  split horizontally, retaining fixed-sized groups of columns
 * \param incr Size of each group of columns
 *
 *   horzcat(horzsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector<MatType > horzsplit(const MatType &v, int incr=1) {
  casadi_assert(incr>=1);
  int sz2 = static_cast<const MatType&>(v).size2();
  std::vector<int> offset2 = range(0, sz2, incr);
  offset2.push_back(sz2);
  return horzsplit(v, offset2);
}

/** \brief  split vertically, retaining groups of rows
 * \param output_offset List of all start rows for each group
 *      the last row group will run to the end.
 *
 *   vertcat(vertsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector<MatType > vertsplit(const MatType &v,
                                              const std::vector<int>& offset) {
  return v.zz_vertsplit(offset);
}

/** \brief Helper function, get offsets corresponding to a vector of matrices
 */
inline SWIG_FRIEND std::vector<int > offset(const std::vector<MatType> &v, bool vert=true) {
  return MatType::zz_offset(v, vert);
}

/** \brief  split vertically, retaining fixed-sized groups of rows
 * \param incr Size of each group of rows
 *
 *   vertcat(vertsplit(x, ...)) = x
     
 \doctest
 print vertsplit(SX.sym("a",4))
 \doctestout
 [SX(a_0), SX(a_1), SX(a_2), SX(a_3)]
 \enddoctest
     
 \doctest
 print vertsplit(SX.sym("a",4),2)
 \doctestout
 [SX([a_0, a_1]), SX([a_2, a_3])]
 \enddoctest
     
 If the number of rows is not a multiple of \p incr,
 the last entry returned will have a size smaller than \p incr.
     
 \doctest
 print vertsplit(DMatrix([0,1,2,3,4]),2)
 \doctestout
 [DMatrix([0, 1]), DMatrix([2, 3]), DMatrix(4)]
 \enddoctest
 *
 */
inline SWIG_FRIEND std::vector<MatType > vertsplit(const MatType &v, int incr=1) {
  casadi_assert(incr>=1);
  int sz1 = static_cast<const MatType&>(v).size1();
  std::vector<int> offset1 = range(0, sz1, incr);
  offset1.push_back(sz1);
  return vertsplit(v, offset1);
}

/** \brief Construct a matrix from a list of list of blocks.
 */
inline SWIG_FRIEND MatType blockcat(const std::vector< std::vector<MatType > > &v) {
  return MatType::zz_blockcat(v);
}

/** \brief Construct a matrix from 4 blocks
 */
inline SWIG_FRIEND MatType blockcat(const MatType &A, const MatType &B,
                               const MatType &C, const MatType &D) {
  return vertcat(horzcat(A, B), horzcat(C, D));
}

/** \brief  chop up into blocks
 * \param vert_offset Defines the boundaries of the block rows
 * \param horz_offset Defines the boundaries of the block columns
 *
 *   blockcat(blocksplit(x,..., ...)) = x
 */
inline SWIG_FRIEND
std::vector< std::vector< MatType > > blocksplit(const MatType& x,
                                                 const std::vector<int>& vert_offset,
                                                 const std::vector<int>& horz_offset) {
  return x.zz_blocksplit(vert_offset, horz_offset);
}

/** \brief  chop up into blocks
 * \param vert_incr Defines the increment for block boundaries in row dimension
 * \param horz_incr Defines the increment for block boundaries in column dimension
 *
 *   blockcat(blocksplit(x,..., ...)) = x
 */
inline SWIG_FRIEND std::vector< std::vector< MatType > >
blocksplit(const MatType& x, int vert_incr=1, int horz_incr=1) {
  casadi_assert(horz_incr>=1);
  casadi_assert(vert_incr>=1);
  int sz1 = static_cast<const MatType&>(x).size1();
  std::vector<int> offset1 = range(0, sz1, vert_incr);
  offset1.push_back(sz1);
  int sz2 = static_cast<const MatType&>(x).size2();
  std::vector<int> offset2 = range(0, sz2, horz_incr);
  offset2.push_back(sz2);
  return blocksplit(x, offset1, offset2);
}

/** \brief Construct a matrix with given block on the diagonal */
inline SWIG_FRIEND MatType diagcat(const std::vector<MatType> &A) {
  return MatType::zz_diagcat(A);
}

#ifndef SWIG

/** \brief Concatenate along diagonal, two matrices */
inline SWIG_FRIEND MatType diagcat(const MatType &x, const MatType &y) {
  MatType v[] = {x, y};
  return diagcat(std::vector<MatType>(v, v+2));
}

/** \brief Concatenate along diagonal, three matrices */
inline SWIG_FRIEND MatType diagcat(const MatType &x, const MatType &y, const MatType &z) {
  MatType v[] = {x, y, z};
  return diagcat(std::vector<MatType>(v, v+3));
}

/** \brief Concatenate along diagonal, four matrices */
inline SWIG_FRIEND MatType diagcat(const MatType &x, const MatType &y, const MatType &z,
                              const MatType &w) {
  MatType v[] = {x, y, z, w};
  return diagcat(std::vector<MatType>(v, v+4));
}

#endif // SWIG

/** \brief  split diagonally, retaining square matrices
 * \param output_offset1 List of all start locations (row) for each group
 *      the last matrix will run to the end.
 * \param output_offset2 List of all start locations (row) for each group
 *      the last matrix will run to the end.
 *
 *   diagcat(diagsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector< MatType > diagsplit(const MatType& x,
                                               const std::vector<int>& output_offset1,
                                               const std::vector<int>& output_offset2) {
  return x.zz_diagsplit(output_offset1, output_offset2);
}

/** \brief  split diagonally, retaining square matrices
 * \param output_offset List of all start locations for each group
 *      the last matrix will run to the end.
 *
 *   diagcat(diagsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector< MatType > diagsplit(const MatType& x,
                                               const std::vector<int>& output_offset) {
  casadi_assert_message(x.issquare(), "diagsplit(x,incr)::input must be square but got "
                        << x.dimString()  << ".");
  return diagsplit(x, output_offset, output_offset);
}

/** \brief  split diagonally, retaining groups of square matrices
 * \param incr Size of each matrix
 *
 *  diagsplit(diagsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector< MatType > diagsplit(const MatType& x, int incr=1) {
  casadi_assert(incr>=1);
  casadi_assert_message(x.issquare(), "diagsplit(x,incr)::input must be square but got "
                        << x.dimString()  << ".");
  std::vector<int> offset2 = range(0, x.size2(), incr);
  offset2.push_back(x.size2());
  return diagsplit(x, offset2);
}

/** \brief  split diagonally, retaining fixed-sized matrices
 * \param incr1 Row dimension of each matrix
 * \param incr2 Column dimension of each matrix
 *
 *  diagsplit(diagsplit(x, ...)) = x
 */
inline SWIG_FRIEND std::vector< MatType > diagsplit(const MatType& x, int incr1, int incr2) {
  casadi_assert(incr1>=1);
  casadi_assert(incr2>=1);
  std::vector<int> offset1 = range(0, x.size1(), incr1);
  offset1.push_back(x.size1());
  std::vector<int> offset2 = range(0, x.size2(), incr2);
  offset2.push_back(x.size2());
  return diagsplit(x, offset1, offset2);
}

/** \brief  concatenate vertically while vectorizing all arguments with vec */
inline SWIG_FRIEND MatType veccat(const std::vector< MatType >& x) {
  return MatType::zz_veccat(x);
}

/** \brief Matrix product of two matrices:  */
inline SWIG_FRIEND MatType mul(const MatType &X, const MatType &Y) {
  return X.zz_mtimes(Y);
}

/** \brief Matrix product and addition
    Matrix product of two matrices (X and Y), adding the result to
    a third matrix Z. The result has the same sparsity pattern as
    C meaning that other entries of (X*Y) are ignored.
    The operation is equivalent to: Z+mul(X,Y).project(Z.sparsity()).
*/
inline SWIG_FRIEND MatType mul(const MatType &X, const MatType &Y, const MatType &Z) {
  return X.zz_mtimes(Y, Z);
}

/** \brief Matrix product of n matrices */
inline SWIG_FRIEND MatType mul(const std::vector<MatType> &args) {
  casadi_assert_message(args.size()>=1,
                        "mul(std::vector<MatType> &args): "
                        "supplied list must not be empty.");
  MatType ret = args[0];
  for (int i=1; i<args.size(); ++i) ret = mul(ret, args[i]);
  return ret;
}

/** \brief Transpose */
inline SWIG_FRIEND MatType transpose(const MatType& X) {
  return X.T();
}

/** \brief  make a vector
    Reshapes/vectorizes the matrix such that the shape becomes (expr.numel(), 1).
    Columns are stacked on top of each other.
    Same as reshape(expr, expr.numel(), 1)

    a c \n
    b d \n

    turns into

    a \n
    b \n
    c \n
    d \n

*/
inline SWIG_FRIEND MatType vec(const MatType& a) { return a.zz_vec();}

/** \brief Returns a flattened version of the matrix, preserving only nonzeros
 */
inline SWIG_FRIEND MatType vecNZ(const MatType& a) { return a.zz_vecNZ();}

//! \brief Returns a reshaped version of the matrix
inline SWIG_FRIEND MatType reshape(const MatType& a, int nrow, int ncol) {
  return a.zz_reshape(nrow, ncol);
}

//! \brief Returns a reshaped version of the matrix, dimensions as a vector
inline SWIG_FRIEND MatType reshape(const MatType& a, std::pair<int, int> rc) {
  return reshape(a, rc.first, rc.second);
}

//! \brief Reshape the matrix
inline SWIG_FRIEND MatType reshape(const MatType& a, const Sparsity& sp) {
  return a.zz_reshape(sp);
}

/// Obtain the structural rank of a sparsity-pattern
inline SWIG_FRIEND int sprank(const MatType& A) {
  return A.zz_sprank();
}

/** 0-norm (nonzero count) of a Matrix-matrix product,*/
inline SWIG_FRIEND int norm_0_mul(const MatType &x, const MatType &y) {
  return x.zz_norm_0_mul(y);
}

/** \brief Get the upper triangular part of a matrix
 */
inline SWIG_FRIEND MatType triu(const MatType& a, bool includeDiagonal=true) {
  return a.zz_triu(includeDiagonal);
}

/** \brief Get the lower triangular part of a matrix
 */
inline SWIG_FRIEND MatType tril(const MatType& a, bool includeDiagonal=true) {
  return a.zz_tril(includeDiagonal);
}

/** \brief Kronecker tensor product
 *
 * Creates a block matrix in which each element (i, j) is a_ij*b
 */
inline SWIG_FRIEND MatType kron(const MatType& a, const MatType& b) {
  return a.zz_kron(b);
}

/** \brief Repeat matrix A n times vertically and m times horizontally */
inline SWIG_FRIEND MatType repmat(const MatType &A, int n, int m=1) {
  return A.zz_repmat(n, m);
}

/** \brief Repeat matrix A n times vertically and m times horizontally */
inline SWIG_FRIEND MatType repmat(const MatType &A, const std::pair<int, int>& rc) {
  return A.zz_repmat(rc.first, rc.second);
}
