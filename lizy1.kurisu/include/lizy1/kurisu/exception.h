#pragma once


// Lizy1 - Kurisu - Kurisu Support for Kurisu Defined Exceptions
// Copyright (c) 2020 Li Zhongyuan
// SPDX-License-Identifier: MIT


#include "std/stdexcept"


template<> struct lizy1::kurisu::Case<lizy1::kurisu::KurisuException> :lizy1::kurisu::impl_K::StdException_Normal<lizy1::kurisu::KurisuException> {};
template<> struct lizy1::kurisu::Case<lizy1::kurisu::LoadException>   :lizy1::kurisu::impl_K::StdException_Normal<lizy1::kurisu::LoadException> {};
template<> struct lizy1::kurisu::Case<lizy1::kurisu::DumpException>   :lizy1::kurisu::impl_K::StdException_Normal<lizy1::kurisu::DumpException> {};
