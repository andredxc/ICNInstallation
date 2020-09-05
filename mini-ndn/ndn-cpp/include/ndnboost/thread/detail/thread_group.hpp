#ifndef NDNBOOST_THREAD_DETAIL_THREAD_GROUP_HPP
#define NDNBOOST_THREAD_DETAIL_THREAD_GROUP_HPP
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2007-9 Anthony Williams

#include <list>
#include <ndnboost/thread/shared_mutex.hpp>
#include <ndnboost/thread/mutex.hpp>
#include <ndnboost/thread/lock_guard.hpp>

#include <ndnboost/config/abi_prefix.hpp>

#ifdef NDNBOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4251)
#endif

namespace ndnboost
{
    class thread_group
    {
    private:
        thread_group(thread_group const&);
        thread_group& operator=(thread_group const&);
    public:
        thread_group() {}
        ~thread_group()
        {
            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
                delete *it;
            }
        }

        bool is_this_thread_in()
        {
            thread::id id = this_thread::get_id();
            ndnboost::shared_lock<shared_mutex> guard(m);
            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
              if ((*it)->get_id() == id)
                return true;
            }
            return false;
        }

        bool is_thread_in(thread* thrd)
        {
          if(thrd)
          {
            thread::id id = thrd->get_id();
            ndnboost::shared_lock<shared_mutex> guard(m);
            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
              if ((*it)->get_id() == id)
                return true;
            }
            return false;
          }
          else
          {
            return false;
          }
        }

        template<typename F>
        thread* create_thread(F threadfunc)
        {
            ndnboost::lock_guard<shared_mutex> guard(m);
            std::auto_ptr<thread> new_thread(new thread(threadfunc));
            threads.push_back(new_thread.get());
            return new_thread.release();
        }

        void add_thread(thread* thrd)
        {
            if(thrd)
            {
                NDNBOOST_THREAD_ASSERT_PRECONDITION( ! is_thread_in(thrd) ,
                    thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur), "ndnboost::thread_group: trying to add a duplicated thread")
                );

                ndnboost::lock_guard<shared_mutex> guard(m);
                threads.push_back(thrd);
            }
        }

        void remove_thread(thread* thrd)
        {
            ndnboost::lock_guard<shared_mutex> guard(m);
            std::list<thread*>::iterator const it=std::find(threads.begin(),threads.end(),thrd);
            if(it!=threads.end())
            {
                threads.erase(it);
            }
        }

        void join_all()
        {
            NDNBOOST_THREAD_ASSERT_PRECONDITION( ! is_this_thread_in() ,
                thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur), "ndnboost::thread_group: trying joining itself")
            );
            ndnboost::shared_lock<shared_mutex> guard(m);

            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
              if ((*it)->joinable())
                (*it)->join();
            }
        }

#if defined NDNBOOST_THREAD_PROVIDES_INTERRUPTIONS
        void interrupt_all()
        {
            ndnboost::shared_lock<shared_mutex> guard(m);

            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
                (*it)->interrupt();
            }
        }
#endif

        size_t size() const
        {
            ndnboost::shared_lock<shared_mutex> guard(m);
            return threads.size();
        }

    private:
        std::list<thread*> threads;
        mutable shared_mutex m;
    };
}

#ifdef NDNBOOST_MSVC
#pragma warning(pop)
#endif

#include <ndnboost/config/abi_suffix.hpp>

#endif
