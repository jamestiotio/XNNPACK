// Auto-generated file. Do not edit!
//   Template: src/f32-qs8-vcvt/neon.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vcvt.h>


void xnn_f32_qu8_vcvt_ukernel__neon_x32(
    size_t n,
    const float* x,
    uint8_t* y,
    const union xnn_f32_qu8_cvt_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN
{
  assert(n != 0);
  assert(x != NULL);
  assert(y != NULL);

  const float32x4_t vscale = vld1q_dup_f32(&params->neon.scale);
  const float32x4_t vmagic_bias = vld1q_dup_f32(&params->neon.magic_bias);
  const int32x4_t vmagic_bias_less_zero_point = vld1q_dup_s32(&params->neon.magic_bias_less_zero_point);
  const uint8x16_t voutput_min = vld1q_dup_u8(&params->neon.output_min);
  const uint8x16_t voutput_max = vld1q_dup_u8(&params->neon.output_max);
  for (; n >= 32 * sizeof(uint8_t); n -= 32 * sizeof(uint8_t)) {
    float32x4_t vx0123 = vld1q_f32(x); x += 4;
    float32x4_t vx4567 = vld1q_f32(x); x += 4;
    float32x4_t vx89AB = vld1q_f32(x); x += 4;
    float32x4_t vxCDEF = vld1q_f32(x); x += 4;
    float32x4_t vxGHIJ = vld1q_f32(x); x += 4;
    float32x4_t vxKLMN = vld1q_f32(x); x += 4;
    float32x4_t vxOPQR = vld1q_f32(x); x += 4;
    float32x4_t vxSTUV = vld1q_f32(x); x += 4;

    vx0123 = vmulq_f32(vx0123, vscale);
    vx4567 = vmulq_f32(vx4567, vscale);
    vx89AB = vmulq_f32(vx89AB, vscale);
    vxCDEF = vmulq_f32(vxCDEF, vscale);
    vxGHIJ = vmulq_f32(vxGHIJ, vscale);
    vxKLMN = vmulq_f32(vxKLMN, vscale);
    vxOPQR = vmulq_f32(vxOPQR, vscale);
    vxSTUV = vmulq_f32(vxSTUV, vscale);

    vx0123 = vaddq_f32(vx0123, vmagic_bias);
    vx4567 = vaddq_f32(vx4567, vmagic_bias);
    vx89AB = vaddq_f32(vx89AB, vmagic_bias);
    vxCDEF = vaddq_f32(vxCDEF, vmagic_bias);
    vxGHIJ = vaddq_f32(vxGHIJ, vmagic_bias);
    vxKLMN = vaddq_f32(vxKLMN, vmagic_bias);
    vxOPQR = vaddq_f32(vxOPQR, vmagic_bias);
    vxSTUV = vaddq_f32(vxSTUV, vmagic_bias);

    const int32x4_t vacc0123 = vqsubq_s32(vreinterpretq_s32_f32(vx0123), vmagic_bias_less_zero_point);
    const int32x4_t vacc4567 = vqsubq_s32(vreinterpretq_s32_f32(vx4567), vmagic_bias_less_zero_point);
    const int32x4_t vacc89AB = vqsubq_s32(vreinterpretq_s32_f32(vx89AB), vmagic_bias_less_zero_point);
    const int32x4_t vaccCDEF = vqsubq_s32(vreinterpretq_s32_f32(vxCDEF), vmagic_bias_less_zero_point);
    const int32x4_t vaccGHIJ = vqsubq_s32(vreinterpretq_s32_f32(vxGHIJ), vmagic_bias_less_zero_point);
    const int32x4_t vaccKLMN = vqsubq_s32(vreinterpretq_s32_f32(vxKLMN), vmagic_bias_less_zero_point);
    const int32x4_t vaccOPQR = vqsubq_s32(vreinterpretq_s32_f32(vxOPQR), vmagic_bias_less_zero_point);
    const int32x4_t vaccSTUV = vqsubq_s32(vreinterpretq_s32_f32(vxSTUV), vmagic_bias_less_zero_point);

    const int16x8_t vacc01234567 = vcombine_s16(vqmovn_s32(vacc0123), vqmovn_s32(vacc4567));
    const int16x8_t vacc89ABCDEF = vcombine_s16(vqmovn_s32(vacc89AB), vqmovn_s32(vaccCDEF));
    const int16x8_t vaccGHIJKLMN = vcombine_s16(vqmovn_s32(vaccGHIJ), vqmovn_s32(vaccKLMN));
    const int16x8_t vaccOPQRSTUV = vcombine_s16(vqmovn_s32(vaccOPQR), vqmovn_s32(vaccSTUV));

    uint8x16_t vy0123456789ABCDEF = vcombine_u8(vqmovun_s16(vacc01234567), vqmovun_s16(vacc89ABCDEF));
    uint8x16_t vyGHIJKLMNOPQRSTUV = vcombine_u8(vqmovun_s16(vaccGHIJKLMN), vqmovun_s16(vaccOPQRSTUV));

    vy0123456789ABCDEF = vmaxq_u8(vy0123456789ABCDEF, voutput_min);
    vyGHIJKLMNOPQRSTUV = vmaxq_u8(vyGHIJKLMNOPQRSTUV, voutput_min);

    vy0123456789ABCDEF = vminq_u8(vy0123456789ABCDEF, voutput_max);
    vyGHIJKLMNOPQRSTUV = vminq_u8(vyGHIJKLMNOPQRSTUV, voutput_max);

    vst1q_u8(y, vy0123456789ABCDEF); y += 16;
    vst1q_u8(y, vyGHIJKLMNOPQRSTUV); y += 16;
  }
  for (; n >= 8 * sizeof(uint8_t); n -= 8 * sizeof(uint8_t)) {
    float32x4_t vx_lo = vld1q_f32(x); x += 4;
    float32x4_t vx_hi = vld1q_f32(x); x += 4;

    vx_lo = vmulq_f32(vx_lo, vscale);
    vx_hi = vmulq_f32(vx_hi, vscale);

    vx_lo = vaddq_f32(vx_lo, vmagic_bias);
    vx_hi = vaddq_f32(vx_hi, vmagic_bias);

    const int32x4_t vacc_lo = vqsubq_s32(vreinterpretq_s32_f32(vx_lo), vmagic_bias_less_zero_point);
    const int32x4_t vacc_hi = vqsubq_s32(vreinterpretq_s32_f32(vx_hi), vmagic_bias_less_zero_point);

    const int16x8_t vacc = vcombine_s16(vqmovn_s32(vacc_lo), vqmovn_s32(vacc_hi));

    uint8x8_t vy = vqmovun_s16(vacc);
    vy = vmax_u8(vy, vget_low_u8(voutput_min));
    vy = vmin_u8(vy, vget_low_u8(voutput_max));
    vst1_u8(y, vy); y += 8;
  }
  if XNN_UNLIKELY(n != 0) {
    assert(n >= 1 * sizeof(uint8_t));
    assert(n <= 7 * sizeof(uint8_t));
    float32x4_t vx_lo = vld1q_f32(x);
    const float* x_hi = x + 4;
    if XNN_UNPREDICTABLE((n & (4 * sizeof(uint8_t))) == 0) {
      x_hi = x;
    }
    float32x4_t vx_hi = vld1q_f32(x_hi);

    vx_lo = vmulq_f32(vx_lo, vscale);
    vx_hi = vmulq_f32(vx_hi, vscale);

    vx_lo = vaddq_f32(vx_lo, vmagic_bias);
    vx_hi = vaddq_f32(vx_hi, vmagic_bias);

    const int32x4_t vacc_lo = vqsubq_s32(vreinterpretq_s32_f32(vx_lo), vmagic_bias_less_zero_point);
    const int32x4_t vacc_hi = vqsubq_s32(vreinterpretq_s32_f32(vx_hi), vmagic_bias_less_zero_point);

    const int16x8_t vacc = vcombine_s16(vqmovn_s32(vacc_lo), vqmovn_s32(vacc_hi));

    uint8x8_t vy = vqmovun_s16(vacc);
    vy = vmax_u8(vy, vget_low_u8(voutput_min));
    vy = vmin_u8(vy, vget_low_u8(voutput_max));

    if (n & (4 * sizeof(uint8_t))) {
      vst1_lane_u32((void*) y, vreinterpret_u32_u8(vy), 0); y += 4;
      vy = vext_u8(vy, vy, 4);
    }
    if (n & (2 * sizeof(uint8_t))) {
      vst1_lane_u16((void*) y, vreinterpret_u16_u8(vy), 0); y += 2;
      vy = vext_u8(vy, vy, 2);
    }
    if (n & (1 * sizeof(uint8_t))) {
      vst1_lane_u8(y, vy, 0);
    }
  }
}
