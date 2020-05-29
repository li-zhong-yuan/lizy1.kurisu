#pragma once


/*
Lizy1 - Kurisu - Core

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2020 Li Zhongyuan
SPDX-License-Identifier: MIT

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/*!
note This header file itself (without its includings) is a statement file \
     for all interfaces that Kurisu exports at namespace lizy1::kurisu
     Kurisu is responsible for implementing Kurisu Support for C++ Standard Library \
     To include support for a specific standard header, just include the same named \
     file in directory <lizy1/kurisu/std>

note All exceptions defined by Kurisu:
        KurisuException: The base class of all other exceptions defined by Kurisu
        LoadException:   This exception is thrown by load() and construct()
        DumpException:   This exception is thrown by dump()
     File <lizy1/kurisu/exception.h> implements Kurisu Support for these exceptions
*/


#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <iostream>


namespace lizy1 {
    namespace kurisu {
        namespace impl_K {
        }
    }
}


#include <lizy1/kurisu/impl/forward.gadgets.h>
#include <lizy1/kurisu/impl/forward.cases.h>


/// Exceptions


namespace lizy1 { namespace kurisu {


    struct KurisuException :std::runtime_error { explicit KurisuException(std::string const& message) :std::runtime_error(message) {} };
    struct LoadException   :KurisuException    { explicit LoadException  (std::string const& message) :KurisuException(message) {}    };
    struct DumpException   :KurisuException    { explicit DumpException  (std::string const& message) :KurisuException(message) {}    };


}}


/// Meta


namespace lizy1 { namespace kurisu {


    template<class... Ts> using IsLoadable      = impl_K::_Star<impl_K::Case_General<Ts>::is_loadable...>;       // yield a std::integral_constant<bool, bool b>
    template<class... Ts> using IsDumpable      = impl_K::_Star<impl_K::Case_General<Ts>::is_dumpable...>;       // yield a std::integral_constant<bool, bool b>
    template<class... Ts> using IsConstructible = impl_K::_Star<impl_K::Case_General<Ts>::is_constructible...>;  // yield a std::integral_constant<bool, bool b>


}}


/// Functions


namespace lizy1 { namespace kurisu {


    template<class... Ts, class = impl_K::_If<IsLoadable<Ts...>::value>> void load(std::istream &is, Ts      &... values);  // thread-safe, instant, raise<LoadException>
    template<class... Ts, class = impl_K::_If<IsDumpable<Ts...>::value>> void dump(std::ostream &os, Ts const&... values);  // thread-safe, instant, raise<DumpException>
    template<class T, class = impl_K::_If<IsConstructible<T>::value>>    T construct(std::istream &is);                     // thread-safe, instant, raise<LoadException>


}}


/// Case


namespace lizy1 { namespace kurisu {


    template<typename T> struct Case;


}}


#include <lizy1/kurisu/impl/machine_bytes.h>
#include <lizy1/kurisu/impl/functions.h>
#include <lizy1/kurisu/impl/case.general.h>
#include <lizy1/kurisu/impl/case.integral.h>
#include <lizy1/kurisu/impl/case.floating.h>
#include <lizy1/kurisu/impl/case.enum.h>
#include <lizy1/kurisu/impl/case.array.h>
#include <lizy1/kurisu/impl/case.struct.h>
