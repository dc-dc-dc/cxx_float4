#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#else
#include <immintrin.h>
#endif

struct float4
{
private:
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        float32x4_t v;
#else
        __m128 v;
#endif

public:
        float4() : float4(0) {}
        float4(float a) : float4(a, a, a, a) {}
        float4(float x, float y, float z, float w)
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                float tmp[4] = {x, y, z, w};
                v = vld1q_f32(tmp);
#else
                v = _mm_set_ps(w, z, y, x);
#endif
        }

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        float4(float32x4_t v) : v(v)
        {
        }
#else
        float4(__m128 v) : v(v)
        {
        }
#endif

        float4
        operator+(const float4 &rhs) const
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return float4(vaddq_f32(v, rhs.v));
#else
                return float4(_mm_add_ps(v, rhs.v));
#endif
        }

        float4
        operator-(const float4 &rhs) const
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return float4(vsubq_f32(v, rhs.v));
#else
                return float4(_mm_sub_ps(v, rhs.v));
#endif
        }

        float4
        operator*(const float4 &rhs) const
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return float4(vmulq_f32(v, rhs.v));
#else
                return float4(_mm_mul_ps(v, rhs.v));
#endif
        }

        float4
        operator/(const float4 &rhs) const
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return float4(vdivq_f32(v, rhs.v));
#else
                return float4(_mm_div_ps(v, rhs.v));
#endif
        }

        float4 &operator+=(const float4 &rhs)
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                v = vaddq_f32(v, rhs.v);
#else
                v = _mm_add_ps(v, rhs.v);
#endif
                return *this;
        }

#ifndef __ARM_NEON
        template <unsigned i>
        float vectorGetByIndex(__m128 V)
        {
                union
                {
                        __m128 v;
                        float a[4];
                } converter;
                converter.v = V;
                return converter.a[i];
        }
#endif

        float x()
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return vgetq_lane_f32(v, 0);
#else
                return vectorGetByIndex<0>(v);
#endif
        }

        float y()
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return vgetq_lane_f32(v, 1);
#else
                return vectorGetByIndex<1>(v);
#endif
        }

        float z()
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return vgetq_lane_f32(v, 2);
#else
                return vectorGetByIndex<2>(v);
#endif
        }

        float w()
        {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
                return vgetq_lane_f32(v, 3);
#else
                return vectorGetByIndex<3>(v);
#endif
        }
};