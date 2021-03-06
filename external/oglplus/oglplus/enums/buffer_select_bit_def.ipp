//  File implement/oglplus/enums/buffer_select_bit_def.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/buffer_select_bit.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2017 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_COLOR_BUFFER_BIT
# ifdef OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined ColorBuffer
#  pragma push_macro("ColorBuffer")
#  undef ColorBuffer
   OGLPLUS_ENUM_CLASS_VALUE(ColorBuffer, GL_COLOR_BUFFER_BIT)
#  pragma pop_macro("ColorBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(ColorBuffer, GL_COLOR_BUFFER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_DEPTH_BUFFER_BIT
# ifdef OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined DepthBuffer
#  pragma push_macro("DepthBuffer")
#  undef DepthBuffer
   OGLPLUS_ENUM_CLASS_VALUE(DepthBuffer, GL_DEPTH_BUFFER_BIT)
#  pragma pop_macro("DepthBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(DepthBuffer, GL_DEPTH_BUFFER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STENCIL_BUFFER_BIT
# ifdef OGLPLUS_LIST_NEEDS_COMMA
   OGLPLUS_ENUM_CLASS_COMMA
# endif
# if defined StencilBuffer
#  pragma push_macro("StencilBuffer")
#  undef StencilBuffer
   OGLPLUS_ENUM_CLASS_VALUE(StencilBuffer, GL_STENCIL_BUFFER_BIT)
#  pragma pop_macro("StencilBuffer")
# else
   OGLPLUS_ENUM_CLASS_VALUE(StencilBuffer, GL_STENCIL_BUFFER_BIT)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

