/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
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

#ifndef OOQP_INTERNAL_HPP
#define OOQP_INTERNAL_HPP

#include "symbolic/fx/qp_solver_internal.hpp"
#include <QpGenData.h>
#include <QpGenVars.h>
#include <QpGenResiduals.h>
#include <GondzioSolver.h>
#include <QpGenSparseMa27.h>

// A variable that controls the printlevel of OOQP
// This is the only possible way to access it using the C++ interface
extern int gOoqpPrintLevel;

namespace CasADi{

/** \brief Internal class for OOQPSolver
 * 
    @copydoc QPSolver_doc
 * */
class OOQPInternal : public QPSolverInternal {
  friend class OOQPSolver;
public:
  /** \brief  Constructor */
  explicit OOQPInternal();

  /** \brief  Clone */
  virtual OOQPInternal* clone() const;
  
  /** \brief  Create a new Solver */
  explicit OOQPInternal(const CRSSparsity& H, const CRSSparsity& A);

  /** \brief  Destructor */
  virtual ~OOQPInternal();

  /** \brief  Initialize */
  virtual void init();
  
  /** \brief  Allocate
  *  Because constraints after initialization, we cannot allocate a Solver during init
  */
  virtual void allocate();
  
  virtual void evaluate(int nfdir, int nadir);
  
  protected:
    /** 
     * OOQP specific pointers.
     * @ {
     * */
    QpGenSparseMa27 * qp_;
    QpGenData      * prob_;
    QpGenVars      * vars_; 
    QpGenResiduals * resid_;
    GondzioSolver  * s_;
    /* @} */
    
    /// The non-zero indices of the equality and inequality constraints
    std::vector<int> eq_, ineq_;
        
    /// The lower triangular part of H
    DMatrix Hl_;
    
    /// The equality and inequality parts of A
    DMatrix A_eq_, A_ineq_;
    
    /// The equality part of LBA/UBA
    std::vector<double> bA_eq_;
    
    /// The inequality part of LBA and UBA
    std::vector<double> lbA_ineq_, ubA_ineq_;
    
    /// The LBX/UBX with infinities substituted by 0 (needed for OOQP)
    std::vector<double> lbX_, ubX_;
    
    /** 
     *  In OOQP, infinite bounds need a special treatment. They must be deactivated by setting the i-something std::vector<char>.
     *  they have to be zero for infinite bounds and 1 otherwise
     * @{
     */
    std::vector<char> ixlow_, ixupp_, iclow_, icupp_;

    
    /// Temporary vector
    std::vector<double> temp_;
    
    /// Throw error
    static void ooqp_error(const std::string& module, int flag);
    
    /// Calculate the error message map
    static std::map<int,std::string> calc_flagmap();
    
    /// Error message map
    static std::map<int,std::string> flagmap;
};


} // namespace CasADi

#endif //OOQP_INTERNAL_HPP

