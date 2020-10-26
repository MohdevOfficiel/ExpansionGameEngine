#pragma once

#ifndef _MAT4_H__
#define _MAT4_H__

#ifdef _WIN32
#ifdef EXPANSIONMATH_EXPORTS
#define EXPANSIONMATH_API __declspec(dllexport)
#else
#define EXPANSIONMATH_API __declspec(dllimport)
#endif

#else

#define EXPANSIONMATH_API

#endif //_WIN32

#include <iostream>
#include <algorithm>
#include <cstring>
#include <immintrin.h>

#include "vec4.h"
#include "vec3.h"
#include "basic_math.h"

template<class T>
class mat4
{
public:
	mat4(T init_val) {
		memset(m_mat, 0, 16 * sizeof(T));

		if (sizeof(T) == sizeof(float)) {
			_simd_enabled = true;
		}
		else {
			_simd_enabled = false;
		}

		/*
		* Making identity matrix

		ival,	0.0f,	0.0f,	0.0f,
		0.0f,	ival,	0.0f,	0.0f,
		0.0f,	0.0f,	ival,	0.0f,
		0.0f,	0.0f,	0.0f,	ival,

		*/

		for (int i = 0; i < 16; i += 5) {
			m_mat[i] = init_val;
		}
	}

	mat4(T mat[16]) {
		memset(m_mat, 0, sizeof(m_mat));
		memcpy(m_mat, mat, 16 * sizeof(T));
	}

	~mat4() {

	}

	float GetValAt(int row, int column) {
		return m_mat[4 * row + column];
	}

	void DBG_print_matrix() {
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				std::cout << m_mat[4 * x + y] << ", ";
			}

			std::cout << std::endl;
		}
	}

	vec4<T> operator*(vec4<T> a) {
		if (_simd_enabled) {
			__m128 vec = { a.GetX(), a.GetY(), a.GetZ(), a.GetW() };

			T XYZW[4];
			for (int i = 0; i < 16; i += 4) {
				__m128 mat_row = { m_mat[i] , m_mat[i + 1], m_mat[i + 2], m_mat[i + 3] };
				__m128 vec_new = _mm_mul_ps(mat_row, vec);

				XYZW[i / 4] = vec_new.m128_f32[0] + vec_new.m128_f32[1] + vec_new.m128_f32[2] + vec_new.m128_f32[3];
			}

			return vec4<T>(XYZW[0], XYZW[1], XYZW[2], XYZW[3]);
		}
		else {
			T XYZW[4];
			for (int i = 0; i < 16; i += 4) {
				XYZW[i / 4] = a.GetX() * m_mat[i] + a.GetY() * m_mat[i + 1] + a.GetZ() * m_mat[i + 2] + a.GetW() * m_mat[i + 3];
			}

			return vec4<T>(XYZW[0], XYZW[1], XYZW[2], XYZW[3]);
		}
	}

	mat4<T> operator*(float a) {
		T nMat[16];
		memset(nMat, 0, 16 * sizeof(T));

		if (_simd_enabled) {
			__m128 scalar = _mm_load_ss(&a);
			for (int i = 0; i < 16; i += 4) {
				__m128 m = { m_mat[i], m_mat[i + 1], m_mat[i + 2], m_mat[i + 3] };
				__m128 mmultiplied = _mm_mul_ps(m, scalar);

				memcpy(&nMat[i], mmultiplied.m128_f32, 4 * sizeof(float));
			}
		}
		else {
			for (int i = 0; i < 16; i++) {
				nMat[i] = m_mat[i] * a;
			}
		}

		return mat4<T>(nMat);
	}

	mat4<T> operator*(mat4<T> const& a) {
		if (_simd_enabled) {
			//SIMD Impl.

			//Allocating matrix in XMM registers
			__m128 mat_1_rows[4];
			for (int i = 0; i < 16; i += 4) {
				mat_1_rows[i / 4] = { m_mat[i], m_mat[i + 1], m_mat[i + 2], m_mat[i + 3] };
			}

			//Declaring result mat
			T nMat[16];

			for (int i = 0; i < 4; i++) {
				for (int c = 0; c < 4; c++) {
					//Getting column of the second matrix
					__m128 col = { a.m_mat[c], a.m_mat[c + 4], a.m_mat[c + 8], a.m_mat[c + 12] };

					//Multiplying & storing results
					__m128 result = _mm_mul_ps(mat_1_rows[i], col);

					//Sum up everything
					T comp = 0;
					for (int s = 0; s < 4; s++) {
						comp += result.m128_f32[s];
					}

					nMat[4 * i + c] = comp;
				}
			}

			return mat4<T>(nMat);
		}
		else {
			//Non-SIMD impl.

			T nMat[16];
			for (int i = 0; i < 4; i++) {
				for (int c = 0; c < 4; c++) {
					T col[4] = { a.m_mat[c], a.m_mat[c + 4], a.m_mat[c + 8], a.m_mat[c + 12] };

					//Multiply all
					T results[4];
					for (int m = 0; m < 4; m++) {
						results[m] = col[m] * m_mat[4 * i + c];
					}

					//Sum up everything
					T comp = 0;
					for (int s = 0; s < 4; s++) {
						comp += results[s];
					}
				}
			}

			return mat4<T>(nMat);
		}
	}

	T* GetPTR() {
		return &m_mat[0];
	}

