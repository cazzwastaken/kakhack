#pragma once
#include <cstdint>

enum ShaderStencilOp
{
	SHADER_STENCILOP_KEEP = 1,
	SHADER_STENCILOP_ZERO = 2,
	SHADER_STENCILOP_SET_TO_REFERENCE = 3,
	SHADER_STENCILOP_INCREMENT_CLAMP = 4,
	SHADER_STENCILOP_DECREMENT_CLAMP = 5,
	SHADER_STENCILOP_INVERT = 6,
	SHADER_STENCILOP_INCREMENT_WRAP = 7,
	SHADER_STENCILOP_DECREMENT_WRAP = 8,
	SHADER_STENCILOP_FORCE_DWORD = 0x7fffffff
};

enum ShaderStencilFunc
{
	SHADER_STENCILFUNC_NEVER = 1,
	SHADER_STENCILFUNC_LESS = 2,
	SHADER_STENCILFUNC_EQUAL = 3,
	SHADER_STENCILFUNC_LEQUAL = 4,
	SHADER_STENCILFUNC_GREATER = 5,
	SHADER_STENCILFUNC_NOTEQUAL = 6,
	SHADER_STENCILFUNC_GEQUAL = 7,
	SHADER_STENCILFUNC_ALWAYS = 8,

	SHADER_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};

struct ShaderStencilState
{
	bool m_bEnable;
	ShaderStencilOp m_FailOp;
	ShaderStencilOp m_ZFailOp;
	ShaderStencilOp m_PassOp;
	ShaderStencilFunc m_CompareFunc;
	int m_nReferenceValue;
	uint32_t m_nTestMask;
	uint32_t m_nWriteMask;

	ShaderStencilState()
	{
		m_bEnable = false;
		m_PassOp = m_FailOp = m_ZFailOp = SHADER_STENCILOP_KEEP;
		m_CompareFunc = SHADER_STENCILFUNC_ALWAYS;
		m_nReferenceValue = 0;
		m_nTestMask = m_nWriteMask = 0xFFFFFFFF;
	}
};
