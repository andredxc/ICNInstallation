//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

// sample.h

#if !defined(NDNBOOST_PP_IS_ITERATING)

   #ifndef NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_DETAILS_INCLUDED
   #define NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_DETAILS_INCLUDED

      #include <ndnboost/intrusive/detail/config_begin.hpp>
      #include <ndnboost/intrusive/detail/workaround.hpp>
      #include <ndnboost/intrusive/detail/preprocessor.hpp>
      #include <ndnboost/intrusive/detail/mpl.hpp>
      #include <ndnboost/static_assert.hpp>
      #include <ndnboost/move/move.hpp>

      //Mark that we don't support 0 arg calls due to compiler ICE in GCC 3.4/4.0/4.1 and
      //wrong SFINAE for GCC 4.2/4.3
      #if defined(__GNUC__) && !defined(__clang__) && ((__GNUC__*100 + __GNUC_MINOR__*10) >= 340) && ((__GNUC__*100 + __GNUC_MINOR__*10) <= 430)
      #define NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED
      #elif defined(NDNBOOST_INTEL) && (NDNBOOST_INTEL < 1200 )
      #define NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED
      #endif

      namespace ndnboost_intrusive_has_member_function_callable_with {

      struct dont_care
      {
         dont_care(...);
      };

      struct private_type
      {
         static private_type p;
         private_type const &operator,(int) const;
      };

      typedef char yes_type;            // sizeof(yes_type) == 1
      struct no_type{ char dummy[2]; }; // sizeof(no_type)  == 2

      template<typename T>
      no_type is_private_type(T const &);
      yes_type is_private_type(private_type const &);

      }  //boost_intrusive_has_member_function_callable_with

      #include <ndnboost/intrusive/detail/config_end.hpp>

   #endif   //NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_DETAILS_INCLUDED

