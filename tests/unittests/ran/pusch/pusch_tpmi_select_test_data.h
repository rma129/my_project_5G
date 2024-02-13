/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#pragma once

// This file was generated using the following MATLAB class on 20-02-2024 (seed 0):
//   + "srsTPMISelectUnittest.m"

#include "srsran/ran/pusch/pusch_tpmi_select.h"
#include "srsran/ran/srs/srs_channel_matrix.h"

namespace srsran {

struct test_case_t {
  srs_channel_matrix     channel_matrix;
  float                  noise_variance;
  pusch_tpmi_select_info info;
};

static const std::vector<test_case_t> pusch_tpmi_select_test_data = {
    // clang-format off
{srs_channel_matrix({cf_t(0.537667, -2.258847), cf_t(1.833885, 0.862173)}, 1, 2), 1.9904, {{5, 6.721121},}},
{srs_channel_matrix({cf_t(-1.307688, 0.342624), cf_t(-0.433592, 3.578397)}, 1, 2), 0.15523, {{4, 18.860710},}},
{srs_channel_matrix({cf_t(-1.349887, 0.725404), cf_t(3.034923, -0.063055)}, 1, 2), 0.96758, {{3, 10.110059},}},
{srs_channel_matrix({cf_t(-0.204966, 1.489698), cf_t(-0.124144, 1.409034)}, 1, 2), 0.17958, {{2, 13.746798},}},
{srs_channel_matrix({cf_t(0.671497, 0.717239), cf_t(-1.207487, 1.630235)}, 1, 2), 1.683, {{5, 4.272519},}},
{srs_channel_matrix({cf_t(1.034693, -0.303441), cf_t(0.726885, 0.293871)}, 1, 2), 7.6653, {{2, -6.937425},}},
{srs_channel_matrix({cf_t(0.888396, -1.068870), cf_t(-1.147070, -0.809499)}, 1, 2), 10.1264, {{4, -4.147666},}},
{srs_channel_matrix({cf_t(1.438380, -0.754928), cf_t(0.325191, 1.370299)}, 1, 2), 14.6286, {{5, -5.093284},}},
{srs_channel_matrix({cf_t(-0.102242, 0.319207), cf_t(-0.241447, 0.312859)}, 1, 2), 7.2845, {{2, -14.494137},}},
{srs_channel_matrix({cf_t(-0.030051, 0.627707), cf_t(-0.164879, 1.093266)}, 1, 2), 1.2223, {{2, 0.888649},}},
{srs_channel_matrix({cf_t(-0.863653, -1.214117), cf_t(0.077359, -1.113501)}, 1, 2), 3.0245, {{2, -0.009346},}},
{srs_channel_matrix({cf_t(1.532630, 0.371379), cf_t(-0.769666, -0.225584)}, 1, 2), 1.2421, {{3, 3.574097},}},
{srs_channel_matrix({cf_t(-1.089064, 0.552527), cf_t(0.032557, 1.100610)}, 1, 2), 0.18049, {{4, 11.532158},}},
{srs_channel_matrix({cf_t(0.085931, -0.742302), cf_t(-1.491590, -1.061582)}, 1, 2), 0.7535, {{4, 6.217135},}},
{srs_channel_matrix({cf_t(-0.615602, -0.192419), cf_t(0.748077, 0.888610)}, 1, 2), 4.5595, {{3, -4.787585},}},
{srs_channel_matrix({cf_t(-1.402269, 0.488194), cf_t(-1.422376, -0.177375)}, 1, 2), 4.5388, {{2, -0.508140},}},
{srs_channel_matrix({cf_t(1.419310, -0.804466),  cf_t(0.291584, 0.696624),  cf_t(0.197811, 0.835088), cf_t(1.587699, -0.243715)}, 2, 2), 2.4579, {{5, 1.461981},{1, -1.769549},}},
{srs_channel_matrix({cf_t(-1.165844, 2.585491), cf_t(-1.147953, -0.666891),   cf_t(0.104875, 0.187331), cf_t(0.722254, -0.082494)}, 2, 2), 19.2438, {{3, -5.359049},{0, -8.704529},}},
{srs_channel_matrix({cf_t(-0.438966, 0.100093), cf_t(-1.794679, -0.544529),   cf_t(0.840376, 0.303521), cf_t(-0.888032, -0.600327)}, 2, 2), 1.8437, {{2, 3.793230},{1, -1.381617},}},
{srs_channel_matrix({cf_t(0.739363, -0.839589),   cf_t(1.711888, 1.354594), cf_t(-0.194124, -1.072155), cf_t(-2.138355, 0.960954)}, 2, 2), 2.6894, {{5, 5.675573},{1, -0.127439},}},
{srs_channel_matrix({cf_t(1.436697, 2.908008), cf_t(-1.960900, 0.825219), cf_t(-0.197698, 1.378972), cf_t(-1.207845, -1.058180)}, 2, 2), 3.9818, {{5, 5.877500},{0, -1.128085},}},
{srs_channel_matrix({cf_t(-0.272469, -2.051816),  cf_t(1.098425, -0.353850), cf_t(-0.277872, -0.823587), cf_t(0.701541, -1.577057)}, 2, 2), 0.60834, {{2, 11.062479}, {1, 4.810719},}},
{srs_channel_matrix({cf_t(0.281984, 0.350179), cf_t(0.033480, -0.299066), cf_t(-1.333678, 0.022890), cf_t(1.127492, -0.261995)}, 2, 2), 11.1938, {{5, -6.496824},{0, -11.256090},}},
{srs_channel_matrix({cf_t(-0.285651, -0.533557), cf_t(-0.831367, -2.002636),  cf_t(-0.979206, 0.964229), cf_t(-1.156402, 0.520060)}, 2, 2), 3.0904, {{4, 4.036525},{0, -3.047601},}},
{srs_channel_matrix({cf_t(-0.034771, -0.714530),  cf_t(-0.798164, 1.351386),  cf_t(1.018685, -0.224771), cf_t(-0.133217, -0.589029)}, 2, 2), 3.9371, {{5, -0.388925},{0, -5.971891},}},
{srs_channel_matrix({cf_t(-0.847926, 0.307535), cf_t(-1.120128, -1.257118),  cf_t(2.526000, -0.865468), cf_t(1.655498, -0.176534)}, 2, 2), 0.85554, {{3, 11.018067}, {1, 4.222248},}},
{srs_channel_matrix({cf_t(-1.332004, 0.391354),  cf_t(-2.329867, 0.451679), cf_t(-1.449097, -0.130285), cf_t(0.333511, 0.183689)}, 2, 2), 5.2824, {{2, 0.622089},{0, -3.412172},}},
{srs_channel_matrix({cf_t(0.862022, -0.334887), cf_t(-1.361694, 0.552783),  cf_t(0.455030, 1.039091), cf_t(-0.848709, -1.117639)}, 2, 2), 0.31804, {{5, 12.881381},{1, -0.090114},}},
{srs_channel_matrix({cf_t(0.660143, -0.303108), cf_t(-0.067866, 0.023046), cf_t(-0.195221, 0.051290), cf_t(-0.217606, 0.826063)}, 2, 2), 0.99725, {{3, -1.167051},{0, -4.904117},}},
{srs_channel_matrix({cf_t(0.466914, -1.029768), cf_t(-0.209713, 0.949222),  cf_t(0.625190, 0.307062), cf_t(0.183227, 0.135175)}, 2, 2), 2.0588, {{5, -0.202222},{0, -4.954878},}},
{srs_channel_matrix({cf_t(0.261406, -0.532011),  cf_t(-0.941486, 1.682104), cf_t(-0.162338, -0.875729), cf_t(-0.146055, -0.483815)}, 2, 2), 7.6775, {{5, -4.163022},{0, -7.803920},}},
{srs_channel_matrix({cf_t(-1.174212, -0.249025), cf_t(-0.192240, -1.064213),  cf_t(-0.274070, 1.603457), cf_t(1.530073, 1.234679)}, 2, 2), 3.5766, {{3, 2.421687},{0, -2.226541},}},
{srs_channel_matrix({cf_t(-1.506160, -0.947961), cf_t(-0.444628, -0.741106), cf_t(-0.155941, -0.507818),  cf_t(0.276068, -0.320576),  cf_t(-0.261164, 0.012469),  cf_t(0.443422, -3.029177),  cf_t(0.391894, -0.457015), cf_t(-1.250679, 1.242448)}, 4, 2), 15.3432, {{2, -1.647274},{0, -5.581959},}},
{srs_channel_matrix({cf_t(0.933728, 0.041374),  cf_t(0.350321, -0.734169), cf_t(-0.029006, -0.030814),   cf_t(0.182452, 0.232347),  cf_t(-1.565056, 0.426388), cf_t(-0.084539, -0.372809),  cf_t(1.603946, -0.236455), cf_t(0.098348, 2.023691)}, 4, 2), 14.2321, {{3, -3.526674},{0, -7.109971},}},
{srs_channel_matrix({cf_t(2.229446, 0.471634), cf_t(0.337564, -1.212847),  cf_t(1.000061, 0.066190), cf_t(-1.664164, 0.652356), cf_t(-0.590035, 0.327060), cf_t(-0.278064, 1.082634),  cf_t(0.422716, 1.006077), cf_t(-1.670201, -0.650908)}, 4, 2), 1.5568, {{5, 9.125793},{0, 3.495892},}},
{srs_channel_matrix({cf_t(-0.944378, 1.250251),  cf_t(-1.321789, 0.929789),   cf_t(0.924826, 0.239763),  cf_t(0.000050, -0.690361), cf_t(-0.054919, -0.651554),   cf_t(0.911127, 1.192102),  cf_t(0.594584, -1.611830), cf_t(0.350201, -0.024462)}, 4, 2), 7.7488, {{4, 0.762089},{1, -4.385994},}},
{srs_channel_matrix({cf_t(1.020498, 0.079934), cf_t(0.861716, -0.948481),  cf_t(0.001162, 0.411491), cf_t(-0.070837, 0.676978), cf_t(-2.486284, 0.857733), cf_t(0.581172, -0.691159), cf_t(-2.192435, 0.449378), cf_t(-2.319280, 0.100633)}, 4, 2), 0.11899, {{5, 20.774681},{0, 15.551061},}},
{srs_channel_matrix({cf_t(0.536157, -0.382585),   cf_t(0.897888, 0.648679),  cf_t(-0.131938, 0.825727), cf_t(-0.147201, -1.014944),  cf_t(1.007773, -0.471070),  cf_t(-2.123655, 0.137025), cf_t(-0.504586, -0.291863), cf_t(-1.270594, 0.301819)}, 4, 2), 2.0206, {{3, 5.397915},{0, 1.208681},}},
{srs_channel_matrix({cf_t(-0.929962, -0.020858), cf_t(-0.176830, -0.560665),  cf_t(-2.132095, 2.177779),   cf_t(1.145362, 1.138465), cf_t(-0.629091, -2.496887),  cf_t(-1.203850, 0.441327), cf_t(-0.253945, -1.398138), cf_t(-1.428647, -0.255055)}, 4, 2), 2.6132, {{5, 8.656211},{1, 2.963929},}},
{srs_channel_matrix({cf_t(0.747734, 0.323213), cf_t(-0.273047, -0.784146),  cf_t(1.576300, -1.805373),  cf_t(-0.480937, 1.858593),  cf_t(0.327512, -0.604530),   cf_t(0.664734, 0.103360),   cf_t(0.085189, 0.563167), cf_t(0.880953, 0.113597)}, 4, 2), 7.2026, {{3, 0.300607},{0, -3.592447},}},
{srs_channel_matrix({cf_t(-0.467715, -0.284141), cf_t(-0.124890, -0.086690),  cf_t(1.478958, -1.469395),  cf_t(-0.860816, 0.192182),  cf_t(0.784668, -0.822293),  cf_t(0.308623, -0.094241),  cf_t(-0.233860, 0.336213), cf_t(-1.056973, -0.904654)}, 4, 2), 5.3694, {{5, 0.662797},{0, -4.016587},}},
{srs_channel_matrix({cf_t(0.350063, 1.877865),  cf_t(-1.835859, 0.940704),   cf_t(1.035976, 0.787346),  cf_t(2.424461, -0.875874),   cf_t(0.959401, 0.319949), cf_t(-0.315772, -0.558294),  cf_t(0.428623, -0.311429), cf_t(-1.035985, -0.570010)}, 4, 2), 7.9187, {{4, 2.151205},{0, -2.364794},}},
{srs_channel_matrix({cf_t(-0.908746, -1.483121), cf_t(-0.209897, -1.020264), cf_t(-1.698864, -0.446995),   cf_t(0.607601, 0.109659),  cf_t(-0.117798, 1.128736),  cf_t(0.699160, -0.289963),   cf_t(0.269649, 1.261551), cf_t(0.494287, 0.475425)}, 4, 2), 0.13833, {{4, 17.622018},{1, 11.883528},}},
{srs_channel_matrix({cf_t(0.126947, -1.096593), cf_t(-0.656816, -0.493010), cf_t(-1.481399, -0.180739),   cf_t(0.155489, 0.045841),  cf_t(0.818551, -0.063783),  cf_t(-0.292588, 0.611335),  cf_t(-0.540786, 0.109318), cf_t(-0.308642, 1.814015)}, 4, 2), 1.9538, {{2, 4.388034},{1, 0.568394},}},
{srs_channel_matrix({cf_t(1.804494, -1.441014),  cf_t(-0.723121, 0.401844),   cf_t(0.526547, 1.470201), cf_t(-0.260251, -0.326814),   cf_t(0.600143, 0.812323),   cf_t(0.593931, 0.545540), cf_t(-2.186022, -1.051632), cf_t(-1.327043, 0.397467)}, 4, 2), 4.1255, {{5, 4.941982},{1, -0.039744},}},
{srs_channel_matrix({cf_t(1.516267, 0.612511), cf_t(-0.032567, -0.054886),  cf_t(1.636000, -1.118732), cf_t(-0.425058, -0.626379),   cf_t(0.589433, 0.249518), cf_t(-0.062791, -0.993019),  cf_t(-2.021959, 0.974950), cf_t(-0.982132, -0.640710)}, 4, 2), 0.3743, {{3, 14.256197}, {1, 9.925905},}},
{srs_channel_matrix({cf_t(-1.079866, -0.373071),   cf_t(0.199189, 0.815489),  cf_t(-1.521027, 0.798887),  cf_t(-0.723631, 0.120205),  cf_t(-0.593250, 0.571248),   cf_t(0.401336, 0.412796),  cf_t(0.942133, -0.986962), cf_t(0.300486, 0.759568)}, 4, 2), 6.2666, {{3, -0.172373},{1, -4.533946},}},
{srs_channel_matrix({cf_t(-0.603918, -0.238302),   cf_t(0.176947, 0.229597),  cf_t(-0.307503, 0.439998), cf_t(-0.131820, -0.616866),   cf_t(0.595358, 0.274837),   cf_t(1.046833, 0.601102),  cf_t(-0.197959, 0.092308), cf_t(0.327678, 1.729841)}, 4, 2), 5.7712, {{3, -1.355727},{0, -5.813710},}},
{srs_channel_matrix({cf_t(-0.737060, -0.079893),  cf_t(-1.749879, 0.898476),   cf_t(0.910483, 0.183703), cf_t(0.867083, 0.290790)}, 1, 4), 2.6449, {{14, 2.380825},}},
{srs_channel_matrix({cf_t(0.439952, -1.854299), cf_t(0.101662, -1.140681), cf_t(2.787335, -1.093343), cf_t(-1.166665, -0.433609)}, 1, 4), 3.4836, {{16, 4.487145},}},
{srs_channel_matrix({cf_t(-0.218534, 1.778256),  cf_t(0.541334, 1.223063), cf_t(0.389266, -1.283256), cf_t(0.751229, -2.328955)}, 1, 4), 1.5722, {{14, 8.488748},}},
{srs_channel_matrix({cf_t(-1.835639, -0.069214),  cf_t(0.066757, -0.507323),   cf_t(0.035479, 0.235810), cf_t(2.227168, 0.245805)}, 1, 4), 2.8395, {{27, 2.225421},}},
{srs_channel_matrix({cf_t(-0.608581, -1.032184),  cf_t(-1.222593, 1.331216),  cf_t(0.316500, -0.418903), cf_t(-1.342869, -0.140322)}, 1, 4), 1.6254, {{19, 5.103215},}},
{srs_channel_matrix({cf_t(-0.300111, 0.629335),  cf_t(1.029366, -0.213015), cf_t(-0.345066, -0.865697), cf_t(1.012802, -1.043108)}, 1, 4), 3.7232, {{24, -2.281627},}},
{srs_channel_matrix({cf_t(-0.438141, 1.143679), cf_t(-0.408674, -0.531620),   cf_t(0.983545, 0.972566), cf_t(-0.297697, -0.522250)}, 1, 4), 0.92312, {{20, 4.977579},}},
{srs_channel_matrix({cf_t(0.970738, 0.950993), cf_t(-0.413972, -0.432004),  cf_t(-0.438271, 0.648941), cf_t(2.003391, -0.360076)}, 1, 4), 0.79094, {{23, 8.085299},}},
{srs_channel_matrix({cf_t(1.415849, 0.047471), cf_t(-1.604516, 1.746257),  cf_t(1.028853, 0.155388), cf_t(1.457968, -1.237120)}, 1, 4), 6.9927, {{25, -1.039307},}},
{srs_channel_matrix({cf_t(-0.333407, -0.577086),   cf_t(0.713543, 0.144002),  cf_t(0.317408, -1.638666), cf_t(0.413610, -0.760090)}, 1, 4), 8.6553, {{24, -4.758370},}},
{srs_channel_matrix({cf_t(0.519729, -0.689811), cf_t(-0.014160, -0.666699),  cf_t(-1.155529, 0.864149), cf_t(-0.009525, 0.113419)}, 1, 4), 0.317, {{18, 8.241568},}},
{srs_channel_matrix({cf_t(0.883970, 1.170609), cf_t(0.180258, 0.475861), cf_t(0.550855, 1.412233), cf_t(0.682964, 0.022608)}, 1, 4), 3.1919, {{12, 0.634324},}},
{srs_channel_matrix({cf_t(1.701335, 0.149809), cf_t(-0.509712, 1.404933), cf_t(-0.002855, 1.034122), cf_t(0.919867, 0.291570)}, 1, 4), 6.0777, {{22, -2.455675},}},
{srs_channel_matrix({cf_t(0.566696, 0.213042), cf_t(-1.382621, 0.879677),  cf_t(0.244475, 2.038876), cf_t(0.808439, 0.923932)}, 1, 4), 2.3549, {{13, 3.020281},}},
{srs_channel_matrix({cf_t(0.641662, 1.224688), cf_t(0.425485, -0.043584), cf_t(-1.314724, 0.582423), cf_t(-0.416411, -1.006500)}, 1, 4), 2.5783, {{27, 0.760560},}},
{srs_channel_matrix({cf_t(0.600292, -0.939535), cf_t(-1.361515, -0.037533),  cf_t(0.347593, -1.896304), cf_t(-0.181843, -2.127977)}, 1, 4), 6.872, {{16, 0.213123},}},
{srs_channel_matrix({cf_t(-0.990532, 0.093109), cf_t(-1.173032, -0.378157), cf_t(-1.725428, -1.482676),  cf_t(0.288228, -0.043819),  cf_t(-1.594184, 0.960825),   cf_t(0.110219, 1.738245),  cf_t(0.787067, -0.430206), cf_t(-0.002227, -1.627323)}, 2, 4), 2.4797, {{24, 5.197610},{20, 0.186947},}},
{srs_channel_matrix({cf_t(0.376266, 0.317851),  cf_t(-0.226950, 0.138048), cf_t(-1.148912, -0.710735),   cf_t(2.024333, 0.777004),  cf_t(-2.359524, 0.622394),  cf_t(-0.509972, 0.647381), cf_t(-1.321626, -0.425632), cf_t(-0.636128, 1.048581)}, 2, 4), 0.29465, {{27, 14.044752}, {10, 8.625050},}},
{srs_channel_matrix({cf_t(2.508772, 0.555139),  cf_t(1.063460, -0.556778),  cf_t(1.156922, -0.895113),  cf_t(0.052979, -0.409328), cf_t(-1.288386, -0.160887),  cf_t(-0.371221, 0.409334), cf_t(-0.757792, -0.952636), cf_t(-0.563969, 0.317317)}, 2, 4), 2.5256, {{14, 6.008590},{10, -0.503156},}},
{srs_channel_matrix({cf_t(1.324385, -0.892661),  cf_t(-0.213170, 1.908512),  cf_t(-0.134479, 0.122231),  cf_t(-1.171356, 1.047033), cf_t(-1.385263, -0.226920),  cf_t(0.310508, -0.162502),  cf_t(-0.249489, 0.690052), cf_t(0.503744, 0.555757)}, 2, 4), 9.9904, {{13, -2.271692},{11, -6.442332},}},
{srs_channel_matrix({cf_t(-1.532693, 0.439411), cf_t(-1.097868, -0.089622),  cf_t(-1.415773, 1.021180),  cf_t(0.059571, -0.873979),  cf_t(-0.411251, 0.414700),  cf_t(-0.368011, 0.348441),  cf_t(-1.360963, 0.349254), cf_t(0.779567, -0.729247)}, 2, 4), 2.2387, {{12, 5.167847},{12, -0.439300},}},
{srs_channel_matrix({cf_t(-0.514882, -3.232038), cf_t(-0.896446, -1.086959), cf_t(-1.203268, -1.426436),  cf_t(1.037816, -1.014451), cf_t(-0.845944, -0.213267), cf_t(-0.172914, -0.325348),  cf_t(-1.208652, 1.944398), cf_t(-0.297127, -0.571773)}, 2, 4), 5.2674, {{13, 4.869396},{15, -1.373769},}},
{srs_channel_matrix({cf_t(-1.569315, 1.460013),  cf_t(-0.477383, 2.050043),  cf_t(-1.337977, 0.120501),  cf_t(0.030299, -0.989902),   cf_t(0.853087, 1.197771),  cf_t(0.404253, -0.592656), cf_t(-0.700620, -0.469809), cf_t(-1.630543, 0.886377)}, 2, 4), 19.8562, {{21, -3.125471},{13, -7.925554},}},
{srs_channel_matrix({cf_t(-1.956754, 0.809972),  cf_t(0.420684, 0.173247), cf_t(0.400738, -0.505543), cf_t(0.095142, -1.193306),  cf_t(0.496684, 0.646971), cf_t(1.082241, -0.353623),  cf_t(0.970448, 0.046435), cf_t(-0.568570, -0.792948)}, 2, 4), 8.9317, {{17, -1.874603},{12, -6.904876},}},
{srs_channel_matrix({cf_t(0.171586, 0.497981),  cf_t(-0.062139, 2.789081),   cf_t(1.199028, 0.727572),  cf_t(0.801704, -0.773064),   cf_t(1.053305, 0.836634), cf_t(-0.748877, -1.128330), cf_t(-0.936326, -1.424470), cf_t(-1.269087, 0.717442)}, 2, 4), 4.8305, {{18, 4.384766},{16, -1.026578},}},
{srs_channel_matrix({cf_t(0.315986, -1.540877), cf_t(1.406535, -0.203143), cf_t(0.401125, -0.499965),  cf_t(0.929660, 0.383024), cf_t(-1.605802, 0.412035),  cf_t(0.661536, 0.405493), cf_t(2.138502, -0.363781), cf_t(0.541139, -0.599272)}, 2, 4), 10.6215, {{21, -2.455953},{12, -6.737523},}},
{srs_channel_matrix({cf_t(0.853541, 0.161364), cf_t(-1.853008, -0.268183), cf_t(-0.207303, -0.409873),  cf_t(0.270378, -0.711323),  cf_t(-0.652771, 0.061445),  cf_t(0.477227, -1.846129), cf_t(-0.071320, -0.398333), cf_t(-0.938301, -0.543548)}, 2, 4), 9.4968, {{22, -3.176380}, {8, -6.338377},}},
{srs_channel_matrix({cf_t(0.652699, 0.540870), cf_t(-0.734271, -1.262565),   cf_t(0.540633, 1.110424),  cf_t(0.975841, -0.989563), cf_t(-0.156870, -1.828836),   cf_t(0.277799, 1.384499),  cf_t(0.639517, -0.062727), cf_t(-0.080978, 0.448921)}, 2, 4), 4.023, {{25, 2.764149},{21, -2.556165},}},
{srs_channel_matrix({cf_t(-1.020583, 1.147328),  cf_t(-3.072989, 0.597865),  cf_t(0.626279, -1.281281), cf_t(-0.286685, -2.203264), cf_t(-0.197343, -0.571246),   cf_t(0.405605, 0.213996),  cf_t(-1.419348, 0.942377), cf_t(-0.729445, 0.093725)}, 2, 4), 9.633, {{25, 1.312246},{21, -4.520607},}},
{srs_channel_matrix({cf_t(0.306158, -0.462422), cf_t(-1.172335, -0.409785), cf_t(-0.960967, -0.503539),  cf_t(-0.653735, 1.233297),  cf_t(-1.229394, 0.610305),  cf_t(-0.270965, 0.059072), cf_t(-0.899950, -1.466947), cf_t(-0.285686, -1.625803)}, 2, 4), 11.1156, {{22, -3.914039},{10, -7.170668},}},
{srs_channel_matrix({cf_t(2.605196, -0.449397),  cf_t(0.972375, -0.084292),  cf_t(0.256981, -1.991997),  cf_t(-0.974240, 0.841246), cf_t(-1.146364, -0.414659),   cf_t(0.547640, 1.912181),  cf_t(1.565084, -0.390899), cf_t(-1.693344, 0.409182)}, 2, 4), 8.1144, {{23, 1.459961},{10, -3.440890},}},
{srs_channel_matrix({cf_t(-0.624864, 1.196251),  cf_t(-1.168723, 0.120283),  cf_t(0.392575, -1.036843),  cf_t(1.301840, -0.857103), cf_t(-0.593642, -0.169874),  cf_t(0.436375, -0.191668), cf_t(-0.504362, -0.865815), cf_t(0.102108, 0.180664)}, 2, 4), 1.2928, {{27, 4.767162},{21, -0.505018},}},
{srs_channel_matrix({cf_t(-0.251169, 0.540364), cf_t(-0.204570, -0.091539), cf_t(-2.201522, -0.760252), cf_t(-0.774513, -0.693595),  cf_t(-1.393273, 1.281458), cf_t(-0.386235, -0.809738),  cf_t(0.525586, -1.236818),   cf_t(1.523269, 0.214686),   cf_t(1.798494, 2.010772),  cf_t(-0.116884, 0.025554),  cf_t(-0.320196, 0.308299),  cf_t(0.817516, -0.938247),   cf_t(0.490159, 1.674216),   cf_t(0.765251, 0.124988),   cf_t(0.778279, 0.530101), cf_t(-1.480305, -0.952068)}, 4, 4), 0.91942, {{13, 12.328757}, {20, 7.065233},  {6, 4.488540},  {3, 0.803254},}},
{srs_channel_matrix({cf_t(0.389146, -0.698654),  cf_t(-1.156001, 0.832771),  cf_t(0.039740, -0.694605), cf_t(-0.450599, -0.461883),   cf_t(0.109248, 0.883617),  cf_t(-0.250553, 0.435944),  cf_t(-0.189902, 0.896747),  cf_t(-1.032914, 0.504732), cf_t(-0.323292, -0.400897),  cf_t(0.766527, -0.513848),   cf_t(1.744673, 0.796368), cf_t(-1.160520, -0.671190),   cf_t(2.377412, 1.186659),   cf_t(1.526078, 0.790702),   cf_t(0.168508, 0.287721), cf_t(-0.301207, 0.003226)}, 4, 4), 1.9677, {{13, 5.706799},{11, 2.835869},{2, -0.185431},{0, -1.776047},}},
{srs_channel_matrix({cf_t(3.526678, 1.768992),  cf_t(-0.112437, 1.510582),  cf_t(-1.556594, 0.164010),  cf_t(1.915102, -0.282764),   cf_t(0.609846, 1.152166), cf_t(-0.647912, -1.146508),   cf_t(2.617335, 0.673699),  cf_t(0.550950, -0.669113),  cf_t(0.294204, -0.400323), cf_t(-0.777844, -0.671802),  cf_t(-1.064930, 0.575629), cf_t(-1.768414, -0.778094), cf_t(-0.422920, -1.063561),  cf_t(-1.053102, 0.552978),  cf_t(0.647755, -0.423429), cf_t(-0.317628, 0.361587)}, 4, 4), 4.1582, {{17, 5.955043},{11, 2.239470},{2, -0.289404},{0, -2.073018},}},
{srs_channel_matrix({cf_t(0.269541, -1.323334), cf_t(-2.564449, 0.128340), cf_t(0.465864, -1.442379),  cf_t(1.853561, 1.302508),  cf_t(1.039289, 1.409912), cf_t(0.910897, -1.662543), cf_t(-0.239731, 1.943684), cf_t(0.180998, -1.084698),  cf_t(0.244250, 0.226819),  cf_t(0.096393, 1.098929), cf_t(-0.830468, 0.147189), cf_t(-0.352252, 2.295666), cf_t(-0.174775, 2.752558), cf_t(-0.480653, 0.138318), cf_t(0.836837, -1.907066), cf_t(2.538349, -0.364993)}, 4, 4), 7.3959, {{23, 4.624214},{19, 0.892043},{5, -2.032019},{3, -4.024456},}},
{srs_channel_matrix({cf_t(-0.764753, 0.067454), cf_t(-1.127695, -0.187121),   cf_t(0.078189, 0.291727),   cf_t(2.106630, 0.987695),  cf_t(-0.715847, 0.392935),  cf_t(-0.280516, 0.194551),   cf_t(1.166475, 0.279785),   cf_t(1.212821, 0.051220),  cf_t(0.485541, -0.774466),   cf_t(1.026016, 0.786782),   cf_t(0.870726, 1.408907), cf_t(-0.381758, -0.534099),   cf_t(0.428893, 1.927758), cf_t(-0.299131, -0.176248), cf_t(-0.899869, -0.243750), cf_t(0.634745, -0.897601)}, 4, 4), 9.0082, {{26, 0.319062},{11, -3.932389}, {2, -6.367418}, {2, -8.503519},}},
{srs_channel_matrix({cf_t(-0.952975, -1.633802),   cf_t(0.353905, 0.761200),   cf_t(1.597026, 1.193307),   cf_t(0.527470, 1.632057),  cf_t(0.854202, -1.532190),  cf_t(1.341847, -1.336852), cf_t(-2.499533, -1.473846), cf_t(-0.167559, -0.041663),  cf_t(0.353015, -0.615507),   cf_t(0.717254, 1.314155), cf_t(-1.304852, -1.455067), cf_t(-1.005869, -1.742349),   cf_t(0.790683, 0.205305),  cf_t(-0.116571, 1.192930),  cf_t(0.553090, -0.802823), cf_t(-0.960645, -1.265636)}, 4, 4), 4.6986, {{27, 6.537971},{10, 1.141677},{2, -1.575251},{2, -3.747263},}},
{srs_channel_matrix({cf_t(-1.636447, 0.490752), cf_t(0.017344, -0.586126),  cf_t(0.828387, 0.744900), cf_t(0.217738, -0.828155), cf_t(-1.909245, 0.574521), cf_t(-0.536822, 0.281841), cf_t(-0.302032, 1.139306), cf_t(1.813582, -0.425868),  cf_t(0.914852, 0.636140), cf_t(-0.057081, 0.793178), cf_t(1.309362, -0.898377), cf_t(-1.044736, 0.156245), cf_t(-0.348267, 1.597254),  cf_t(1.412561, 0.112440), cf_t(1.502383, -0.308625), cf_t(0.730376, 0.456660)}, 4, 4), 4.4293, {{13, 5.887188},{15, 0.572613},{4, -2.557978},{2, -5.054490},}},
{srs_channel_matrix({cf_t(0.443144, -0.870563), cf_t(-0.134765, -0.497688), cf_t(-0.018328, -0.106672),  cf_t(0.460789, -0.687829),   cf_t(1.362315, 0.331881),   cf_t(0.451875, 2.365225),  cf_t(1.648384, -0.482231),  cf_t(-2.028362, 0.647448), cf_t(-0.449257, -1.034425),   cf_t(0.235993, 1.339555), cf_t(-0.835173, -0.969140),  cf_t(-1.275955, 0.208716),  cf_t(0.617035, -0.618593),   cf_t(0.612702, 0.512016),   cf_t(0.289381, 0.011354), cf_t(0.395316, -0.043989)}, 4, 4), 0.56976, {{17, 12.293614}, {12, 8.270981},  {1, 4.459924},  {0, 1.953526},}},
{srs_channel_matrix({cf_t(-0.630046, -0.296348), cf_t(-0.046879, -1.496919),  cf_t(2.683026, -0.904834), cf_t(-1.146691, -0.404182),  cf_t(0.552999, -0.725798), cf_t(-1.076458, -0.866485),  cf_t(1.030640, -0.421847),  cf_t(0.327530, -0.942666),   cf_t(0.652125, 1.341884), cf_t(-0.278861, -0.988435),   cf_t(0.245192, 1.817943),  cf_t(1.472513, -0.374437), cf_t(-2.275102, -1.451741), cf_t(-1.633291, -0.618682),   cf_t(0.415469, 0.934501), cf_t(-0.654769, 1.055929)}, 4, 4), 2.6368, {{15, 7.441655}, {8, 3.113279}, {4, 0.890923},{0, -1.480045},}},
{srs_channel_matrix({cf_t(0.287400, 0.384707),   cf_t(0.632906, 0.696367), cf_t(-1.459042, -0.112716), cf_t(-0.581710, -0.038824),  cf_t(-1.830149, 0.088089), cf_t(-0.449103, -0.789656),   cf_t(0.949275, 1.422961),   cf_t(0.717441, 0.006332),   cf_t(2.287829, 0.686481),  cf_t(0.166728, -0.854934), cf_t(-2.156491, -1.075235),  cf_t(1.689399, -0.090967),  cf_t(1.282281, -0.252772),  cf_t(-0.582631, 1.194824),   cf_t(0.222614, 0.606064), cf_t(0.779451, 0.540514)}, 4, 4), 8.7451, {{19, 1.494477},{17, -2.830749}, {1, -5.088718}, {0, -6.925003},}},
{srs_channel_matrix({cf_t(-0.967694, 0.036223),  cf_t(0.202051, -0.364631),  cf_t(-0.347878, 1.771020),   cf_t(1.290088, 0.221273),   cf_t(1.341154, 2.730378), cf_t(-0.580798, -0.296165),   cf_t(0.875136, 0.564296),   cf_t(1.395450, 1.582621),   cf_t(0.320985, 2.729230),   cf_t(1.623382, 0.303564),  cf_t(1.062433, -0.790258),   cf_t(0.214105, 0.803380),  cf_t(0.876803, -1.319903),  cf_t(0.194407, -0.273846),  cf_t(-0.414892, 0.271867), cf_t(0.358459, 1.489554)}, 4, 4), 0.91006, {{17, 13.281404}, {17, 8.476553},  {4, 4.225631},  {0, 1.656617},}},
{srs_channel_matrix({cf_t(-0.027561, -0.473237),   cf_t(0.923931, 2.184241),  cf_t(-0.321280, 0.809881),   cf_t(0.661125, 0.716343),  cf_t(1.915294, -1.005571),   cf_t(0.156760, 0.433987),  cf_t(-0.300536, 0.520144), cf_t(-0.500035, -1.092245),  cf_t(0.716471, -0.225794),  cf_t(1.337289, -0.404922),   cf_t(2.125680, 0.527859),  cf_t(0.054046, -1.006963),   cf_t(0.163036, 1.089027),  cf_t(-0.632707, 1.784875),  cf_t(1.611991, -0.303755), cf_t(-0.075449, -0.008697)}, 4, 4), 1.5814, {{12, 8.147412},{13, 5.225459}, {2, 2.002600}, {2, 0.145322},}},
{srs_channel_matrix({cf_t(1.203252, -0.364963),   cf_t(0.522018, 0.117271),   cf_t(0.397046, 0.174340), cf_t(-0.482811, -0.215656), cf_t(-0.231497, -0.152611),   cf_t(0.613385, 0.033688),   cf_t(1.682851, 0.458282),   cf_t(0.568394, 1.281631),  cf_t(-1.206029, 0.620090),  cf_t(0.433060, -0.286674),  cf_t(-0.092121, 0.598016), cf_t(-0.244055, -0.245533), cf_t(-0.219189, -1.780737), cf_t(-0.879767, -2.347239), cf_t(-0.320804, -1.713595), cf_t(-0.784415, -0.237127)}, 4, 4), 5.2039, {{26, 2.932870},{11, -1.400166}, {2, -4.287798}, {0, -5.979855},}},
{srs_channel_matrix({cf_t(-0.720160, 0.494233),   cf_t(0.040657, 0.991440),  cf_t(-0.658981, 1.077140),  cf_t(-0.630515, 0.776842),  cf_t(0.609625, -2.259840),  cf_t(0.782335, -0.564377),   cf_t(2.436584, 0.901491),   cf_t(0.302407, 0.394676),   cf_t(0.058320, 0.004854),  cf_t(-0.574134, 0.436919),  cf_t(-0.195212, 1.130073),  cf_t(-0.050531, 0.153771), cf_t(-1.755775, -0.758627), cf_t(-0.257358, -0.180163),  cf_t(0.749542, -0.207790), cf_t(-0.570764, 0.896745)}, 4, 4), 2.0757, {{21, 7.773821}, {7, 3.413658},{5, -1.082223},{2, -2.531567},}},
{srs_channel_matrix({cf_t(0.547520, -0.291910),   cf_t(0.147835, 0.458445),  cf_t(-0.362267, 1.755289),   cf_t(0.061141, 0.931491),   cf_t(0.216706, 0.825264), cf_t(-1.398122, -0.814807),  cf_t(0.178870, -0.534204),   cf_t(0.927584, 0.242552), cf_t(-0.110178, -0.100648),  cf_t(1.572398, -1.625048),  cf_t(0.560491, -1.514423),  cf_t(-0.420345, 1.026189), cf_t(-0.153945, -0.758127),  cf_t(-0.275199, 2.078345),  cf_t(0.241120, -2.221987), cf_t(0.754686, 0.448764)}, 4, 4), 3.0085, {{21, 6.119198},{11, 2.208475},{2, -0.886681},{0, -3.051977},}},
{srs_channel_matrix({cf_t(-0.756239, -0.363569),   cf_t(0.404325, 0.149556), cf_t(-0.793853, -1.944518),   cf_t(0.859783, 1.523895),   cf_t(0.066869, 0.545810),  cf_t(-1.639387, 2.009927),  cf_t(-2.424750, 1.416671),  cf_t(-0.283830, 0.011481),  cf_t(1.145806, -0.939049),  cf_t(0.181169, -1.738908),   cf_t(0.054250, 0.016971),   cf_t(0.687754, 0.219159),  cf_t(-1.393407, 1.045821),  cf_t(1.425366, -0.950983),  cf_t(-0.893851, 0.794797), cf_t(0.037765, 0.071430)}, 4, 4), 7.6688, {{16, 2.329630},{18, -1.891056}, {6, -3.833947}, {0, -5.730489},}},
    // clang-format on
};

} // namespace srsran
