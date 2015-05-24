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


#ifndef CASADI_IO_SCHEME_INTERNAL_HPP
#define CASADI_IO_SCHEME_INTERNAL_HPP

#include "io_scheme.hpp"
#include "../casadi_exception.hpp"
#include <map>


/// \cond INTERNAL
class SharedObjectNode;

namespace casadi {

  class CASADI_EXPORT IOSchemeInternal : public SharedObjectNode {
  public:
    /// Constructor
    IOSchemeInternal(const std::vector<std::string>& data);

    /// Clone
    virtual IOSchemeInternal* clone() const { return new IOSchemeInternal(data_);}

    /// List available entries
    virtual std::string entryNames() const;

    /// Get index by entry name
    virtual int index(const std::string &name) const;

    /// Number of entries
    virtual int size() const;

    /// Get the entry name by index
    virtual std::string entry(int i) const;

    /// Get the entry enum name by index
    virtual std::string entryEnum(int i) const;

    /// Print a description of the object
    virtual void print(std::ostream &stream=std::cout) const;

    /// Print a representation of the object
    virtual void repr(std::ostream &stream=std::cout) const;

    /// Describe the index
    virtual std::string describe(int i) const;
    std::vector<std::string> data_;
  };


} // namespace casadi
/// \endcond

#endif // CASADI_IO_SCHEME_INTERNAL_HPP