#else //!NDNBOOST_PP_IS_ITERATING

   #ifndef  NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
   #error "NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME not defined!"
   #endif

   #ifndef  NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN
   #error "NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN not defined!"
   #endif

   #ifndef  NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END
   #error "NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END not defined!"
   #endif

   #if NDNBOOST_PP_ITERATION_START() > NDNBOOST_PP_ITERATION_FINISH()
   #error "NDNBOOST_PP_ITERATION_START() must be <= NDNBOOST_PP_ITERATION_FINISH()"
   #endif

   #if NDNBOOST_PP_ITERATION() == NDNBOOST_PP_ITERATION_START()

      NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN

      template <typename Type>
      class NDNBOOST_PP_CAT(has_member_function_named_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
      {
         struct BaseMixin
         {
            void NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME();
         };

         struct Base : public ::ndnboost::intrusive::detail::remove_cv<Type>::type, public BaseMixin { Base(); };
         template <typename T, T t> class Helper{};

         template <typename U>
         static ndnboost_intrusive_has_member_function_callable_with::no_type  deduce
            (U*, Helper<void (BaseMixin::*)(), &U::NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME>* = 0);
         static ndnboost_intrusive_has_member_function_callable_with::yes_type deduce(...);

         public:
         static const bool value =
            sizeof(ndnboost_intrusive_has_member_function_callable_with::yes_type) == sizeof(deduce((Base*)(0)));
      };

      #if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

         template<typename Fun, bool HasFunc
                  NDNBOOST_PP_ENUM_TRAILING(NDNBOOST_PP_ITERATION_FINISH(), NDNBOOST_INTRUSIVE_PP_TEMPLATE_PARAM_VOID_DEFAULT, _)>
         struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME), _impl);
         //!

         template<typename Fun NDNBOOST_PP_ENUM_TRAILING_PARAMS(NDNBOOST_PP_ITERATION_FINISH(), class P)>
         struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME), _impl)
            <Fun, false NDNBOOST_PP_ENUM_TRAILING_PARAMS(NDNBOOST_PP_ITERATION_FINISH(), P)>
         {
            static const bool value = false;
         };
         //!

      #else //!defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

         template<typename Fun, bool HasFunc, class ...Args>
         struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl);

         template<typename Fun, class ...Args>
         struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
            <Fun, false, Args...>
         {
            static const bool value = false;
         };

         #ifdef NDNBOOST_NO_CXX11_DECLTYPE

         //Special case for 0 args
         template< class F
               , std::size_t N =
                     sizeof((ndnboost::move_detail::declval<F>().
                        NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME (), 0))>
         struct NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
         {
            ndnboost_intrusive_has_member_function_callable_with::yes_type dummy;
            NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)(int);
         };

         //For buggy compilers like MSVC 7.1+ ((F*)0)->func() does not
         //SFINAE-out the zeroarg_checker_ instantiation but sizeof yields to 0.
         template<class F>
         struct NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<F, 0>
         {
            ndnboost_intrusive_has_member_function_callable_with::no_type dummy;
            NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)(int);
         };

         #endif   //#ifdef NDNBOOST_NO_CXX11_DECLTYPE

         template<typename Fun>
         struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
            <Fun, true>
         {
            #ifndef NDNBOOST_NO_CXX11_DECLTYPE
            template<class U, class V = decltype(ndnboost::move_detail::declval<U>().NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME()) >
            static ndnboost_intrusive_has_member_function_callable_with::yes_type Test(U*);
            #else
            template<class U>
               static NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
               <U> Test(NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<U>*);
            #endif
   
            template <class U>
            static ndnboost_intrusive_has_member_function_callable_with::no_type Test(...);

            static const bool value = sizeof(Test< Fun >(0))
                                 == sizeof(ndnboost_intrusive_has_member_function_callable_with::yes_type);
         };

         template<typename Fun, class ...DontCares>
         struct NDNBOOST_PP_CAT( funwrap_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME )
            : Fun
         {
            NDNBOOST_PP_CAT( funwrap_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME )();
            using Fun::NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME;

            ndnboost_intrusive_has_member_function_callable_with::private_type
               NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
                  ( DontCares...)  const;
         };

         template<typename Fun, class ...Args>
         struct NDNBOOST_PP_CAT( NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME), _impl)
            <Fun, true , Args...>
         {
            template<class T>
            struct make_dontcare
            {
               typedef ndnboost_intrusive_has_member_function_callable_with::dont_care type;
            };

            typedef NDNBOOST_PP_CAT( funwrap_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME )
               <Fun, typename make_dontcare<Args>::type...> FunWrap;

            static bool const value = (sizeof(ndnboost_intrusive_has_member_function_callable_with::no_type) ==
                                       sizeof(ndnboost_intrusive_has_member_function_callable_with::is_private_type
                                                ( (::ndnboost::move_detail::declval< FunWrap >().
                                          NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
                                             ( ::ndnboost::move_detail::declval<Args>()... ), 0) )
                                             )
                                       );
         };

         template<typename Fun, class ...Args>
         struct NDNBOOST_PP_CAT( has_member_function_callable_with_
                            , NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
            : public NDNBOOST_PP_CAT( NDNBOOST_PP_CAT(has_member_function_callable_with_
                                 , NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
               < Fun
               , NDNBOOST_PP_CAT( has_member_function_named_
                             , NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME )<Fun>::value
               , Args... >
         {};

      #endif   //!defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

      NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END

   #endif   //NDNBOOST_PP_ITERATION() == NDNBOOST_PP_ITERATION_START()

   #if NDNBOOST_PP_ITERATION() == 0

      NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN

      #if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

         #if !defined(_MSC_VER) || (_MSC_VER < 1600)

            #if defined(NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED)

            template<typename Fun>
            struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
               <Fun, true NDNBOOST_PP_ENUM_TRAILING(NDNBOOST_PP_SUB(NDNBOOST_PP_ITERATION_FINISH(), NDNBOOST_PP_ITERATION()), NDNBOOST_INTRUSIVE_PP_IDENTITY, void)>
            {
               //Mark that we don't support 0 arg calls due to compiler ICE in GCC 3.4/4.0/4.1 and
               //wrong SFINAE for GCC 4.2/4.3
               static const bool value = true;
            };

            #else //defined(NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED)

            //Special case for 0 args
            template< class F
                  , std::size_t N =
                        sizeof((ndnboost::move_detail::declval<F>().
                           NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME (), 0))>
            struct NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
            {
               ndnboost_intrusive_has_member_function_callable_with::yes_type dummy;
               NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)(int);
            };

            //For buggy compilers like MSVC 7.1+ ((F*)0)->func() does not
            //SFINAE-out the zeroarg_checker_ instantiation but sizeof yields to 0.
            template<class F>
            struct NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<F, 0>
            {
               ndnboost_intrusive_has_member_function_callable_with::no_type dummy;
               NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)(int);
            };

            template<typename Fun>
            struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
               <Fun, true NDNBOOST_PP_ENUM_TRAILING(NDNBOOST_PP_SUB(NDNBOOST_PP_ITERATION_FINISH(), NDNBOOST_PP_ITERATION()), NDNBOOST_INTRUSIVE_PP_IDENTITY, void)>
            {
               template<class U>
               static NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<U>
                  Test(NDNBOOST_PP_CAT(zeroarg_checker_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<U>*);

               template <class U>
               static ndnboost_intrusive_has_member_function_callable_with::no_type Test(...);

               static const bool value = sizeof(Test< Fun >(0))
                                    == sizeof(ndnboost_intrusive_has_member_function_callable_with::yes_type);
            };
            #endif   //defined(NDNBOOST_INTRUSIVE_DETAIL_HAS_MEMBER_FUNCTION_CALLABLE_WITH_0_ARGS_UNSUPPORTED)

         #else //#if !defined(_MSC_VER) || (_MSC_VER < 1600)
            template<typename Fun>
            struct NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
               <Fun, true NDNBOOST_PP_ENUM_TRAILING(NDNBOOST_PP_SUB(NDNBOOST_PP_ITERATION_FINISH(), NDNBOOST_PP_ITERATION()), NDNBOOST_INTRUSIVE_PP_IDENTITY, void)>
            {
               template<class U>
               static decltype( ndnboost::move_detail::declval<U>().NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME()
                              , ndnboost_intrusive_has_member_function_callable_with::yes_type())
                  Test(U*);

               template<class U>
               static ndnboost_intrusive_has_member_function_callable_with::no_type Test(...);

               static const bool value = sizeof(Test<Fun>(0))
                                    == sizeof(ndnboost_intrusive_has_member_function_callable_with::yes_type);
            };
         #endif   //#if !defined(_MSC_VER) || (_MSC_VER < 1600)

      #else   //#if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

      #endif   //#if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

      NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END

   #else   //NDNBOOST_PP_ITERATION() == 0

      #if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

         NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN

         template<typename Fun>
         struct NDNBOOST_PP_CAT( NDNBOOST_PP_CAT(funwrap, NDNBOOST_PP_ITERATION())
                           , NDNBOOST_PP_CAT(_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME))
            : Fun
         {
            NDNBOOST_PP_CAT( NDNBOOST_PP_CAT(funwrap, NDNBOOST_PP_ITERATION())
                        , NDNBOOST_PP_CAT(_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME))();

            using Fun::NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME;
            ndnboost_intrusive_has_member_function_callable_with::private_type
               NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
                  ( NDNBOOST_PP_ENUM(NDNBOOST_PP_ITERATION()
                  , NDNBOOST_INTRUSIVE_PP_IDENTITY
                  , ndnboost_intrusive_has_member_function_callable_with::dont_care))  const;
         };

         template<typename Fun NDNBOOST_PP_ENUM_TRAILING_PARAMS(NDNBOOST_PP_ITERATION(), class P)>
         struct NDNBOOST_PP_CAT( NDNBOOST_PP_CAT(has_member_function_callable_with_
                            , NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME),_impl)
            <Fun, true
            NDNBOOST_PP_ENUM_TRAILING_PARAMS(NDNBOOST_PP_ITERATION(), P)
            NDNBOOST_PP_ENUM_TRAILING( NDNBOOST_PP_SUB(NDNBOOST_PP_ITERATION_FINISH(), NDNBOOST_PP_ITERATION())
                                  , NDNBOOST_INTRUSIVE_PP_IDENTITY
                                  , void)>
         {
            typedef NDNBOOST_PP_CAT( NDNBOOST_PP_CAT(funwrap, NDNBOOST_PP_ITERATION())
                              , NDNBOOST_PP_CAT(_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME))<Fun>
                     FunWrap;
            static bool const value =
            (sizeof(ndnboost_intrusive_has_member_function_callable_with::no_type) ==
               sizeof(ndnboost_intrusive_has_member_function_callable_with::is_private_type
                        (  (ndnboost::move_detail::declval<FunWrap>().
                              NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
                                 ( NDNBOOST_PP_ENUM( NDNBOOST_PP_ITERATION(), NDNBOOST_INTRUSIVE_PP_DECLVAL, _) ), 0
                           )
                        )
                     )
            );
         };

         NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END
      #endif   //#if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

   #endif   //NDNBOOST_PP_ITERATION() == 0

   #if NDNBOOST_PP_ITERATION() == NDNBOOST_PP_ITERATION_FINISH()

      #if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

         NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN

         template<typename Fun
                  NDNBOOST_PP_ENUM_TRAILING(NDNBOOST_PP_ITERATION_FINISH(), NDNBOOST_INTRUSIVE_PP_TEMPLATE_PARAM_VOID_DEFAULT, _)>
         struct NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)
            : public NDNBOOST_PP_CAT(NDNBOOST_PP_CAT(has_member_function_callable_with_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME), _impl)
               <Fun, NDNBOOST_PP_CAT(has_member_function_named_, NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME)<Fun>::value
               NDNBOOST_PP_ENUM_TRAILING_PARAMS(NDNBOOST_PP_ITERATION_FINISH(), P) >
         {};

         NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END

      #endif //#if !defined(NDNBOOST_INTRUSIVE_PERFECT_FORWARDING)

      #undef NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME
      #undef NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEGIN
      #undef NDNBOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END

   #endif   //#if NDNBOOST_PP_ITERATION() == NDNBOOST_PP_ITERATION_FINISH()

#endif   //!NDNBOOST_PP_IS_ITERATING
