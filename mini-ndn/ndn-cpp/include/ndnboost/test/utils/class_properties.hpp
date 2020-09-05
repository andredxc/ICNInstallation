//  (C) Copyright Gennadiy Rozental 2001-2008.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : simple facility that mimmic notion of read-only read-write 
//  properties in C++ classes. Original idea by Henrik Ravn.
// ***************************************************************************

#ifndef NDNBOOST_TEST_CLASS_PROPERTIES_HPP_071894GER
#define NDNBOOST_TEST_CLASS_PROPERTIES_HPP_071894GER

// Boost.Test
#include <ndnboost/test/detail/config.hpp>

// Boost
#if !NDNBOOST_WORKAROUND(__IBMCPP__, NDNBOOST_TESTED_AT(600))
#include <ndnboost/preprocessor/seq/for_each.hpp>
#endif
#include <ndnboost/call_traits.hpp>
#include <ndnboost/type_traits/add_pointer.hpp>
#include <ndnboost/type_traits/add_const.hpp>
#include <ndnboost/utility/addressof.hpp>

// STL
#include <iosfwd>

#include <ndnboost/test/detail/suppress_warnings.hpp>

//____________________________________________________________________________//

namespace ndnboost {

namespace unit_test {

// ************************************************************************** //
// **************                 class_property               ************** //
// ************************************************************************** //

template<class PropertyType>
class class_property {
protected:
    typedef typename call_traits<PropertyType>::const_reference     read_access_t;
    typedef typename call_traits<PropertyType>::param_type          write_param_t;
    typedef typename add_pointer<typename add_const<PropertyType>::type>::type address_res_t;
public:
    // Constructor
                    class_property() : value( PropertyType() ) {}
    explicit        class_property( write_param_t init_value )
    : value( init_value ) {}

    // Access methods
    operator        read_access_t() const   { return value; }
    read_access_t   get() const             { return value; }
    bool            operator!() const       { return !value; }
    address_res_t   operator&() const       { return &value; }

    // Data members
#ifndef NDNBOOST_TEST_NO_PROTECTED_USING
protected:
#endif
    PropertyType        value;
};

//____________________________________________________________________________//

#ifdef NDNBOOST_CLASSIC_IOSTREAMS

template<class PropertyType>
inline std::ostream&
operator<<( std::ostream& os, class_property<PropertyType> const& p )

#else

template<typename CharT1, typename Tr,class PropertyType>
inline std::basic_ostream<CharT1,Tr>&
operator<<( std::basic_ostream<CharT1,Tr>& os, class_property<PropertyType> const& p )

#endif
{
    return os << p.get();
}

//____________________________________________________________________________//

#define DEFINE_PROPERTY_FREE_BINARY_OPERATOR( op )                              \
template<class PropertyType>                                                    \
inline bool                                                                     \
operator op( PropertyType const& lhs, class_property<PropertyType> const& rhs ) \
{                                                                               \
    return lhs op rhs.get();                                                    \
}                                                                               \
template<class PropertyType>                                                    \
inline bool                                                                     \
operator op( class_property<PropertyType> const& lhs, PropertyType const& rhs ) \
{                                                                               \
    return lhs.get() op rhs;                                                    \
}                                                                               \
template<class PropertyType>                                                    \
inline bool                                                                     \
operator op( class_property<PropertyType> const& lhs,                           \
             class_property<PropertyType> const& rhs )                          \
{                                                                               \
    return lhs.get() op rhs.get();                                              \
}                                                                               \
/**/

DEFINE_PROPERTY_FREE_BINARY_OPERATOR( == )
DEFINE_PROPERTY_FREE_BINARY_OPERATOR( != )

#undef DEFINE_PROPERTY_FREE_BINARY_OPERATOR

#if NDNBOOST_WORKAROUND(NDNBOOST_MSVC, < 1300)

#define DEFINE_PROPERTY_LOGICAL_OPERATOR( op )                                  \
template<class PropertyType>                                                    \
inline bool                                                                     \
operator op( bool b, class_property<PropertyType> const& p )                    \
{                                                                               \
    return b op p.get();                                                        \
}                                                                               \
template<class PropertyType>                                                    \
inline bool                                                                     \
operator op( class_property<PropertyType> const& p, bool b )                    \
{                                                                               \
    return b op p.get();                                                        \
}                                                                               \
/**/

DEFINE_PROPERTY_LOGICAL_OPERATOR( && )
DEFINE_PROPERTY_LOGICAL_OPERATOR( || )

#endif

// ************************************************************************** //
// **************               readonly_property              ************** //
// ************************************************************************** //

template<class PropertyType>
class readonly_property : public class_property<PropertyType> {
    typedef class_property<PropertyType>         base_prop;
    typedef typename base_prop::address_res_t    arrow_res_t;
protected:
    typedef typename base_prop::write_param_t    write_param_t;
public:
    // Constructor
                    readonly_property() {}
    explicit        readonly_property( write_param_t init_value ) : base_prop( init_value ) {}

    // access methods
    arrow_res_t     operator->() const      { return ndnboost::addressof( base_prop::value ); }
};

//____________________________________________________________________________//

#if NDNBOOST_WORKAROUND(__IBMCPP__, NDNBOOST_TESTED_AT(600))

#define NDNBOOST_READONLY_PROPERTY( property_type, friends ) ndnboost::unit_test::readwrite_property<property_type >

#else

#define NDNBOOST_READONLY_PROPERTY_DECLARE_FRIEND(r, data, elem) friend class elem;

#define NDNBOOST_READONLY_PROPERTY( property_type, friends )                           \
class NDNBOOST_JOIN( readonly_property, __LINE__ )                                     \
: public ndnboost::unit_test::readonly_property<property_type > {                      \
    typedef ndnboost::unit_test::readonly_property<property_type > base_prop;          \
    NDNBOOST_PP_SEQ_FOR_EACH( NDNBOOST_READONLY_PROPERTY_DECLARE_FRIEND, ' ', friends )   \
    typedef base_prop::write_param_t  write_param_t;                                \
public:                                                                             \
                NDNBOOST_JOIN( readonly_property, __LINE__ )() {}                      \
    explicit    NDNBOOST_JOIN( readonly_property, __LINE__ )( write_param_t init_v  )  \
    : base_prop( init_v ) {}                                                        \
}                                                                                   \
/**/

#endif

// ************************************************************************** //
// **************              readwrite_property              ************** //
// ************************************************************************** //

template<class PropertyType>
class readwrite_property : public class_property<PropertyType> {
    typedef class_property<PropertyType>                base_prop;
    typedef typename add_pointer<PropertyType>::type    arrow_res_t;
    typedef typename base_prop::address_res_t           const_arrow_res_t;
    typedef typename base_prop::write_param_t           write_param_t;
public:
                    readwrite_property() : base_prop() {}
    explicit        readwrite_property( write_param_t init_value ) : base_prop( init_value ) {}

    // access methods
    void            set( write_param_t v )  { base_prop::value = v; }
    arrow_res_t     operator->()            { return ndnboost::addressof( base_prop::value ); }
    const_arrow_res_t operator->() const    { return ndnboost::addressof( base_prop::value ); }

#ifndef NDNBOOST_TEST_NO_PROTECTED_USING
    using           base_prop::value;
#endif
};

//____________________________________________________________________________//

} // unit_test

} // namespace ndnboost

//____________________________________________________________________________//

#include <ndnboost/test/detail/enable_warnings.hpp>

#undef NDNBOOST_TEST_NO_PROTECTED_USING

#endif // NDNBOOST_TEST_CLASS_PROPERTIES_HPP_071894GER