private:
	T m_mat[16];

	bool _simd_enabled;
};

template<class T>
mat4<T> TranslateMatrix(mat4<T> srcMat, vec3f trans) {
	T transMat[16] = {
		1, 0, 0, trans.getX(),
		0, 1, 0, trans.getY(),
		0, 0, 1, trans.getZ(),
		0, 0, 0, 1
	};
	mat4<T> tmat(transMat);

	return srcMat * tmat;
}

template<class T>
mat4<T> ScaleMatrix(mat4<T> srcMat, vec3f scale) {
	T scaleMat[16] = {
		scale.getX(), 0			  , 0			, 0			   ,
		0			, scale.getY(), 0			, 0			   ,
		0			, 0			  , scale.getZ(), 0			   ,
		0			, 0			  ,	0			, 1
	};
	mat4<T> smat(scaleMat);

	return srcMat * scaleMat;
}

template<class T>
mat4<T> RotateMatrix(mat4<T> srcMat, vec3f rot) {
	mat4<T> srcCopy = srcMat;

	float X = DEG_TO_RAD(rot.getX());
	float Y = DEG_TO_RAD(rot.getY());
	float Z = DEG_TO_RAD(rot.getZ());

	//X
	float Stheta = sin(X);
	float Ctheta = cos(X);

	T rxMat[16] = {
	1,		0,		 0, 0,
	0, Ctheta, -Stheta, 0,
	0, Stheta,  Ctheta, 0,
	0,		0,		 0, 1
	};

	srcCopy = srcCopy * mat4<T>(rxMat);

	//Y
	Stheta = sin(Y);
	Ctheta = cos(Y);

	T ryMat[16] = {
		 Ctheta,	 0, Stheta,		0,
			  0,	 1,		 0,		0,
		-Stheta,	 0, Ctheta,		0,
			  0,	 0,		 0,		1
	};

	srcCopy = srcCopy * mat4<T>(ryMat);

	//Z
	Stheta = sin(Z);
	Ctheta = cos(Z);

	T rzMat[16] = {
		Ctheta, -Stheta, 0, 0,
		Stheta,  Ctheta, 0, 0,
			 0,		  0, 1, 0,
			 0,		  0, 0, 1
	};

	srcCopy = srcCopy * mat4<T>(rzMat);

	return srcCopy;
}

template<class T>
mat4<T> LookAt(vec3<T> pos, vec3<T> target, vec3<T> up) {
	//Dir
	vec3<T> cam_dir(pos - target);
	cam_dir.NormalizeVector();

	//Right
	vec3<T> cam_right(Cross(up, cam_dir));
	cam_right.NormalizeVector();

	//Up
	vec3<T> cam_up(Cross(cam_dir, cam_right));

	T mat_rot[16] = {
		cam_right.getX(), cam_right.getY(), cam_right.getZ(), 0,
		   cam_up.getX(),	 cam_up.getY(),	   cam_up.getZ(), 0,
		  cam_dir.getX(),	cam_dir.getY(),	  cam_dir.getZ(), 0,
					   0,				 0,				   0, 1,
	};

	T mat_trans[16] = {
		1, 0, 0, -pos.getX(),
		0, 1, 0, -pos.getY(),
		0, 0, 1, -pos.getZ(),
		0, 0, 0, 1
	};

	return mat4<T>(mat_rot) * mat4<T>(mat_trans);
}

template<class T>
mat4<T> ProjPersp(float FOV, float ImageRatio, float nearv = 0.1f, float farv = 1000.0f) {
	T mat[16] = {
		1 / (ImageRatio * tan(FOV / 2)),				0,									   0,  0,
									  0, 1 / tan(FOV / 2),									   0,  0,
									  0,				0,    -((farv + nearv) / (farv - nearv)), -((2 * (farv * nearv)) / (farv - nearv)),
									  0,				0, -1,  0
	};

	return mat4<T>(mat);
}

template<class T>
mat4<T> ProjOrtho(T right, T left, T top, T bottom, T nearv, T farv) {
	T mat[16] = {
		2 / (right - left), 0, 0, -((right + left) / (right - left)),
		0, 2 / (top - bottom), 0, -((top + bottom) / (top - bottom)),
		0, 0, -2 / (farv - nearv), -((farv + nearv) / (farv - nearv)),
		0, 0, 0, 1
	};

	return mat4<T>(mat);
}

typedef mat4<float> mat4f;

#endif // _MAT4_H__
