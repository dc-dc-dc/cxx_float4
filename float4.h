#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

struct float4
{
private:
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
    float32x4_t v;
#else
    float v[4];
#endif

public:
    float4() : float4(0) {}
    float4(float a)
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        v = vdupq_n_f32(a);
#else
        v[0] = a;
        v[1] = a;
        v[2] = a;
        v[3] = a;
#endif
    }
    float4(float x, float y, float z, float w)
    {
        float tmp[4] = {x, y, z, w};
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        v = vld1q_f32(tmp);
#else
        v = tmp;
#endif
    }

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
    float4(float32x4_t v) : v(v)
    {
    }
#endif

    float4
    operator+(const float4 &rhs) const
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return float4(vaddq_f32(v, rhs.v));
#else
        return float4(v[0] + rhs.v[0], v[1] + rhs.v[1], v[2] + rhs.v[2], v[3] + rhs.v[3]);
#endif
    }

    float4
    operator-(const float4 &rhs) const
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return float4(vsubq_f32(v, rhs.v));
#else
        return float4(v[0] - rhs.v[0], v[1] - rhs.v[1], v[2] - rhs.v[2], v[3] - rhs.v[3]);
#endif
    }

    float4
    operator*(const float4 &rhs) const
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return float4(vmulq_f32(v, rhs.v));
#else
        return float4(v[0] * rhs.v[0], v[1] * rhs.v[1], v[2] * rhs.v[2], v[3] * rhs.v[3]);
#endif
    }

    float4
    operator/(const float4 &rhs) const
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return float4(vdivq_f32(v, rhs.v));
#else
        return float4(v[0] / rhs.v[0], v[1] / rhs.v[1], v[2] / rhs.v[2], v[3] / rhs.v[3]);
#endif
    }

    float4 &operator+=(const float4 &rhs)
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        v = vaddq_f32(v, rhs.v);
#else
        v[0] += rhs.v[0];
        v[1] += rhs.v[1];
        v[2] += rhs.v[2];
        v[3] += rhs.v[3];
#endif
        return *this;
    }

    float x()
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return vgetq_lane_f32(v, 0);
#else
        return v[0];
#endif
    }

    float y()
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return vgetq_lane_f32(v, 1);
#else
        return v[1];
#endif
    }

    float z()
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return vgetq_lane_f32(v, 2);
#else
        return v[2];
#endif
    }

    float w()
    {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
        return vgetq_lane_f32(v, 3);
#else
        return v[3];
#endif
    }
};