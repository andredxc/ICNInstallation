//  (C) Copyright Gennadiy Rozental 2005-2008.
//  Use, modification, and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : defines model of parameter with single char name
// ***************************************************************************

#ifndef NDNBOOST_RT_CLA_CHAR_PARAMETER_HPP_062604GER
#define NDNBOOST_RT_CLA_CHAR_PARAMETER_HPP_062604GER

// Boost.Runtime.Parameter
#include <ndnboost/test/utils/runtime/config.hpp>
#include <ndnboost/test/utils/runtime/validation.hpp>

#include <ndnboost/test/utils/runtime/cla/basic_parameter.hpp>
#include <ndnboost/test/utils/runtime/cla/id_policy.hpp>

namespace ndnboost {

namespace NDNBOOST_RT_PARAM_NAMESPACE {

namespace cla {

// ************************************************************************** //
// **************               char_name_policy               ************** //
// ************************************************************************** //

class char_name_policy : public basic_naming_policy {
public:
    // Constructor
    char_name_policy();
    NDNBOOST_RT_PARAM_UNNEEDED_VIRTUAL ~char_name_policy() {}

    // policy interface
    virtual bool    conflict_with( identification_policy const& ) const;

    // Accept modifier
    template<typename Modifier>
    void            accept_modifier( Modifier const& m )
    {
        basic_naming_policy::accept_modifier( m );

        NDNBOOST_RT_PARAM_VALIDATE_LOGIC( p_name->size() <= 1, "Invalid parameter name "  << p_name );
    }
};

// ************************************************************************** //
// **************          runtime::cla::char_parameter        ************** //
// ************************************************************************** //

template<typename T>
class char_parameter_t : public basic_parameter<T,char_name_policy> {
    typedef basic_parameter<T,char_name_policy> base;
public:
    // Constructors
    explicit    char_parameter_t( char_type name ) : base( cstring( &name, 1 ) ) {}
};

//____________________________________________________________________________//

template<typename T>
inline shared_ptr<char_parameter_t<T> >
char_parameter( char_type name )
{
    return shared_ptr<char_parameter_t<T> >( new char_parameter_t<T>( name ) );
}

//____________________________________________________________________________//

inline shared_ptr<char_parameter_t<cstring> >
char_parameter( char_type name )
{
    return shared_ptr<char_parameter_t<cstring> >( new char_parameter_t<cstring>( name ) );
}

//____________________________________________________________________________//

} // namespace cla

} // namespace NDNBOOST_RT_PARAM_NAMESPACE

} // namespace ndnboost

#ifndef NDNBOOST_RT_PARAM_OFFLINE

#  define NDNBOOST_RT_PARAM_INLINE inline
#  include <ndnboost/test/utils/runtime/cla/char_parameter.ipp>

#endif

#endif // NDNBOOST_RT_CLA_CHAR_PARAMETER_HPP_062604GER
