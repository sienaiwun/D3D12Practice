
#pragma once

#pragma warning(disable:4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable:4238) // nonstandard extension used : class rvalue used as lvalue
#pragma warning(disable:4324) // structure was padded due to __declspec(align())

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
    #define NOMINMAX
#endif
#include <windows.h>

#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#define MY_IID_PPV_ARGS IID_PPV_ARGS
#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)


#pragma region
#include <d3dx12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>
#pragma endregion


#pragma region

#pragma comment (lib, "d3dcompiler.lib")

#pragma endregion

#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <memory>
#include <string>
#include <exception>
#include <numeric>
#include <wrl.h>
#include <ppltasks.h>
#include <gsl\gsl>

#include "Utility.h"
#include "VectorMath.h"
#include "EngineTuning.h"
#include "EngineProfiling.h"

template< typename T >
using NotNull = gsl::not_null< T >;

#define SHADER_ARGS(shader) (shader), \
								 sizeof(shader)

template<typename T, std::size_t N>
struct Array :public std::array<T, N>
{
    static inline std::function<T(T, T)> multiply = [](T priview, T current) {
        return priview * current;
    };
public:
    T product()
    {
        return std::accumulate(begin(), end(), 1, multiply);
    }  
};
using U8 = uint8_t;
using U32 = uint32_t;
using U32x1 = U32;
using U32x2 = Array<U32, 2>;
using U32x3 = Array<U32, 3>;
using U32x4 = Array<U32, 4>;
using F32 = float;
using F32x2 = Array<F32, 2>;
using F32x3 = Array<F32, 3>;
using F32x4 = Array<F32, 4>;


#pragma region voxel
#define VOXEL_RESOLUTION 128
#define CLIP_REGION_COUNT 6
#define FACE_COUNT 6
#pragma endregion


template <typename T, size_t N > Array<T, N> DivideByMultiple(Array <T, N> value, Array <T, N> alignment)
{
    Array <T, N> result;
    for (size_t i = 0; i < N; i++)
    {
        result[i] = (T)((value[i] + alignment[i] - 1) / alignment[i]);
    }
    return result;
}