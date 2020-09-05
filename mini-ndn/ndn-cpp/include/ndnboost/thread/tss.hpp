#ifndef NDNBOOST_THREAD_TSS_HPP
#define NDNBOOST_THREAD_TSS_HPP
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2007-8 Anthony Williams

#include <ndnboost/thread/detail/config.hpp>
#include <ndnboost/shared_ptr.hpp>
#include <ndnboost/thread/detail/thread_heap_alloc.hpp>

#include <ndnboost/config/abi_prefix.hpp>

namespace ndnboost
{
    namespace detail
    {
        struct tss_cleanup_function
        {
            virtual ~tss_cleanup_function()
            {}
            
            virtual void operator()(void* data)=0;
        };
        
        NDNBOOST_THREAD_DECL void set_tss_data(void const* key,ndnboost::shared_ptr<tss_cleanup_function> func,void* tss_data,bool cleanup_existing);
        NDNBOOST_THREAD_DECL void* get_tss_data(void const* key);
    }

    template <typename T>
    class thread_specific_ptr
    {
    private:
        thread_specific_ptr(thread_specific_ptr&);
        thread_specific_ptr& operator=(thread_specific_ptr&);

        struct delete_data:
            detail::tss_cleanup_function
        {
            void operator()(void* data)
            {
                delete static_cast<T*>(data);
            }
        };
        
        struct run_custom_cleanup_function:
            detail::tss_cleanup_function
        {
            void (*cleanup_function)(T*);
            
            explicit run_custom_cleanup_function(void (*cleanup_function_)(T*)):
                cleanup_function(cleanup_function_)
            {}
            
            void operator()(void* data)
            {
                cleanup_function(static_cast<T*>(data));
            }
        };


        ndnboost::shared_ptr<detail::tss_cleanup_function> cleanup;
        
    public:
        typedef T element_type;
        
        thread_specific_ptr():
            cleanup(detail::heap_new<delete_data>(),detail::do_heap_delete<delete_data>())
        {}
        explicit thread_specific_ptr(void (*func_)(T*))
        {
            if(func_)
            {
                cleanup.reset(detail::heap_new<run_custom_cleanup_function>(func_),detail::do_heap_delete<run_custom_cleanup_function>());
            }
        }
        ~thread_specific_ptr()
        {
            detail::set_tss_data(this,ndnboost::shared_ptr<detail::tss_cleanup_function>(),0,true);
        }

        T* get() const
        {
            return static_cast<T*>(detail::get_tss_data(this));
        }
        T* operator->() const
        {
            return get();
        }
        T& operator*() const
        {
            return *get();
        }
        T* release()
        {
            T* const temp=get();
            detail::set_tss_data(this,ndnboost::shared_ptr<detail::tss_cleanup_function>(),0,false);
            return temp;
        }
        void reset(T* new_value=0)
        {
            T* const current_value=get();
            if(current_value!=new_value)
            {
                detail::set_tss_data(this,cleanup,new_value,true);
            }
        }
    };
}

#include <ndnboost/config/abi_suffix.hpp>

#endif
