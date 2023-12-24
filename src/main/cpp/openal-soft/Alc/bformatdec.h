#ifndef BFORMATDEC_H
#define BFORMATDEC_H

#include "alMain.h"


/* These are the necessary scales for first-order HF responses to play over
 * higher-order 2D (non-periphonic) decoders.
 */
#define W_SCALE_2H0P   1.224744871f /* sqrt(1.5) */
#define XYZ_SCALE_2H0P 1.0f
#define W_SCALE_3H0P   1.414213562f /* sqrt(2) */
#define XYZ_SCALE_3H0P 1.082392196f

/* These are the necessary scales for first-order HF responses to play over
 * higher-order 3D (periphonic) decoders.
 */
#define W_SCALE_2H2P   1.341640787f /* sqrt(1.8) */
#define XYZ_SCALE_2H2P 1.0f
#define W_SCALE_3H3P   1.695486018f
#define XYZ_SCALE_3H3P 1.136697713f


/* NOTE: These are scale factors as applied to Ambisonics content. Decoder
 * coefficients should be divided by these values to get proper N3D scalings.
 */
static ALfloat N3D2N3DScale[MAX_AMBI_COEFFS] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
static ALfloat SN3D2N3DScale[MAX_AMBI_COEFFS] = {
    1.000000000f, /* ACN  0 (W), sqrt(1) */
    1.732050808f, /* ACN  1 (Y), sqrt(3) */
    1.732050808f, /* ACN  2 (Z), sqrt(3) */
    1.732050808f, /* ACN  3 (X), sqrt(3) */
    2.236067978f, /* ACN  4 (V), sqrt(5) */
    2.236067978f, /* ACN  5 (T), sqrt(5) */
    2.236067978f, /* ACN  6 (R), sqrt(5) */
    2.236067978f, /* ACN  7 (S), sqrt(5) */
    2.236067978f, /* ACN  8 (U), sqrt(5) */
    2.645751311f, /* ACN  9 (Q), sqrt(7) */
    2.645751311f, /* ACN 10 (O), sqrt(7) */
    2.645751311f, /* ACN 11 (M), sqrt(7) */
    2.645751311f, /* ACN 12 (K), sqrt(7) */
    2.645751311f, /* ACN 13 (L), sqrt(7) */
    2.645751311f, /* ACN 14 (N), sqrt(7) */
    2.645751311f, /* ACN 15 (P), sqrt(7) */
};
static ALfloat FuMa2N3DScale[MAX_AMBI_COEFFS] = {
    1.414213562f, /* ACN  0 (W), sqrt(2) */
    1.732050808f, /* ACN  1 (Y), sqrt(3) */
    1.732050808f, /* ACN  2 (Z), sqrt(3) */
    1.732050808f, /* ACN  3 (X), sqrt(3) */
    1.936491673f, /* ACN  4 (V), sqrt(15)/2 */
    1.936491673f, /* ACN  5 (T), sqrt(15)/2 */
    2.236067978f, /* ACN  6 (R), sqrt(5) */
    1.936491673f, /* ACN  7 (S), sqrt(15)/2 */
    1.936491673f, /* ACN  8 (U), sqrt(15)/2 */
    2.091650066f, /* ACN  9 (Q), sqrt(35/8) */
    1.972026594f, /* ACN 10 (O), sqrt(35)/3 */
    2.231093404f, /* ACN 11 (M), sqrt(224/45) */
    2.645751311f, /* ACN 12 (K), sqrt(7) */
    2.231093404f, /* ACN 13 (L), sqrt(224/45) */
    1.972026594f, /* ACN 14 (N), sqrt(35)/3 */
    2.091650066f, /* ACN 15 (P), sqrt(35/8) */
};

struct AmbDecConf;
struct BFormatDec;
struct AmbiUpsampler;


struct BFormatDec *bformatdec_alloc();
void bformatdec_free(struct BFormatDec **dec);
void bformatdec_reset(struct BFormatDec *dec, const struct AmbDecConf *conf, ALsizei chancount, ALuint srate, const ALsizei chanmap[MAX_OUTPUT_CHANNELS]);

/* Decodes the ambisonic input to the given output channels. */
void bformatdec_process(struct BFormatDec *dec, ALfloat (*restrict OutBuffer)[BUFFERSIZE], ALsizei OutChannels, const ALfloat (*restrict InSamples)[BUFFERSIZE], ALsizei SamplesToDo);

/* Up-samples a first-order input to the decoder's configuration. */
void bformatdec_upSample(struct BFormatDec *dec, ALfloat (*restrict OutBuffer)[BUFFERSIZE], const ALfloat (*restrict InSamples)[BUFFERSIZE], ALsizei InChannels, ALsizei SamplesToDo);


/* Stand-alone first-order upsampler. Kept here because it shares some stuff
 * with bformatdec. Assumes a periphonic (4-channel) input mix!
 */
struct AmbiUpsampler *ambiup_alloc();
void ambiup_free(struct AmbiUpsampler **ambiup);
void ambiup_reset(struct AmbiUpsampler *ambiup, const ALCdevice *device, ALfloat w_scale, ALfloat xyz_scale);

void ambiup_process(struct AmbiUpsampler *ambiup, ALfloat (*restrict OutBuffer)[BUFFERSIZE], ALsizei OutChannels, const ALfloat (*restrict InSamples)[BUFFERSIZE], ALsizei SamplesToDo);

#endif /* BFORMATDEC_H */
