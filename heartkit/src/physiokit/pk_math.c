/**
 * @file pk_math.c
 * @author Adam Page (adam.page@ambiq.com)
 * @brief PhysioKit: Math
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <math.h>
#include "arm_math.h"

#include "pk_math.h"

uint32_t
pk_mean_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize)
{
    /**
     * @brief Compute mean of signal
     *
     */
    arm_mean_f32(pSrc, blockSize, pResult);
    return 0;
}

uint32_t
pk_std_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize)
{
    /**
     * @brief Compute standard deviation of signal
     *
     */
    arm_std_f32(pSrc, blockSize, pResult);
    return 0;
}


uint32_t
pk_gradient_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize)
{
    /**
     * @brief Compute gradient of signal using forward, centered, and backward difference
     *
     */
    for (size_t i = 1; i < blockSize - 1; i++)
    {
        pResult[i] = (pSrc[i + 1] - pSrc[i - 1]) / 2.0;
    }
    // Edge cases: Use forward and backward difference
    pResult[0] = (-3 * pSrc[0] + 4 * pSrc[1] - pSrc[2]) / 2.0;
    pResult[blockSize - 1] = (3 * pSrc[blockSize - 1] - 4 * pSrc[blockSize - 2] + pSrc[blockSize - 3]) / 2.0;
    return 0;
}

uint32_t
pk_rms_f32(float32_t *pSrc, float32_t *pResult, uint32_t blockSize)
{
    /**
     * @brief Compute root mean square of signal
     *
     */
    arm_rms_f32(pSrc, blockSize, pResult);
    return 0;
}

uint32_t
pk_next_power_of_2(uint32_t val) {
    uint32_t n = 1;
    while (n < val) { n <<= 1; }
    return n;
}


uint32_t
cosine_similarity_f32(
    float32_t *ref,
    float32_t *sig,
    size_t len,
    float32_t *result
) {
    float32_t dot = 0.0f, normA = 0.0f, normB = 0.0f;
    arm_dot_prod_f32(ref, sig, len, &dot);
    arm_dot_prod_f32(ref, ref, len, &normA);
    arm_dot_prod_f32(sig, sig, len, &normB);
    *result = dot / (sqrtf(normA) * sqrtf(normB));
    return 0;
}
